//*****************************************************
//
// ３Dエフェクト処理[effect3D.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "debrisSpawner.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define SPEED_MOVE	(7.0f)	// 移動速度

//=====================================================
// コンストラクタ
//=====================================================
CDebrisSpawner::CDebrisSpawner(int nPriority)
{
	m_nLife = 0;
	m_fDecreaseAlpha = 0.0f;
	m_move = { 0.0f,0.0f,0.0f };
	m_fGravity = 0.0f;
}

//=====================================================
// デストラクタ
//=====================================================
CDebrisSpawner::~CDebrisSpawner()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CDebrisSpawner::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	int nIdx = CModel::Load("data\\MODEL\\sample_debris.x");

	// モデル読込
	BindModel(nIdx);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CDebrisSpawner::Uninit(void)
{
	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CDebrisSpawner::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();

	// 寿命減衰
	m_nLife--;

	// 重力加算
	m_move.y -= m_fGravity;

	// αの減少


	// 位置更新
	SetPosition(GetPosition() + m_move);

	if (m_nLife < 0)
	{// 自分の削除
		Uninit();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CDebrisSpawner::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CDebrisSpawner* CDebrisSpawner::Create(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move, float fGravity, int nPriority)
{
	CDebrisSpawner* pDebtisSpawner = nullptr;

	if (pDebtisSpawner == nullptr)
	{// インスタンス生成
		pDebtisSpawner = new CDebrisSpawner(nPriority);

		if (pDebtisSpawner != nullptr)
		{
			pDebtisSpawner->SetPosition(pos);

			// 初期化処理
			pDebtisSpawner->Init();

			// Xファイルの読込


			pDebtisSpawner->m_nLife = nLife;

			pDebtisSpawner->m_move = move;

			pDebtisSpawner->m_fDecreaseAlpha = 1.0f / nLife;

			pDebtisSpawner->m_fGravity = fGravity;
		}
	}

	return pDebtisSpawner;
}

//=====================================================
// 読込処理
//=====================================================
HRESULT CDebrisSpawner::Load(void)
{
	return S_OK;
}

//=====================================================
// テクスチャ破棄
//=====================================================
void CDebrisSpawner::Unload(void)
{

}