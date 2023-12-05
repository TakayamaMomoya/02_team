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
#include "rocket.h"
#include "sound.h"
#include "manager.h"
#include "fan3D.h"
#include "motionDiv.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CItemRepair::CItemRepair(int nPriority) : CGimmick(nPriority)
{
	m_pPlayer = nullptr;
	m_pGauge = nullptr;
	m_bInRocket = false;
	m_fCntRepair = 0.0f;
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
	CGimmick::Init();

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

	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	// �p���N���X�̏I��
	CGimmick::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CItemRepair::Update(void)
{
	bool bRelease = false;

	if (m_pPlayer != nullptr && m_bInRocket == false)
	{
		bRelease = m_pPlayer->InputInteract();

		if (bRelease)
		{// �����グ�Ă���v���C���[�̌��o
			// �����L��������
			m_pPlayer->EnableWeapon(true);
			
			// �v���C���[�̏C���A�C�e���|�C���^��������
			m_pPlayer->ReleaseItemRepair();

			m_pPlayer = nullptr;

			SetEnable(true);
		}
		else
		{

		}
	}
	
	if (bRelease == false)
	{
		// �p���N���X�̍X�V
		CGimmick::Update();
	}

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
	

	if (m_pPlayer == nullptr)
	{
		return;
	}

	CMotionDiv *pBody = m_pPlayer->GetBody();

	if (pBody != nullptr)
	{
		CParts *pParts = pBody->GetParts(CMotionDiv::DIV_BODY_UPPER, 6)->pParts;

		if (pParts != nullptr)
		{
			// �I�t�Z�b�g�̐ݒ�
			D3DXMATRIX *pMtx = GetMatrix();
			D3DXMATRIX *pMtxPart = pParts->GetMatrix();
			D3DXVECTOR3 offset = { -10.0f,0.0f,0.0f };

			universal::SetOffSet(pMtx, *pMtxPart, offset);

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
void CItemRepair::Interact(CObject *pObj)
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
				{// �����グ��
					m_pPlayer = pPlayer;

					// ����𖳌�������
					pPlayer->EnableWeapon(false);

					// �v���C���[�ɏC���A�C�e���̃|�C���^�ݒ�
					pPlayer->SetItemRepair(this);

					// �v���C���[�̏C���A�C�e�����͏��
					pPlayer->SetItemTrigger(true);

					SetEnable(false);
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
		m_bInRocket = pCollisionSphere->SphereCollision(CCollision::TAG_ROCKET);

		if (m_bInRocket)
		{
			//�@�T�E���h�C���X�^���X�̎擾
			CSound* pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_SE_REPAIR);
			}

			// ���P�b�g�C���^�C�}�[���Z
			CRocket *pRocket = CRocket::GetInstance();

			if (pRocket != nullptr && m_pPlayer != nullptr)
			{
				bool bInteract = m_pPlayer->InputInteractPress();

				if (bInteract)
				{
					float fTime = pRocket->GetTime();

					if (m_pGauge == nullptr)
					{// �Q�[�W�̐���
						D3DXVECTOR3 pos = GetPosition();

						pos.y += 150.0f;
						pos.x += 50.0f;

						m_pGauge = CFan3D::Create();
						m_pGauge->SetPosition(pos);
						m_pGauge->SetRadius(30.0f);
						m_pGauge->EnableBillboard(true);
						m_pGauge->EnableZtest(true);

						m_pGauge->SetVtx();
					}

					if (m_pGauge != nullptr)
					{// �Q�[�W�̊p�x�ݒ�
						float fRate = m_fCntRepair / fTime;
						m_pGauge->SetAngleMax(fRate);
						m_pGauge->SetVtx();
					}

					// �J�E���^�[�����Z
					float fTick = CManager::GetTick();

					m_fCntRepair += fTick;

					if (fTime <= m_fCntRepair)
					{
						// �����L��������
						m_pPlayer->EnableWeapon(true);

						// �v���C���[�̏C���A�C�e���|�C���^��������
						m_pPlayer->ReleaseItemRepair();

						// �C���i�s
						pRocket->AddProgress(1);

						Uninit();
					}
				}
				else
				{
					if (m_pGauge != nullptr)
					{// �Q�[�W�̔j��
						m_pGauge->Uninit();
						m_pGauge = nullptr;
					}
				}
			}
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
	CGimmick::Draw();
}