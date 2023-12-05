//*****************************************************
//
// UIマネージャー[UIManager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
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
// マクロ定義
//*****************************************************
#define TIME_PENALTY	(15)	// タイムペナルティ

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const D3DXVECTOR3 FRAME_POS[NUM_PLAYER] =
	{// 基準の位置
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
	{// ファイル名
		"data\\TEXTURE\\UI\\UIFrame000.png",
		"data\\TEXTURE\\UI\\UIFrame001.png",
		"data\\TEXTURE\\UI\\UIFrame002.png",
		"data\\TEXTURE\\UI\\UIFrame003.png",
	};

	const D3DXVECTOR3 LIFE_POS_PLUS[NUM_PLAYER] =
	{// 基準から加算分の位置
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
	{// 基準から加算分の位置
		D3DXVECTOR3( 15.0f,  80.0f, 0.0f),
		D3DXVECTOR3(-65.0f,  80.0f, 0.0f),
		D3DXVECTOR3( 15.0f, -80.0f, 0.0f),
		D3DXVECTOR3(-65.0f, -80.0f, 0.0f),
	};
	const D3DXVECTOR3 MAGAZINE_MAX_POS_PLUS[NUM_PLAYER] =
	{// 基準から加算分の位置
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
// 静的メンバ変数宣言
//*****************************************************
CUIManager *CUIManager::m_pUIManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CUIManager::CUIManager()
{
	m_bDisp = false;
	ZeroMemory(&m_aInfo[0], sizeof(m_aInfo));
}

//=====================================================
// デストラクタ
//=====================================================
CUIManager::~CUIManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CUIManager *CUIManager::Create(void)
{
	if (m_pUIManager == nullptr)
	{// インスタンス生成
		m_pUIManager = new CUIManager;

		// 初期化処理
		m_pUIManager->Init();
	}

	return m_pUIManager;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CUIManager::Init(void)
{
	m_bDisp = true;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CUIManager::Uninit(void)
{
	m_pUIManager = nullptr;

	Release();
}

//=====================================================
// 更新処理
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
// プレイヤーUIの生成処理
//=====================================================
void CUIManager::SetPlayer(int nIdx)
{
	// フレームの生成処理
	CUI* pFrame = CreateFrame();

	if (pFrame != NULL &&
		m_aInfo[nIdx].pFrame == NULL)
	{
		// ライフのポインタを代入
		m_aInfo[nIdx].pFrame = pFrame;

		// ライフの設定
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

	// ライフの生成処理
	CLife* pLife = CreateLife(nIdx);

	if (pLife != NULL &&
		m_aInfo[nIdx].pLife == NULL)
	{
		// ライフのポインタを代入
		m_aInfo[nIdx].pLife = pLife;

		// ライフの設定
		m_aInfo[nIdx].pLife->SetPosition(FRAME_POS[nIdx] + LIFE_POS_PLUS[nIdx]);
		m_aInfo[nIdx].pLife->SetSize(LIFE_WIDTH,LIFE_HEIGHT);
		m_aInfo[nIdx].pLife->SetCol(LIFE_COLOR);
		//m_aInfo[nIdx].pLife->SetTexture(LIFE_FILE_NAME);
	}

	// 装弾数UIの生成処理
	CUIMagazine* pUIMagazine = CreateUIMagazine(nIdx);

	if (pUIMagazine != NULL &&
		m_aInfo[nIdx].pUIMagazine == NULL)
	{
		// ライフのポインタを代入
		m_aInfo[nIdx].pUIMagazine = pUIMagazine;

		// ライフの設定
		m_aInfo[nIdx].pUIMagazine->SetPosition(
			FRAME_POS[nIdx] + MAGAZINE_POS_PLUS[nIdx],
			FRAME_POS[nIdx] + MAGAZINE_MAX_POS_PLUS[nIdx]);
		m_aInfo[nIdx].pUIMagazine->SetSize(MAGAZINE_WIDTH, MAGAZINE_HEIGHT);
		m_aInfo[nIdx].pUIMagazine->SetCol(MAGAZINE_COLOR);
		//m_aInfo[nIdx].pLife->SetTexture(LIFE_FILE_NAME);
	}
}

//=====================================================
// フレームの生成処理
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
// ライフの生成処理
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
// 装弾数の生成処理
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
// 描画処理
//=====================================================
void CUIManager::Draw(void)
{
#ifdef _DEBUG

#endif
}