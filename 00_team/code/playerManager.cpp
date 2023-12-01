//*****************************************************
//
// �v���C���[�}�l�[�W���[[playerManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "playerManager.h"
#include "player.h"
#include <stdio.h>

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CPlayerManager *CPlayerManager::m_pPlayerManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CPlayerManager::CPlayerManager()
{
	m_nNumPlayer = 0;
	ZeroMemory(&m_apPlayer[0], sizeof(m_apPlayer));
	ZeroMemory(&m_anIDJoypad[0], sizeof(m_anIDJoypad));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CPlayerManager::~CPlayerManager()
{

}

//=====================================================
// ��������
//=====================================================
CPlayerManager *CPlayerManager::Create(void)
{
	if (m_pPlayerManager == nullptr)
	{// �C���X�^���X����
		m_pPlayerManager = new CPlayerManager;

		// ����������
		m_pPlayerManager->Init();
	}

	return m_pPlayerManager;
}

//=====================================================
// �v���C���[��������
//=====================================================
void CPlayerManager::CreatePlayer(void)
{
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		if(m_anIDJoypad[i] != -1)
		{
			CPlayer* pPlayer = nullptr;

			pPlayer = CPlayer::Create(m_nNumPlayer);

			if (pPlayer != nullptr)
			{
				pPlayer->SetIDJoypad(m_anIDJoypad[i]);

				pPlayer->SetPosition(D3DXVECTOR3(50.0f * m_nNumPlayer, 0.0f, 0.0f));

				m_apPlayer[m_nNumPlayer] = pPlayer;

				m_nNumPlayer++;
			}
		}
	}
}

//=====================================================
// �v���C���[�o�^����
//=====================================================
CPlayer *CPlayerManager::BindPlayer(int nIdxJoypad)
{
	if (nIdxJoypad < 0 || nIdxJoypad >= NUM_PLAYER)
	{
		return nullptr;
	}

	CPlayer* pPlayer = nullptr;

	pPlayer = CPlayer::Create(m_nNumPlayer);

	if (pPlayer != nullptr)
	{
		pPlayer->SetIDJoypad(nIdxJoypad);

		m_apPlayer[m_nNumPlayer] = pPlayer;

		m_anIDJoypad[m_nNumPlayer] = nIdxJoypad;

		pPlayer->SetPosition(D3DXVECTOR3(50.0f * m_nNumPlayer, 0.0f, 0.0f));

		m_nNumPlayer++;
	}

	return pPlayer;
}

//=====================================================
// ����������
//=====================================================
HRESULT CPlayerManager::Init(void)
{
	// �v���C���[�̔ԍ��̏����ݒ�
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		m_anIDJoypad[i] = -1;
	}

	// �v���C���[�p�����[�^�[�̓ǂݍ���
	LoadParamPlayer();

	return S_OK;
}

//=====================================================
// �v���C���[�p�����[�^�[�ǂݍ���
//=====================================================
void CPlayerManager::LoadParamPlayer(void)
{
	// �ϐ��錾
	char cTemp[256];

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen("data\\TEXT\\playerParam.txt", "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "LIFE") == 0)
			{// �����̗�
				(void)fscanf(pFile, "%s", &cTemp[0]);

				(void)fscanf(pFile, "%f", &m_paramPlayer.fInitialLife);
			}

			if (strcmp(cTemp, "SPEED_MOVE") == 0)
			{// �ړ����x
				(void)fscanf(pFile, "%s", &cTemp[0]);

				(void)fscanf(pFile, "%f", &m_paramPlayer.fSpeedMove);
			}

			if (strcmp(cTemp, "SPEED_ROT") == 0)
			{// ��]���x
				(void)fscanf(pFile, "%s", &cTemp[0]);

				(void)fscanf(pFile, "%f", &m_paramPlayer.fSpeedRot);
			}

			if (strcmp(cTemp, "TIME_DAMAGE") == 0)
			{// ���G����
				(void)fscanf(pFile, "%s", &cTemp[0]);

				(void)fscanf(pFile, "%f", &m_paramPlayer.fTimeDamage);
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// �I������
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		assert(("�v���C���[�p�����[�^�[�ǂݍ��݂Ɏ��s", false));
	}
}

//=====================================================
// �I������
//=====================================================
void CPlayerManager::Uninit(void)
{
	m_pPlayerManager = nullptr;

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		if (m_apPlayer[i] != nullptr)
		{
			m_apPlayer[i] = nullptr;
		}
	}

	delete this;
}

//=====================================================
// �ʏI������
//=====================================================
void CPlayerManager::ReleasePlayer(int nIdx)
{
	m_apPlayer[nIdx] = nullptr;

	m_nNumPlayer--;
}