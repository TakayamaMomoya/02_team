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
	m_nNumPlayer = 0;
	ZeroMemory(&m_apPlayer[0], sizeof(m_apPlayer));
	ZeroMemory(&m_anIDJoypad[0], sizeof(m_anIDJoypad));
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
void CPlayerManager::CreatePlayer(void)
{
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		if(m_anIDJoypad[i] != -1)
		{
			CPlayer* pPlayer = nullptr;

			pPlayer = CPlayer::Create();

			if (pPlayer != nullptr)
			{
				pPlayer->SetID(m_nNumPlayer);
				pPlayer->SetIDJoypad(m_anIDJoypad[i]);

				pPlayer->SetPosition(D3DXVECTOR3(50.0f * m_nNumPlayer, 0.0f, 0.0f));

				m_apPlayer[m_nNumPlayer] = pPlayer;

				m_nNumPlayer++;
			}
		}
	}
}

//=====================================================
// プレイヤー登録処理
//=====================================================
CPlayer *CPlayerManager::BindPlayer(int nIdxJoypad)
{
	if (nIdxJoypad < 0 || nIdxJoypad >= NUM_PLAYER)
	{
		return nullptr;
	}

	CPlayer* pPlayer = nullptr;

	pPlayer = CPlayer::Create();

	if (pPlayer != nullptr)
	{
		pPlayer->SetID(m_nNumPlayer);
		pPlayer->SetIDJoypad(nIdxJoypad);

		m_apPlayer[m_nNumPlayer] = pPlayer;

		m_anIDJoypad[m_nNumPlayer] = nIdxJoypad;

		pPlayer->SetPosition(D3DXVECTOR3(50.0f * m_nNumPlayer, 0.0f, 0.0f));

		m_nNumPlayer++;
	}

	return pPlayer;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPlayerManager::Init(void)
{
	// プレイヤーの番号の初期設定
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		m_anIDJoypad[i] = -1;
	}

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

	delete this;
}

//=====================================================
// 個別終了処理
//=====================================================
void CPlayerManager::ReleasePlayer(int nIdx)
{
	m_apPlayer[nIdx] = nullptr;

	m_nNumPlayer--;
}