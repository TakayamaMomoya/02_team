//*****************************************************
//
// �R���e�i�[�̏���[container.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "Container.h"
#include "manager.h"
#include "renderer.h"
#include "playerManager.h"
#include "weapon.h"
#include "player.h"
#include "universal.h"
#include "itemWeapon.h"
#include "weaponManager.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const char* BODY_PATH = "data\\MODEL\\gimmick\\MysteryBox_Down.x";	// �{�̂̃p�X
	const char* CAP_PATH = "data\\MODEL\\gimmick\\MysteryBox_Up.x";	// �W�̃p�X
	const float TIME_DEATH = 1.5f;	// ���S�܂ł̎���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CContainer::CContainer(int nPriority) : CItem(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CContainer::~CContainer()
{

}

//=====================================================
// ��������
//=====================================================
CContainer *CContainer::Create(void)
{
	CContainer *pContainer = nullptr;

	if (pContainer == nullptr)
	{
		pContainer = new CContainer;

		if (pContainer != nullptr)
		{
			// ������
			pContainer->Init();
		}
	}

	return pContainer;
}

//=====================================================
// ����������
//=====================================================
HRESULT CContainer::Init(void)
{
	// �p���N���X�̏�����
	CItem::Init();

	// �ǂݍ���
	Load();

	m_info.state = STATE_NORMAL;
	m_info.fTimerDeath = TIME_DEATH;

	return S_OK;
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CContainer::Load(void)
{
	// �{�̂̓Ǎ�
	int nIdx = CModel::Load((char*)BODY_PATH);
	SetIdxModel(nIdx);
	BindModel(nIdx);

	if (m_info.pCap == nullptr)
	{// �W�̐���
		m_info.pCap = CObjectX::Create();

		if (m_info.pCap != nullptr)
		{
			// �W�̓ǂݍ���
			int nIdx = CModel::Load((char*)CAP_PATH);
			m_info.pCap->SetIdxModel(nIdx);
			m_info.pCap->BindModel(nIdx);
		}
	}
}

//=====================================================
// �I������
//=====================================================
void CContainer::Uninit(void)
{
	if (m_info.pCap != nullptr)
	{
		m_info.pCap->Uninit();
		m_info.pCap = nullptr;
	}

	// �p���N���X�̏I��
	CItem::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CContainer::Update(void)
{
	// �p���N���X�̍X�V
	CItem::Update();

	if (m_info.state == STATE_OPEN)
	{// �J���Ă����Ԃ̍X�V
		UpdateOpen();
	}
}

//=====================================================
// �J���Ă����Ԃ̍X�V
//=====================================================
void CContainer::UpdateOpen(void)
{
	float fTick = CManager::GetTick();

	m_info.fTimerDeath -= fTick;

	if (m_info.fTimerDeath <= 0.0f)
	{
		m_info.fTimerDeath = 0.0f;

		Uninit();
	}
}

//=====================================================
// �A�C�e�����莞�̏���
//=====================================================
void CContainer::Interact(CObject *pObj)
{
	if (m_info.state != STATE_NORMAL)
	{
		return;
	}

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
			{// �v���C���[�̃C���^���N�g���o
				bool bGet = pPlayer->InputInteract();

				if (bGet)
				{// �����J��
					Open();
				}
			}
		}
	}
}

//=====================================================
// �����J������
//=====================================================
void CContainer::Open(void)
{
	// �����J�����
	m_info.state = STATE_OPEN;

	// ����̎�ނ������_���Őݒ�
	CUniversal *pUniversal = CUniversal::GetInstance();

	CWeapon::TYPE type = (CWeapon::TYPE)WeaponRand();

	// ����̐ݒu
	CItemWeapon *pWeapon = CItemWeapon::Create(type);

	if (pWeapon != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		pWeapon->SetPosition(pos);
	}

	m_info.state = STATE_OPEN;
}

//=====================================================
// ����̃����_���Őݒ肷�鏈��
//=====================================================
int CContainer::WeaponRand(void)
{
	int anProb[CWeapon::TYPE::TYPE_MAX];	// �m���̕ۑ��p
	int nMinProb = INT_MAX;
	int nMax = 0;

	ZeroMemory(&anProb[0], sizeof(int) * CWeapon::TYPE::TYPE_MAX);

	// ����}�l�[�W���[����e����̊m�����擾�A�ő�l�̐ݒ�
	CWeaponManager *pWeaponManager = CWeaponManager::GetInstance();

	if (pWeaponManager != nullptr)
	{
		for (int i = 0; i < CWeapon::TYPE::TYPE_MAX; i++)
		{
			anProb[i] = pWeaponManager->GetProb(i);

			if (anProb[i] > nMax)
			{
				nMax = anProb[i];
			}
		}
	}

	// �����̐ݒ�
	CUniversal *pUniversal = CUniversal::GetInstance();
	int nProb = pUniversal->RandRange(nMax,1);	// ���Ғl�̍��v���ő�l�Ƃ��ė�����U��
	int nIdxWeapon = -1;

	for (int i = 0; i < CWeapon::TYPE::TYPE_MAX; i++)
	{
		if (nProb <= anProb[i])
		{// �m�����̂Ƃ�
			if (anProb[i] < nMinProb)
			{// ���̓��������m�����Ⴂ�ꍇ�̂ݓK�p
				nIdxWeapon = i;
				nMinProb = anProb[i];
			}
		}
	}

	if (nIdxWeapon == -1)
	{
		assert(("����̐ݒ�Ɏ��s", false));
	}

	return nIdxWeapon;
}

//=====================================================
// �ʒu�̐ݒ�
//=====================================================
void CContainer::SetPosition(D3DXVECTOR3 pos)
{
	// �p���N���X�̐ݒu
	CObjectX::SetPosition(pos);

	if (m_info.pCap != nullptr)
	{// �W�̒Ǐ]
		D3DXVECTOR3 pos = GetPosition();

		m_info.pCap->SetPosition(pos);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CContainer::Draw(void)
{
	// �p���N���X�̕`��
	CItem::Draw();
}