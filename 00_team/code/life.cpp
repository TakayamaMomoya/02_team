//*****************************************************
//
// ライフ表示の処理[life.cpp]
// Author:��山桃也
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
void CLife::SetCol(D3DXCOLOR col)
{
	if (m_pUi != NULL)
	{
		m_pUi->SetCol(col);

		m_pUi->SetVtx();
	}
}

//=====================================================
// テクスチャ設定処理
//=====================================================
void CLife::SetTexture(const char *pFileName)
{
	m_info.nIdxTexture = CTexture::GetInstance()->Regist(pFileName);

	if (m_pUi != nullptr)
	{
		m_pUi->SetIdxTexture(m_info.nIdxTexture);

		m_pUi->SetVtx();
	}
}