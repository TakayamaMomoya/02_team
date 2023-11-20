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
	const char* BODY_PATH[NUM_PLAYER] =
	{// 体のパス
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
		D3DXVECTOR3(0.0f, D3DX_PI * 0.10f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f),
	};

	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f);	// ロゴの位置
	const float LOGO_WIDTH = 875.0f * 0.35f;	// ロゴの幅
	const float LOGO_HEIGHT = 320.0f * 0.35f;	// ロゴの高さ
	const char* LOGO_PATH = "data\\TEXTURE\\UI\\logo000.png";	// ロゴのパス

	const D3DXVECTOR3 STATE_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f);	// ロゴの位置
	const float START_WIDTH = 200.0f;	// スタート表示の幅
	const float START_HEIGHT = 50.0f;	// スタート表示の高さ
	const char* START_PATH = "data\\TEXTURE\\UI\\start.png";	// スタート表示のパス

	const float DEST_WIDTH = 500.0f;	// スタート表示の幅
	const float CHANGE_FACT = 0.1f;		// 変化する係数
	const float ALPHA_CHANGE = 0.05f;	// α値の変化量
}

//=====================================================
// コンストラクタ
//=====================================================
CTitle::CTitle()
{
	m_pStart = nullptr;
	ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
	m_state = STATE_NONE;
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
	CObject2D *pLogo = CObject2D::Create(7);
	pLogo->SetSize(LOGO_WIDTH, LOGO_HEIGHT);
	pLogo->SetPosition(LOGO_POS);

	int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
	pLogo->SetIdxTexture(nIdx);
	pLogo->SetVtx();

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
	nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\field00.jpg");
	pField->SetIdxTexture(nIdx);

	// タイトルモデルの生成
	CObjectX* pTitleModel = CObjectX::Create();
	nIdx = CModel::Load("data\\MODEL\\title\\title_model.x");
	pTitleModel->BindModel(nIdx);

	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		// キャラクターの生成処理
		m_apModelPlayer[nCount] = CMotion::Create((char*)BODY_PATH[nCount]);

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
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	CCamera *pCamera = CManager::GetCamera();

	// シーンの更新
	CScene::Update();
	
	CFade *pFade = CFade::GetInstance();

	if (m_state == STATE_NONE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr)
		{
			if (pKeyboard->GetTrigger(DIK_RETURN) ||
				pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
				pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
			{// フェード
				if (pFade != nullptr)
				{
					pFade->SetFade(CScene::MODE_SELECT);
				}
			}
		}
	}
	else if(m_state == STATE_OUT)
	{
		// スタート表示の管理
		ManageStart();
	}
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

	float fWidth = m_pStart->GetWidth();
	float fHeight = m_pStart->GetHeight();
	float fDiffWidth;
	float fDiffHeight;

	// 減少分の計算
	fDiffWidth = (DEST_WIDTH - fWidth) * CHANGE_FACT;
	fDiffHeight = (0.0f - fHeight) * CHANGE_FACT;

	// 透明にする
	D3DXCOLOR col = m_pStart->GetCol();

	col.a -= ALPHA_CHANGE;

	if (col.a <= 0.0f)
	{
		col.a = 0.0f;
	}

	m_pStart->SetCol(col);

	// サイズ設定
	m_pStart->SetSize(fWidth + fDiffWidth, fHeight + fDiffHeight);
	m_pStart->SetVtx();
}

//=====================================================
// 描画処理
//=====================================================
void CTitle::Draw(void)
{

}