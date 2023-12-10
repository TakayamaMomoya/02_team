//*****************************************************
//
// �e����[Missile.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "missile.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int EDGE_ORBIT = 20;	// �O�Ղ̕ӂ̐�
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CMissile::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CMissile::CMissile(int nPriority) : CObject(nPriority)
{
	m_fLife = 0.0f;
	m_fDamage = 0.0f;
	m_move = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_pCollisionSphere = nullptr;

	// �����J�E���g�A�b�v
	m_nNumAll++;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMissile::~CMissile()
{
	m_nNumAll--;
}

//=====================================================
// ����������
//=====================================================
HRESULT CMissile::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMissile::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{// �����蔻��̏���
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMissile::Update(void)
{
	// �ϐ��錾
	bool bHit = false;

	// ��������
	float fTIck = CManager::GetTick();

	m_fLife -= fTIck;

	m_posOld = m_pos;

	// �ʒu�̍X�V
	m_pos += m_move;

	if (m_pCollisionSphere != nullptr)
	{// �����蔻��̊Ǘ�
		// �G�Ƃ̓����蔻��

		if (m_pCollisionSphere->TriggerCube(CCollision::TAG_BLOCK))
		{// �u���b�N�Ƃ̓����蔻��
			Death();
		}
	}

	if (bHit == false)
	{
		if (m_fLife < 0)
		{// �����̍폜
			Death();
		}
	}
	else
	{
		Death();
	}
}

//=====================================================
// ���S����
//=====================================================
void CMissile::Death(void)
{
	// �I������
	Uninit();
}

//=====================================================
// �`�揈��
//=====================================================
void CMissile::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//=====================================================
// ��������
//=====================================================
CMissile *CMissile::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move)
{
	CMissile *pMissile = nullptr;

	if (pMissile == nullptr)
	{// �C���X�^���X����
		pMissile = new CMissile;

		if (pMissile != nullptr)
		{
			pMissile->m_move = move;
			pMissile->m_pos = pos;
			pMissile->m_posOld = pos;

			if (pMissile->m_pCollisionSphere == nullptr)
			{// �����蔻�萶��
				pMissile->m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_PLAYERBULLET, CCollision::TYPE_SPHERE, pMissile);
			}

			if (pMissile->m_pCollisionSphere != nullptr)
			{
				pMissile->m_pCollisionSphere->SetPosition(pMissile->m_pos);

				pMissile->m_pCollisionSphere->SetRadius(20.0f);
			}

			// ����������
			pMissile->Init();
		}
	}

	return pMissile;
}