//*****************************************************
//
// �G�C�x���g�̏���[enemyEvent.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "enemyEvent.h"
#include "manager.h"
#include "light.h"
#include "enemyManager.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float INITIAL_LIFE = 10.0f;	// ��������
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyEvent::CEnemyEvent(int nPriority) : CObject(nPriority)
{
	m_fLife = 0.0f;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyEvent::~CEnemyEvent()
{

}

//=====================================================
// ��������
//=====================================================
CEnemyEvent *CEnemyEvent::Create(void)
{
	CEnemyEvent *pEnemyEvent = nullptr;

	if (pEnemyEvent == nullptr)
	{
		pEnemyEvent = new CEnemyEvent;

		if (pEnemyEvent != nullptr)
		{
			// ������
			pEnemyEvent->Init();
		}
	}

	return pEnemyEvent;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyEvent::Init(void)
{
	m_fLife = INITIAL_LIFE;

	// ���C�g��Ԃ�����
	CLight *pLight = CManager::GetLight();

	if (pLight != nullptr)
	{
		for (int i = 0; i < MAX_LIGHT; i++)
		{
			pLight->SetColDest(i, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	// �G�̏o���p�x��ύX
	CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager != nullptr)
	{
		pEnemyManager->SetTimeScale(0.5f);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemyEvent::Uninit(void)
{
	// ���C�g�̐F��߂�
	CLight *pLight = CManager::GetLight();

	if (pLight != nullptr)
	{
		pLight->ResetColDest();
	}

	// �G�̏o���p�x��߂�
	CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager != nullptr)
	{
		pEnemyManager->SetTimeScale(1.0f);
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyEvent::Update(void)
{
	// �����ł̏���
	float fTick = CManager::GetTick();

	m_fLife -= fTick;

	if (m_fLife <= 0.0f)
	{
		Uninit();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyEvent::Draw(void)
{

}