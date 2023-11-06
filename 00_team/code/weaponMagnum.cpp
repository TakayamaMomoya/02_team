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

	int nID = GetID();

	if (pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_RB,nID))
	{
		D3DXMATRIX *pMtx = GetMatrix();

		D3DXVECTOR3 pos = 
		{
			pMtx->_41,
			pMtx->_42,
			pMtx->_43,
		};

		D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

		CPlayer *pPlayer = GetPlayer();

		if (pPlayer != nullptr)
		{
			D3DXVECTOR3 rot = pPlayer->GetRot();

			move = 
			{
				sinf(rot.y) * BULLET_SPEED,
				0.0f,
				cosf(rot.y) * BULLET_SPEED,
			};
		}

		CBullet::Create(pos, -move, 100, CBullet::TYPE_PLAYER, false);
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