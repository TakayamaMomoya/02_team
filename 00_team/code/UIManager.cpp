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

#include "life.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define TIME_PENALTY	(15)	// タイムペナルティ

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
	ZeroMemory(&m_info, sizeof(SInfo));
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
void CUIManager::SetPlayer(int nNumPlayer)
{
	for (int nIdx = 0; nIdx < nNumPlayer; nIdx++)
	{
		// ライフの生成処理
		CLife* pLife = CreateLife(nIdx);

		if (pLife != NULL &&
			m_info.m_apLife[nIdx] == NULL)
		{
			// ライフを代入
			m_info.m_apLife[nIdx] = pLife;
		}
	}
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