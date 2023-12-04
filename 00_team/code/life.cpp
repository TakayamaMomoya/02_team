//*****************************************************
//
// ライフ表示の処理[life.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "life.h"
#include "UI.h"

#include "texture.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const D3DXVECTOR3 POS[NUM_PLAYER] =
	{// 位置
		D3DXVECTOR3(SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.975f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.7f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.975f, SCREEN_HEIGHT * 0.7f, 0.0f),
	};

	const float WIDTH = 15.0f;
	const float HEIGHT = 100.0f;
	const D3DXCOLOR COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
}
//=====================================================
// コンストラクタ
//=====================================================
CLife::CLife(int nPriority) : CObject(nPriority)
{
	m_pUi = NULL;
	ZeroMemory(&m_info, sizeof(m_info));
}

//=====================================================
// デストラクタ
//=====================================================
CLife::~CLife()
{

}

//=====================================================
// 生成処理
//=====================================================
CLife *CLife::Create(int nIdx)
{
	CLife *pLife = nullptr;

	pLife = new CLife;

	if (pLife != nullptr)
	{
		// プレイヤー番号を設定
		pLife->m_info.nIdxPlayer = nIdx;

		if (pLife->m_pUi == NULL)
		{
			// UIオブジェクトの生成処理
			pLife->m_pUi = CUI::Create();
		}

		// ライフの初期化
		pLife->Init();

		// 設定処理
		pLife->SetPosition(POS[nIdx]);
		pLife->SetSize(WIDTH,HEIGHT);
		pLife->SetColor(COLOR);
	}

	return pLife;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CLife::Init(void)
{
	if (m_pUi != nullptr)
	{
		// 初期値設定処理
		m_pUi->SetSize(50.0f, 100.0f);
		m_pUi->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// テクスチャ番号取得
	//m_info.nIdxTexture = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\number001.png");

	if (m_pUi != nullptr)
	{
		//m_pUi->SetIdxTexture(m_info.nIdxTexture);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CLife::Uninit(void)
{
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CLife::Update(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CLife::Draw(void)
{

}

//=====================================================
// 体力設定処理
//=====================================================
void CLife::SetLife(int nLife)
{
	m_info.nLife = nLife;
}

//=====================================================
// 位置設定処理
//=====================================================
void CLife::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pUi != NULL)
	{
		// フレームの位置
		m_pUi->SetPosition(pos);

		m_pUi->SetVtx();
	}
}

//=====================================================
// 大きさ設定処理
//=====================================================
void CLife::SetSize(float width, float height)
{
	if (m_pUi != NULL)
	{
		m_pUi->SetSize(width, height);

		m_pUi->SetVtx();
	}
}

//=====================================================
// 色設定処理
//=====================================================
void CLife::SetColor(D3DXCOLOR col)
{
	if (m_pUi != NULL)
	{
		m_pUi->SetCol(col);

		m_pUi->SetVtx();
	}
}