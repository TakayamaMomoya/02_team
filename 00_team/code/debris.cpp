//*****************************************************
//
// 破片処理[debris.cpp]
// Author:小笠原彪
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "debris.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//*****************************************************
// マクロ定義
//*****************************************************
namespace
{
	const float GEOWND(10.0f);	// 床判定の高さ
	const float BOUNCE(4.0f);	// 跳ね返りの強さ
	const float SPEED_MOVE(7.0f);	// 移動速度
	const float ROT_VELOCITY(0.05f);	// 回転速度の制限
};

//=====================================================
// コンストラクタ
//=====================================================
CDebris::CDebris(int nPriority)
{
	m_rotVelocity = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_nLife = 0;
	m_fDecreaseAlpha = 0.0f;
	m_fGravity = 0.0f;
}

//=====================================================
// デストラクタ
//=====================================================
CDebris::~CDebris()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CDebris::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	int nIdx = CModel::Load("data\\MODEL\\sample_debris.x");

	m_rotVelocity.x = (float)(rand() % 629 - 314) / 100.0f;
	m_rotVelocity.y = (float)(rand() % 629 - 314) / 100.0f;
	m_rotVelocity.z = (float)(rand() % 629 - 314) / 100.0f;

	// モデル読込
	BindModel(nIdx);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CDebris::Uninit(void)
{
	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CDebris::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();

	D3DXVECTOR3 pos = GetPosition();

	// 寿命減衰
	m_nLife--;

	// 重力加算
	m_move.y -= m_fGravity;

	// 移動量の減衰
	m_move.x *= 0.98f;
	m_move.z *= 0.98f;

	if (pos.y > 10.0f)
	{
		// 回転
		D3DXVECTOR3 rot = GetRot();
		rot.x += m_rotVelocity.x * ROT_VELOCITY;
		rot.y += m_rotVelocity.y * ROT_VELOCITY;
		rot.z += m_rotVelocity.z * ROT_VELOCITY;
		SetRot(rot);
	}
	if (pos.y <= GEOWND)
	{
		pos.y = GEOWND;

		if (m_move.x < 0.4f && m_move.z < 0.4f) 
		{
			m_move.x = 0.0f;
			m_move.z = 0.0f;
		}
		else
		{
			m_move.y += BOUNCE;
		}
	}

	// 位置更新
	SetPosition(pos + m_move);

	if (m_nLife < 0)
	{// 自分の削除
		Uninit();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CDebris::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CDebris* CDebris::Create(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move, float fGravity, int nPriority)
{
	CDebris* pDebtisSpawner = nullptr;

	if (pDebtisSpawner == nullptr)
	{// インスタンス生成
		pDebtisSpawner = new CDebris(nPriority);

		if (pDebtisSpawner != nullptr)
		{
			pDebtisSpawner->SetPosition(pos);

			// 初期化処理
			pDebtisSpawner->Init();

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
HRESULT CDebris::Load(void)
{
	return S_OK;
}

//=====================================================
// テクスチャ破棄
//=====================================================
void CDebris::Unload(void)
{

}