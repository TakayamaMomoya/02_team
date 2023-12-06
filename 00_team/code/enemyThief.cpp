//*****************************************************
//
// 泥棒敵の処理[enemyThief.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemyThief.h"
#include "manager.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include <stdio.h>
#include "player.h"
#include "game.h"
#include "enemyManager.h"
#include "debrisSpawner.h"
#include "block.h"
#include "universal.h"
#include "rocket.h"
#include "motion.h"

//=====================================================
// コンストラクタ
//=====================================================
CEnemyThief::CEnemyThief()
{
	m_bTakeRepair = false;
}

//=====================================================
// デストラクタ
//=====================================================
CEnemyThief::~CEnemyThief()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyThief::Init(void)
{
	// 継承クラスの初期化
	CEnemy::Init();

	// 歩きモーションに設定
	CMotion *pBody = GetBody();

	if (pBody != nullptr)
	{
		pBody->SetMotion(MOTION_WALK);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyThief::Uninit(void)
{
	// 継承クラスの終了
	CEnemy::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyThief::Update(void)
{
	// 継承クラスの更新
	CEnemy::Update();

	CBlock *pBlock = GetTouchBlock();

	if (pBlock != nullptr)
	{
		pBlock->Hit(5.0f);
	}

	CEnemy::STATE state = GetState();

	if (state == CEnemy::STATE::STATE_DEATH)
	{// 死亡モーション
		int nMotion = GetMotion();

		if (nMotion != MOTION_DEATH)
		{
			SetMotion(MOTION_DEATH);
		}
	}

	// ロケットを追う処理
	ChaseRocket();
}

//=====================================================
// ロケットを追う処理
//=====================================================
void CEnemyThief::ChaseRocket(void)
{
	// ゲーム状態によって追跡させない
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		CGame::STATE state = pGame->GetState();

		if (state != CGame::STATE::STATE_NORMAL)
		{
			return;
		}
	}

	// 目標位置の取得
	D3DXVECTOR3 posTarget = { 0.0f,0.0f,0.0f };

	CRocket *pRocket = CRocket::GetInstance();

	if (pRocket != nullptr)
	{
		posTarget = pRocket->GetPosition();
	}

	// 移動量の設定
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 vecDiff = posTarget - pos;
	D3DXVECTOR3 move = GetMove();

	D3DXVec3Normalize(&vecDiff, &vecDiff);

	float fSpeed = GetSpeed();

	vecDiff *= fSpeed;

	move += vecDiff;

	SetMove(move);

	// 向きを目標方向に補正
	float fAngleDist = atan2f(vecDiff.x, vecDiff.z);
	D3DXVECTOR3 rot = GetRot();

	fAngleDist += D3DX_PI;

	universal::FactingRot(&rot.y, fAngleDist, 0.1f);

	SetRot(rot);
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyThief::Draw(void)
{
	// 継承クラスの描画
	CEnemy::Draw();
}