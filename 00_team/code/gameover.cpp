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
#include "camera.h"
#include "manager.h"
#include "goalTimer.h"
#include "UIManager.h"
#include "goal.h"
#include "texture.h"
#include "game.h"

//===============================================
// 定数定義
//===============================================
namespace
{
	// プレイヤーの体のパス
	const char* PLAYER_BODY_PATH[NUM_PLAYER] =
	{
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman02.txt",
		"data\\MOTION\\motionPotatoman03.txt",
		"data\\MOTION\\motionPotatoman04.txt"
	};

	// プレイヤーの位置
	const D3DXVECTOR3 PLAYER_POS[NUM_PLAYER] =
	{
		D3DXVECTOR3(150.0f, 0.0f, 100.0f),
		D3DXVECTOR3(200.0f, 0.0f, 100.0f),
		D3DXVECTOR3(250.0f, 0.0f, 100.0f),
		D3DXVECTOR3(100.0f, 0.0f, 100.0f)
	};

	// プレイヤーの向き
	const D3DXVECTOR3 PLAYER_ROT[NUM_PLAYER] =
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.15f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.15f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.10f, 0.0f)
	};

	// 敵の体のパス
	const char* ENEMY_BODY_PATH = "data\\MOTION\\motionEnemy00.txt";

	// 敵の位置
	const D3DXVECTOR3 ENEMY_POS[NUM_ENEMY] =
	{
		D3DXVECTOR3(170.0f, 0.0f, 200.0f),
	};

	// 敵の向き
	const D3DXVECTOR3 ENEMY_ROT[NUM_ENEMY] =
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
	};

	// 視点カメラの位置
	const D3DXVECTOR3 CAMERA_POSV = D3DXVECTOR3(170.0f, 120.0f, -50.0f);

	// 注視点カメラの位置
	const D3DXVECTOR3 CAMERA_POSR = D3DXVECTOR3(170.0f, -50.0f, 300.0f);

	// ゲームオーバーのテクスチャのパス
	const char* LOGO_PATH = "data\\TEXTURE\\UI\\start_game.png";

	// ゲームオーバーの横幅
	const float LOGO_WIDTH = 300.0f;

	// ゲームオーバーの縦幅
	const float LOGO_HEIGHT = 100.0f;

	// ゲームオーバーの位置
	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f);
}

//===============================================
// 静的メンバ変数宣言
//===============================================
CGameover* CGameover::m_pGameover = nullptr;	// 自身のポインタ

//===============================================
// コンストラクタ
//===============================================
CGameover::CGameover()
{
	// 値のクリア
	ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
	ZeroMemory(&m_apModelEnemy[0], sizeof(m_apModelEnemy));
	m_pLogo = nullptr;
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
	if (m_pGameover == nullptr)
	{
		// ゲームオーバーの生成
		m_pGameover = new CGameover;

		if (m_pGameover != nullptr)
		{
			// 初期化処理
			m_pGameover->Init();
		}
		else if (m_pGameover == nullptr)
		{
			return nullptr;
		}
	}

	return m_pGameover;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CGameover::Init()
{
	// インスタンスを取得
	CEnemyManager* pEnemyManager = CEnemyManager::GetInstance();
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();
	CGame* pGame = CGame::GetInstance();

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

		// ゲームオーバー状態にして敵のスポーンを停止する
		if (pGame != nullptr)
		{
			pGame->SetState(CGame::STATE_GAMEOVER);
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
	m_pGameover = nullptr;

	delete this;
}

//===============================================
// 更新処理
//===============================================
void CGameover::Update(void)
{
	// インスタンスを取得
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();
	CCamera* pCamera = CManager::GetCamera();
	CGoalTimer* pGoalTimer = CGoalTimer::GetInstance();
	CUIManager* pUIManager = CUIManager::GetInstance();
	CGoal* pGoal = CGoal::GetInstance();

	// UIを非表示
	if (pUIManager != nullptr)
	{
		pUIManager->EnableDisp(false);
	}
	if (pGoal != nullptr)
	{
		pGoal->Uninit();
	}

	// カメラをロケット付近へ移動
	if (pCamera != nullptr)
	{
		// カメラの設定
		pCamera->UpdateGameover(CAMERA_POSV, CAMERA_POSR);
	}

	// ゲームオーバーの表示
	if (m_pLogo == nullptr)
	{
		m_pLogo = CObject2D::Create(7);
	}

	if (m_pLogo != nullptr)
	{
		m_pLogo->SetSize(LOGO_WIDTH, LOGO_HEIGHT);
		m_pLogo->SetPosition(LOGO_POS);
		int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
		m_pLogo->SetIdxTexture(nIdx);
		m_pLogo->SetVtx();
	}

	CFade* pFade = CFade::GetInstance();

	if (pKeyboard->GetTrigger(DIK_RETURN) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{//ENTERキーが押されたら
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);	// ランキングに遷移

			// プレイヤーマネージャーの終了
			CPlayerManager *pPlayerManger = CPlayerManager::GetInstance();

			if (pPlayerManger != nullptr)
			{
				pPlayerManger->Uninit();
			}
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CGameover::Draw(void)
{
	
}