//*****************************************************
//
// �C���A�C�e���̏���[ItemRepair.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "ItemRepair.h"
#include "playerManager.h"
#include "player.h"
#include "universal.h"
#include "parts.h"
#include "motion.h"
#include "collision.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CItemRepair::CItemRepair(int nPriority) : CItem(nPriority)
{
	m_pPlayer = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CItemRepair::~CItemRepair()
{

}

//=====================================================
// ��������
//=====================================================
CItemRepair *CItemRepair::Create(void)
{
	CItemRepair *pItemRepair = nullptr;

	if (pItemRepair == nullptr)
	{
		pItemRepair = new CItemRepair;

		if (pItemRepair != nullptr)
		{
			// ������
			pItemRepair->Init();
		}
	}

	return pItemRepair;
}

//=====================================================
// ����������
//=====================================================
HRESULT CItemRepair::Init(void)
{
	// �p���N���X�̏�����
	CItem::Init();

	// �ǂݍ���
	Load();

	return S_OK;
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CItemRepair::Load(void)
{
	// ���f���̓Ǎ�
	int nIdx = CModel::Load("data\\MODEL\\item\\repairKit.x");
	SetIdxModel(nIdx);
	BindModel(nIdx);
}

//=====================================================
// �I������
//=====================================================
void CItemRepair::Uninit(void)
{
	m_pPlayer = nullptr;

	// �p���N���X�̏I��
	CItem::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CItemRepair::Update(void)
{
	if (m_pPlayer != nullptr)
	{
		bool bGet = m_pPlayer->InputInteract();

		if (bGet)
		{// �����グ�Ă���v���C���[�̌��o
			m_pPlayer = nullptr;
		}
	}

	// �p���N���X�̍X�V
	CItem::Update();

	// �v���C���[�̐����m�F
	CheckPlayerAlive();

	if (m_pPlayer == nullptr)
	{// �����グ�Ă��Ȃ����
		// �ړ��ʔ��f
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 move = GetMove();

		// �d�͂̔��f
		move.y -= 0.98f;

		pos += move;

		// ���Ƃ̔���
		if (pos.y <= 0.0f)
		{
			pos.y = 0.0f;
			move.y = 0.0f;
		}

		SetPosition(pos);
	}
	else
	{// �����グ���Ă���ꍇ
		FollowPlayerHand();
	}

	// ���P�b�g�Ƃ̓����蔻��
	CollisionRocket();
}

//=====================================================
// �v���C���[�̎��Ǐ]
//=====================================================
void CItemRepair::FollowPlayerHand(void)
{
	CUniversal *pUniversal = CUniversal::GetInstance();

	if (m_pPlayer == nullptr)
	{
		return;
	}

	CMotion *pBody = m_pPlayer->GetBody();

	if (pBody != nullptr)
	{
		CParts *pParts = pBody->GetParts(5)->pParts;

		if (pParts != nullptr)
		{
			// �I�t�Z�b�g�̐ݒ�
			D3DXMATRIX *pMtx = GetMatrix();
			D3DXMATRIX *pMtxPart = pParts->GetMatrix();
			D3DXVECTOR3 offset = { -15.0f,0.0f,0.0f };

			pUniversal->SetOffSet(pMtx, *pMtxPart, offset);

			// ��ɒǏ]����
			D3DXVECTOR3 posHand =
			{
				pMtx->_41,
				pMtx->_42,
				pMtx->_43,
			};
			D3DXVECTOR3 rot = m_pPlayer->GetRot();

			SetPosition(posHand);
			SetRot(rot);
		}
	}
}

//=====================================================
// �A�C�e�����莞�̏���
//=====================================================
void CItemRepair::GetItem(CObject *pObj)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pObj == nullptr || pPlayerManager == nullptr)
	{
		return;
	}

	// �v���C���[�擾
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

		if (pPlayer != nullptr)
		{
			if ((CObject*)pPlayer == pObj)
			{// �v���C���[���o
				bool bGet = pPlayer->InputInteract();

				if (bGet)
				{// �����グ�Ă���v���C���[�̌��o
					m_pPlayer = pPlayer;
				}
			}
		}
	}
}

//=====================================================
// ���P�b�g�Ƃ̓����蔻��
//=====================================================
void CItemRepair::CollisionRocket(void)
{
	CCollisionSphere *pCollisionSphere = GetCollisionSphere();

	if (pCollisionSphere != nullptr)
	{
		bool bHit = pCollisionSphere->SphereCollision(CCollision::TAG_ROCKET);

		if (bHit)
		{
			Uninit();
		}
	}
}

//=====================================================
// ������̃v���C���[���������Ă��邩�̊m�F
//=====================================================
void CItemRepair::CheckPlayerAlive(void)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pPlayerManager == nullptr || m_pPlayer == nullptr)
	{
		return;
	}

	bool bAlive = false;

	// �v���C���[�擾
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

		if (pPlayer != nullptr)
		{
			if (pPlayer == m_pPlayer)
			{// �v���C���[���o
				bAlive = true;
			}
		}
	}

	if (bAlive == false)
	{// �v���C���[�����o�ł��Ȃ������ꍇ�A���ɗ�����
		m_pPlayer = nullptr;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CItemRepair::Draw(void)
{
	// �p���N���X�̕`��
	CItem::Draw();
}