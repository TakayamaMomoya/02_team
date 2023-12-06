//*****************************************************
//
// 敵マネージャー[enemyManager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemyManager.h"
#include "enemyNormal.h"
#include "enemyThief.h"
#include "manager.h"
#include "camera.h"
#include "universal.h"
#include <stdio.h>
#include "game.h"
#include "rocket.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int RAND_SPAWN = 1000;	// スポーン範囲
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CEnemyManager *CEnemyManager::m_pEnemyManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CEnemyManager::CEnemyManager()
{
	m_nCntSpawn = 0;
	m_nMinTimeSpawnThief = 0;
	m_nMaxTimeSpawnThief = 0;
	m_fTimerThief = 0.0f;
	m_fTimeSpawnThief = 0.0f;
	m_pThief = nullptr;

	m_pHead = nullptr;
	m_pTail = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CEnemyManager::~CEnemyManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CEnemyManager *CEnemyManager::Create(void)
{
	if (m_pEnemyManager == nullptr)
	{// インスタンス生成
		m_pEnemyManager = new CEnemyManager;

		// 初期化処理
		m_pEnemyManager->Init();
	}

	return m_pEnemyManager;
}

//=====================================================
// 敵の生成処理
//=====================================================
CEnemy *CEnemyManager::CreateEnemy(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	char *apPath[CEnemy::TYPE_MAX] = 
	{
		nullptr,
		"data\\MOTION\\motionEnemy00.txt",
		"data\\MOTION\\motionEnemy01.txt",
	};

	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// インスタンス生成
		switch (type)
		{
		case CEnemy::TYPE_NORMAL:

			pEnemy = new CEnemyNormal;

			break;
		case CEnemy::TYPE_THIEF:

			pEnemy = new CEnemyThief;

			break;
		default:
			break;
		}

		if (pEnemy != nullptr)
		{
			// 位置設定
			pEnemy->SetPosition(pos);

			// モーション読込
			pEnemy->Load(apPath[type]);

			// 初期化処理
			pEnemy->Init();
		}
	}

	return pEnemy;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyManager::Init(void)
{
	// 読込処理
	Load();

	// 最初の出現時間設定
	m_fTimeSpawnThief = (float)universal::RandRange(m_nMaxTimeSpawnThief, m_nMinTimeSpawnThief);

	return S_OK;
}

//=====================================================
// 読込処理
//=====================================================
void CEnemyManager::Load(void)
{
	// 変数宣言
	char cTemp[256];
	int nCntAttack = 0;

	// ファイルから読み込む
	FILE *pFile = fopen("data\\TEXT\\enemy.txt", "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "TIME_SPAWN_THIEF") == 0)
			{// 初期体力
				(void)fscanf(pFile, "%s", &cTemp[0]);

				(void)fscanf(pFile, "%d", &m_nMinTimeSpawnThief);
				(void)fscanf(pFile, "%d", &m_nMaxTimeSpawnThief);
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		assert(("敵情報読み込みに失敗", false));
	}
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyManager::Uninit(void)
{
	m_pEnemyManager = nullptr;

	m_pThief = nullptr;

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyManager::Update(void)
{
	// ゲーム状態によってスポーンさせない
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		CGame::STATE state = pGame->GetState();

		if (state != CGame::STATE::STATE_NORMAL)
		{
			return;
		}
	}

	// 通常敵のスポーン
	m_nCntSpawn++;

	if (m_nCntSpawn >= 60)
	{
		D3DXVECTOR3 posCenter = { 0.0f,0.0f,0.0f };

		// 出現する座標を設定
		posCenter.x = (float)universal::RandRange(RAND_SPAWN, -RAND_SPAWN);
		posCenter.z = (float)universal::RandRange(RAND_SPAWN, -RAND_SPAWN);

		// 位置の正規化
		D3DXVec3Normalize(&posCenter, &posCenter);
		posCenter *= RAND_SPAWN;

		// 敵スポーン
		CreateEnemy(posCenter, CEnemy::TYPE::TYPE_NORMAL);

		m_nCntSpawn = 0;
	}

	// 泥棒敵のスポーン
	CRocket *pRocket = CRocket::GetInstance();

	if (pRocket != nullptr && m_pThief == nullptr)
	{// 既にいる場合は通らない
		int nProgress = pRocket->GetProgress();

		if (nProgress > 0)
		{// 一度でも修理されている場合のみスポーン
			SpawnThief();
		}
	}
}

//=====================================================
// 泥棒のスポーン
//=====================================================
void CEnemyManager::SpawnThief(void)
{
	float fTick = CManager::GetTick();
	m_fTimerThief += fTick;

	if (m_fTimerThief > m_fTimeSpawnThief)
	{
		D3DXVECTOR3 posCenter = { 0.0f,0.0f,0.0f };

		// 出現する座標を設定
		posCenter.x = (float)universal::RandRange(RAND_SPAWN, -RAND_SPAWN);
		posCenter.z = (float)universal::RandRange(RAND_SPAWN, -RAND_SPAWN);

		// 位置の正規化
		D3DXVec3Normalize(&posCenter, &posCenter);
		posCenter *= RAND_SPAWN;

		// 敵スポーン
		m_pThief = CreateEnemy(posCenter, CEnemy::TYPE::TYPE_THIEF);

		m_fTimerThief = 0.0f;

		// 次に出現する時間を設定
		m_fTimeSpawnThief = (float)universal::RandRange(m_nMaxTimeSpawnThief,m_nMinTimeSpawnThief);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyManager::Draw(void)
{
#ifdef _DEBUG
	//CDebugProc::GetInstance()->Print("\n敵の位置：[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
#endif
}