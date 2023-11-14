//*****************************************************
//
// 修理アイテムの処理[ItemRepair.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "ItemRepair.h"
#include "playerManager.h"
#include "player.h"

//=====================================================
// コンストラクタ
//=====================================================
CItemRepair::CItemRepair(int nPriority) : CItem(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CItemRepair::~CItemRepair()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CItemRepair::Init(void)
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
void CItemRepair::Load(void)
{
	// モデルの読込
	int nIdx = CModel::Load("data\\MODEL\\item\\repairKit.x");
	SetIdxModel(nIdx);
	BindModel(nIdx);
}

//=====================================================
// 終了処理
//=====================================================
void CItemRepair::Uninit(void)
{
	// 継承クラスの終了
	CItem::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CItemRepair::Update(void)
{
	// 継承クラスの更新
	CItem::Update();
}

//=====================================================
// アイテム入手時の処理
//=====================================================
void CItemRepair::GetItem(CObject *pObj)
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
				bool bGet = pPlayer->InputInteract();

				if (bGet)
				{

				}
			}
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CItemRepair::Draw(void)
{
	// 継承クラスの描画
	CItem::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CItemRepair *CItemRepair::Create(void)
{
	CItemRepair *pItemRepair = nullptr;

	if (pItemRepair == nullptr)
	{
		pItemRepair = new CItemRepair;

		if (pItemRepair != nullptr)
		{
			// 初期化
			pItemRepair->Init();
		}
	}

	return pItemRepair;
}