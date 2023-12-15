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

#include <stdio.h>

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
#include "sound.h"

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
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.55f, 0.0f),
	};
	const float GENRE_ICON_SIZE[CRecord::GENRE_TYPE_MAX] =
	{// 大きさ[種類]
		250.0f,
		250.0f,
	};
	const float GENRE_ICON_WIDTH[CRecord::GENRE_TYPE_MAX] =
	{// 横幅[種類]
		0.5f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
		0.5f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const float GENRE_ICON_HEIGHT[CRecord::GENRE_TYPE_MAX] =
	{// 縦幅[種類]
		0.4f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
		0.6f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const char* GENRE_ICON_TEX[CRecord::GENRE_TYPE_MAX] =
	{// テクスチャのパス[種類]
		"data\\TEXTURE\\UI\\Icon_destroyer.png",
		"data\\TEXTURE\\UI\\Icon_madman.png",
	};

	// 戦績種類文
	const D3DXVECTOR3 GENRE_TEXT_POS[CRecord::GENRE_TYPE_MAX] =
	{// 位置[種類]
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.35f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.35f, 0.0f),
	};
	const float GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_MAX] =
	{// 大きさ[種類]
		175.0f,
		175.0f,
	};
	const float GENRE_TEXT_WIDTH[CRecord::GENRE_TYPE_MAX] =
	{// 横幅[種類]
		1.0f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
		1.0f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const float GENRE_TEXT_HEIGHT[CRecord::GENRE_TYPE_MAX] =
	{// 縦幅[種類]
		0.2f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
		0.2f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const char* GENRE_TEXT_TEX[CRecord::GENRE_TYPE_MAX] =
	{// テクスチャのパス[種類]
		"data\\TEXTURE\\UI\\rank_text_destroyer.png",
		"data\\TEXTURE\\UI\\rank_text_madman.png",
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
	const float FIELD_HEIGHT = 500.0f;		// フィールドの高さ
	const char* FIELD_FILE_NAME = "data\\TEXTURE\\MATERIAL\\WodenWall_00.jpg";	// フィールドのパス

	// ウォール
	const float WALL_WIDTH = 800.0f;		// ウォールの幅
	const float WALL_HEIGHT = 500.0f;		// ウォールの高さ
	const char* WALL_FILE_NAME = "data\\TEXTURE\\MATERIAL\\concrete_00.jpg";	// ウォールのパス

	// カメラ
	const D3DXVECTOR3 CAMERA_POS_V = D3DXVECTOR3(0.0f, 200.0f, -800.0f);
	const D3DXVECTOR3 CAMERA_POS_R = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	const D3DXVECTOR3 CAMERA_MOVE = D3DXVECTOR3(0.0f, 0.0f, 7.0f);

	// 役者
	const char* PLAYER_BODY_PATH[CRanking::ACTOR_TYPE_MAX] =
	{// 役者の体のパス[役者番号]
		"data\\MOTION\\motionRanking01.txt",
		"data\\MOTION\\motionRanking02.txt",
		"data\\MOTION\\motionRanking03.txt",
		"data\\MOTION\\motionRanking04.txt",
		"data\\MOTION\\motionEnemy00.txt",
		"data\\MOTION\\motionEnemy00.txt",
		"data\\MOTION\\motionEnemy00.txt",
	};
	const D3DXVECTOR3 PLAYER_POS[CRanking::DIRECTION_TYPE_MAX][CRanking::ACTOR_TYPE_MAX] =
	{// 役者の位置[役者番号][演出番号]

		// 行進
		D3DXVECTOR3(500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(600.0f, 0.0f, 0.0f),
		D3DXVECTOR3(700.0f, 0.0f, 0.0f),
		D3DXVECTOR3(800.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし

		// 逃げる
		D3DXVECTOR3(500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(600.0f, 0.0f, 0.0f),
		D3DXVECTOR3(650.0f, 0.0f, 30.0f),
		D3DXVECTOR3(675.0f, 0.0f, -30.0f),

		// 追いかける
		D3DXVECTOR3(-600.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(1050.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(-500.0f, 0.0f,  0.0f),

	};
	const D3DXVECTOR3 PLAYER_ROT[CRanking::DIRECTION_TYPE_MAX][CRanking::ACTOR_TYPE_MAX] =
	{// 役者の向き[役者番号][演出番号]

		// 行進
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし

		// 逃げる
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),

		// 追いかける
		D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f),

	};
	const D3DXVECTOR3 PLAYER_MOVE[CRanking::DIRECTION_TYPE_MAX][CRanking::ACTOR_TYPE_MAX] =
	{// 役者の移動量[役者番号][演出番号]

		// 行進
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし

		// 逃げる
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),

		// 追いかける
		D3DXVECTOR3(4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// 出番なし
		D3DXVECTOR3(4.0f, 0.0f, 0.0f),
	};

	const int DIRECTION_CHANGE_COUNT = 300;	// 演出を変えるまでの時間
	const int GENRE_CHANGE_COUNT = 300;		// 種類を変えるまでの時間

	const char* RANKING_BIN_FILE = "data\\BINARY\\ranking";	// ランキングのファイル名

	// ランキングの数字
	const D3DXVECTOR3 RANK_NUM_POS[RANK::NUM_MAX] =
	{// 位置[種類]
		D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.6f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.7f, 0.0f),
	};
	const D3DXVECTOR3 RANK_POS_PLUS = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	const float RANK_NUM_SIZE = 50.0f;
	const float RANK_NUM_WIDTH = 0.5f * RANK_NUM_SIZE;
	const float RANK_NUM_HEIGHT = 0.4f * RANK_NUM_SIZE;
	const char* RANK_NUM_TEX[RANK::NUM_MAX] =
	{// テクスチャのパス[種類]
		"data\\TEXTURE\\UI\\1st.png",
		"data\\TEXTURE\\UI\\2nd.png",
		"data\\TEXTURE\\UI\\3rd.png",
	};
}

//=====================================================
// コンストラクタ
//=====================================================
CRanking::CRanking()
{
	ZeroMemory(&m_infoVisualUi, sizeof(m_infoVisualUi));
	ZeroMemory(&m_infoVisualObj,sizeof(m_infoVisualObj)); 
	m_typeDirection = (DIRECTION_TYPE)0;
	m_typeGenre = (CRecord::GENRE_TYPE)0;
	m_nDirectionCnt = 0;
	m_nGenreCnt = 0;

	for (int nCount = 0; nCount < CRecord::GENRE_TYPE_MAX; nCount++)
	{
		ZeroMemory(&m_aRankScore[nCount][0], sizeof(m_aRankScore[nCount]));
		ZeroMemory(&m_aRankFace[nCount][0], sizeof(m_aRankScore[nCount]));
	}

	ZeroMemory(&m_aUpdateIdx[0], sizeof(m_aUpdateIdx));
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
	// 戦績のポインタを取得
	CRecord* pRecord = CRecord::GetInstance();

	if (pRecord != nullptr)
	{
		// 戦績のソート
		pRecord->AllSort();
	}

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

	// 初期設定
	ResetRank();
	SortRank();

	// 取得したスコアでランキング設定
	SetRank();

	// 保存
	SaveRank();

	// サウンドインスタンスの取得
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(pSound->LABEL_BGM_RANKING);
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

	// 演出の更新
	UpdateDirection();

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

	if (pRecord != nullptr)
	{
		int nMaxPlayer = pRecord->GetNumSuvived();

		for (int nCount = 0; nCount < nMaxPlayer; nCount++)
		{
			// プレイヤー顔の生成
			m_infoVisualUi.apFace[nCount] = CObject2D::Create(7);

			if (m_infoVisualUi.apFace[nCount] != nullptr)
			{
				if (pRecord != nullptr)
				{
					int nRankNum = pRecord->GetDestroyRank(nCount);

					m_infoVisualUi.apFace[nCount]->SetPosition(FACE_POS[nRankNum]);
					m_infoVisualUi.apFace[nCount]->SetSize(FACE_WIDTH, FACE_HEIGHT);
				}

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
				if (pRecord != nullptr)
				{
					int nRankNum = pRecord->GetDestroyRank(nCount);

					m_infoVisualUi.apNumber[nCount]->SetPosition(NUMBER_POS[nRankNum]);
					m_infoVisualUi.apNumber[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_WIDTH);
				}

				m_infoVisualUi.apNumber[nCount]->SetValue(pRecord->GetDestroy(nCount), 4);

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

	// 地面の生成
	m_infoVisualObj.pWall = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (m_infoVisualObj.pWall != nullptr)
	{
		m_infoVisualObj.pWall->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
		m_infoVisualObj.pWall->SetSize(WALL_WIDTH, WALL_HEIGHT);
		m_infoVisualObj.pWall->SetRot(D3DXVECTOR3(D3DX_PI * -0.5f, 0.0f, 0.0f));
		int nIdx = CTexture::GetInstance()->Regist(WALL_FILE_NAME);
		m_infoVisualObj.pWall->SetIdxTexture(nIdx);
	}
	else if (m_infoVisualObj.pWall == nullptr)
	{
		return E_FAIL;
	}

	for (int nCount = 0; nCount < ACTOR_TYPE_MAX; nCount++)
	{
		// 役者の生成
		m_infoVisualObj.apModelActor[nCount] = CMotion::Create((char*)PLAYER_BODY_PATH[nCount]);

		if (m_infoVisualObj.apModelActor[nCount] != nullptr)
		{
			m_infoVisualObj.apModelActor[nCount]->SetPosition(PLAYER_POS[m_typeDirection][nCount]);
			m_infoVisualObj.apModelActor[nCount]->SetRot(PLAYER_ROT[m_typeDirection][nCount]);
			m_infoVisualObj.apModelActor[nCount]->SetMotion(1);
		}
		else if (m_infoVisualObj.apModelActor[nCount] == nullptr)
		{
			return E_FAIL;
		}
	}

	// ランキングの数字の生成
	for (int nCount = 0; nCount < ACTOR_TYPE_MAX; nCount++)
	{
		if (m_infoVisualUi.apNumRank[nCount] == nullptr)
		{
			m_infoVisualUi.apNumRank[nCount] = CNumber::Create(4, m_aRankScore[m_typeGenre][nCount]);
		}
	}

	// ランキング数値の設定処理
	SetRankNum();

	return S_OK;
}

//=====================================================
// 各戦績の設定処理
//=====================================================
void CRanking::SetRecordGenre(void)
{
	// テクスチャのポインタを取得
	CTexture* pTexture = CTexture::GetInstance();

	// 戦績のポインタを取得
	CRecord* pRecord = CRecord::GetInstance();

	// 戦績アイコンの設定処理
	if (m_infoVisualUi.pGenreIcon != nullptr)
	{
		m_infoVisualUi.pGenreIcon->SetPosition(GENRE_ICON_POS[m_typeGenre]);
		m_infoVisualUi.pGenreIcon->SetSize(GENRE_ICON_WIDTH[m_typeGenre], GENRE_ICON_HEIGHT[m_typeGenre]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_ICON_TEX[m_typeGenre]);
			m_infoVisualUi.pGenreIcon->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pGenreIcon->SetVtx();
	}

	// 戦績テキストの設定処理
	if (m_infoVisualUi.pGenreText != nullptr)
	{
		m_infoVisualUi.pGenreText->SetPosition(GENRE_TEXT_POS[m_typeGenre]);
		m_infoVisualUi.pGenreText->SetSize(GENRE_TEXT_WIDTH[m_typeGenre], GENRE_TEXT_HEIGHT[m_typeGenre]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_TEXT_TEX[m_typeGenre]);
			m_infoVisualUi.pGenreText->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pGenreText->SetVtx();
	}

	if (pRecord != nullptr)
	{
		int nMaxPlayer = pRecord->GetNumSuvived();

		for (int nCount = 0; nCount < nMaxPlayer; nCount++)
		{
			if (pRecord != nullptr)
			{
				int nRank = 0;		// 順位
				int nNumRank = 0;	// 順位での値

				// 種類ごとに戦績の順位を取得
				switch (m_typeGenre)
				{
				case CRecord::GENRE_TYPE_DESTROY:

					nRank = pRecord->GetDestroyRank(nCount);
					nNumRank = pRecord->GetDestroy(nCount);

					break;
				case CRecord::GENRE_TYPE_MADMAN:

					nRank = pRecord->GetMadmanRank(nCount);
					nNumRank = pRecord->GetMadman(nCount);

					break;
				}

				// 顔UIの設定処理
				if (m_infoVisualUi.apFace[nCount] != nullptr)
				{
					// 顔UIを順位の位置に変更
					m_infoVisualUi.apFace[nCount]->SetPosition(FACE_POS[nRank]);
					m_infoVisualUi.apFace[nCount]->SetSize(FACE_WIDTH, FACE_HEIGHT);

					if (pTexture != nullptr)
					{
						int nIdx = pTexture->Regist(FACE_FILE_NAME[nCount]);
						m_infoVisualUi.apFace[nCount]->SetIdxTexture(nIdx);
					}

					m_infoVisualUi.apFace[nCount]->SetVtx();
				}

				// 数字の設定処理
				if (m_infoVisualUi.apNumber[nCount] != nullptr)
				{
					m_infoVisualUi.apNumber[nCount]->SetPosition(NUMBER_POS[nRank]);
					m_infoVisualUi.apNumber[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_WIDTH);

					m_infoVisualUi.apNumber[nCount]->SetValue(nNumRank, 4);

					if (pTexture != nullptr)
					{
						//int nIdx = pTexture->Regist();
						//m_infoVisualUi.apNumber[nCount]->SetIdxTexture(nIdx);
						//m_infoVisualUi.apNumber[nCount]->SetVtx();
					}
				}
			}
		}
	}
}

//=====================================================
// 演出の更新
//=====================================================
void CRanking::UpdateDirection(void)
{
	// 演出カウントが設定値以下
	if (m_nDirectionCnt <= DIRECTION_CHANGE_COUNT)
	{
		// カウントを加算
		m_nDirectionCnt++;
	}
	else
	{
		// カウントの初期化
		m_nDirectionCnt = 0;

		// 演出番号を増やす
		m_typeDirection = (DIRECTION_TYPE)(m_typeDirection + 1);

		// 演出が最大数
		if (m_typeDirection >= DIRECTION_TYPE_MAX)
		{
			// 演出を初期化
			m_typeDirection = (DIRECTION_TYPE)0;
		}

		// 演出を設定
		SetDirection();
	}

	// 種類カウントが設定値以下
	if (m_nGenreCnt <= GENRE_CHANGE_COUNT)
	{
		// カウントを増やす
		m_nGenreCnt++;
	}
	else
	{
		// カウントを初期化
		m_nGenreCnt = 0;

		// 戦績種類を増やす
		m_typeGenre = (CRecord::GENRE_TYPE)(m_typeGenre + 1);

		// 戦績種類が最大値
		if (m_typeGenre >= CRecord::GENRE_TYPE_MAX)
		{
			// 戦績種類を初期化
			m_typeGenre = (CRecord::GENRE_TYPE)0;
		}

		// 戦績種類の設定
		SetRecordGenre();

		// ランクの数字を表示
		SetRankNum();
	}

	for (int nCount = 0; nCount < ACTOR_TYPE_MAX; nCount++)
	{
		if (m_infoVisualObj.apModelActor[nCount] != nullptr)
		{
			D3DXVECTOR3 playerMove = m_infoVisualObj.apModelActor[nCount]->GetPosition() + PLAYER_MOVE[m_typeDirection][nCount];

			m_infoVisualObj.apModelActor[nCount]->SetPosition(playerMove);
		}
	}
}

//=====================================================
// 演出の設定処理
//=====================================================
HRESULT CRanking::SetDirection(void)
{
	for (int nCount = 0; nCount < ACTOR_TYPE_MAX; nCount++)
	{
		if (m_infoVisualObj.apModelActor[nCount] != nullptr)
		{
			m_infoVisualObj.apModelActor[nCount]->SetPosition(PLAYER_POS[m_typeDirection][nCount]);
			m_infoVisualObj.apModelActor[nCount]->SetRot(PLAYER_ROT[m_typeDirection][nCount]);
			m_infoVisualObj.apModelActor[nCount]->SetMotion(1);
		}
		else if (m_infoVisualObj.apModelActor[nCount] == nullptr)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=====================================================
// 設定処理
//=====================================================
void CRanking::SetRank(void)
{
	// 変数宣言
	bool bNewRank = false;

	// 戦績の取得
	CRecord* pRecord = CRecord::GetInstance();

	// ソート
	SortRank();

	for (int nCntGenre = 0; nCntGenre < CRecord::GENRE_TYPE_MAX; nCntGenre++)
	{
		for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
		{
			if (pRecord != nullptr)
			{
				int nNewScore = 0;

				switch (nCntGenre)
				{
				case CRecord::GENRE_TYPE_DESTROY:

					nNewScore = pRecord->GetDestroy(nCount);

					break;

				case CRecord::GENRE_TYPE_MADMAN:

					nNewScore = pRecord->GetMadman(nCount);

					break;
				}

				if (nNewScore > m_aRankScore[nCntGenre][RANK::NUM_MAX - 1])
				{// 最小値を越したら代入
					m_aRankScore[nCntGenre][RANK::NUM_MAX - 1] = nNewScore;

					// 再ソート
					SortRank();

					bNewRank = true;
				}
			}
		}
	}

	for (int nCntGenre = 0; nCntGenre < CRecord::GENRE_TYPE_MAX; nCntGenre++)
	{
		for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
		{
			if (pRecord != nullptr &&
				bNewRank == true)
			{
				int nNewScore = 0;

				switch (nCntGenre)
				{
				case CRecord::GENRE_TYPE_DESTROY:

					nNewScore = pRecord->GetDestroy(nCount);

					break;

				case CRecord::GENRE_TYPE_MADMAN:

					nNewScore = pRecord->GetMadman(nCount);

					break;
				}

				for (int nCnt = 0; nCnt < RANK::NUM_MAX; nCnt++)
				{// 足した値と合致する記録を探す
					if (nNewScore == m_aRankScore[nCntGenre][nCnt])
					{// ニューレコード番号を記録
						m_aUpdateIdx[nCount] = nCnt;
					}
				}
			}
		}
	}

	// ランクの数字を表示
	SetRankNum();

	// 保存処理
#ifndef _DEBUG
	SaveRank();
#endif
}

//=====================================================
// ランキング数値の設定処理
//=====================================================
void CRanking::SetRankNum(void)
{
	// 数字の設定
	for (int nCount = 0; nCount < RANK::NUM_MAX; nCount++)
	{
		if (m_infoVisualUi.apNumRank[nCount] != nullptr)
		{
			// 値の設定
			m_infoVisualUi.apNumRank[nCount]->SetValue(m_aRankScore[m_typeGenre][nCount],4);
			m_infoVisualUi.apNumRank[nCount]->SetPosition(RANK_NUM_POS[nCount]);
			m_infoVisualUi.apNumRank[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_HEIGHT);

			// 順位の生成
			CObject2D* pObject2D = CObject2D::Create();
			pObject2D->SetPosition(RANK_NUM_POS[nCount] + RANK_POS_PLUS);
			pObject2D->SetSize(RANK_NUM_WIDTH, RANK_NUM_HEIGHT);

			int nIdx = CTexture::GetInstance()->Regist(RANK_NUM_TEX[nCount]);
			pObject2D->SetIdxTexture(nIdx);
			pObject2D->SetVtx();
		}
	}
}

//=====================================================
// ランキングソート
//=====================================================
void CRanking::SortRank(void)
{
	for (int nCntGenre = 0; nCntGenre < CRecord::GENRE_TYPE_MAX ; nCntGenre++)
	{
		for (int nCntRanking = 0; nCntRanking < RANK::NUM_MAX - 1; nCntRanking++)
		{//ランキングをソート

			// 左端の値を最大値とする
			int nTop = nCntRanking;

			for (int nCount2 = nCntRanking + 1; nCount2 < RANK::NUM_MAX; nCount2++)
			{//左の値と対象の値を比較
				if (m_aRankScore[nCntGenre][nTop] < m_aRankScore[nCntGenre][nCount2])
				{//もし比較した数字が小さかったら
					nTop = nCount2;
				}
			}

			//要素の入れ替え
			int nTemp = m_aRankScore[nCntGenre][nCntRanking];
			m_aRankScore[nCntGenre][nCntRanking] = m_aRankScore[nCntGenre][nTop];
			m_aRankScore[nCntGenre][nTop] = nTemp;
		}
	}
}

//=====================================================
// ランキング情報リセット
//=====================================================
void CRanking::ResetRank(void)
{
	//外部ファイル読み込み
	LoadRank();
}

//=====================================================
// ランキング情報保存
//=====================================================
void CRanking::SaveRank(void)
{
	//ポインタ宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(RANKING_BIN_FILE, "wb");

	if (pFile != NULL)
	{//ファイルが開けた場合

		for (int nCount = 0; nCount < CRecord::GENRE_TYPE_MAX; nCount++)
		{
			//バイナリファイルに書き込む
			fwrite(&m_aRankScore[nCount][0], sizeof(int), RANK::NUM_MAX, pFile);
			fwrite(&m_aRankFace[nCount][0], sizeof(int), RANK::NUM_MAX, pFile);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		assert(("ランキング保存に失敗", false));
	}
}

//=====================================================
//ランキング情報読み込み
//=====================================================
void CRanking::LoadRank(void)
{
	//ポインタ宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(RANKING_BIN_FILE, "rb");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//バイナリファイルから読み込む
		for (int nCount = 0; nCount < CRecord::GENRE_TYPE_MAX; nCount++)
		{
			fread(&m_aRankScore[nCount][0], sizeof(int), RANK::NUM_MAX, pFile);
			fread(&m_aRankFace[nCount][0], sizeof(int), RANK::NUM_MAX, pFile);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		assert(("ランキング読み込みに失敗", false));
	}
}