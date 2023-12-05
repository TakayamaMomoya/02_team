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

#include "texture.h"

#include "UI.h"
#include "life.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define TIME_PENALTY	(15)	// �^�C���y�i���e�B

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const D3DXVECTOR3 POS[NUM_PLAYER] =
	{// �ʒu
		D3DXVECTOR3(SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.975f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.7f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.975f, SCREEN_HEIGHT * 0.7f, 0.0f),
	};

	const float FRAME_WIDTH = 30.0f;
	const float FRAME_HEIGHT = 100.0f;
	const D3DXCOLOR FRAME_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const char* FRAME_FILE_NAME[NUM_PLAYER] =
	{// �ʒu
		"data\\TEXTURE\\UI\\UIFrame000.png",
		"data\\TEXTURE\\UI\\UIFrame001.png",
		"data\\TEXTURE\\UI\\UIFrame002.png",
		"data\\TEXTURE\\UI\\UIFrame003.png",
	};

	const float LIFE_WIDTH = 15.0f;
	const float LIFE_HEIGHT = 100.0f;
	const D3DXCOLOR LIFE_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	const char* LIFE_FILE_NAME = "data\\UI\\UILife000.txt";


}

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
	ZeroMemory(&m_aInfo[0], sizeof(m_aInfo));
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
void CUIManager::SetPlayer(int nIdx)
{
	// �t���[���̐�������
	CUI* pFrame = CreateFrame();

	if (pFrame != NULL &&
		m_aInfo[nIdx].pFrame == NULL)
	{
		// ���C�t�̃|�C���^����
		m_aInfo[nIdx].pFrame = pFrame;

		// ���C�t�̐ݒ�
		m_aInfo[nIdx].pFrame->SetPosition(POS[nIdx]);
		m_aInfo[nIdx].pFrame->SetSize(FRAME_WIDTH, FRAME_HEIGHT);
		m_aInfo[nIdx].pFrame->SetCol(FRAME_COLOR);

		CTexture* pTexture = CTexture::GetInstance();

		if (pTexture != NULL)
		{
			int nTexIdx = pTexture->Regist(FRAME_FILE_NAME[nIdx]);
			m_aInfo[nIdx].pFrame->SetIdxTexture(nTexIdx);
			m_aInfo[nIdx].pFrame->SetVtx();
		}

	}

	//// ���C�t�̐�������
	//CLife* pLife = CreateLife(nIdx);

	//if (pLife != NULL &&
	//	m_aInfo[nIdx].pLife == NULL)
	//{
	//	// ���C�t�̃|�C���^����
	//	m_aInfo[nIdx].pLife = pLife;

	//	// ���C�t�̐ݒ�
	//	m_aInfo[nIdx].pLife->SetPosition(POS[nIdx]);
	//	m_aInfo[nIdx].pLife->SetSize(LIFE_WIDTH,LIFE_HEIGHT);
	//	m_aInfo[nIdx].pLife->SetCol(LIFE_COLOR);
	//	//m_aInfo[nIdx].pLife->SetTexture(LIFE_FILE_NAME);
	//}
}

//=====================================================
// �t���[���̐�������
//=====================================================
CUI* CUIManager::CreateFrame(void)
{
	CUI* pFrame = nullptr;

	pFrame = CUI::Create();

	return pFrame;
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