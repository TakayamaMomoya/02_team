//*****************************************************
//
// �G�}�l�[�W���[[enemyManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemyManager.h"
#include "enemyNormal.h"
#include "enemyThief.h"
#include "manager.h"
#include "camera.h"
#include "universal.h"
#include <stdio.h>
#include "game.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define RAND_SPAWN	(1000)	// �X�|�[���͈�

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CEnemyManager *CEnemyManager::m_pEnemyManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyManager::CEnemyManager()
{
	m_nCntSpawn = 0;

	m_pHead = nullptr;
	m_pTail = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyManager::~CEnemyManager()
{

}

//=====================================================
// ��������
//=====================================================
CEnemyManager *CEnemyManager::Create(void)
{
	if (m_pEnemyManager == nullptr)
	{// �C���X�^���X����
		m_pEnemyManager = new CEnemyManager;

		// ����������
		m_pEnemyManager->Init();
	}

	return m_pEnemyManager;
}

//=====================================================
// �G�̐�������
//=====================================================
CEnemy *CEnemyManager::CreateEnemy(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	char *apPath[CEnemy::TYPE_MAX] = 
	{
		nullptr,
		"data\\MOTION\\motionEnemy00.txt",
		"data\\MOTION\\motionEnemy01.txt",
	};

	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// �C���X�^���X����
		switch (type)
		{
		case CEnemy::TYPE_NORMAL:

			pEnemy = new CEnemyNormal;

			break;
		case CEnemy::TYPE_THIEF:

			pEnemy = new CEnemyThief;

			break;
		default:
			break;
		}

		if (pEnemy != nullptr)
		{
			// �ʒu�ݒ�
			pEnemy->SetPosition(pos);

			// ���[�V�����Ǎ�
			pEnemy->Load(apPath[type]);

			// ����������
			pEnemy->Init();
		}
	}

	return pEnemy;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyManager::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemyManager::Uninit(void)
{
	m_pEnemyManager = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyManager::Update(void)
{
	// �Q�[����Ԃɂ���ăX�|�[�������Ȃ�
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		CGame::STATE state = pGame->GetState();

		if (state != CGame::STATE::STATE_NORMAL)
		{
			return;
		}
	}

	m_nCntSpawn++;

	if (m_nCntSpawn >= 60)
	{
		D3DXVECTOR3 posCenter = { 0.0f,0.0f,0.0f };

		// �o��������W��ݒ�
		posCenter.x = (float)universal::RandRange(1000, -1000);
		posCenter.z = (float)universal::RandRange(1000, -1000);

		// �ʒu�̐��K��
		D3DXVec3Normalize(&posCenter, &posCenter);
		posCenter *= RAND_SPAWN;

		// �G�X�|�[��
		CreateEnemy(posCenter, CEnemy::TYPE_NORMAL);

		m_nCntSpawn = 0;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyManager::Draw(void)
{
#ifdef _DEBUG
	//CDebugProc::GetInstance()->Print("\n�G�̈ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
#endif
}