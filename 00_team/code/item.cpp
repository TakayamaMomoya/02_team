//*****************************************************
//
// �A�C�e���̏���[item.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "playerManager.h"
#include "weapon.h"
#include "player.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CItem::CItem(int nPriority) : CObjectX(nPriority)
{
	m_type = TYPE_MAGNUM;
	m_pCollisionSphere = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CItem::~CItem()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CItem::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	// �ǂݍ���
	Load();

	if (m_pCollisionSphere == nullptr)
	{// �����蔻��̐���
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ITEM, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionSphere != nullptr)
		{
			m_pCollisionSphere->SetRadius(10.0f);
		}
	}

	return S_OK;
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CItem::Load(void)
{
	char* apPath[CItem::TYPE_MAX] =
	{
		"data\\MODEL\\weapon\\shotgun.x",
		"data\\MODEL\\weapon\\shotgun.x",
		"data\\MODEL\\weapon\\shotgun.x",
	};

	// ���f���̓Ǎ�
	int nIdx = CModel::Load(apPath[m_type]);
	SetIdxModel(nIdx);
	BindModel(nIdx);
}

//=====================================================
// �I������
//=====================================================
void CItem::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->Uninit();
		m_pCollisionSphere = nullptr;
	}

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CItem::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	if (m_pCollisionSphere != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		m_pCollisionSphere->SetPosition(pos);

		// �v���C���[�Ƃ̓����蔻��
		if (m_pCollisionSphere->SphereCollision(CCollision::TAG_PLAYER))
		{
			// ���������I�u�W�F�N�g�̎擾
			CObject *pObj = m_pCollisionSphere->GetOther();

			// �A�C�e�����菈��
			GetItem(pObj);
		}
	}
}

//=====================================================
// �A�C�e�����莞�̏���
//=====================================================
void CItem::GetItem(CObject *pObj)
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
				// ���ʂ̕t�^
				ApplyEffect(pPlayer);

				Uninit();
			}
		}
	}
}

//=====================================================
// ���ʂ�K�p���鏈��
//=====================================================
void CItem::ApplyEffect(CPlayer* pPlayer)
{
	if (pPlayer == nullptr)
	{
		return;
	}

	switch (m_type)
	{
	case CItem::TYPE_MAGNUM:

		pPlayer->SetWeapon(CWeapon::TYPE_MAGNUM);

		break;
	case CItem::TYPE_MACHINEGUN:
		break;
	case CItem::TYPE_RIFLE:
		break;
	default:
		break;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CItem::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// ��������
//=====================================================
CItem *CItem::Create(TYPE type)
{
	CItem *pItem = nullptr;

	if (pItem == nullptr)
	{
		pItem = new CItem;

		if (pItem != nullptr)
		{
			pItem->m_type = type;

			// ������
			pItem->Init();
		}
	}

	return pItem;
}