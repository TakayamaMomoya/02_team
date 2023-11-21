//*****************************************************
//
// �M�~�b�N�}�l�[�W���[[gimmickManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "GimmickManager.h"
#include "Gimmick.h"
#include "door.h"
#include "container.h"
#include "itemRepair.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const char* MAP_PATH = "data\\MAP\\gimmick.txt";	// �z�u���̃p�X
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CGimmickManager *CGimmickManager::m_pGimmickManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CGimmickManager::CGimmickManager()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGimmickManager::~CGimmickManager()
{

}

//=====================================================
// ��������
//=====================================================
CGimmickManager *CGimmickManager::Create(void)
{
	if (m_pGimmickManager == nullptr)
	{// �C���X�^���X����
		m_pGimmickManager = new CGimmickManager;

		// ����������
		m_pGimmickManager->Init();
	}

	return m_pGimmickManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CGimmickManager::Init(void)
{
	// �z�u�f�[�^�̓Ǎ�
	Load();

	return S_OK;
}

//=====================================================
// �Ǎ�����
//=====================================================
void CGimmickManager::Load(void)
{
	// �ϐ��錾
	char cTemp[256];

	// �t�@�C������ǂݍ���
	FILE* pFile = fopen(MAP_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			(void)fscanf(pFile, "%s", &cTemp[0]);

			// �M�~�b�N�̐���
			CreateGimmick(pFile, &cTemp[0]);

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// �ǂݍ��݂̏I��
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		assert(("�M�~�b�N�z�u���ǂݍ��݂Ɏ��s", false));
	}
}

//=====================================================
// �f�[�^���Ƃɐ������鏈��
//=====================================================
void CGimmickManager::CreateGimmick(FILE *pFile, char *pTemp)
{
	if (strcmp(pTemp, "DOORSET") == 0)
	{// �h�A�̐ݒu
		LoadDoor(pFile, pTemp);
	}

	if (strcmp(pTemp, "CONTAINERSET") == 0)
	{// �R���e�i�̐ݒu
		LoadContainer(pFile, pTemp);
	}

	if (strcmp(pTemp, "REPAIRSET") == 0)
	{// ���i�̐ݒu
		LoadRepair(pFile, pTemp);
	}
}

//=====================================================
// �h�A�Ǎ�����
//=====================================================
void CGimmickManager::LoadDoor(FILE *pFile, char *pTemp)
{
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	while (true)
	{
		(void)fscanf(pFile, "%s", pTemp);

		if (strcmp(pTemp, "POS") == 0)
		{// �ʒu
			(void)fscanf(pFile, "%s", pTemp);

			for (int i = 0; i < 3; i++)
			{
				(void)fscanf(pFile, "%f", &pos[i]);
			}
		}

		if (strcmp(pTemp, "END_DOORSET") == 0)
		{// �h�A�ݒ�I��
			CDoor *pDoor = CDoor::Create();

			if (pDoor != nullptr)
			{
				pDoor->SetPosition(pos);
			}

			break;
		}
	}
}

//=====================================================
// �R���e�i�Ǎ�����
//=====================================================
void CGimmickManager::LoadContainer(FILE *pFile, char *pTemp)
{
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	while (true)
	{
		(void)fscanf(pFile, "%s", pTemp);

		if (strcmp(pTemp, "POS") == 0)
		{// �ʒu
			(void)fscanf(pFile, "%s", pTemp);

			for (int i = 0; i < 3; i++)
			{
				(void)fscanf(pFile, "%f", &pos[i]);
			}
		}

		if (strcmp(pTemp, "END_CONTAINERSET") == 0)
		{// �R���e�i�ݒ�I��
			CContainer *pContainer = CContainer::Create();

			if (pContainer != nullptr)
			{
				pContainer->SetPosition(pos);
			}

			break;
		}
	}
}

//=====================================================
// ���i�Ǎ�����
//=====================================================
void CGimmickManager::LoadRepair(FILE *pFile, char *pTemp)
{
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	while (true)
	{
		(void)fscanf(pFile, "%s", pTemp);

		if (strcmp(pTemp, "POS") == 0)
		{// �ʒu
			(void)fscanf(pFile, "%s", pTemp);

			for (int i = 0; i < 3; i++)
			{
				(void)fscanf(pFile, "%f", &pos[i]);
			}
		}

		if (strcmp(pTemp, "END_REPAIRSET") == 0)
		{// ���i�ݒ�I��
			CItemRepair *pRapair = CItemRepair::Create();

			if (pRapair != nullptr)
			{
				pRapair->SetPosition(pos);
			}

			break;
		}
	}
}

//=====================================================
// �I������
//=====================================================
void CGimmickManager::Uninit(void)
{
	m_pGimmickManager = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CGimmickManager::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CGimmickManager::Draw(void)
{

}