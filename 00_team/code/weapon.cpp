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
#include "weaponMachinegun.h"
#include "weaponManager.h"
#include "motion.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"

//=====================================================
// コンストラクタ
//=====================================================
CWeapon::CWeapon(int nPriority) : CObjectX(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
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
			// マシンガンの生成
			pWeapon = new CMachinegun;

			break;
		default:
			break;
		}

		if (pWeapon != nullptr)
		{
			pWeapon->m_info.nIdxHand = nIdxhand;
			pWeapon->m_info.type = type;

			// 初期化
			pWeapon->Init();

			// モデルの読み込み
			char* apPath[CWeapon::TYPE_MAX] =
			{
				"data\\MODEL\\weapon\\magnum.x",
				"data\\MODEL\\weapon\\mac10.x",
			};

			int nIdx = CModel::Load(apPath[type]);
			pWeapon->SetIdxModel(nIdx);
			pWeapon->BindModel(nIdx);
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

	// モデルの読込
	int nIdx = CModel::Load("data\\MODEL\\weapon\\shotgun.x");
	BindModel(nIdx);

	// 基底パラメーター取得
	CWeaponManager* pWeaponManager = CWeaponManager::GetInstance();

	if (pWeaponManager != nullptr)
	{
		CWeapon::SInfo info = pWeaponManager->GetBaseInfo(m_info.type);

		SetMaxBullet(info.nMaxBullet);
		SetRapid(info.nRapid);
	}

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

	if (m_info.nCntShot > 0)
	{
		m_info.nCntShot--;
	}
}

//=====================================================
// プレイヤーの手を追従
//=====================================================
void CWeapon::FollowPlayerHand(void)
{
	CUniversal *pUniversal = CUniversal::GetInstance();

	if (m_info.pPlayer == nullptr)
	{
		return;
	}

	CMotion *pBody = m_info.pPlayer->GetBody();

	if (pBody != nullptr)
	{
		CParts *pParts = pBody->GetParts(m_info.nIdxHand)->pParts;

		if (pParts != nullptr)
		{
			D3DXMATRIX *pMtx = GetMatrix();
			D3DXMATRIX *pMtxPart = pParts->GetMatrix();
			D3DXVECTOR3 offset = { -10.0f,0.0f,0.0f };

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

	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n最大弾数[%d]", m_info.nMaxBullet);
	pDebugProc->Print("\n弾数[%d]", m_info.nNumBullet);
	pDebugProc->Print("\n連射力[%d]", m_info.nRapid);
}

//=====================================================
// プレイヤー設定
//=====================================================
void CWeapon::SetPlayer(CPlayer *pPlayer)
{
	m_info.pPlayer = pPlayer;

	if (m_info.pPlayer != nullptr)
	{
		m_info.nIdxPlayer = pPlayer->GetID();
	}
}

//=====================================================
// 弾数設定
//=====================================================
void CWeapon::SetBullet(int nBullet)
{
	m_info.nNumBullet = nBullet;

	if (m_info.nNumBullet <= 0)
	{// 弾切れした場合、破棄
		if (m_info.pPlayer != nullptr)
		{
			m_info.pPlayer->ReleaseWeapon();
		}

		Uninit();
	}
	else if (m_info.nNumBullet > m_info.nMaxBullet)
	{// 最大数を越えた場合の補正
		m_info.nNumBullet = m_info.nMaxBullet;
	}
}

//=====================================================
// 最大弾数設定
//=====================================================
void CWeapon::SetMaxBullet(int nBullet)
{
	m_info.nMaxBullet = nBullet;
	m_info.nNumBullet = nBullet;
}