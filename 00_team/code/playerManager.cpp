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
	ZeroMemory(&m_apPlayer[0], sizeof(m_apPlayer));
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
void CPlayerManager::CreatePlayer(int nNumPlayer)
{
	for (int i = 0; i < nNumPlayer; i++)
	{
		CPlayer *pPlayer = nullptr;

		pPlayer = CPlayer::Create();

		if (pPlayer != nullptr)
		{
			pPlayer->SetID(i);

			m_apPlayer[i] = pPlayer;
		}
	}
}

//=====================================================
// ����������
//=====================================================
HRESULT CPlayerManager::Init(void)
{
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

	Release();
}

//=====================================================
// �ʏI������
//=====================================================
void CPlayerManager::ReleasePlayer(int nIdx)
{
	m_apPlayer[nIdx] = nullptr;
}

//=====================================================
// �X�V����
//=====================================================
void CPlayerManager::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CPlayerManager::Draw(void)
{

}