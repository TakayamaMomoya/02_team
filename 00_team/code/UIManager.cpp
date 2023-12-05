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

//*****************************************************
// マクロ定義
//*****************************************************
#define TIME_PENALTY	(15)	// タイムペナルティ

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const D3DXVECTOR3 POS[NUM_PLAYER] =
	{// 位置
		D3DXVECTOR3(SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.975f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.7f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.975f, SCREEN_HEIGHT * 0.7f, 0.0f),
	};

	const float FRAME_WIDTH = 30.0f;
	const float FRAME_HEIGHT = 100.0f;
	const D3DXCOLOR FRAME_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const char* FRAME_FILE_NAME[NUM_PLAYER] =
	{// 位置
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

	//// ライフの生成処理
	//CLife* pLife = CreateLife(nIdx);

	//if (pLife != NULL &&
	//	m_aInfo[nIdx].pLife == NULL)
	//{
	//	// ライフのポインタを代入
	//	m_aInfo[nIdx].pLife = pLife;

	//	// ライフの設定
	//	m_aInfo[nIdx].pLife->SetPosition(POS[nIdx]);
	//	m_aInfo[nIdx].pLife->SetSize(LIFE_WIDTH,LIFE_HEIGHT);
	//	m_aInfo[nIdx].pLife->SetCol(LIFE_COLOR);
	//	//m_aInfo[nIdx].pLife->SetTexture(LIFE_FILE_NAME);
	//}
}

//=====================================================
// フレームの生成処理
//=====================================================
CUI* CUIManager::CreateFrame(void)
{
	CUI* pFrame = nullptr;

	pFrame = CUI::Create();

	return pFrame;
}

//=====================================================
// ライフの生成処理
//=====================================================
CLife *CUIManager::CreateLife(int nIdx)
{
	CLife *pLife = nullptr;

	pLife = CLife::Create(nIdx);
	
	return pLife;
}

//=====================================================
// 描画処理
//=====================================================
void CUIManager::Draw(void)
{
#ifdef _DEBUG

#endif
}