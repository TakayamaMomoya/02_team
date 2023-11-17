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

//=====================================================
// �R���X�g���N�^
//=====================================================
CContainer::CContainer(int nPriority) : CItem(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CContainer::~CContainer()
{

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

	return S_OK;
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CContainer::Load(void)
{

}

//=====================================================
// �I������
//=====================================================
void CContainer::Uninit(void)
{
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
				{
					Uninit();
				}
			}
		}
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