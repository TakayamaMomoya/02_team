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

#include "player.h"
#include "playerManager.h"

//=====================================================
// コンストラクタ
//=====================================================
CLife::CLife(int nPriority) : CObject(nPriority)
{
	m_pUILife = nullptr;
	m_pUILifeFrame = nullptr;
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
	CLife *pLife = new CLife;

	if (pLife != nullptr)
	{
		// プレイヤー番号を設定
		pLife->m_info.nIdxPlayer = nIdx;

		if (pLife->m_pUILifeFrame == nullptr)
		{
			// ライフ枠の生成処理
			pLife->m_pUILifeFrame = CUI::Create();
		}

		if (pLife->m_pUILife == nullptr)
		{
			// ライフの生成処理
			pLife->m_pUILife = CUI::Create();
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
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		// 初期値設定処理
		m_pUILife->SetSize(50.0f, 100.0f);
		m_pUILife->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pUILifeFrame->SetSize(50.0f, 100.0f);
		m_pUILifeFrame->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CLife::Uninit(void)
{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		m_pUILife->Uninit();
		m_pUILifeFrame->Uninit();
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CLife::Update(void)
{
	// プレイヤーの体力
	SetLife();
}

//=====================================================
// 描画処理
//=====================================================
void CLife::Draw(void)
{

}

//=====================================================
// 位置設定処理
//=====================================================
void CLife::SetLife(void)
{
	// プレイヤー管理の取得
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();
	CPlayer* pPlayer = nullptr;

	if (pPlayerManager != nullptr)
	{
		// プレイヤーの取得
		pPlayer = pPlayerManager->GetPlayer(m_info.nIdxPlayer);
	}

	if (pPlayerManager != nullptr )
	{
		if (pPlayer != nullptr)
		{
			// 現在の体力を取得
			float fLife = pPlayer->GetLife();

			// 体力の初期値を取得
			float fMaxLife = pPlayerManager->GetPlayerParam().fInitialLife;

			// ゲージの消費量を計算
			float fLifeRatio = (1.0f - (fLife / fMaxLife));
			m_info.fHeightSub = fLifeRatio * m_info.fHeight;

			m_pUILife->SetTex(D3DXVECTOR2(0.0f, fLifeRatio), D3DXVECTOR2(1.0f, 1.0f));
			SetVtxGage();
			m_pUILifeFrame->SetVtx();
		}
		else
		{
			// 体力はない
			float fLife = 0.0f;

			// 体力の初期値を取得
			float fMaxLife = pPlayerManager->GetPlayerParam().fInitialLife;

			// ゲージの消費量を計算
			float fLifeRatio = (1.0f - (fLife / fMaxLife));
			m_info.fHeightSub = fLifeRatio * m_info.fHeight;

			m_pUILife->SetTex(D3DXVECTOR2(0.0f, fLifeRatio), D3DXVECTOR2(1.0f, 1.0f));
			SetVtxGage();
			m_pUILifeFrame->SetVtx();
		}
	}
}

//=====================================================
// 位置設定処理
//=====================================================
void CLife::SetPosition(D3DXVECTOR3 posLife, D3DXVECTOR3 posLifeFrame)

{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		m_info.posLife = posLife;
		m_info.posLifeFrame = posLifeFrame;
		
		m_pUILife->SetPosition(posLife);
		m_pUILifeFrame->SetPosition(posLifeFrame);

		SetVtxGage();
		m_pUILifeFrame->SetVtx();
	}
}

//=====================================================
// 大きさ設定処理
//=====================================================
void CLife::SetSize(float width, float height)
{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		m_info.fWidth = width;
		m_info.fHeight = height;

		m_pUILife->SetSize(width, height);
		m_pUILifeFrame->SetSize(width, height);

		SetVtxGage();
		m_pUILifeFrame->SetVtx();
	}
}

//=====================================================
// 色設定処理
//=====================================================
void CLife::SetCol(D3DXCOLOR colLife, D3DXCOLOR colLifeFrame)
{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		m_info.colLife = colLife;
		m_info.colLifeFrame = colLifeFrame;

		m_pUILife->SetCol(colLife);
		m_pUILifeFrame->SetCol(colLifeFrame);

		SetVtxGage();
		m_pUILifeFrame->SetVtx();
	}
}

//=====================================================
// テクスチャ設定処理
//=====================================================
void CLife::SetTexture(const char* pFileName)
{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		CTexture* pTexture = CTexture::GetInstance();

		if (pTexture != nullptr)
		{
			m_info.nIdxTexture = pTexture->Regist(pFileName);
		}

		m_pUILife->SetIdxTexture(m_info.nIdxTexture);
		m_pUILifeFrame->SetIdxTexture(m_info.nIdxTexture);

		SetVtxGage();
		m_pUILifeFrame->SetVtx();
	}
}

//=====================================================
// ゲージ用の頂点情報設定処理
//=====================================================
void CLife::SetVtxGage(void)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	if (m_pUILife != nullptr)
	{
		if (m_pUILife->GetVtxBuff() != nullptr)
		{
			// 頂点バッファをロックし、頂点情報へのポインタを取得
			m_pUILife->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

			// 対角線の角度取得
			float fAngleUp = atan2f(m_info.fWidth, m_info.fHeight);
			// 長さの取得
			float fLengthUp = sqrtf(m_info.fWidth * m_info.fWidth + m_info.fHeight * m_info.fHeight);
			float fLengthSub = sqrtf(m_info.fWidthSub * m_info.fWidthSub + m_info.fHeightSub * m_info.fHeightSub);

			if (fLengthUp - fLengthSub <= 1.0f)
			{
				fLengthUp = 0.0f;
				fLengthSub = 0.0f;
			}

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3
			(
				m_info.posLife.x + sinf(0.0f - D3DX_PI + fAngleUp) * fLengthUp,
				m_info.posLife.y + cosf(0.0f - D3DX_PI + fAngleUp) * ((fLengthUp * 2.0f) - (fLengthSub * 2.0f)),
				0.0f
			);
			pVtx[1].pos = D3DXVECTOR3
			(
				m_info.posLife.x + sinf(0.0f + D3DX_PI - fAngleUp) * fLengthUp,
				m_info.posLife.y + cosf(0.0f + D3DX_PI - fAngleUp) * ((fLengthUp * 2.0f) - (fLengthSub * 2.0f)),
				0.0f
			);
			pVtx[2].pos = D3DXVECTOR3
			(
				m_info.posLife.x + sinf(0.0f - fAngleUp) * fLengthUp,
				m_info.posLife.y + cosf(0.0f - fAngleUp),
				0.0f
			);
			pVtx[3].pos = D3DXVECTOR3
			(
				m_info.posLife.x + sinf(0.0f + fAngleUp) * fLengthUp,
				m_info.posLife.y + cosf(0.0f + fAngleUp),
				0.0f
			);


			// 頂点バッファのアンロック
			m_pUILife->GetVtxBuff()->Unlock();
		}
	}
}