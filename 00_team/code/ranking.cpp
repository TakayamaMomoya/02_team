//*****************************************************
//
// ランキングの処理[Ranking.cpp]
// Author:酒井南勝
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************

#include "ranking.h"
#include "main.h"

#include "manager.h"
#include "camera.h"
#include "record.h"

#include "object2D.h"
#include "number.h"

#include "object3D.h"
#include "motion.h"

#include "texture.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "inputmouse.h"

#include "fade.h"

//*****************************************************
// マクロ定義
//*****************************************************

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	// 戦績文
	const D3DXVECTOR3 RECORD_TEXT_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.15f, 0.0f);	// 戦績文の位置
	const float RECORD_TEXT_SIZE = 250.0f;										// 戦績文の大きさ
	const float RECORD_TEXT_WIDTH = 1.0f * RECORD_TEXT_SIZE;					// 戦績文の幅
	const float RECORD_TEXT_HEIGHT = 0.2f * RECORD_TEXT_SIZE;					// 戦績文の高さ
	const char* RECORD_TEXT_TEX = "data\\TEXTURE\\UI\\renk_text_record.png";	// 戦績文のパス

	// 戦績種類アイコン
	const D3DXVECTOR3 GENRE_ICON_POS[CRecord::GENRE_TYPE_MAX] =
	{// 位置[種類]
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.55f, 0.0f),
	};
	const float GENRE_ICON_SIZE[CRecord::GENRE_TYPE_MAX] =
	{// 大きさ[種類]
		250.0f,
	};
	const float GENRE_ICON_WIDTH[CRecord::GENRE_TYPE_MAX] =
	{// 横幅[種類]
		0.5f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const float GENRE_ICON_HEIGHT[CRecord::GENRE_TYPE_MAX] =
	{// 縦幅[種類]
		0.4f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const char* GENRE_ICON_TEX[CRecord::GENRE_TYPE_MAX] =
	{// テクスチャのパス[種類]
		"data\\TEXTURE\\UI\\Icon_destroyer.png",
	};

	// 戦績種類文
	const D3DXVECTOR3 GENRE_TEXT_POS[CRecord::GENRE_TYPE_MAX] =
	{// 位置[種類]
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.35f, 0.0f),
	};
	const float GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_MAX] =
	{// 大きさ[種類]
		175.0f,
	};
	const float GENRE_TEXT_WIDTH[CRecord::GENRE_TYPE_MAX] =
	{// 横幅[種類]
		1.0f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const float GENRE_TEXT_HEIGHT[CRecord::GENRE_TYPE_MAX] =
	{// 縦幅[種類]
		0.2f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const char* GENRE_TEXT_TEX[CRecord::GENRE_TYPE_MAX] =
	{// テクスチャのパス[種類]
		"data\\TEXTURE\\UI\\rank_text_destroyer.png",
	};

	// 顔表示
	const D3DXVECTOR3 FACE_POS[NUM_PLAYER] =
	{// 位置[プレイヤー番号]
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.3f,  0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.425f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.550f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.675f,0.0f),
	};
	const float FACE_SIZE = 70.0f;
	const float FACE_WIDTH = 0.5f * FACE_SIZE;
	const float FACE_HEIGHT = 0.6f * FACE_SIZE;
	const char* FACE_FILE_NAME[NUM_PLAYER] =
	{// ファイル名 [プレイヤー番号]
		"data\\TEXTURE\\UI\\player01.png",
		"data\\TEXTURE\\UI\\player02.png",
		"data\\TEXTURE\\UI\\player03.png",
		"data\\TEXTURE\\UI\\player04.png",
	};

	// 数字
	const D3DXVECTOR3 NUMBER_POS[NUM_PLAYER] =
	{// 位置[プレイヤー番号]
		D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.3f,  0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.425f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.550f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.675f,0.0f),
	};
	const float NUMBER_SIZE = 25.0f;
	const float NUMBER_WIDTH = 1.0f * NUMBER_SIZE;
	const float NUMBER_HEIGHT = 1.0f * NUMBER_SIZE;
	const char* NUMBER_TEX = nullptr;

	// フィールド
	const float FIELD_WIDTH = 1000.0f;		// フィールドの幅
	const float FIELD_HEIGHT = 500.0f;	// フィールドの高さ
	const char* FIELD_FILE_NAME = "data\\TEXTURE\\MATERIAL\\WodenWall_00.jpg";	// 戦績文のパス

	const D3DXVECTOR3 CAMERA_POS_V = D3DXVECTOR3(0.0f, 200.0f, -800.0f);
	const D3DXVECTOR3 CAMERA_POS_R = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	const D3DXVECTOR3 CAMERA_MOVE = D3DXVECTOR3(0.0f, 0.0f, 7.0f);

	// プレイヤーの生成処理
	const char* PLAYER_BODY_PATH[NUM_PLAYER] =
	{// 敵の体のパス
		"data\\MOTION\\motionTitle01.txt",
		"data\\MOTION\\motionTitle02.txt",
		"data\\MOTION\\motionTitle03.txt",
		"data\\MOTION\\motionTitle04.txt",
	};
	const D3DXVECTOR3 PLAYER_POS[NUM_PLAYER] =
	{// プレイヤーの位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	};
	const D3DXVECTOR3 PLAYER_ROT[NUM_PLAYER] =
	{// プレイヤーの向き
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	};
	const D3DXVECTOR3 PLAYER_ESC_MOVE = D3DXVECTOR3(0.0f, 0.0f, 8.0f);		// プレイヤーの逃げるときの移動量 
	const D3DXVECTOR3 PLAYER_ESC_ROT = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// プレイヤーの逃げるときの向き
}

//=====================================================
// コンストラクタ
//=====================================================
CRanking::CRanking()
{
	m_infoVisualUi = {};
	m_infoVisualObj = {};
}

//=====================================================
// デストラクタ
//=====================================================
CRanking::~CRanking()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CRanking::Init(void)
{
	// UIの初期化処理
	if (InitUi() != S_OK)
	{
		return E_FAIL;
	}
	
	// オブジェクトの初期化処理
	if (InitObj() != S_OK)
	{
		return E_FAIL;
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CRanking::Uninit(void)
{
	// 戦績の終了処理
	CRecord* pRecord = CRecord::GetInstance();

	if (pRecord != nullptr)
	{
		pRecord->Uninit();
	}

	CObject::ReleaseAll();
}

//=====================================================
// 更新処理
//=====================================================
void CRanking::Update(void)
{
	// 入力情報取得
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	CFade *pFade = CFade::GetInstance();

	// シーンの更新
	CScene::Update();

	// 画面遷移==========================================
	if (pKeyboard->GetTrigger(DIK_RETURN) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{//ENTERキーが押されたら
		//タイトルに移行
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_TITLE);
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CRanking::Draw(void)
{

}

//=====================================================
// UIの初期化処理
//=====================================================
HRESULT CRanking::InitUi(void)
{
	// テクスチャのポインタを取得
	CTexture* pTexture = CTexture::GetInstance();

	// 戦績のポインタを取得
	CRecord* pRecord = CRecord::GetInstance();

	// レコードテキストの生成
	m_infoVisualUi.pRecordText = CObject2D::Create(7);

	if (m_infoVisualUi.pRecordText != nullptr)
	{
		m_infoVisualUi.pRecordText->SetPosition(RECORD_TEXT_POS);
		m_infoVisualUi.pRecordText->SetSize(RECORD_TEXT_WIDTH, RECORD_TEXT_HEIGHT);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(RECORD_TEXT_TEX);
			m_infoVisualUi.pRecordText->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pRecordText->SetVtx();
	}
	if (m_infoVisualUi.pRecordText == nullptr)
	{
		return E_FAIL;
	}

	// 種類アイコンの生成
	m_infoVisualUi.pGenreIcon = CObject2D::Create(7);

	if (m_infoVisualUi.pGenreIcon != nullptr)
	{
		m_infoVisualUi.pGenreIcon->SetPosition(GENRE_ICON_POS[CRecord::GENRE_TYPE_DESTROY]);
		m_infoVisualUi.pGenreIcon->SetSize(GENRE_ICON_WIDTH[CRecord::GENRE_TYPE_DESTROY], GENRE_ICON_HEIGHT[CRecord::GENRE_TYPE_DESTROY]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_ICON_TEX[CRecord::GENRE_TYPE_DESTROY]);
			m_infoVisualUi.pGenreIcon->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pGenreIcon->SetVtx();
	}
	if (m_infoVisualUi.pGenreIcon == nullptr)
	{
		return E_FAIL;
	}

	// 種類のテキストの生成
	m_infoVisualUi.pGenreText = CObject2D::Create(7);

	if (m_infoVisualUi.pGenreText != nullptr)
	{
		m_infoVisualUi.pGenreText->SetPosition(GENRE_TEXT_POS[CRecord::GENRE_TYPE_DESTROY]);
		m_infoVisualUi.pGenreText->SetSize(GENRE_TEXT_WIDTH[CRecord::GENRE_TYPE_DESTROY], GENRE_TEXT_HEIGHT[CRecord::GENRE_TYPE_DESTROY]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_TEXT_TEX[CRecord::GENRE_TYPE_DESTROY]);
			m_infoVisualUi.pGenreText->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pGenreText->SetVtx();
	}
	if (m_infoVisualUi.pGenreText == nullptr)
	{
		return E_FAIL;
	}

	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		// プレイヤー顔の生成
		m_infoVisualUi.apFace[nCount] = CObject2D::Create(7);

		if (m_infoVisualUi.apFace[nCount] != nullptr)
		{
			m_infoVisualUi.apFace[nCount]->SetPosition(FACE_POS[nCount]);
			m_infoVisualUi.apFace[nCount]->SetSize(FACE_WIDTH, FACE_HEIGHT);

			if (pTexture != nullptr)
			{
				int nIdx = pTexture->Regist(FACE_FILE_NAME[nCount]);
				m_infoVisualUi.apFace[nCount]->SetIdxTexture(nIdx);
			}

			m_infoVisualUi.apFace[nCount]->SetVtx();
		}
		if (m_infoVisualUi.apFace[nCount] == nullptr)
		{
			return E_FAIL;
		}

		// 数字の生成
		m_infoVisualUi.apNumber[nCount] = CNumber::Create(4, 0);

		if (m_infoVisualUi.apNumber[nCount] != nullptr)
		{
			m_infoVisualUi.apNumber[nCount]->SetPosition(NUMBER_POS[nCount]);
			m_infoVisualUi.apNumber[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_WIDTH);

			if (pRecord != nullptr)
			{
				m_infoVisualUi.apNumber[nCount]->SetValue(pRecord->GetDestroy(nCount), 4);
			}

			if (pTexture != nullptr)
			{
				//int nIdx = pTexture->Regist();
				//m_infoVisualUi.apNumber[nCount]->SetIdxTexture(nIdx);
				//m_infoVisualUi.apNumber[nCount]->SetVtx();
			}
		}
		if (m_infoVisualUi.apNumber[nCount] == nullptr)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=====================================================
// オブジェクトの初期化処理
//=====================================================
HRESULT CRanking::InitObj(void)
{
	// 情報取得
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		// ランキングの設定
		pCamera->SetRanking();
	}
	else if (pCamera == nullptr)
	{
		return E_FAIL;
	}

	// 地面の生成
	m_infoVisualObj.pField = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (m_infoVisualObj.pField != nullptr)
	{
		m_infoVisualObj.pField->SetSize(FIELD_WIDTH, FIELD_HEIGHT);
		int nIdx = CTexture::GetInstance()->Regist(FIELD_FILE_NAME);
		m_infoVisualObj.pField->SetIdxTexture(nIdx);
	}
	else if (m_infoVisualObj.pField == nullptr)
	{
		return E_FAIL;
	}

	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		m_infoVisualObj.apModelPlayer[nCount] = CMotion::Create((char*)PLAYER_BODY_PATH[nCount]);

		if (m_infoVisualObj.apModelPlayer[nCount] != nullptr)
		{
			m_infoVisualObj.apModelPlayer[nCount]->SetPosition(PLAYER_POS[nCount]);
			m_infoVisualObj.apModelPlayer[nCount]->SetRot(PLAYER_ROT[nCount]);
			m_infoVisualObj.apModelPlayer[nCount]->SetMotion(0);
		}
		else if (m_infoVisualObj.apModelPlayer[nCount] == nullptr)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}