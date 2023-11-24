//*****************************************************
//
// �����蔻�菈��[collision.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "collision.h"
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "manager.h"
#include "debugproc.h"
#include "billboard.h"
#include "texture.h"
#include "effect3D.h"
#include "universal.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int NUM_EDGE = 4;	// �ӂ̐�
	const int NUM_WALL = 2;	// �ǂ̐�
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CCollision *CCollision::m_apCollision[NUM_OBJECT] = {};	// �����蔻��Ǘ��p�̔z��
int CCollision::m_nNumAll = 0;

//=====================================================
// �R���X�g���N�^
//=====================================================
CCollision::CCollision()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_tag = TAG_NONE;
	m_type = TYPE::TYPE_NONE;
	m_nID = -1;
	m_pObjectOwner = nullptr;
	m_pObjectOther = nullptr;

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apCollision[nCnt] == nullptr)
		{// �ۊǂ���
			m_apCollision[nCnt] = this;

			// ID�L��
			m_nID = nCnt;

			m_nNumAll++;

			break;
		}
	}
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCollision::~CCollision()
{
	m_nNumAll--;
}

//=====================================================
// ����������
//=====================================================
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCollision::Uninit(void)
{
	if (m_apCollision[m_nID] != nullptr)
	{
		m_apCollision[m_nID] = nullptr;
	}

	if (m_pObjectOwner != nullptr)
	{
		m_pObjectOwner = nullptr;
	}

	if (m_pObjectOther != nullptr)
	{
		m_pObjectOther = nullptr;
	}

	Release();
}

//=====================================================
// �폜����
//=====================================================
void CCollision::DeleteAll(void)
{
	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apCollision[nCnt] != nullptr)
		{// �폜����
			m_apCollision[nCnt]->Uninit();
		}
	}
}

//=====================================================
// �X�V����
//=====================================================
void CCollision::Update(void)
{

}

//=====================================================
// �L���[�u�Ƃ̃g���K�[����
//=====================================================
bool CCollision::TriggerCube(TAG tag)
{
	// �ϐ��錾
	bool bHitOld = false;
	bool bHit = false;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;

	// �����蔻��̎擾
	CCollision **ppCollision = GetCollision();

	pos = GetOwner()->GetPosition();
	posOld = GetOwner()->GetPositionOld();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE)
			{
				if (ppCollision[nCnt]->GetTag() != tag && tag != TAG_NONE)
				{
					continue;
				}

				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();

				if (pos.y > vtxMin.y && pos.y < vtxMax.y &&
					pos.x > vtxMin.x && pos.x < vtxMax.x &&
					pos.z > vtxMin.z && pos.z < vtxMax.z)
				{// ���݃u���b�N�̒��ɂ���
					if (posOld.y < vtxMin.y || posOld.y > vtxMax.y ||
						posOld.x < vtxMin.x || posOld.x > vtxMax.x ||
						posOld.z < vtxMin.z || posOld.z > vtxMax.z)
					{// �O��u���b�N�̒��ɂ��Ȃ�
						SetOther(ppCollision[nCnt]->GetOwner());

						bHit = true;
					}
				}
			}
		}
	}

	return bHit;
}

//=====================================================
// �L���[�u����_�Ԃɂ��邩����
//=====================================================
bool CCollision::ChckObstclBtwn(CObject *pObj, D3DXVECTOR3 vecDiff)
{
	D3DXVECTOR3 pos,posTarget;
	D3DXVECTOR3 vtxMax, vtxMin;
	D3DXVECTOR3 vtxMaxOwn, vtxMinOwn;
	D3DXVECTOR3 aVector[NUM_EDGE];
	int nIdx;
	float fRate;

	if (pObj == nullptr)
	{
		return false;
	}

	// �󂯎�����I�u�W�F�N�g�̈ʒu���擾
	pos = pObj->GetPosition();
	posTarget = pos + vecDiff;

	// �����蔻��̎擾
	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE && ppCollision[nCnt] != this)
			{
				if (ppCollision[nCnt]->GetTag() != TAG_BLOCK)
				{// �^�O�ɍ���Ȃ���ΌJ��Ԃ�
					continue;
				}

				// �ő�E�ŏ����_�̎擾
				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();
				vtxMaxOwn = GetVtxMax();
				vtxMinOwn = GetVtxMin();

				// �l�_�̈ʒu��ݒ�
				aVector[0] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
				aVector[1] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
				aVector[2] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
				aVector[3] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
				
				// �ǂ̃x�N�g���Ƀg���K�[���肪�������̂��m�F
				for (int nCntEdge = 0; nCntEdge < NUM_EDGE; nCntEdge++)
				{
					nIdx = (nCntEdge + 1) % NUM_EDGE;

					if (IsCross(pos, aVector[nCntEdge], aVector[nIdx], &fRate, vecDiff) &&
						IsCross(posTarget, aVector[nCntEdge], aVector[nIdx], &fRate, vecDiff) == false)
					{
						fRate *= 1;

						if (fRate < 1.0f && fRate > 0.0f)
						{// �������ӂɐڐG���Ă�����

							if (pos.y < vtxMax.y)
							{
								return true;
							}
						}
					}

				}
			}
		}
	}

	return false;
}

//=====================================================
// �O�ς̓����蔻��v�Z
//=====================================================
bool CCollision::IsCross(D3DXVECTOR3 posTarget, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest, float *pRate,D3DXVECTOR3 move)
{
	// �ėp�����擾
	CUniversal *pUniversal = CUniversal::GetInstance();

	bool bHit = false;

	// �ǂ̃x�N�g��
	D3DXVECTOR3 vecWall = vecDest - vecSorce;

	// �ǂƈړ��x�N�g���̊O�ς��v�Z
	float fArea = pUniversal->CrossProduct(vecWall, move);

	CDebugProc::GetInstance()->Print("fArea�F[%f]\n", fArea);
	//CDebugProc::GetInstance()->Print("move�F[%f,%f,%f]\n", &fArea);

	if (fArea > 0.0f)
	{// �����̍��ɂ��锻��
		if (pRate != nullptr)
		{// ������ɂ��邩�̃`�F�b�N
			D3DXVECTOR3 vecToPos = posTarget - vecSorce;

			float fArea2 = pUniversal->CrossProduct(vecToPos, move);

			*pRate = fArea2 / fArea;

			if (*pRate <= 1.0f && *pRate >= 0.0f)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}

//=====================================================
// �O�ς̃g���K�[����v�Z
//=====================================================
bool CCollision::IsCrossTrigger(D3DXVECTOR3 posTarget, D3DXVECTOR3 posTargetOld, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest)
{
	bool bHit = false;

	D3DXVECTOR3 vecLine = vecDest - vecSorce;

	D3DXVECTOR3 vecToPos = posTarget - vecSorce;
	D3DXVECTOR3 vecToPosOld = posTargetOld - vecSorce;

	if (vecLine.z * vecToPos.x - vecLine.x * vecToPos.z >= 0 &&
		vecLine.z * vecToPosOld.x - vecLine.x * vecToPosOld.z < 0)
	{
		bHit = true;
	}

	return bHit;
}

//=====================================================
// �ʒu�ݒ�
//=====================================================
void CCollision::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
// ��������
//=====================================================
CCollision *CCollision::Create(TAG tag, TYPE type, CObject *obj)
{
	CCollision *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// �C���X�^���X����
		switch (type)
		{
		case TYPE_SPHERE:
			pCollision = new CCollisionSphere;
			break;
		default:
			break;
		}

		if (pCollision != nullptr)
		{
			// ����������
			pCollision->Init();

			// �^�O�󂯎��
			pCollision->m_tag = tag;

			// ������̃|�C���^
			pCollision->m_pObjectOwner = obj;
		}
	}

	return pCollision;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CCollisionSphere::CCollisionSphere()
{
	m_fRadius = 0.0f;

	SetType(TYPE_SPHERE);

	m_pBillboard = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCollisionSphere::~CCollisionSphere()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CCollisionSphere::Init(void)
{
	if (m_pBillboard == nullptr)
	{// �r���{�[�h�̐���
		m_pBillboard = CBillboard::Create(GetPosition(),m_fRadius,m_fRadius);

		if (m_pBillboard != nullptr)
		{
			int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\EFFECT\\collision.png");
			m_pBillboard->SetIdxTexture(nIdx);
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCollisionSphere::Uninit(void)
{
	if (m_pBillboard != nullptr)
	{// �r���{�[�h�̍폜
		m_pBillboard->Uninit();
		m_pBillboard = nullptr;
	}

	CCollision::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CCollisionSphere::Update(void)
{
	if (m_pBillboard != nullptr)
	{// �r���{�[�h�̒Ǐ]
		D3DXVECTOR3 pos = GetPosition();

		m_pBillboard->SetPosition(pos);

		m_pBillboard->SetSize(m_fRadius, m_fRadius);
	}
}

//=====================================================
// ���̓����蔻��
//=====================================================
bool CCollisionSphere::SphereCollision(TAG tag)
{
	bool bHit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// �����擾
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				float fLength = D3DXVec3Length(&vecDiff);

				if (fLength < ppCollision[nCnt]->GetRadius() + GetRadius())
				{
					// �Ԃ���������̎�����𔻕�
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bHit;
}

//=====================================================
// ����ʂ蔲��������
//=====================================================
bool CCollisionSphere::IsTriggerExit(TAG tag)
{
	bool bExit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// �����擾
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				// �����̒���
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// �O��̈ʒu�Ƃ̍���
				vecDiff = ppCollision[nCnt]->GetOwner()->GetPositionOld() - GetPositionOld();

				float fLengthOld = D3DXVec3Length(&vecDiff);

				// �Ԃ��鎞�̋���
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff >= fLength && fLengthOld < fLength)
				{
					// �Ԃ���������̎�����𔻕�
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bExit;
}

//=====================================================
// �����Ԃ������u�Ԃ̔���
//=====================================================
bool CCollisionSphere::IsTriggerEnter(TAG tag)
{
	bool bExit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// �����擾
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				// �����̒���
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// �O��̈ʒu�Ƃ̍���
				vecDiff = ppCollision[nCnt]->GetOwner()->GetPositionOld() - GetPositionOld();

				float fLengthOld = D3DXVec3Length(&vecDiff);

				// �Ԃ��鎞�̋���
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff <= fLength && fLengthOld > fLength)
				{
					// �Ԃ���������̎�����𔻕�
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bExit;
}

//=====================================================
// ���̉����o���̔���
//=====================================================
void CCollisionSphere::PushCollision(D3DXVECTOR3* pPos, TAG tag)
{

	CCollision** ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag || ppCollision[nCnt] == this)
				{
					continue;
				}

				D3DXVECTOR3 pos = { pPos->x,0.0f,pPos->z };
				D3DXVECTOR3 posTarget = { ppCollision[nCnt]->GetPosition().x,0.0f, ppCollision[nCnt]->GetPosition().z };

				// �����擾
				D3DXVECTOR3 vecDiff = posTarget - pos;

				// �����̒���
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// �Ԃ��鎞�̋���
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff < fLength)
				{
					D3DXVECTOR3 posAfter;	// �����o����̍��W

					// �����x�N�g�����牟���o����̈ʒu���v�Z
					D3DXVec3Normalize(&posAfter,&vecDiff);

					posAfter *= -fLength;

					posAfter += posTarget;

					*pPos = posAfter;
				}
			}
		}
	}
}

//=====================================================
// ��������
//=====================================================
CCollisionSphere *CCollisionSphere::Create(TAG tag, TYPE type, CObject *obj)
{
	CCollisionSphere *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// �C���X�^���X����
		pCollision = new CCollisionSphere;

		if (pCollision != nullptr)
		{
			// ����������
			pCollision->Init();

			// �^�O�󂯎��
			pCollision->SetTag(tag);

			// ������̃|�C���^
			pCollision->SetOwner(obj);
		}
	}

	return pCollision;
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CCollisionCube::CCollisionCube()
{
	m_vtxMax = { 0.0f,0.0f,0.0f };
	m_vtxMin = { 0.0f,0.0f,0.0f };

	SetType(TYPE_CUBE);
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCollisionCube::~CCollisionCube()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CCollisionCube::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCollisionCube::Uninit(void)
{
	CCollision::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CCollisionCube::Update(void)
{

}

//=====================================================
// �����̂̓����蔻��
//=====================================================
bool CCollisionCube::CubeCollision(TAG tag, D3DXVECTOR3 *pMove, CObject **ppObjOther)
{
	// �ėp�����̎擾
	CUniversal *pUniversal = CUniversal::GetInstance();

	bool bLand = false;
	CCollision **ppCollision = GetCollision();
	SWall *apWall[NUM_WALL] = {};
	int nNumWall = 0;

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{// ���������ǂ̌��o
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE)
			{
				if (ppCollision[nCnt]->GetTag() != tag && tag != TAG_NONE)
				{// �^�O�ɍ���Ȃ���ΌJ��Ԃ�
					continue;
				}

				// ���g�̈ʒu���擾
				D3DXVECTOR3 posOld = GetOwner()->GetPositionOld();

				// ����̈ʒu�ƍő�E�ŏ����_���擾
				D3DXVECTOR3 posTarget = ppCollision[nCnt]->GetPosition();
				D3DXVECTOR3 vtxMax = ppCollision[nCnt]->GetVtxMax();
				D3DXVECTOR3 vtxMin = ppCollision[nCnt]->GetVtxMin();

				// �S���_�̐ݒ�
				D3DXVECTOR3 aVector[NUM_EDGE];

				aVector[0] = D3DXVECTOR3(vtxMin.x, 0.0f, vtxMin.z);
				aVector[1] = D3DXVECTOR3(vtxMin.x, 0.0f, vtxMax.z);
				aVector[2] = D3DXVECTOR3(vtxMax.x, 0.0f, vtxMax.z);
				aVector[3] = D3DXVECTOR3(vtxMax.x, 0.0f, vtxMin.z);

				// �ǂ̃x�N�g���Ƀg���K�[���肪�������̂��m�F
				for (int nCntEdge = 0; nCntEdge < NUM_EDGE; nCntEdge++)
				{
					D3DXVECTOR3 posCross;	// ��_�̕ۑ��p

					// ��ڂ̒��_�̔ԍ�
					int nIdx = (nCntEdge + 1) % NUM_EDGE;

					D3DXVECTOR3 posTemp = GetPosition();

					// �O�ς̉����o������
					bool bHit = CrossProduct(posOld, &posTemp, aVector[nIdx] + posTarget, aVector[nCntEdge] + posTarget, 0.0f,nullptr,&posCross);

					if (bHit)
					{
						if (apWall[nNumWall] == nullptr)
						{// �Ǐ��̕ۑ�
							apWall[nNumWall] = new SWall;

							if (apWall[nNumWall] != nullptr)
							{
								apWall[nNumWall]->posStart = aVector[nIdx] + posTarget;
								apWall[nNumWall]->posEnd = aVector[nCntEdge] + posTarget;
								apWall[nNumWall]->posCross = posCross;

								nNumWall++;
							}
						}
					}
				}
			}
		}
	}

	// ���g�̈ʒu���擾
	D3DXVECTOR3 pos = GetOwner()->GetPosition();
	D3DXVECTOR3 posOld = GetOwner()->GetPositionOld();

	//if (nNumWall > 1)
	//{// �����ǂ��������ꍇ�A�\�[�g����
	//	// �ړ��p�x�̎擾
	//	D3DXVECTOR3 vecMove = pos - posOld;

	//	float fRotMove = atan2f(vecMove.x, vecMove.z);

	//	// �P�ڂ̊p�x�̍������͂���
	//	D3DXVECTOR3 vecWall1 = apWall[0]->posEnd - apWall[0]->posStart;
	//	float fRot1 = atan2f(vecWall1.x, vecWall1.z);

	//	float fRotDiff1 = fRotMove - fRot1;

	//	pUniversal->LimitRot(&fRotDiff1);

	//	// �Q�ڂ̊p�x�̍������͂���
	//	D3DXVECTOR3 vecWall2 = apWall[1]->posEnd - apWall[1]->posStart;
	//	float fRot2 = atan2f(vecWall2.x, vecWall2.z);

	//	float fRotDiff2 = fRotMove - fRot2;

	//	pUniversal->LimitRot(&fRotDiff2);

	//	if (fRot2 * fRot2 < fRot1 * fRot1)
	//	{// �Ǐ������ւ���
	//		SWall *pWallTemp = nullptr;

	//		pWallTemp = apWall[0];

	//		apWall[1] = apWall[0];

	//		apWall[0] = pWallTemp;
	//	}
	//}

	for (int i = 0; i < NUM_WALL; i++)
	{// ���������ǂƂ̓����蔻��
		if (apWall[i] != nullptr)
		{
			// �O�ς̉����o������
			CrossProduct(posOld, &pos, apWall[i]->posStart, apWall[i]->posEnd, 0.0f, nullptr, nullptr);
		}
	}

	GetOwner()->SetPosition(pos);

	for (int i = 0; i < NUM_WALL; i++)
	{// �Ǐ��̔j��
		if (apWall[i] != nullptr)
		{// ���̔j��
			delete apWall[i];
			apWall[i] = nullptr;
		}
	}
	
	return bLand;
}

//=====================================================
// ���_�ݒ�
//=====================================================
void CCollisionCube::SetVtx(D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	m_vtxMax = vtxMax;
	m_vtxMin = vtxMin;

	m_aVtx[VTX_LD] = { vtxMin.x,0.0f,0.0f };
	m_aVtx[VTX_LU] = { 0.0f,0.0f,0.0f };
	m_aVtx[VTX_RU] = { 0.0f,0.0f,0.0f };
	m_aVtx[VTX_RD] = { 0.0f,0.0f,0.0f };
}

//=====================================================
// ���������x�N�g���̎擾
//=====================================================
D3DXVECTOR3 CCollisionCube::CollisionVector(CObject *pObj)
{
	D3DXVECTOR3 vecDest = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vecDiff;
	D3DXVECTOR3 pos, posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 vecToPos;
	D3DXVECTOR3 vtxMax, vtxMin;
	D3DXVECTOR3 vtxMaxOwn, vtxMinOwn;
	D3DXVECTOR3 aVector[NUM_EDGE];
	int nIdx;
	float fLengthSorce;
	float fLengthDest;

	if (pObj == nullptr)
	{
		return vecDest;
	}

	// �󂯎�����I�u�W�F�N�g�̈ʒu���擾
	pos = pObj->GetPosition();
	posOld = pObj->GetPositionOld();

	move = pos - posOld;

	// �����蔻��̎擾
	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE && ppCollision[nCnt] != this)
			{
				if (ppCollision[nCnt]->GetTag() != TAG_BLOCK)
				{// �^�O�ɍ���Ȃ���ΌJ��Ԃ�
					continue;
				}

				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();
				vtxMaxOwn = GetVtxMax();
				vtxMinOwn = GetVtxMin();

				if (pos.z >= vtxMin.z - vtxMaxOwn.z &&
					pos.z <= vtxMax.z - vtxMinOwn.z &&
					pos.x >= vtxMin.x - vtxMaxOwn.x &&
					pos.x <= vtxMax.x - vtxMinOwn.x &&
					pos.y >= vtxMin.y - vtxMaxOwn.y &&
					pos.y <= vtxMax.y - vtxMinOwn.y)
				{// ���݃u���b�N�̒��ɂ���
					aVector[0] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
					aVector[1] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
					aVector[2] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
					aVector[3] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);

					// �ǂ̃x�N�g���Ƀg���K�[���肪�������̂��m�F
					for (int nCntEdge = 0; nCntEdge < NUM_EDGE; nCntEdge++)
					{
						nIdx = (nCntEdge + 1) % NUM_EDGE;

						if (IsCrossTrigger(pos, posOld, aVector[nCntEdge], aVector[nIdx]))
						{
							vecDest = aVector[nIdx] - aVector[nCntEdge];

							vecToPos = pos - aVector[nIdx];

							// �������Z�o
							float fAreaMax = (vecDest.z * move.x) - (vecDest.x * move.z);
							float fArea = (vecToPos.z * move.x) - (vecToPos.x * move.z);
							float fRate = fArea / fAreaMax;

							fLengthDest = D3DXVec3Length(&aVector[nIdx]);
							fLengthSorce = D3DXVec3Length(&aVector[nCntEdge]);

							// �ŒZ�����ɂ���ĖڕW�x�N�g�����]
							if (fLengthSorce < fLengthDest)
							{
								vecDest *= -1.0f - fRate;
							}
							else
							{
								vecDest *= -fRate;
							}
						}
					}
				}
			}
		}
	}

	return vecDest;
}

//=====================================================
// ��������
//=====================================================
CCollisionCube *CCollisionCube::Create(TAG tag, CObject *obj)
{
	CCollisionCube *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// �C���X�^���X����
		pCollision = new CCollisionCube;

		if (pCollision != nullptr)
		{
			// ����������
			pCollision->Init();

			// �^�O�󂯎��
			pCollision->SetTag(tag);

			// ������̃|�C���^
			pCollision->SetOwner(obj);
		}
	}

	return pCollision;
}

//=====================================================
// �O�ςɂ��ǂ̉����o������
//=====================================================
bool CCollisionCube::CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 vtxStart, D3DXVECTOR3 vtxEnd, float width, SWall *pWall, D3DXVECTOR3 *pPosCross)
{
	bool bHit = false;

	// �ėp�����擾
	CUniversal *pUniversal = CUniversal::GetInstance();

	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//��UY���W�͕���
		vtxEnd.x - vtxStart.x,
		0.0f,
		vtxEnd.z - vtxStart.z
	);

	//��ڂ̒��_���猻�݈ʒu�܂ł̃x�N�g��
	D3DXVECTOR3 vecToPos = D3DXVECTOR3
	(
		pos->x - vtxStart.x,
		0.0f,
		pos->z - vtxStart.z
	);

	//�ړ��ʃx�N�g��
	D3DXVECTOR3 vecMove = D3DXVECTOR3
	(
		pos->x - posOld.x,
		0.0f,
		pos->z - posOld.z
	);

	D3DXVECTOR3 vecToPosOld = D3DXVECTOR3
	(// �O��̈ʒu�ւ̃x�N�g��
		posOld.x - vtxStart.x,
		0.0f,
		posOld.z - vtxStart.z
	);

	// �ǂ̌������擾
	float fAngle = atan2f(vecLine.x, vecLine.z);

	// �e�O�ς��擾
	float fAreaMax = pUniversal->CrossProduct(vecLine, vecMove);
	float fArea = pUniversal->CrossProduct(vecLine, vecToPos);
	float fArea2 = pUniversal->CrossProduct(vecToPos, vecMove);
	float fAreaOld = pUniversal->CrossProduct(vecLine, vecToPosOld);
	float fRate = fArea2 / fAreaMax;

	if (fAreaMax == 0)
	{
		return bHit;
	}

	if ((fRate > 0.0f) && (fRate < 1.0f))
	{
		if (fArea <= 0.0f && fAreaOld >= 0.0f)
		{// �����̍��ɂ���A�O�񂪂߂荞��ł��Ȃ�
			CDebugProc::GetInstance()->Print("\nfRate[%f]", fRate);

			// �ǂ̒������v�Z
			float fLength = sqrtf(vecLine.x * vecLine.x + vecLine.z * vecLine.z) * fRate;

			D3DXVECTOR3 posCross =
			{// ��_
				vtxStart.x + sinf(fAngle) * fLength,
				pos->y,
				vtxStart.z + cosf(fAngle) * fLength
			};

			if (pPosCross != nullptr)
			{
				*pPosCross = posCross;
			}

			// �͂ݏo�鍷���x�N�g�����擾�A�������v�Z
			D3DXVECTOR3 diffMove;

			diffMove = *pos - posCross;

			// ��_�Ɉʒu��ݒ�
			*pos = posCross;

			// ��_�ɃG�t�F�N�g���o��
			CEffect3D::Create(posCross, 10.0f, 60, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// �ړ��̊p�x�擾
			float fAngleMove = atan2f(vecMove.x, vecMove.z);
			float fAngleMid = fAngle + D3DX_PI * 0.5f;

			// ���p�x���C��
			if (fAngleMid > D3DX_PI)
			{
				fAngleMid -= 6.28f;
			}
			if (fAngleMid < -D3DX_PI)
			{
				fAngleMid += 6.28f;
			}

			// �����̊p�x���擾
			float fAngleDiff = fAngleMove - fAngleMid;

			// �����p�x���C��
			if (fAngleDiff > D3DX_PI)
			{
				fAngleDiff -= 6.28f;
			}
			if (fAngleDiff < -D3DX_PI)
			{
				fAngleDiff += 6.28f;
			}

			// �͂ݏo�����̒������擾
			float fLengthProtrude = D3DXVec3Length(&diffMove);

			// �ǂ̃x�N�g������
			if (fAngleDiff <= 0.0f)
			{// �����p�x���v���X�̏ꍇ
				diffMove = vecLine;
			}
			else
			{// �����p�x���}�C�i�X�̏ꍇ
				diffMove = -vecLine;
			}

			// �������̃x�N�g���𐳋K�����āA�ړ��ʂ̒����ɂ���
			D3DXVec3Normalize(&diffMove, &diffMove);
			diffMove *= fLengthProtrude;

			// ����镪�̈ʒu�𑫂�
			*pos += diffMove;

			bHit = true;
		}
	}

	return bHit;
}