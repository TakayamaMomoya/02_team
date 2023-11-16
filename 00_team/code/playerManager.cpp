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

			pPlayer = CPlayer::Create();

			if (pPlayer != nullptr)
			{
				pPlayer->SetID(m_nNumPlayer);
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

	pPlayer = CPlayer::Create();

	if (pPlayer != nullptr)
	{
		pPlayer->SetID(m_nNumPlayer);
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

	return S_OK;
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