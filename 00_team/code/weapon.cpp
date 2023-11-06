//*****************************************************
//
// 武器の処理[weapon.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "weapon.h"
#include "weaponMagnum.h"
#include "motion.h"
#include "player.h"
#include "universal.h"

//=====================================================
// コンストラクタ
//=====================================================
CWeapon::CWeapon(int nPriority) : CObjectX(nPriority)
{
	m_nIdxHand = 0;
	m_nIdxPlayer = 0;
}

//=====================================================
// デストラクタ
//=====================================================
CWeapon::~CWeapon()
{

}

//=====================================================
// 生成処理
//=====================================================
CWeapon *CWeapon::Create(CWeapon::TYPE type, int nIdxhand)
{
	CWeapon *pWeapon = nullptr;

	if (pWeapon == nullptr)
	{
		switch (type)
		{
		case CWeapon::TYPE_MAGNUM:
			// マグナムの生成
			pWeapon = new CMagnum;

			break;
		case CWeapon::TYPE_MACHINEGUN:
			break;
		default:
			break;
		}

		if (pWeapon != nullptr)
		{
			pWeapon->m_nIdxHand = nIdxhand;

			// 初期化
			pWeapon->Init();
		}
	}

	return pWeapon;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CWeapon::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// モデルの読込
	int nIdx = CModel::Load("data\\MODEL\\weapon\\shotgun.x");
	SetIdxModel(nIdx);
	BindModel(nIdx);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CWeapon::Uninit(void)
{
	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CWeapon::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();

	// プレイヤーの手とマトリックスをかけ合わせる
	FollowPlayerHand();
}

//=====================================================
// プレイヤーの手を追従
//=====================================================
void CWeapon::FollowPlayerHand(void)
{
	CUniversal *pUniversal = CUniversal::GetInstance();

	if (m_pPlayer == nullptr)
	{
		return;
	}

	CMotion *pBody = m_pPlayer->GetBody();

	if (pBody != nullptr)
	{
		CParts *pParts = pBody->GetParts(m_nIdxHand)->pParts;

		if (pParts != nullptr)
		{
			D3DXMATRIX *pMtx = GetMatrix();
			D3DXMATRIX *pMtxPart = pParts->GetMatrix();
			D3DXVECTOR3 offset = { 0.0f,0.0f,0.0f };

			pUniversal->SetOffSet(pMtx, *pMtxPart, offset);
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CWeapon::Draw(void)
{
	// 継承クラスの描画
	CObjectX::JustDraw();
}

//=====================================================
// プレイヤー設定
//=====================================================
void CWeapon::SetPlayer(CPlayer *pPlayer)
{
	m_pPlayer = pPlayer;

	if (m_pPlayer != nullptr)
	{
		m_nIdxPlayer = pPlayer->GetID();
	}
}