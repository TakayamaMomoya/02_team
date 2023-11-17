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

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const char* BODY_PATH = "data\\MODEL\\gimmick\\MysteryBox_Down.x";	// �{�̂̃p�X
	const char* CAP_PATH = "data\\MODEL\\gimmick\\MysteryBox_Up.x";	// �W�̃p�X
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
}

//=====================================================
// �A�C�e�����莞�̏���
//=====================================================
void CContainer::Interact(CObject *pObj)
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

	// ����������_���ɏo��������
	CUniversal *pUniversal = CUniversal::GetInstance();

	CWeapon::TYPE type = (CWeapon::TYPE)pUniversal->RandRange(CWeapon::TYPE::TYPE_MAX, 0);

	CItemWeapon *pWeapon = CItemWeapon::Create(type);

	if (pWeapon != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		pWeapon->SetPosition(pos);
	}
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