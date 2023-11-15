//*****************************************************
//
// タイトル処理[title.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "select.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "manager.h"
#include "motion.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"

#include "playerManager.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define LOGO_PATH	"data\\TEXTURE\\UI\\logo000.png"	// ロゴのパス
#define START_WIDTH	(200.0f)	// スタート表示の幅
#define START_HEIGHT	(50.0f)	// スタート表示の高さ
#define DEST_WIDTH	(500.0f)	// スタート表示の幅
#define CHANGE_FACT	(0.1f)	// 変化する係数
#define ALPHA_CHANGE	(0.05f)	// α値の変化量

#define NUMBER_POS	(D3DXVECTOR2(300.0f, 600.0f))
#define SPACE	(220.0f)

//=====================================================
// コンストラクタ
//=====================================================
CSelect::CSelect()
{
	for (int nCntFirst = 0; nCntFirst < NUM_PLAYER; nCntFirst++)
	{
		for (int nCntSecond = 0; nCntSecond < MENU_MAX; nCntSecond++)
		{
			m_aMenuData[nCntFirst].pMenu2D[nCntSecond] = nullptr;
		}
		m_aMenuData[nCntFirst].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		bJoin[nCntFirst] = false;
	}
	m_pPlayerManager = nullptr;
	m_pStart = nullptr;
	m_state = STATE_NONE;
}

//=====================================================
// デストラクタ
//=====================================================
CSelect::~CSelect()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CSelect::Init(void)
{
	// ロゴの生成
	/*CObject2D *pObject2D = CObject2D::Create(7);
	pObject2D->SetSize(875.0f * 0.45f, 320.0f * 0.45f);
	pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.7f, 200.0f, 0.0f));

	int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
	pObject2D->SetIdxTexture(nIdx);
	pObject2D->SetVtx();*/

	// プレイヤーマネージャーの生成
	m_pPlayerManager = CPlayerManager::Create();

	MenuInit();

	return S_OK;
}

//=====================================================
// メニューの初期化処理
//=====================================================
void CSelect::MenuInit(void)
{
	//人数分の選択メニューを生成
	int aIdx[NUM_PLAYER] = {};

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME] = CObject2D::Create(6);
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER] = CObject2D::Create(7);

		//メニュー枠
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetPosition(D3DXVECTOR3(NUMBER_POS.x + (nCnt * SPACE), NUMBER_POS.y, 0.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetSize(80.0f, 80.0f);
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetIdxTexture(CTexture::GetInstance()->Regist("frame.png"));

		//メニュー文字
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetPosition(D3DXVECTOR3(NUMBER_POS.x + (nCnt * SPACE), NUMBER_POS.y, 0.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetSize(50.0f, 50.0f);
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

		switch (nCnt)
		{
		case 0:
			aIdx[nCnt] = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\1st.png");
			m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(aIdx[nCnt]);
			break;
		case 1:
			aIdx[nCnt] = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\2nd.png");
			m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(aIdx[nCnt]);
			break;
		case 2:
			aIdx[nCnt] = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\3rd.png");
			m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(aIdx[nCnt]);
			break;
		case 3:
			aIdx[nCnt] = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\4th.png");
			m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(aIdx[nCnt]);
			break;

		default:
			break;
		}

		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetVtx();
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetVtx();
	}
}

//=====================================================
// 終了処理
//=====================================================
void CSelect::Uninit(void)
{
	// オブジェクト全破棄
	CObject::ReleaseAll();
}

//=====================================================
// 更新処理
//=====================================================
void CSelect::Update(void)
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
				pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0))
			{// フェード
				if (pFade != nullptr)
				{
					pFade->SetFade(CScene::MODE_GAME);
				}
			}
		}

		MenuUpdate();
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
void CSelect::ManageStart(void)
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
// 更新
//=====================================================
void CSelect::MenuUpdate(void)
{
	// 情報取得
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		if (pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, nCntPlayer))
		{
			if (bJoin[nCntPlayer] == true)
			{
				continue;
			}

			bJoin[nCntPlayer] = true;

			if (m_pPlayerManager != nullptr)
			{
				m_pPlayerManager->CreatePlayer1(nCntPlayer);
			}
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CSelect::Draw(void)
{

}