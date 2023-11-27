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
#include "manager.h"
#include "camera.h"
#include "universal.h"
#include <stdio.h>
#include "game.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define FILE_PATH	"data\\MAP\\enemies.txt"	// 配置データのパス
#define RAND_SPAWN	(1000)	// スポーン範囲

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
	};

	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// インスタンス生成
		switch (type)
		{
		case CEnemy::TYPE_NORMAL:

			pEnemy = new CEnemyNormal;

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
	//Load();

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
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "ENEMYSET") == 0)
			{
				CEnemy::TYPE type;
				D3DXVECTOR3 pos;

				while (true)
				{
					// 文字読み込み
					(void)fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "POS") == 0)
					{// 位置
						(void)fscanf(pFile, "%s", &cTemp[0]);

						for (int nCntPos = 0; nCntPos < 3; nCntPos++)
						{
							(void)fscanf(pFile, "%f", &pos[nCntPos]);
						}
					}

					if (strcmp(cTemp, "TYPE") == 0)
					{// 種類
						(void)fscanf(pFile, "%s", &cTemp[0]);
						
						(void)fscanf(pFile, "%d", &type);
					}

					if (strcmp(cTemp, "END_ENEMYSET") == 0)
					{
						CreateEnemy(pos,type);

						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// 終了条件
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		assert(("敵配置データの読み込みに失敗",false));
	}
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyManager::Uninit(void)
{
	m_pEnemyManager = nullptr;

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

	m_nCntSpawn++;

	if (m_nCntSpawn >= 60)
	{
		CUniversal *pUniversal = CUniversal::GetInstance();

		D3DXVECTOR3 posCenter = { 0.0f,0.0f,0.0f };

		// 出現する座標を設定
		posCenter.x = pUniversal->RandRange(1000, -1000);
		posCenter.z = pUniversal->RandRange(1000, -1000);

		// 位置の正規化
		D3DXVec3Normalize(&posCenter, &posCenter);
		posCenter *= RAND_SPAWN;

		// 敵スポーン
		CreateEnemy(posCenter, CEnemy::TYPE_NORMAL);

		m_nCntSpawn = 0;
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