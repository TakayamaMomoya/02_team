//*****************************************************
//
// 弾処理[Missile.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "missile.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const int EDGE_ORBIT = 20;	// 軌跡の辺の数
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
int CMissile::m_nNumAll = 0;	// 総数

//=====================================================
// コンストラクタ
//=====================================================
CMissile::CMissile(int nPriority) : CObject(nPriority)
{
	m_fLife = 0.0f;
	m_fDamage = 0.0f;
	m_move = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_pos = { 0.0f,0.0f,0.0f };
	m_posOld = { 0.0f,0.0f,0.0f };
	m_pCollisionSphere = nullptr;

	// 総数カウントアップ
	m_nNumAll++;
}

//=====================================================
// デストラクタ
//=====================================================
CMissile::~CMissile()
{
	m_nNumAll--;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CMissile::Init(void)
{
	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMissile::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{// 当たり判定の消去
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMissile::Update(void)
{
	// 変数宣言
	bool bHit = false;

	// 寿命減衰
	float fTIck = CManager::GetTick();

	m_fLife -= fTIck;

	m_posOld = m_pos;

	// 位置の更新
	m_pos += m_move;

	if (m_pCollisionSphere != nullptr)
	{// 当たり判定の管理
		// 敵との当たり判定

		if (m_pCollisionSphere->TriggerCube(CCollision::TAG_BLOCK))
		{// ブロックとの当たり判定
			Death();
		}
	}

	if (bHit == false)
	{
		if (m_fLife < 0)
		{// 自分の削除
			Death();
		}
	}
	else
	{
		Death();
	}
}

//=====================================================
// 死亡処理
//=====================================================
void CMissile::Death(void)
{
	// 終了処理
	Uninit();
}

//=====================================================
// 描画処理
//=====================================================
void CMissile::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//=====================================================
// 生成処理
//=====================================================
CMissile *CMissile::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move)
{
	CMissile *pMissile = nullptr;

	if (pMissile == nullptr)
	{// インスタンス生成
		pMissile = new CMissile;

		if (pMissile != nullptr)
		{
			pMissile->m_move = move;
			pMissile->m_pos = pos;
			pMissile->m_posOld = pos;

			if (pMissile->m_pCollisionSphere == nullptr)
			{// 当たり判定生成
				pMissile->m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_PLAYERBULLET, CCollision::TYPE_SPHERE, pMissile);
			}

			if (pMissile->m_pCollisionSphere != nullptr)
			{
				pMissile->m_pCollisionSphere->SetPosition(pMissile->m_pos);

				pMissile->m_pCollisionSphere->SetRadius(20.0f);
			}

			// 初期化処理
			pMissile->Init();
		}
	}

	return pMissile;
}