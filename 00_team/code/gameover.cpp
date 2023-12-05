//=========================================================
//
// ゲームオーバー処理 [gameover.cpp]
// Author = 阿部翔大郎
//
//=========================================================

//===============================================
// インクルード
//===============================================
#include "gameover.h"
#include "enemyManager.h"
#include "playerManager.h"
#include "particle.h"
#include "scene.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"

//===============================================
// 定数定義
//===============================================
namespace
{
	// 敵の体のパス
	const char* PLAYER_BODY_PATH[NUM_PLAYER] =
	{
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman02.txt",
		"data\\MOTION\\motionPotatoman03.txt",
		"data\\MOTION\\motionPotatoman04.txt",
	};

	// プレイヤーの位置
	const D3DXVECTOR3 PLAYER_POS[NUM_PLAYER] =
	{
		D3DXVECTOR3(0.0f, 0.0f, -150.0f),
		D3DXVECTOR3(-125.0f, 0.0f, -100.0f),
		D3DXVECTOR3(100.0f, 0.0f,  -50.0f),
		D3DXVECTOR3(-75.0f, 0.0f,  100.0f),
	};

	// プレイヤーの向き
	const D3DXVECTOR3 PLAYER_ROT[NUM_PLAYER] =
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.25f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.10f, 0.0f),
	};

	// 敵の体のパス
	const char* ENEMY_BODY_PATH = "data\\MOTION\\motionEnemy00.txt";

	// 敵の位置
	const D3DXVECTOR3 ENEMY_POS[NUM_ENEMY] =
	{
		D3DXVECTOR3(0.0f, 0.0f, -150.0f),
	};

	// 敵の向き
	const D3DXVECTOR3 ENEMY_ROT[NUM_ENEMY] =
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
	};
}

//===============================================
// 静的メンバ変数
//===============================================

//===============================================
// コンストラクタ
//===============================================
CGameover::CGameover()
{
	// 値のクリア
	ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
}

//===============================================
// デストラクタ
//===============================================
CGameover::~CGameover()
{
	
}

//===============================================
// 生成処理
//===============================================
CGameover *CGameover::Create(int nPriority)
{
	CGameover *pGameover;

	// ゲームオーバーの生成
	pGameover = new CGameover;

	if (pGameover != nullptr)
	{
		// 初期化処理
		pGameover->Init();
	}
	else if(pGameover == nullptr)
	{
		return nullptr;
	}

	return pGameover;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CGameover::Init()
{
	// インスタンスを取得
	CEnemyManager* pEnemyManager = CEnemyManager::GetInstance();
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();

	if (pEnemyManager != nullptr)
	{
		// 先頭オブジェクトを代入
		CEnemy* pEnemy = pEnemyManager->GetHead();

		// 現在出現している敵を削除
		while (pEnemy != nullptr)
		{
			// 次のアドレスを保存
			CEnemy* pEnemyNext = pEnemy->GetNext();

			// エフェクトを生成
			//CParticle::Create(pEnemy->GetPosition(), CParticle::TYPE_EXPLOSION);

			// 終了処理
			pEnemy->Uninit();

			// 次のアドレスを代入
			pEnemy = pEnemyNext;
		}

		// 敵を生成
		for (int nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
		{
			m_apModelEnemy[nCntEnemy] = CMotion::Create((char*)ENEMY_BODY_PATH);

			// 敵の情報の設定
			m_apModelEnemy[nCntEnemy]->SetPosition(ENEMY_POS[nCntEnemy]);	// 位置
			m_apModelEnemy[nCntEnemy]->SetRot(ENEMY_ROT[nCntEnemy]);		// 向き
			m_apModelEnemy[nCntEnemy]->SetMotion(0);						// モーション
		}
	}
	else if (pEnemyManager == nullptr)
	{
		return E_FAIL;
	}

	// プレイヤーの生成
	if (pPlayerManager != nullptr)
	{
		// プレイヤーが死んだときにplayerなどから数を取得

		//int nNumPlayer = pPlayerManager->GetNumPlayer();
		int nNumPlayer = 4;

		if (nNumPlayer >= 0)
		{
			for (int nCntPlayer = 0; nCntPlayer < nNumPlayer; nCntPlayer++)
			{
				m_apModelPlayer[nCntPlayer] = CMotion::Create((char*)PLAYER_BODY_PATH[nCntPlayer]);	// 生成

				// プレイヤーの情報の設定
				m_apModelPlayer[nCntPlayer]->SetPosition(PLAYER_POS[nCntPlayer]);	// 位置
				m_apModelPlayer[nCntPlayer]->SetRot(PLAYER_ROT[nCntPlayer]);		// 向き
				m_apModelPlayer[nCntPlayer]->SetMotion(5);							// モーション
			}
		}
	}
	else if (pPlayerManager == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CGameover::Uninit(void)
{
	
}

//===============================================
// 更新処理
//===============================================
void CGameover::Update(void)
{
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	// カメラをロケット付近へ移動



	// ゲームオーバーの表示

	CFade* pFade = CFade::GetInstance();

	if (pKeyboard->GetTrigger(DIK_RETURN) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{//ENTERキーが押されたら
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);	// ランキングに遷移
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CGameover::Draw(void)
{
	
}

//===============================================
// 設定処理
//===============================================
void CGameover::Set(const D3DXVECTOR3 pos, const bool bMove)
{
	
}