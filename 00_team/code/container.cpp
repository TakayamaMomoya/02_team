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
#include "universal.h"
#include "itemWeapon.h"
#include "weaponManager.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const char* BODY_PATH = "data\\MODEL\\gimmick\\MysteryBox_Down.x";	// 本体のパス
	const char* CAP_PATH = "data\\MODEL\\gimmick\\MysteryBox_Up.x";	// 蓋のパス
}

//=====================================================
// コンストラクタ
//=====================================================
CContainer::CContainer(int nPriority) : CItem(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// デストラクタ
//=====================================================
CContainer::~CContainer()
{

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

//=====================================================
// 初期化処理
//=====================================================
HRESULT CContainer::Init(void)
{
	// 継承クラスの初期化
	CItem::Init();

	// 読み込み
	Load();

	m_info.state = STATE_NORMAL;

	return S_OK;
}

//=====================================================
// 読み込み処理
//=====================================================
void CContainer::Load(void)
{
	// 本体の読込
	int nIdx = CModel::Load((char*)BODY_PATH);
	SetIdxModel(nIdx);
	BindModel(nIdx);

	if (m_info.pCap == nullptr)
	{// 蓋の生成
		m_info.pCap = CObjectX::Create();

		if (m_info.pCap != nullptr)
		{
			// 蓋の読み込み
			int nIdx = CModel::Load((char*)CAP_PATH);
			m_info.pCap->SetIdxModel(nIdx);
			m_info.pCap->BindModel(nIdx);
		}
	}
}

//=====================================================
// 終了処理
//=====================================================
void CContainer::Uninit(void)
{
	if (m_info.pCap != nullptr)
	{
		m_info.pCap->Uninit();
		m_info.pCap = nullptr;
	}

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
				{// 箱を開く
					Open();
				}
			}
		}
	}
}

//=====================================================
// 箱を開く処理
//=====================================================
void CContainer::Open(void)
{
	// 箱を開く状態
	m_info.state = STATE_OPEN;

	// 武器の種類をランダムで設定
	CUniversal *pUniversal = CUniversal::GetInstance();

	CWeapon::TYPE type = (CWeapon::TYPE)WeaponRand();

	// 武器の設置
	CItemWeapon *pWeapon = CItemWeapon::Create(type);

	if (pWeapon != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		pWeapon->SetPosition(pos);
	}

	Uninit();
}

//=====================================================
// 武器のランダムで設定する処理
//=====================================================
int CContainer::WeaponRand(void)
{
	int anProb[CWeapon::TYPE::TYPE_MAX];	// 確率の保存用
	int nMinProb = INT_MAX;
	int nMax = 0;

	ZeroMemory(&anProb[0], sizeof(int) * CWeapon::TYPE::TYPE_MAX);

	// 武器マネージャーから各武器の確率を取得、最大値の設定
	CWeaponManager *pWeaponManager = CWeaponManager::GetInstance();

	if (pWeaponManager != nullptr)
	{
		for (int i = 0; i < CWeapon::TYPE::TYPE_MAX; i++)
		{
			anProb[i] = pWeaponManager->GetProb(i);

			if (anProb[i] > nMax)
			{
				nMax = anProb[i];
			}
		}
	}

	// 乱数の設定
	CUniversal *pUniversal = CUniversal::GetInstance();
	int nProb = pUniversal->RandRange(nMax,1);	// 期待値の合計を最大値として乱数を振る
	int nIdxWeapon = -1;

	for (int i = 0; i < CWeapon::TYPE::TYPE_MAX; i++)
	{
		if (nProb <= anProb[i])
		{// 確率内のとき
			if (anProb[i] < nMinProb)
			{// 他の当たった確率より低い場合のみ適用
				nIdxWeapon = i;
				nMinProb = anProb[i];
			}
		}
	}

	if (nIdxWeapon == -1)
	{
		assert(("武器の設定に失敗", false));
	}

	return nIdxWeapon;
}

//=====================================================
// 位置の設定
//=====================================================
void CContainer::SetPosition(D3DXVECTOR3 pos)
{
	// 継承クラスの設置
	CObjectX::SetPosition(pos);

	if (m_info.pCap != nullptr)
	{// 蓋の追従
		D3DXVECTOR3 pos = GetPosition();

		m_info.pCap->SetPosition(pos);
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