//*****************************************************
//
// UI�}�l�[�W���[[UIManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "inputkeyboard.h"
#include "UIManager.h"
#include "game.h"

#include "life.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define TIME_PENALTY	(15)	// �^�C���y�i���e�B

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CUIManager *CUIManager::m_pUIManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CUIManager::CUIManager()
{
	m_bDisp = false;
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CUIManager::~CUIManager()
{

}

//=====================================================
// ��������
//=====================================================
CUIManager *CUIManager::Create(void)
{
	if (m_pUIManager == nullptr)
	{// �C���X�^���X����
		m_pUIManager = new CUIManager;

		// ����������
		m_pUIManager->Init();
	}

	return m_pUIManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CUIManager::Init(void)
{
	m_bDisp = true;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CUIManager::Uninit(void)
{
	m_pUIManager = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CUIManager::Update(void)
{
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetTrigger(DIK_1))
		{
			m_bDisp = m_bDisp ? false : true;
		}
	}
}

//=====================================================
// �v���C���[UI�̐�������
//=====================================================
void CUIManager::SetPlayer(int nNumPlayer)
{
	for (int nIdx = 0; nIdx < nNumPlayer; nIdx++)
	{
		// ���C�t�̐�������
		CLife* pLife = CreateLife(nIdx);

		if (pLife != NULL &&
			m_info.m_apLife[nIdx] == NULL)
		{
			// ���C�t����
			m_info.m_apLife[nIdx] = pLife;
		}
	}
}

//=====================================================
// ���C�t�̐�������
//=====================================================
CLife *CUIManager::CreateLife(int nIdx)
{
	CLife *pLife = nullptr;

	pLife = CLife::Create(nIdx);
	
	return pLife;
}

//=====================================================
// �`�揈��
//=====================================================
void CUIManager::Draw(void)
{
#ifdef _DEBUG

#endif
}