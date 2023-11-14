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

//=====================================================
// �R���X�g���N�^
//=====================================================
CItemRepair::CItemRepair(int nPriority) : CItem(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CItemRepair::~CItemRepair()
{

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
	// �p���N���X�̏I��
	CItem::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CItemRepair::Update(void)
{
	// �p���N���X�̍X�V
	CItem::Update();
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
				{

				}
			}
		}
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