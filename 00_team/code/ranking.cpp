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

#include "object2D.h"
#include "number.h"
#include "record.h"

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
	const D3DXVECTOR3 RECORD_TEXT_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f);	// 戦績文の位置
	const float RECORD_TEXT_SIZE = 200.0f;								// 戦績文の大きさ
	const float RECORD_TEXT_WIDTH = 1.0f * RECORD_TEXT_SIZE;			// 戦績文の幅
	const float RECORD_TEXT_HEIGHT = 0.2f * RECORD_TEXT_SIZE;			// 戦績文の高さ
	const char* RECORD_TEXT_TEX = "data\\TEXTURE\\UI\\gamestart.png";	// 戦績文のパス

	// 戦績種類アイコン
	const D3DXVECTOR3 GENRE_ICON_POS[CRecord::GENRE_TYPE_MAX] =
	{// 位置[種類]
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, 0.0f),
	};
	const float GENRE_ICON_SIZE[NUM_PLAYER] =
	{// 大きさ[種類]
		250.0f,
	};
	const float GENRE_ICON_WIDTH[NUM_PLAYER] =
	{// 横幅[種類]
		1.0f * GENRE_ICON_SIZE[NUM_PLAYER],
	};
	const float GENRE_ICON_HEIGHT[NUM_PLAYER] =
	{// 縦幅[種類]
		0.2f * GENRE_ICON_SIZE[NUM_PLAYER],
	};
	const char* GENRE_ICON_TEX[NUM_PLAYER] =
	{// テクスチャのパス[種類]
		"data\\TEXTURE\\UI\\GenreIcon000",
	};

	// 戦績種類文
	const D3DXVECTOR3 GENRE_TEXT_POS[CRecord::GENRE_TYPE_MAX] =
	{// 位置[種類]
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.3f, 0.0f),
	};
	const float GENRE_TEXT_SIZE[NUM_PLAYER] =
	{// 大きさ[種類]
		250.0f,
	};
	const float GENRE_TEXT_WIDTH[NUM_PLAYER] =
	{// 横幅[種類]
		1.0f * GENRE_TEXT_SIZE[NUM_PLAYER],
	};
	const float GENRE_TEXT_HEIGHT[NUM_PLAYER] =
	{// 縦幅[種類]
		0.2f * GENRE_TEXT_SIZE[NUM_PLAYER],
	};
	const char* GENRE_TEXT_TEX[NUM_PLAYER] =
	{// テクスチャのパス[種類]
		"data\\TEXTURE\\UI\\GenreIcon000",
	};

	// 顔表示
	const D3DXVECTOR3 FACE_POS[NUM_PLAYER] =
	{// 位置[プレイヤー番号]
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.85f, 0.0f),
	};
	const float FACE_SIZE[NUM_PLAYER] =
	{// 大きさ[プレイヤー番号]
		250.0f,
		250.0f,
		250.0f,
		250.0f,
	};
	const float FACE_WIDTH[NUM_PLAYER] =
	{// 横幅[プレイヤー番号]
		1.0f * FACE_SIZE[NUM_PLAYER],
		1.0f * FACE_SIZE[NUM_PLAYER],
		1.0f * FACE_SIZE[NUM_PLAYER],
		1.0f * FACE_SIZE[NUM_PLAYER],
	};
	const float FACE_HEIGHT[NUM_PLAYER] =
	{// 縦幅[プレイヤー番号]
		0.2f * FACE_SIZE[NUM_PLAYER],
		0.2f * FACE_SIZE[NUM_PLAYER],
		0.2f * FACE_SIZE[NUM_PLAYER],
		0.2f * FACE_SIZE[NUM_PLAYER],
	};
	const char* FACE_TEX[NUM_PLAYER] =
	{// テクスチャのパス[プレイヤー番号]
		"data\\TEXTURE\\UI\\GenreIcon000",
		"data\\TEXTURE\\UI\\GenreIcon000",
		"data\\TEXTURE\\UI\\GenreIcon000",
		"data\\TEXTURE\\UI\\GenreIcon000",
	};

	// 数字
	const D3DXVECTOR3 NUMBER_POS[NUM_PLAYER] =
	{// 位置[プレイヤー番号]
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.50f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.60f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.70f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.80f, 0.0f),
	};
	const float NUMBER_SIZE = 25.0f;
	const float NUMBER_WIDTH = 1.0f * NUMBER_SIZE;
	const float NUMBER_HEIGHT = 1.0f * NUMBER_SIZE;
	const char* NUMBER_TEX = "data\\TEXTURE\\UI\\GenreIcon000";
}

//=====================================================
// コンストラクタ
//=====================================================
CRanking::CRanking()
{
	m_infoVisual = {};
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
	// テクスチャのポインタを取得
	//CTexture* pTexture = CTexture::GetInstance();
	CTexture* pTexture = nullptr;

	// レコードテキストの生成
	m_infoVisual.pRecordText = CObject2D::Create(7);

	if (m_infoVisual.pRecordText != nullptr)
	{
		m_infoVisual.pRecordText->SetPosition(RECORD_TEXT_POS);
		m_infoVisual.pRecordText->SetSize(RECORD_TEXT_WIDTH,RECORD_TEXT_HEIGHT);
		
		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(RECORD_TEXT_TEX);
			m_infoVisual.pRecordText->SetIdxTexture(nIdx);
			m_infoVisual.pRecordText->SetVtx();
		}

		m_infoVisual.pRecordText->SetVtx();
	}
	if (m_infoVisual.pRecordText == nullptr)
	{
		return E_FAIL;
	}

	// 種類アイコンの生成
	m_infoVisual.pGenreIcon = CObject2D::Create(7);

	if (m_infoVisual.pGenreIcon != nullptr)
	{
		m_infoVisual.pGenreIcon->SetPosition(GENRE_ICON_POS[CRecord::GENRE_TYPE_DESTROY]);
		m_infoVisual.pGenreIcon->SetSize(GENRE_ICON_WIDTH[CRecord::GENRE_TYPE_DESTROY],GENRE_ICON_HEIGHT[CRecord::GENRE_TYPE_DESTROY]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_ICON_TEX[CRecord::GENRE_TYPE_DESTROY]);
			m_infoVisual.pGenreIcon->SetIdxTexture(nIdx);
			m_infoVisual.pGenreIcon->SetVtx();
		}

		m_infoVisual.pGenreIcon->SetVtx();
	}
	if (m_infoVisual.pGenreIcon == nullptr)
	{
		return E_FAIL;
	}

	// 種類のテキストの生成
	m_infoVisual.pGenreText = CObject2D::Create(7);

	if (m_infoVisual.pGenreText != nullptr)
	{
		m_infoVisual.pGenreText->SetPosition(GENRE_TEXT_POS[CRecord::GENRE_TYPE_DESTROY]);
		m_infoVisual.pGenreText->SetSize(GENRE_TEXT_WIDTH[CRecord::GENRE_TYPE_DESTROY],GENRE_TEXT_HEIGHT[CRecord::GENRE_TYPE_DESTROY]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_TEXT_TEX[CRecord::GENRE_TYPE_DESTROY]);
			m_infoVisual.pGenreText->SetIdxTexture(nIdx);
			m_infoVisual.pGenreText->SetVtx();
		}

		m_infoVisual.pGenreText->SetVtx();
	}
	if (m_infoVisual.pGenreText == nullptr)
	{
		return E_FAIL;

	}

	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		// プレイヤー顔の生成
		m_infoVisual.apFace[nCount] = CObject2D::Create(7);

		if (m_infoVisual.apFace[nCount] != nullptr)
		{
			m_infoVisual.apFace[nCount]->SetPosition(FACE_POS[nCount]);
			m_infoVisual.apFace[nCount]->SetSize(FACE_WIDTH[nCount],FACE_HEIGHT[nCount]);

			if (pTexture != nullptr)
			{
				int nIdx = pTexture->Regist(FACE_TEX[nCount]);
				m_infoVisual.apFace[nCount]->SetIdxTexture(nIdx);
				m_infoVisual.apFace[nCount]->SetVtx();
			}
		}
		if (m_infoVisual.apFace[nCount] == nullptr)
		{
			return E_FAIL;
		}
		m_infoVisual.apFace[nCount]->SetVtx();

		// 数字の生成
		m_infoVisual.apNumber[nCount] = CNumber::Create(4,0);

		if (m_infoVisual.apNumber[nCount] != nullptr)
		{
			m_infoVisual.apNumber[nCount]->SetPosition(NUMBER_POS[nCount]);
			m_infoVisual.apNumber[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_WIDTH);

			if (pTexture != nullptr)
			{
				//int nIdx = pTexture->Regist();
				//m_infoVisual.apNumber[nCount]->SetIdxTexture(nIdx);
				//m_infoVisual.apNumber[nCount]->SetVtx();
			}
		}
		if (m_infoVisual.apNumber[nCount] == nullptr)
		{
			return E_FAIL;
		}
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