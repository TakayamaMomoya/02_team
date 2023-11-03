//*****************************************************
//
// プレイヤーマネージャー[playerManager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "playerManager.h"
#include "player.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CPlayerManager *CPlayerManager::m_pPlayerManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CPlayerManager::CPlayerManager()
{
	ZeroMemory(&m_apPlayer[0], sizeof(m_apPlayer));
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
// プレイヤー生成処理
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
// 個別終了処理
//=====================================================
void CPlayerManager::ReleasePlayer(int nIdx)
{
	m_apPlayer[nIdx] = nullptr;
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