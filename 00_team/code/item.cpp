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
#include "billboard.h"
#include "texture.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define SIZE_INTERACT	(20.0f)	// インタラクト表示のサイズ

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

	if (m_pInteract != nullptr)
	{
		m_pInteract->Uninit();
		m_pInteract = nullptr;
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
			if (m_pInteract == nullptr)
			{// インタラクト表示生成
				D3DXVECTOR3 pos = GetPosition();

				pos.y += 50.0f;

				m_pInteract = CBillboard::Create(pos, SIZE_INTERACT, SIZE_INTERACT);

				if (m_pInteract != nullptr)
				{
					int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\interact.png");
					m_pInteract->SetIdxTexture(nIdx);
					m_pInteract->SetZTest(true);
				}
			}

			// 当たったオブジェクトの取得
			CObject *pObj = m_pCollisionSphere->GetOther();

			// アイテム入手処理
			//GetItem(pObj);
		}
		else
		{
			if (m_pInteract != nullptr)
			{// インタラクト表示削除
				m_pInteract->Uninit();
				m_pInteract = nullptr;
			}
		}
	}
}

//=====================================================
// アイテム入手時の処理
//=====================================================
void CItem::GetItem(CObject *pObj)
{

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
CItem *CItem::Create(void)
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