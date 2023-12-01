//*****************************************************
//
// レールガンの処理[weaponRailgun.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "weaponRailgun.h"
#include "inputjoypad.h"
#include "bullet.h"
#include "player.h"
#include "sound.h"
#include "animEffect3D.h"
#include "universal.h"
#include "debugproc.h"
#include "playerManager.h"
#include "effect3D.h"
#include "enemyManager.h"
#include "weaponManager.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int NUM_VTX = 4;	// 当たり判定の頂点数
}

//=====================================================
// コンストラクタ
//=====================================================
CRailgun::CRailgun(int nPriority) : CWeapon(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfoRailgun));
}

//=====================================================
// デストラクタ
//=====================================================
CRailgun::~CRailgun()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CRailgun::Init(void)
{
	// 継承クラスの初期化
	CWeapon::Init();

	// 固有情報入手
	CWeaponManager *pWeaponManager = CWeaponManager::GetInstance();

	if (pWeaponManager != nullptr)
	{
		CWeaponManager::SInfoRailgun info = pWeaponManager->GetRailgunInfo();

		m_info.fWidth = info.fWidth;
		m_info.fLength = info.fLength;
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CRailgun::Uninit(void)
{
	// 継承クラスの終了
	CWeapon::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CRailgun::Update(void)
{
	// 継承クラスの更新
	CWeapon::Update();
}

//=====================================================
// 攻撃処理
//=====================================================
void CRailgun::Attack(void)
{
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	if (pJoypad == nullptr)
	{
		return;
	}

	int nBullet = GetBullet();
	int nID = GetID();

	if (pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_RB,nID))
	{// 射撃
		int nCntShot = GetCntShot();

		if (nBullet > 0 && nCntShot == 0)
		{// 弾の発射
			// 当たり判定の発生
			Shot();

			// 弾を減らす
			nBullet--;
			SetBullet(nBullet);

			// 連射カウンターのリセット
			nCntShot = GetRapid();

			SetCntShot(nCntShot);
		}
		else
		{// 弾切れの場合

		}
	}
}

//=====================================================
// 射撃処理
//=====================================================
void CRailgun::Shot(void)
{
	// マズルの位置を設定
	D3DXMATRIX* pMtxWeapon = GetMatrix();
	D3DXMATRIX mtxMuzzle;
	universal::SetOffSet(&mtxMuzzle, *pMtxWeapon, D3DXVECTOR3(-18.0f, 6.0f, 0.0f));

	D3DXVECTOR3 posMuzzle =
	{
		mtxMuzzle._41,
		mtxMuzzle._42,
		mtxMuzzle._43,
	};

	// 頂点の設定
	D3DXVECTOR3 aPosVtx[NUM_VTX];
	D3DXMATRIX aMtxVtx[NUM_VTX];
	D3DXVECTOR3 aOffset[NUM_VTX] =
	{
		{ -m_info.fLength,0.0f,m_info.fWidth },
		{ 0.0f,0.0f,m_info.fWidth },
		{ 0.0f,0.0f,-m_info.fWidth },
		{ -m_info.fLength,0.0f,-m_info.fWidth },
	};

	for (int i = 0; i < NUM_VTX; i++)
	{
		universal::SetOffSet(&aMtxVtx[i], mtxMuzzle, aOffset[i]);

		aPosVtx[i] =
		{
			aMtxVtx[i]._41,
			0.0f,
			aMtxVtx[i]._43,
		};

#ifdef _DEBUG
		CEffect3D::Create(aPosVtx[i], 10.0f, 60, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif
	}

	// 敵との接触を判定する
	CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager == nullptr)
	{
		return;
	}

	// 先頭オブジェクトを代入
	CEnemy* pEnemy = pEnemyManager->GetHead();

	while (pEnemy != nullptr)
	{
		// 次のアドレスを保存
		CEnemy* pEnemyNext = pEnemy->GetNext();

		if (pEnemy != nullptr)
		{
			D3DXVECTOR3 posEnemy = pEnemy->GetPosition();

			bool bHit = universal::CubeCrossProduct(aPosVtx[0], aPosVtx[1], aPosVtx[2], aPosVtx[3], posEnemy);

			CWeapon::SInfo info = GetInfo();

			if (bHit)
			{
				pEnemy->Hit(info.fDamage);
			}
		}

		// 次のアドレスを代入
		pEnemy = pEnemyNext;
	}
}

//=====================================================
// 描画処理
//=====================================================
void CRailgun::Draw(void)
{
	// 継承クラスの描画
	CWeapon::Draw();
}