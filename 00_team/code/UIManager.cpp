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
#include "UIMagazine.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define TIME_PENALTY	(15)	// �^�C���y�i���e�B

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const D3DXVECTOR3 FRAME_POS[NUM_PLAYER] =
	{// ��̈ʒu
		D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.225f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.225f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.775f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.775f, 0.0f),
	};
	const float FRAME_SIZE = 150.0f;
	const float FRAME_WIDTH = FRAME_SIZE * 0.4f;
	const float FRAME_HEIGHT = FRAME_SIZE * 1.0f;
	const D3DXCOLOR FRAME_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const char* FRAME_FILE_NAME[NUM_PLAYER] =
	{// �t�@�C����
		"data\\TEXTURE\\UI\\UIFrame000.png",
		"data\\TEXTURE\\UI\\UIFrame001.png",
		"data\\TEXTURE\\UI\\UIFrame002.png",
		"data\\TEXTURE\\UI\\UIFrame003.png",
	};

	const D3DXVECTOR3 LIFE_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3(-15.5f,  45.0f, 0.0f),
		D3DXVECTOR3( 15.5f,  45.0f, 0.0f),
		D3DXVECTOR3(-15.5f, -45.0f, 0.0f),
		D3DXVECTOR3( 15.5f, -45.0f, 0.0f),
	};
	const float LIFE_SIZE = 100.0f;
	const float LIFE_WIDTH = LIFE_SIZE * 0.1f;
	const float LIFE_HEIGHT = LIFE_SIZE * 0.9f;
	const D3DXCOLOR LIFE_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	const char* LIFE_FILE_NAME = "data\\UI\\UILife000.txt";

	const D3DXVECTOR3 MAGAZINE_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3( 15.0f,  80.0f, 0.0f),
		D3DXVECTOR3(-65.0f,  80.0f, 0.0f),
		D3DXVECTOR3( 15.0f, -80.0f, 0.0f),
		D3DXVECTOR3(-65.0f, -80.0f, 0.0f),
	};
	const D3DXVECTOR3 MAGAZINE_MAX_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3( 15.0f,  50.0f, 0.0f),
		D3DXVECTOR3(-65.0f,  50.0f, 0.0f),
		D3DXVECTOR3( 15.0f, -50.0f, 0.0f),
		D3DXVECTOR3(-65.0f, -50.0f, 0.0f),
	};
	const float MAGAZINE_SIZE = 12.5f;
	const float MAGAZINE_WIDTH = MAGAZINE_SIZE * 1.0f;
	const float MAGAZINE_HEIGHT = MAGAZINE_SIZE * 1.0f;
	const D3DXCOLOR MAGAZINE_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const char* MAGAZINE_FILE_NAME = "data\\UI\\UILife000.txt";
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
		m_aInfo[nIdx].pFrame->SetPosition(FRAME_POS[nIdx]);
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

	// ���C�t�̐�������
	CLife* pLife = CreateLife(nIdx);

	if (pLife != NULL &&
		m_aInfo[nIdx].pLife == NULL)
	{
		// ���C�t�̃|�C���^����
		m_aInfo[nIdx].pLife = pLife;

		// ���C�t�̐ݒ�
		m_aInfo[nIdx].pLife->SetPosition(FRAME_POS[nIdx] + LIFE_POS_PLUS[nIdx]);
		m_aInfo[nIdx].pLife->SetSize(LIFE_WIDTH,LIFE_HEIGHT);
		m_aInfo[nIdx].pLife->SetCol(LIFE_COLOR);
		//m_aInfo[nIdx].pLife->SetTexture(LIFE_FILE_NAME);
	}

	// ���e��UI�̐�������
	CUIMagazine* pUIMagazine = CreateUIMagazine(nIdx);

	if (pUIMagazine != NULL &&
		m_aInfo[nIdx].pUIMagazine == NULL)
	{
		// ���C�t�̃|�C���^����
		m_aInfo[nIdx].pUIMagazine = pUIMagazine;

		// ���C�t�̐ݒ�
		m_aInfo[nIdx].pUIMagazine->SetPosition(
			FRAME_POS[nIdx] + MAGAZINE_POS_PLUS[nIdx],
			FRAME_POS[nIdx] + MAGAZINE_MAX_POS_PLUS[nIdx]);
		m_aInfo[nIdx].pUIMagazine->SetSize(MAGAZINE_WIDTH, MAGAZINE_HEIGHT);
		m_aInfo[nIdx].pUIMagazine->SetCol(MAGAZINE_COLOR);
		//m_aInfo[nIdx].pLife->SetTexture(LIFE_FILE_NAME);
	}
}

//=====================================================
// �t���[���̐�������
//=====================================================
CUI* CUIManager::CreateFrame(void)
{
	CUI* pFrame = CUI::Create();

	if (pFrame == nullptr)
	{
		return nullptr;
	}

	return pFrame;
}

//=====================================================
// ���C�t�̐�������
//=====================================================
CLife*CUIManager::CreateLife(int nIdx)
{
	CLife *pLife = CLife::Create(nIdx);

	if (pLife == nullptr)
	{
		return nullptr;
	}
	
	return pLife;
}

//=====================================================
// ���e���̐�������
//=====================================================
CUIMagazine* CUIManager::CreateUIMagazine(int nIdx)
{
	CUIMagazine* pUIMagazine = CUIMagazine::Create(nIdx);

	if (pUIMagazine == nullptr)
	{
		return nullptr;
	}

	return pUIMagazine;
}

//=====================================================
// �`�揈��
//=====================================================
void CUIManager::Draw(void)
{
#ifdef _DEBUG

#endif
}