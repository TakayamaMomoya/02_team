//*****************************************************
//
// プレイヤーマネージャー[playerManager.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "playerManager.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CPlayerManager *CPlayerManager::m_pPlayerManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CPlayerManager::CPlayerManager()
{

}

//=====================================================
// デストラクタ
//=====================================================
CPlayerManager::~CPlayerManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CPlayerManager *CPlayerManager::Create(void)
{
	if (m_pPlayerManager == nullptr)
	{// インスタンス生成
		m_pPlayerManager = new CPlayerManager;

		// 初期化処理
		m_pPlayerManager->Init();
	}

	return m_pPlayerManager;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPlayerManager::Init(void)
{
	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPlayerManager::Uninit(void)
{
	m_pPlayerManager = nullptr;

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayerManager::Update(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CPlayerManager::Draw(void)
{

}