//*****************************************************
//
// マシンガンの処理[weaponMachinegun.cpp]
// Author:日野澤匠泉
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "weaponMachinegun.h"
#include "inputjoypad.h"
#include "bullet.h"
#include "player.h"
#include "universal.h"
#include "sound.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define BULLET_SPEED	(10.0f)	// 弾の速度

//=====================================================
// コンストラクタ
//=====================================================
CMachinegun::CMachinegun(int nPriority) : CWeapon(nPriority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CMachinegun::~CMachinegun()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CMachinegun::Init(void)
{
	// 継承クラスの初期化
	CWeapon::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMachinegun::Uninit(void)
{
	// 継承クラスの終了
	CWeapon::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CMachinegun::Update(void)
{
	// 継承クラスの更新
	CWeapon::Update();
}

//=====================================================
// 攻撃処理	Autor:日野澤
//=====================================================
void CMachinegun::Attack(void)
{
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();
	CUniversal *pUniversal = CUniversal::GetInstance();

	if (pJoypad == nullptr)
	{
		return;
	}

	int nBullet = GetBullet();
	int nID = GetID();

	if (pJoypad->GetPress(CInputJoypad::PADBUTTONS_RB, nID))
	{// 射撃
		int nCntShot = GetCntShot();

		if (nBullet > 0 && nCntShot == 0)
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

				int nRange = pUniversal->RandRange(10, -10);

				float fRand = nRange * 0.01f;

				rot.y += fRand;

				move =
				{
					sinf(rot.y) * BULLET_SPEED,
					0.0f,
					cosf(rot.y) * BULLET_SPEED,
				};
			}

			// 威力取得
			float fDamage = GetDamage();

			// 弾を発射
			CBullet::Create(pos, -move, 100, CBullet::TYPE_PLAYER, false,2.0f, fDamage);

			CSound* pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				// マグナム発砲音
				pSound->Play(pSound->LABEL_SE_GUNSHOT_01);
			}

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
// 描画処理
//=====================================================
void CMachinegun::Draw(void)
{
	// 継承クラスの描画
	CWeapon::Draw();
}