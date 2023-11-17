//*****************************************************
//
// コンテナーの処理[container.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "Container.h"
#include "manager.h"
#include "renderer.h"
#include "playerManager.h"
#include "weapon.h"
#include "player.h"

//=====================================================
// コンストラクタ
//=====================================================
CContainer::CContainer(int nPriority) : CItem(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CContainer::~CContainer()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CContainer::Init(void)
{
	// 継承クラスの初期化
	CItem::Init();

	// 読み込み
	Load();

	return S_OK;
}

//=====================================================
// 読み込み処理
//=====================================================
void CContainer::Load(void)
{

}

//=====================================================
// 終了処理
//=====================================================
void CContainer::Uninit(void)
{
	// 継承クラスの終了
	CItem::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CContainer::Update(void)
{
	// 継承クラスの更新
	CItem::Update();
}

//=====================================================
// アイテム入手時の処理
//=====================================================
void CContainer::Interact(CObject *pObj)
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
			{// プレイヤーのインタラクト検出
				bool bGet = pPlayer->InputInteract();

				if (bGet)
				{
					Uninit();
				}
			}
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CContainer::Draw(void)
{
	// 継承クラスの描画
	CItem::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CContainer *CContainer::Create(void)
{
	CContainer *pContainer = nullptr;

	if (pContainer == nullptr)
	{
		pContainer = new CContainer;

		if (pContainer != nullptr)
		{
			// 初期化
			pContainer->Init();
		}
	}

	return pContainer;
}