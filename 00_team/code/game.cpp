//*****************************************************
//
// ゲーム処理[game.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "manager.h"
#include "game.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputManager.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "scene.h"
#include "debugproc.h"
#include <stdio.h>
#include "UIManager.h"
#include "object3D.h"
#include "playerManager.h"
#include "texture.h"
#include "skybox.h"
#include "itemWeapon.h"
#include "itemRepair.h"
#include "weaponManager.h"
#include "enemyManager.h"
#include "rocket.h"
#include "edit.h"
#include "goal.h"
#include "block.h"
#include "container.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define TRANS_TIME	(60)	// 終了までの余韻のフレーム数

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CGame::STATE CGame::m_state = STATE_NONE;	// 状態
CGame *CGame::m_pGame = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CGame::CGame()
{
	m_nCntState = 0;
	m_bStop = false;
}

//=====================================================
// デストラクタ
//=====================================================
CGame::~CGame()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_state = STATE_NORMAL;
	m_bStop = false;

	// UIマネージャーの追加
	CUIManager::Create();

	CObject3D *pObject = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\field00.jpg");
	pObject->SetIdxTexture(nIdx);

	CSkybox::Create();

	// ブロックの読み込み
	CBlock::Load("data\\MAP\\map00.bin");

	// プレイヤーの生成
	CPlayerManager *pPlayerManger = CPlayerManager::GetInstance();

	if (pPlayerManger != nullptr)
	{
		pPlayerManger->CreatePlayer();
	}

	// 武器マネージャーの生成
	CWeaponManager::Create();

	// アイテム
	CItemWeapon *pItem = CItemWeapon::Create(CWeapon::TYPE_MAGNUM);
	pItem->SetPosition(D3DXVECTOR3(0.0f,0.0f,-40.0f));

	pItem = CItemWeapon::Create(CWeapon::TYPE_MACHINEGUN);
	pItem->SetPosition(D3DXVECTOR3(40.0f, 0.0f, -40.0f));

	// 修理アイテム
	CItemRepair *pRepair = CItemRepair::Create();
	pRepair->SetPosition(D3DXVECTOR3(40.0f, 0.0f, 300.0f));

	pRepair = CItemRepair::Create();
	pRepair->SetPosition(D3DXVECTOR3(-40.0f, 0.0f, 300.0f));

	pRepair = CItemRepair::Create();
	pRepair->SetPosition(D3DXVECTOR3(-200.0f, 0.0f, 300.0f));

	// 敵マネージャーの生成
	CEnemyManager *pEnemyManager = CEnemyManager::Create();

	// ロケットの生成
	CRocket::Create();

	// コンテナの生成
	CContainer *pContainer = CContainer::Create();
	pContainer->SetPosition(D3DXVECTOR3(200.0f, 0.0f, 0.0f));

#ifdef _DEBUG
	// エディットの生成
	CEdit::Create();
#endif

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CGame::Uninit(void)
{
	// オブジェクト全棄
	CObject::ReleaseAll();

	// ブロックの破棄
	CBlock::DeleteAll();

	// プレイヤーマネージャーの終了
	CPlayerManager *pPlayerManger = CPlayerManager::GetInstance();

	if (pPlayerManger != nullptr)
	{
		pPlayerManger->Uninit();
	}

	m_pGame = nullptr;
}

//=====================================================
// 更新処理
//=====================================================
void CGame::Update(void)
{
	CFade *pFade = CFade::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (m_bStop == false)
	{
		// シーンの更新
		CScene::Update();
	}
	else
	{
		// エディットの更新
		CEdit* pEdit = CEdit::GetInstatnce();
		pEdit->Update();
	}

	// カメラ更新
	UpdateCamera();

	// 状態管理
	ManageState();

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// カメラの更新
//=====================================================
void CGame::UpdateCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	if (m_bStop == false)
	{
		if (m_state == STATE_ESCAPE || m_state == STATE_RESULT)
		{
			pCamera->UpdateResult();
		}
	}
	else
	{
		// 操作
		pCamera->Control();
	}
}

//=====================================================
// 状態管理
//=====================================================
void CGame::ManageState(void)
{
	CFade *pFade = CFade::GetInstance();

	switch (m_state)
	{
	case CGame::STATE_NORMAL:
		break;
	case CGame::STATE_ESCAPE:

		m_nCntState++;

		if (m_nCntState >= TRANS_TIME)
		{
			m_nCntState = 0;
			SetState(STATE_RESULT);

			// ゴールでリザルトの表示
			CGoal *pGoal = CGoal::GetInstance();

			if (pGoal != nullptr)
			{
				pGoal->SetResult();
			}
		}

		break;
	case CGame::STATE_END:

		m_nCntState++;

		if (m_nCntState >= TRANS_TIME && pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// デバッグ処理
//=====================================================
void CGame::Debug(void)
{
	// 入力取得
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
	{
		return;
	}

	if (pKeyboard->GetTrigger(DIK_F))
	{
		m_bStop = m_bStop ? false : true;
	}

	if (pKeyboard->GetTrigger(DIK_G))
	{
		CItemRepair *pRepair = CItemRepair::Create();
		pRepair->SetPosition(D3DXVECTOR3(40.0f, 0.0f, 300.0f));
	}
}

//=====================================================
// 描画処理
//=====================================================
void CGame::Draw(void)
{
#ifndef _DEBUG

	return;

#endif

	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	char *apString[STATE::STATE_MAX] =
	{
		"NONE",
		"NORMAL",
		"ESCAPE",
		"RESULT",
		"END",
	};

	pDebugProc->Print("\nゲームの状態[%s]\n", apString[m_state]);
}