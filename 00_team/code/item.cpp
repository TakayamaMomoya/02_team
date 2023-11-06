//*****************************************************
//
// アイテムの処理[item.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "playerManager.h"

//=====================================================
// コンストラクタ
//=====================================================
CItem::CItem(int nPriority) : CObjectX(nPriority)
{
	m_pCollisionSphere = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CItem::~CItem()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CItem::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// モデルの読込
	int nIdx = CModel::Load("data\\MODEL\\weapon\\shotgun.x");
	SetIdxModel(nIdx);
	BindModel(nIdx);

	if (m_pCollisionSphere == nullptr)
	{// 当たり判定の生成
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ITEM, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionSphere != nullptr)
		{
			m_pCollisionSphere->SetRadius(10.0f);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CItem::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->Uninit();
		m_pCollisionSphere = nullptr;
	}

	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CItem::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();

	if (m_pCollisionSphere != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		m_pCollisionSphere->SetPosition(pos);

		// プレイヤーとの当たり判定
		if (m_pCollisionSphere->SphereCollision(CCollision::TAG_PLAYER))
		{
			// 当たったオブジェクトの取得
			CObject *pObj = m_pCollisionSphere->GetOther();

			// アイテム入手処理
			GetItem(pObj);
		}
	}
}

//=====================================================
// アイテム入手時の処理
//=====================================================
void CItem::GetItem(CObject *pObj)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pObj == nullptr || pPlayerManager == nullptr)
	{
		return;
	}

	// プレイヤー取得
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

		if (pPlayer != nullptr)
		{
			if ((CObject*)pPlayer == pObj)
			{// プレイヤー検出
				int n = 9;
			}
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CItem::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CItem *CItem::Create()
{
	CItem *pItem = nullptr;

	if (pItem == nullptr)
	{
		pItem = new CItem;

		if (pItem != nullptr)
		{
			// 初期化
			pItem->Init();
		}
	}

	return pItem;
}