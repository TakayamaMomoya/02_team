//*****************************************************
//
// マグナムの処理[MagnumMagnum.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "weaponMagnum.h"
#include "inputjoypad.h"
#include "bullet.h"
#include "player.h"
#include "weaponManager.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define BULLET_SPEED	(2.0f)	// 弾の速度

//=====================================================
// コンストラクタ
//=====================================================
CMagnum::CMagnum(int nPriority) : CWeapon(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CMagnum::~CMagnum()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CMagnum::Init(void)
{
	// 継承クラスの初期化
	CWeapon::Init();

	// パラメーター取得
	CWeaponManager* pWeaponManager = CWeaponManager::GetInstance();

	if (pWeaponManager != nullptr)
	{
		CWeapon::SInfo info = pWeaponManager->GetBaseInfo(CWeapon::TYPE_MAGNUM);

		SetMaxBullet(info.nMaxBullet);
		SetRapid(info.nRapid);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMagnum::Uninit(void)
{
	// 継承クラスの終了
	CWeapon::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CMagnum::Update(void)
{
	// 継承クラスの更新
	CWeapon::Update();
}

//=====================================================
// 攻撃処理
//=====================================================
void CMagnum::Attack(void)
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
		if (nBullet > 0)
		{// 弾の発射
			D3DXMATRIX* pMtx = GetMatrix();

			D3DXVECTOR3 pos =
			{// 取っ手の位置を取得
				pMtx->_41,
				pMtx->_42,
				pMtx->_43,
			};

			D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

			CPlayer* pPlayer = GetPlayer();

			if (pPlayer != nullptr)
			{// プレイヤーの向きに移動量を設定
				D3DXVECTOR3 rot = pPlayer->GetRot();

				move =
				{
					sinf(rot.y) * BULLET_SPEED,
					0.0f,
					cosf(rot.y) * BULLET_SPEED,
				};
			}

			// 弾を発射
			CBullet::Create(pos, -move, 100, CBullet::TYPE_PLAYER, false);

			// 弾を減らす
			nBullet--;
			SetBullet(nBullet);
		}
		else
		{// 弾切れの場合

		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CMagnum::Draw(void)
{
	// 継承クラスの描画
	CWeapon::Draw();
}