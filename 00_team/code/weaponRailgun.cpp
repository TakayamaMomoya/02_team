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
		{ 0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f },
	};

	for (int i = 0; i < NUM_VTX; i++)
	{
		universal::SetOffSet(&aMtxVtx[i], mtxMuzzle, aOffset[i]);

		D3DXVECTOR3 aPosVtx =
		{
			aMtxVtx[i]._41,
			aMtxVtx[i]._42,
			aMtxVtx[i]._43,
		};
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

			if (bHit)
			{
				pEnemy->Hit(5.0f);
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