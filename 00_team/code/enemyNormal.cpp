//*****************************************************
//
// 通常敵の処理[enemyNormal.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemyNormal.h"
#include "manager.h"
#include "score.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include <stdio.h>
#include "player.h"
#include "game.h"
#include "enemyManager.h"
#include "debrisSpawner.h"
#include "block.h"

//=====================================================
// コンストラクタ
//=====================================================
CEnemyNormal::CEnemyNormal()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyNormal::~CEnemyNormal()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyNormal::Init(void)
{
	// 継承クラスの初期化
	CEnemy::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyNormal::Uninit(void)
{
	// 継承クラスの終了
	CEnemy::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyNormal::Update(void)
{
	// 継承クラスの更新
	CEnemy::Update();

	CBlock *pBlock = GetTouchBlock();

	if (pBlock != nullptr)
	{
		pBlock->Hit(5.0f);

		// 破片を生成
		CDebrisSpawner::Create(D3DXVECTOR3(pBlock->GetPosition().x, pBlock->GetPosition().y + 50.0f, pBlock->GetPosition().z), CDebrisSpawner::TYPE::TYPE_EXPLOSION, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyNormal::Draw(void)
{
	// 継承クラスの描画
	CEnemy::Draw();
}