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
#include "object3D.h"
#include "objectX.h"
#include "particle.h"
#include "debugproc.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const char* MISSILE_MODEL_PATH = "data\\MODEL\\weapon\\atomic.x";	// ミサイル本体のモデルパス
	const float INITIAL_LIFE = 1.0f;	// 初期体力
	const float INITIAL_SPEED = 12.0f;	// 初期速度
	const float INITIAL_SPEED_MAX = 12.0f;	// 初期の最大速度
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
	ZeroMemory(&m_info, sizeof(SInfo));
	ZeroMemory(&m_infoVisual, sizeof(SInfoVisual));

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
	// 見た目の生成
	CreateVisual();

	m_info.fLife = INITIAL_LIFE;
	m_info.fSpeed = INITIAL_SPEED;

	return S_OK;
}

//=====================================================
// 見た目の生成
//=====================================================
void CMissile::CreateVisual(void)
{
	if (m_infoVisual.pMissile == nullptr)
	{
		m_infoVisual.pMissile = CObjectX::Create();

		if (m_infoVisual.pMissile != nullptr)
		{
			// モデルの読込
			int nIdx = CModel::Load((char*)MISSILE_MODEL_PATH);
			m_infoVisual.pMissile->BindModel(nIdx);
		}
	}

	if (m_infoVisual.pBackLight == nullptr)
	{
		//m_infoVisual.pBackLight = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		if (m_infoVisual.pBackLight != nullptr)
		{

		}
	}
}

//=====================================================
// 終了処理
//=====================================================
void CMissile::Uninit(void)
{
	if (m_info.pCollisionSphere != nullptr)
	{// 当たり判定の破棄
		m_info.pCollisionSphere->Uninit();

		m_info.pCollisionSphere = nullptr;
	}

	// 見た目の破棄
	DeleteVisual();

	Release();
}

//=====================================================
// 見た目の破棄
//=====================================================
void CMissile::DeleteVisual(void)
{
	if (m_infoVisual.pMissile != nullptr)
	{
		m_infoVisual.pMissile->Uninit();
		m_infoVisual.pMissile = nullptr;
	}

	if (m_infoVisual.pBackLight != nullptr)
	{
		m_infoVisual.pBackLight->Uninit();
		m_infoVisual.pBackLight = nullptr;
	}
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

	m_info.fLife -= fTIck;

	// 移動の管理
	ManageMove();

	// 見た目の追従
	FollowVisual();

	// パーティクルの生成
	CParticle::Create(m_info.pos, CParticle::TYPE_MISSILE_SMOKE);
	CParticle::Create(m_info.pos, CParticle::TYPE_MISSILE_SPARK);

	if (m_info.pCollisionSphere != nullptr)
	{// 当たり判定の管理
		// 敵との当たり判定

		if (m_info.pCollisionSphere->TriggerCube(CCollision::TAG_BLOCK))
		{// ブロックとの当たり判定
			Death();
		}
	}


	if (bHit == false)
	{
		if (m_info.fLife < 0)
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
// 移動の管理
//=====================================================
void CMissile::ManageMove(void)
{
	D3DXVECTOR3 move = m_info.move;
	D3DXVECTOR3 rot = m_info.rot;

	m_info.posOld = m_info.pos;

	// 移動量の設定
	move += D3DXVECTOR3
	{
		sinf(m_info.rot.y) * m_info.fSpeed,
		0.0f,
		cosf(m_info.rot.y) * m_info.fSpeed
	};

	m_info.move -= move;

	// 速度制限
	universal::LimitSpeed(&m_info.move, INITIAL_SPEED_MAX);

	// 移動量を加算
	m_info.pos += m_info.move;
}

//=====================================================
// 見た目の追従
//=====================================================
void CMissile::FollowVisual(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = m_info.rot;

	if (m_infoVisual.pMissile != nullptr)
	{
		m_infoVisual.pMissile->SetPosition(pos);
		m_infoVisual.pMissile->SetRot(rot);
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
	D3DXMatrixIdentity(&m_info.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_info.rot.y, m_info.rot.x, m_info.rot.z);
	D3DXMatrixMultiply(&m_info.mtxWorld, &m_info.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_info.pos.x, m_info.pos.y, m_info.pos.z);
	D3DXMatrixMultiply(&m_info.mtxWorld, &m_info.mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &m_info.mtxWorld);

#ifdef _DEBUG
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\nミサイル位置[%f,%f,%f]", m_info.pos.x, m_info.pos.y, m_info.pos.z);
#endif
}

//=====================================================
// 生成処理
//=====================================================
CMissile *CMissile::Create(void)
{
	CMissile *pMissile = nullptr;

	if (pMissile == nullptr)
	{// インスタンス生成
		pMissile = new CMissile;

		if (pMissile != nullptr)
		{
			if (pMissile->m_info.pCollisionSphere == nullptr)
			{// 当たり判定生成
				pMissile->m_info.pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_PLAYERBULLET, CCollision::TYPE_SPHERE, pMissile);
			}

			if (pMissile->m_info.pCollisionSphere != nullptr)
			{
				pMissile->m_info.pCollisionSphere->SetPosition(pMissile->m_info.pos);

				pMissile->m_info.pCollisionSphere->SetRadius(20.0f);
			}

			// 初期化処理
			pMissile->Init();
		}
	}

	return pMissile;
}