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
	char *apPath[NUM_PLAYER] =
	{
		"data\\TEXTURE\\UI\\1st.png",
		"data\\TEXTURE\\UI\\2nd.png",
		"data\\TEXTURE\\UI\\3rd.png",
		"data\\TEXTURE\\UI\\4th.png",
	};

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME] = CObject2D::Create(6);
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER] = CObject2D::Create(7);

		// メニュー枠
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetPosition(D3DXVECTOR3(NUMBER_POS.x + (nCnt * SPACE), NUMBER_POS.y, 0.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetSize(80.0f, 80.0f);
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetIdxTexture(CTexture::GetInstance()->Regist("frame.png"));

		// メニュー文字
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetPosition(D3DXVECTOR3(NUMBER_POS.x + (nCnt * SPACE), NUMBER_POS.y, 0.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetSize(50.0f, 50.0f);
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

		int nIdx = CTexture::GetInstance()->Regist(apPath[nCnt]);
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(nIdx);

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

	}
}

//=====================================================
// 更新
//=====================================================
void CSelect::MenuUpdate(void)
{
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
				m_pPlayerManager->CreateOnePlayer(nCntPlayer);
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