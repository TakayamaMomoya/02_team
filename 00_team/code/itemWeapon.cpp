//*****************************************************
//
// 武器アイテムの処理[ItemWeaponWeapon.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "ItemWeapon.h"
#include "manager.h"
#include "renderer.h"
#include "playerManager.h"
#include "weapon.h"
#include "player.h"

//=====================================================
// コンストラクタ
//=====================================================
CItemWeapon::CItemWeapon(int nPriority) : CItem(nPriority)
{
	m_type = CWeapon::TYPE_MAGNUM;
}

//=====================================================
// デストラクタ
//=====================================================
CItemWeapon::~CItemWeapon()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CItemWeapon::Init(void)
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
void CItemWeapon::Load(void)
{
	char* apPath[CWeapon::TYPE_MAX] =
	{
		"data\\MODEL\\weapon\\magnum.x",
		"data\\MODEL\\weapon\\mac10.x",
	};

	// モデルの読込
	int nIdx = CModel::Load(apPath[m_type]);
	SetIdxModel(nIdx);
	BindModel(nIdx);
}

//=====================================================
// 終了処理
//=====================================================
void CItemWeapon::Uninit(void)
{
	// 継承クラスの終了
	CItem::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CItemWeapon::Update(void)
{
	// 継承クラスの更新
	CItem::Update();
}

//=====================================================
// アイテム入手時の処理
//=====================================================
void CItemWeapon::Interact(CObject *pObj)
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
					// 効果の付与
					ApplyEffect(pPlayer);

					Uninit();
				}
			}
		}
	}
}

//=====================================================
// 効果を適用する処理
//=====================================================
void CItemWeapon::ApplyEffect(CPlayer* pPlayer)
{
	if (pPlayer == nullptr)
	{
		return;
	}

	switch (m_type)
	{
	case CWeapon::TYPE_MAGNUM:

		pPlayer->SetWeapon(CWeapon::TYPE_MAGNUM);

		break;
	case CWeapon::TYPE_MACHINEGUN:

		pPlayer->SetWeapon(CWeapon::TYPE_MACHINEGUN);

		break;
	default:
		break;
	}
}

//=====================================================
// 描画処理
//=====================================================
void CItemWeapon::Draw(void)
{
	// 継承クラスの描画
	CItem::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CItemWeapon *CItemWeapon::Create(CWeapon::TYPE type)
{
	if (type >= CWeapon::TYPE_MAX || type < 0)
	{
		assert(("想定外の武器を出そうとしてます",false));
	}

	CItemWeapon *pItemWeapon = nullptr;

	if (pItemWeapon == nullptr)
	{
		pItemWeapon = new CItemWeapon;

		if (pItemWeapon != nullptr)
		{
			pItemWeapon->m_type = type;

			// 初期化
			pItemWeapon->Init();
		}
	}

	return pItemWeapon;
}