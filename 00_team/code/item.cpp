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
#include "billboard.h"
#include "texture.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define SIZE_INTERACT	(20.0f)	// �C���^���N�g�\���̃T�C�Y

//=====================================================
// �R���X�g���N�^
//=====================================================
CItem::CItem(int nPriority) : CObjectX(nPriority)
{
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
// �I������
//=====================================================
void CItem::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->Uninit();
		m_pCollisionSphere = nullptr;
	}

	if (m_pInteract != nullptr)
	{
		m_pInteract->Uninit();
		m_pInteract = nullptr;
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
			if (m_pInteract == nullptr)
			{// �C���^���N�g�\������
				D3DXVECTOR3 pos = GetPosition();

				pos.y += 50.0f;

				m_pInteract = CBillboard::Create(pos, SIZE_INTERACT, SIZE_INTERACT);

				if (m_pInteract != nullptr)
				{
					int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\interact.png");
					m_pInteract->SetIdxTexture(nIdx);
					m_pInteract->SetZTest(true);
				}
			}

			// ���������I�u�W�F�N�g�̎擾
			CObject *pObj = m_pCollisionSphere->GetOther();

			// �A�C�e�����菈��
			//GetItem(pObj);
		}
		else
		{
			if (m_pInteract != nullptr)
			{// �C���^���N�g�\���폜
				m_pInteract->Uninit();
				m_pInteract = nullptr;
			}
		}
	}
}

//=====================================================
// �A�C�e�����莞�̏���
//=====================================================
void CItem::GetItem(CObject *pObj)
{

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
CItem *CItem::Create(void)
{
	CItem *pItem = nullptr;

	if (pItem == nullptr)
	{
		pItem = new CItem;

		if (pItem != nullptr)
		{
			// ������
			pItem->Init();
		}
	}

	return pItem;
}