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
#include "weapon.h"
#include "player.h"

//=====================================================
// コンストラクタ
//=====================================================
CItem::CItem(int nPriority) : CObjectX(nPriority)
{
	m_type = TYPE_MAGNUM;
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

	// 読み込み
	Load();

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
// 読み込み処理
//=====================================================
void CItem::Load(void)
{
	char* apPath[CItem::TYPE_MAX] =
	{
		"data\\MODEL\\weapon\\shotgun.x",
		"data\\MODEL\\weapon\\shotgun.x",
		"data\\MODEL\\weapon\\shotgun.x",
	};

	// モデルの読込
	int nIdx = CModel::Load(apPath[m_type]);
	SetIdxModel(nIdx);
	BindModel(nIdx);
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
				// 効果の付与
				ApplyEffect(pPlayer);

				Uninit();
			}
		}
	}
}

//=====================================================
// 効果を適用する処理
//=====================================================
void CItem::ApplyEffect(CPlayer* pPlayer)
{
	if (pPlayer == nullptr)
	{
		return;
	}

	switch (m_type)
	{
	case CItem::TYPE_MAGNUM:

		pPlayer->SetWeapon(CWeapon::TYPE_MAGNUM);

		break;
	case CItem::TYPE_MACHINEGUN:
		break;
	case CItem::TYPE_RIFLE:
		break;
	default:
		break;
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
CItem *CItem::Create(TYPE type)
{
	CItem *pItem = nullptr;

	if (pItem == nullptr)
	{
		pItem = new CItem;

		if (pItem != nullptr)
		{
			pItem->m_type = type;

			// 初期化
			pItem->Init();
		}
	}

	return pItem;
}