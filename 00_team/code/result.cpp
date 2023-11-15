//*****************************************************
//
// リザルトの処理[result.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "result.h"
#include "manager.h"
#include "object2D.h"
#include "texture.h"
#include "fade.h"
#include "game.h"
#include "player.h"
#include "number.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const float CAPTION_WIDTH = 918.0f * 0.4f;	// 見出しの幅
	const float CAPTION_HEIGHT = 178.0f * 0.4f;	// 見出しの高さ
	const char* CAPTION_PATH = "data\\TEXTURE\\UI\\result.png";	// 見出しのパス

	const int NUM_PLACE = 1;	// 桁数
	const float NUMBER_WIDTH = 25.0f;	// 数字の幅
	const float NUMBER_HEIGHT = 55.0f;	// 数字の高さ
}

//====================================================
// コンストラクタ
//====================================================
CResult::CResult()
{
	m_state = STATE_NONE;
	m_pBg = nullptr;
	m_pCaption = nullptr;
	ZeroMemory(&m_aInfoSurvived[0], sizeof(m_aInfoSurvived));
	m_nNumSuvived = 0;
}

//====================================================
// デストラクタ
//====================================================
CResult::~CResult()
{

}

//====================================================
// 生成処理
//====================================================
CResult *CResult::Create(bool bWin)
{
	CResult *pResult = nullptr;

	pResult = new CResult;

	if (pResult != nullptr)
	{
		pResult->Init();

		pResult->Create2D(bWin);
	}

	return pResult;
}

//====================================================
// ２Dオブジェクトの生成
//====================================================
void CResult::Create2D(bool bWin)
{
	int nIdxTexture;

	char *pPathCaption[2] =
	{
		"data\\TEXTURE\\UI\\result.png",
		"data\\TEXTURE\\UI\\result.png",
	};

	// 背景の生成
	m_pBg = CObject2D::Create(7);

	if (m_pBg != nullptr)
	{
		m_pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5f, 0.0f));

		m_pBg->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

		m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));

		m_pBg->SetVtx();
	}

	// 見出しの生成
	m_pCaption = CObject2D::Create(7);

	if (m_pCaption != nullptr)
	{
		m_pCaption->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.4f, 0.0f));

		m_pCaption->SetSize(CAPTION_WIDTH, CAPTION_HEIGHT);

		m_pCaption->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		nIdxTexture = CTexture::GetInstance()->Regist(pPathCaption[bWin]);

		m_pCaption->SetIdxTexture(nIdxTexture);

		m_pCaption->SetVtx();
	}
}

//====================================================
// 初期化処理
//====================================================
HRESULT CResult::Init(void)
{
	m_state = STATE_WAIT;

	// ゲームをリザルト状態にする
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		pGame->SetState(CGame::STATE_RESULT);
	}

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CResult::Uninit(void)
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	if (m_pCaption != nullptr)
	{
		m_pCaption->Uninit();
		m_pCaption = nullptr;
	}

	ZeroMemory(&m_aInfoSurvived[0], sizeof(m_aInfoSurvived));

	Release();
}

//====================================================
// 更新処理
//====================================================
void CResult::Update(void)
{
	// 操作処理
	Input();
}

//====================================================
// 操作処理
//====================================================
void CResult::Input(void)
{

}

//====================================================
// 描画処理
//====================================================
void CResult::Draw(void)
{

}

//====================================================
// 生存者の設定
//====================================================
void CResult::SetSurvived(CPlayer *pPlayer)
{
	if (m_nNumSuvived == NUM_PLAYER - 1)
	{// 最大に達していた場合のエラー
		return;
	}

	if (m_aInfoSurvived[m_nNumSuvived].pSuvived == nullptr)
	{
		// 情報の保存
		m_aInfoSurvived[m_nNumSuvived].pSuvived = pPlayer;

		// 情報の表示
		DispSuvived(&m_aInfoSurvived[m_nNumSuvived]);

		m_nNumSuvived++;
	}
	else
	{
		assert(("リザルトでプレイヤー情報の受け取りに失敗", false));
	}
}

//====================================================
// 生存者の表示
//====================================================
void CResult::DispSuvived(SInfoSuvived *pInfo)
{
	int nIdx = m_nNumSuvived;

	if (pInfo->pSuvived != nullptr)
	{
		int nID = pInfo->pSuvived->GetID();

		if (pInfo->pNumber == nullptr)
		{// ID表示の数字を生成
			pInfo->pNumber = CNumber::Create(NUM_PLACE, nID);

			if (pInfo->pNumber != nullptr)
			{
				pInfo->pNumber->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + NUMBER_HEIGHT * nIdx, 0.0f));
				pInfo->pNumber->SetSizeAll(NUMBER_WIDTH, NUMBER_HEIGHT);
			}
		}
	}
}