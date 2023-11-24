//*****************************************
//
//���낢��ėp�����l�ߍ���
//Author:���R����
//
//*****************************************

//*****************************************
//�C���N���[�h
//*****************************************
#include "manager.h"
#include "renderer.h"
#include "universal.h"
#include <stdio.h>

//*****************************************
// �ÓI�����o�ϐ��錾
//*****************************************
CUniversal *CUniversal::m_pUniversal = nullptr;	// ���g�̃|�C���^

//=========================================
// �R���X�g���N�^
//=========================================
CUniversal::CUniversal()
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CUniversal::~CUniversal()
{

}

//=========================================
// ��������
//=========================================
CUniversal *CUniversal::Create(void)
{
	if (m_pUniversal == nullptr)
	{
		m_pUniversal = new CUniversal;
	}

	return m_pUniversal;
}

//=========================================
// �I������
//=========================================
void CUniversal::Uninit(void)
{
	delete this;
}

//=========================================
//��]���䏈��
//=========================================
void CUniversal::LimitRot(float *fRot)
{
	if (*fRot > D3DX_PI)
	{
		*fRot -= 6.28f;
	}
	if (*fRot < -D3DX_PI)
	{
		*fRot += 6.28f;
	}
}

//========================================
//�I�t�Z�b�g�ݒ菈��
//========================================
void CUniversal::SetOffSet(D3DXMATRIX *pMtxWorldOffset, D3DXMATRIX mtxWorldOwner, D3DXVECTOR3 posOffset, D3DXVECTOR3 rot)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtxWorldOffset);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, posOffset.x, posOffset.y, posOffset.z);
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxTrans);

	//�}�g���b�N�X���������킹��
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxWorldOwner);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, pMtxWorldOffset);
}

//========================================
// �����␳����
//========================================
void CUniversal::FactingRot(float *pfRot, float fRotDest, float rotateFact)
{
	// �����̊p�x�̕␳
	LimitRot(pfRot);
	LimitRot(&fRotDest);

	//�����p�x���擾
	float fRotDiff = fRotDest - *pfRot;

	//�p�x�̏C��
	LimitRot(&fRotDiff);

	//�p�x�␳
	*pfRot += fRotDiff * rotateFact;

	LimitRot(pfRot);
}

//========================================
// �����̔�r
//========================================
bool CUniversal::DistCmp(D3DXVECTOR3 posOwn, D3DXVECTOR3 posTarget, float fLengthMax, float *fDiff)
{
	D3DXVECTOR3 vecDiff = posTarget - posOwn;
	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength < fLengthMax)
	{
		if (fDiff != nullptr)
		{
			*fDiff = fLength;
		}

		return true;
	}
	else
	{
		return false;
	}
}

//========================================
// �O�ς̌v�Z
//========================================
float CUniversal::CrossProduct(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	return pos1.z * pos2.x - pos1.x * pos2.z;
}

//========================================
// �͈͓��̃����_�����l��Ԃ�����
//========================================
int CUniversal::RandRange(int nMax, int nMin)
{
	int nRange = nMax - nMin;
	int nRand = rand() % nRange + nMin;

	return nRand;
}