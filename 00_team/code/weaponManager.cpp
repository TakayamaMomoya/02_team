//*****************************************************
//
// ����}�l�[�W���[[weaponManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "weaponManager.h"
#include "Weapon.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define PARAM_PATH	"data\\TEXT\\weapon.txt"	// �p�����[�^�[�̃p�X

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CWeaponManager *CWeaponManager::m_pWeaponManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CWeaponManager::CWeaponManager()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CWeaponManager::~CWeaponManager()
{

}

//=====================================================
// ��������
//=====================================================
CWeaponManager *CWeaponManager::Create(void)
{
	if (m_pWeaponManager == nullptr)
	{// �C���X�^���X����
		m_pWeaponManager = new CWeaponManager;

		// ����������
		m_pWeaponManager->Init();
	}

	return m_pWeaponManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CWeaponManager::Init(void)
{
	// �p�����[�^�[�ǂݍ���
	LoadParam();

	return S_OK;
}

//=====================================================
// �p�����[�^�[�ǂݍ��ݏ���
//=====================================================
void CWeaponManager::LoadParam(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntParam = 0;

	// �t�@�C������ǂݍ���
	FILE* pFile = fopen(PARAM_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "MAGNUMSET") == 0)
			{// �p�����[�^�[�Ǎ��J�n
				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					// ���p�����[�^�[�ǂݍ���
					LoadBaseInfo(pFile, &cTemp[0], CWeapon::TYPE_MAGNUM);

					if (strcmp(cTemp, "END_MAGNUMSET") == 0)
					{// �p�����[�^�[�Ǎ��I��
						break;
					}
				}
			}

			if (strcmp(cTemp, "MACHINEGUNSET") == 0)
			{// �p�����[�^�[�Ǎ��J�n
				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					// ���p�����[�^�[�ǂݍ���
					LoadBaseInfo(pFile, &cTemp[0], CWeapon::TYPE_MACHINEGUN);

					if (strcmp(cTemp, "END_MACHINEGUNSET") == 0)
					{// �p�����[�^�[�Ǎ��I��
						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// �ǂݍ��݂̏I��
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
}

//=====================================================
// �p�����[�^�[�Ǎ�
//=====================================================
void CWeaponManager::LoadBaseInfo(FILE* pFile, char* pTemp, int nCntParam)
{
	if (strcmp(pTemp, "BULLET") == 0)
	{// �e��
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%d", &m_aInfo[nCntParam].nMaxBullet);
	}

	if (strcmp(pTemp, "RAPID") == 0)
	{// �A�˗�
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%d", &m_aInfo[nCntParam].nRapid);
	}
}

//=====================================================
// �I������
//=====================================================
void CWeaponManager::Uninit(void)
{
	m_pWeaponManager = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CWeaponManager::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CWeaponManager::Draw(void)
{

}