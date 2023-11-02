//*****************************************************
//
// パーティクル処理[particle.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "particle.h"
#include "effect3D.h"

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_nLife = 0;
	m_nNumEffect = 0;
	m_col = { 0.0f,0.0f,0.0f,0.0f };
}

//=====================================================
//	デストラクタ
//=====================================================
CParticle::~CParticle()
{

}

//=====================================================
//	初期化処理
//=====================================================
HRESULT CParticle::Init(void)
{
	return S_OK;
}

//=====================================================
//	終了処理
//=====================================================
void CParticle::Uninit(void)
{
	Release();
}

//=====================================================
//	更新処理
//=====================================================
void CParticle::Update(void)
{
	// 変数宣言
	float fRot,fRot2,fMove;
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };
	CEffect3D *pEffect3D = NULL;

	for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
	{
		fRot = rand() % 629 - 314 / 100.0f;
		fRot2 = rand() % 629 - 314 / 100.0f;

		//移動量の設定
		fMove = (float)(rand() % (int)(m_fSpeed * 10)) * 0.1f + m_fSpeed * 0.5f;

		move.x = sinf(fRot) * sinf(fRot2) * fMove;
		move.y = cosf(fRot) * fMove;
		move.z = sinf(fRot) * cosf(fRot2) * fMove;

		// エフェクト生成
		pEffect3D = CEffect3D::Create(m_pos, 30.0f, 50, m_col, move);

		if (pEffect3D != NULL)
		{
			// 色設定
			pEffect3D->SetColor(D3DXCOLOR(1.0f, 0.64f, 0.0f, 1.0f));
		}
	}

	m_nLife--;

	if (m_nLife < 0)
	{
		// 自身の破棄
		Uninit();
	}
}

//=====================================================
//	位置設定処理
//=====================================================
void CParticle::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
//	生成処理
//=====================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, TYPE type)
{
	CParticle *pParticle = NULL;

	if (pParticle == NULL)
	{// インスタンス生成
		pParticle = new CParticle;

		switch (type)
		{// パラメーター設定
		case TYPE_EXPLOSION:
			pParticle->m_nLife = 2;

			pParticle->m_pos = pos;

			pParticle->m_fSpeed = 1.0f;

			pParticle->m_nNumEffect = 30;

			pParticle->m_col = D3DXCOLOR{ 1.0f,0.10f,0.0f,1.0f };
			break;
		default:
			break;
		}
	}

	return pParticle;
}