//*****************************************************
//
// タイトル処理[title.cpp]
// Author:酒井南勝
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "title.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "manager.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"

#include "object3D.h"
#include "objectX.h"

//*****************************************************
// マクロ定義
//*****************************************************

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const char* PLAYER_BODY_PATH[NUM_PLAYER] =
	{// 敵の体のパス
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman02.txt",
		"data\\MOTION\\motionPotatoman03.txt",
		"data\\MOTION\\motionPotatoman04.txt",
	};
	const D3DXVECTOR3 PLAYER_POS[NUM_PLAYER] =
	{// プレイヤーの位置
		D3DXVECTOR3(-100.0f, 0.0f, -200.0f),
		D3DXVECTOR3( -50.0f, 0.0f, -150.0f),
		D3DXVECTOR3(  50.0f, 0.0f, -150.0f),
		D3DXVECTOR3( 100.0f, 0.0f, -200.0f),
	};
	const D3DXVECTOR3 PLAYER_ROT[NUM_PLAYER] =
	{// プレイヤーの向き
		D3DXVECTOR3(0.0f, D3DX_PI * -0.25f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.10f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI *  0.10f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI *  0.25f, 0.0f),
	};
	const D3DXVECTOR3 PLAYER_ESC_MOVE = D3DXVECTOR3(0.0f, 0.0f, 8.0f);	// プレイヤーの逃げるときの移動量 
	const D3DXVECTOR3 PLAYER_ESC_ROT = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// プレイヤーの逃げるときの向き

	const char* ENEMY_BODY_PATH[ENEMY::NUM_ENEMY] =
	{// 敵の体のパス
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
	};
	const D3DXVECTOR3 ENEMY_POS[ENEMY::NUM_ENEMY] =
	{// 敵の位置
		D3DXVECTOR3(-250.0f, 0.0f, -600.0f),
		D3DXVECTOR3(-150.0f,  0.0f, -450.0f),
		D3DXVECTOR3(-90.0f,  0.0f, -850.0f),
		D3DXVECTOR3(-30.0f, 0.0f, -600.0f),
		D3DXVECTOR3( 40.0f, 0.0f, -800.0f),
		D3DXVECTOR3( 80.0f,  0.0f, -950.0f),
		D3DXVECTOR3( 120.0f,  0.0f, -750.0f),
		D3DXVECTOR3( 250.0f, 0.0f, -500.0f),
	};
	const D3DXVECTOR3 ENEMY_ROT = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// 敵の向き
	const D3DXVECTOR3 ENEMY_MOVE = D3DXVECTOR3(0.0f, 0.0f, 7.5f);	// 敵の移動量

	const float FIELD_WIDTH = 10000.0f;		// フィールドの幅
	const float FIELD_HEIGHT = 10000.0f;	// フィールドの高さ

	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f);	// ロゴの位置
	const float LOGO_WIDTH = 875.0f * 0.35f;	// ロゴの幅
	const float LOGO_HEIGHT = 320.0f * 0.35f;	// ロゴの高さ
	const char* LOGO_PATH = "data\\TEXTURE\\UI\\logo000.png";	// ロゴのパス

	const D3DXVECTOR3 STATE_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f);	// ロゴの位置
	const float START_WIDTH = 200.0f;	// スタート表示の幅
	const float START_HEIGHT = 50.0f;	// スタート表示の高さ
	const char* START_PATH = "data\\TEXTURE\\UI\\start.png";	// スタート表示のパス

	const float DEST_WIDTH = 500.0f;	// スタート表示の幅

	const int FADE_COUNT = 120;			// フェードまでの時間

	const float ALPHA_UPPER = 1.0f;			// α値の上限量
	const float ALPHA_LOWER = 0.25f;		// α値の下限量
	const float ALPHA_CHANGE = 0.1f;		// α値の変化量
	const float ALPHA_CHANGE_LOGO = 0.01f;	// α値の変化量
}

//=====================================================
// コンストラクタ
//=====================================================
CTitle::CTitle()
{
	m_state = STATE_NONE;
	m_pStart = nullptr;
	ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
	ZeroMemory(&m_apModelEnemy[0], sizeof(m_apModelEnemy));
	m_nFadeCnt = 0;
	m_bIsAlphaChange = false;
}

//=====================================================
// デストラクタ
//=====================================================
CTitle::~CTitle()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CTitle::Init(void)
{
	// 情報取得
	CCamera* pCamera = CManager::GetCamera();

	// カメラの設定
	pCamera->SetTitle();

	// ロゴの生成
	m_pLogo = CObject2D::Create(7);
	m_pLogo->SetSize(LOGO_WIDTH, LOGO_HEIGHT);
	m_pLogo->SetPosition(LOGO_POS);

	int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
	m_pLogo->SetIdxTexture(nIdx);
	m_pLogo->SetVtx();

	// スタート表示の生成
	m_pStart = CObject2D::Create(7);

	if (m_pStart != nullptr)
	{
		m_pStart->SetSize(START_WIDTH, START_HEIGHT);
		m_pStart->SetPosition(STATE_POS);

		int nIdx = CTexture::GetInstance()->Regist(START_PATH);
		m_pStart->SetIdxTexture(nIdx);
		m_pStart->SetVtx();
	}

	// 地面の生成
	CObject3D* pField = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pField->SetSize(FIELD_WIDTH, FIELD_HEIGHT);
	nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\field00.jpg");
	pField->SetIdxTexture(nIdx);

	// タイトルモデルの生成
	CObjectX* pTitleModel = CObjectX::Create();
	nIdx = CModel::Load("data\\MODEL\\title\\title_model.x");
	pTitleModel->BindModel(nIdx);

	// キャラクターの生成処理
	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		m_apModelPlayer[nCount] = CMotion::Create((char*)PLAYER_BODY_PATH[nCount]);

		m_apModelPlayer[nCount]->SetPosition(PLAYER_POS[nCount]);
		m_apModelPlayer[nCount]->SetRot(PLAYER_ROT[nCount]);
		m_apModelPlayer[nCount]->SetMotion(0);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CTitle::Uninit(void)
{
	// オブジェクト全破棄
	CObject::ReleaseAll();
}

//=====================================================
// 更新処理
//=====================================================
void CTitle::Update(void)
{
	// 情報取得
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	CCamera* pCamera = CManager::GetCamera();

	// シーンの更新
	CScene::Update();

	// カメラの更新
	UpdateCamera();

	if (m_state == STATE_NONE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr)
		{
			if (pKeyboard->GetTrigger(DIK_RETURN) ||
				pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
				pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
			{// フェード開始

				// フェード設定
				SetFadeIn();
			}
		}
	}
	else if (m_state == STATE_OUT)
	{
		// フェード更新処理
		UpdateFade();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CTitle::Draw(void)
{

}

//=====================================================
// スタート表示の管理
//=====================================================
void CTitle::ManageStart(void)
{
	if (m_pStart == nullptr)
	{
		return;
	}

	// 色の情報取得
	D3DXCOLOR colStart = m_pStart->GetCol();
	D3DXCOLOR colLogo = m_pLogo->GetCol();

	if (m_bIsAlphaChange == false)
	{
		colStart.a -= ALPHA_CHANGE;
	}
	else if (m_bIsAlphaChange == true)
	{
		colStart.a += ALPHA_CHANGE;
	}

	if (colStart.a <= ALPHA_LOWER)
	{
		m_bIsAlphaChange = true;
	}
	else if (colStart.a >= ALPHA_UPPER)
	{
		m_bIsAlphaChange = false;
	}

	if (colLogo.a >= 0.0f)
	{
		// ロゴのα値を減少
		colLogo.a -= ALPHA_CHANGE_LOGO;
	}

	// 設定処理
	m_pStart->SetCol(colStart);
	m_pStart->SetVtx();
	m_pLogo->SetCol(colLogo);
	m_pLogo->SetVtx();

}

//=====================================================
// フェードの更新処理
//=====================================================
void CTitle::UpdateFade(void)
{
	// 情報取得
	CFade* pFade = CFade::GetInstance();

	// スタート表示の管理
	ManageStart();

	// フェードカウント進める
	m_nFadeCnt++;

	// プレイヤーの設定処理
	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		D3DXVECTOR3 posPlayer = m_apModelPlayer[nCount]->GetPosition();
		m_apModelPlayer[nCount]->SetPosition(posPlayer + PLAYER_ESC_MOVE);
		m_apModelPlayer[nCount]->SetRot(PLAYER_ESC_ROT);
	}

	// 敵の設定処理
	for (int nCount = 0; nCount < ENEMY::NUM_ENEMY; nCount++)
	{
		D3DXVECTOR3 posEnemy = m_apModelEnemy[nCount]->GetPosition();
		m_apModelEnemy[nCount]->SetPosition(posEnemy + ENEMY_MOVE);
	}

	if (m_nFadeCnt == FADE_COUNT)
	{
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_SELECT);
		}
	}
}

//=====================================================
// カメラの更新処理
//=====================================================
void CTitle::UpdateCamera(void)
{
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	if (m_state == STATE_NONE)
	{
		// タイトルのカメラ更新
		pCamera->UpdateTitle();
	}
	else if (m_state == STATE_OUT)
	{
		// タイトルの逃げるときのカメラ更新
		pCamera->UpdateTitleEsc();
	}
}

//=====================================================
// フェード設定
//=====================================================
void CTitle::SetFadeIn(void)
{
	// 情報取得
	CCamera* pCamera = CManager::GetCamera();

	// フェードアウトに設定
	m_state = STATE_OUT;

	// カメラの逃げるとき設定
	pCamera->SetTitleEsc();

	// プレイヤーのモーション設定処理（移動）
	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		m_apModelPlayer[nCount]->SetMotion(1);
	}

	// 敵の生成処理
	for (int nCount = 0; nCount < ENEMY::NUM_ENEMY; nCount++)
	{
		m_apModelEnemy[nCount] = CMotion::Create((char*)ENEMY_BODY_PATH[nCount]);

		m_apModelEnemy[nCount]->SetPosition(ENEMY_POS[nCount]);
		m_apModelEnemy[nCount]->SetRot(ENEMY_ROT);
		m_apModelEnemy[nCount]->SetMotion(1);
	}
}