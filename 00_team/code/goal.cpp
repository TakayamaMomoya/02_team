//*****************************************************
//
// ゴールの処理[goal.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "goal.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "fade.h"
#include "goalTimer.h"
#include "playerManager.h"
#include "player.h"
#include "result.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define INFO_PATH	"data\\TEXT\\goal.txt"	// ゴール情報のテキスト

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CGoal *CGoal::m_pGoal = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CGoal::CGoal(int nPriority) : CObjectX(nPriority)
{
	m_bFinish = false;
	m_fRadius = 0.0f;
	m_pCollisionGoal = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CGoal::~CGoal()
{

}

//=====================================================
// 生成処理
//=====================================================
CGoal *CGoal::Create()
{
	if (m_pGoal == nullptr)
	{
		m_pGoal = new CGoal;

		if (m_pGoal != nullptr)
		{
			// 初期化
			m_pGoal->Init();
		}
	}

	return m_pGoal;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGoal::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	if (m_pCollisionGoal == nullptr)
	{// 球の当たり判定生成
		m_pCollisionGoal = CCollisionSphere::Create(CCollision::TAG_GOAL, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionGoal != nullptr)
		{// 情報の設定
			m_pCollisionGoal->SetPosition(GetPosition());
			m_pCollisionGoal->SetRadius(5);
		}
	}

	// 情報読み込み
	Load();

	return S_OK;
}

//=====================================================
// 読み込み処理
//=====================================================
void CGoal::Load(void)
{
	// 変数宣言
	char cTemp[256];
	int nCntParam = 0;

	// ファイルから読み込む
	FILE* pFile = fopen(INFO_PATH, "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "GOALSET") == 0)
			{// パラメーター読込開始
				while (true)
				{
					// 文字読み込み
					fscanf(pFile, "%s", &cTemp[0]);

					// 基底パラメーター読み込み
					ApplyInfo(pFile, &cTemp[0]);

					if (strcmp(cTemp, "END_GOALSET") == 0)
					{// パラメーター読込終了
						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// 読み込みの終了
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}

//=====================================================
// 情報反映
//=====================================================
void CGoal::ApplyInfo(FILE* pFile, char* pTemp)
{
	if (strcmp(pTemp, "POS") == 0)
	{// 位置
		fscanf(pFile, "%s", pTemp);

		D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

		for (int i = 0;i < 3;i++)
		{
			fscanf(pFile, "%f", &pos[i]);
		}

		SetPosition(pos);

		if (m_pCollisionGoal != nullptr)
		{// 当たり判定の位置設定
			m_pCollisionGoal->SetPosition(pos);
		}
	}

	if (strcmp(pTemp, "MODEL") == 0)
	{// モデル読み込み
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%s", pTemp);

		// モデルの読込
		int nIdx = CModel::Load(pTemp);
		SetIdxModel(nIdx);
		BindModel(nIdx);
	}

	if (strcmp(pTemp, "RADIUS") == 0)
	{// 判定の大きさ
		float fRadius;

		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &fRadius);

		m_fRadius = fRadius;

		if (m_pCollisionGoal != nullptr)
		{// 当たり判定の位置設定
			m_pCollisionGoal->SetRadius(fRadius);
		}
	}
}

//=====================================================
// 終了処理
//=====================================================
void CGoal::Uninit(void)
{
	if (m_pCollisionGoal != nullptr)
	{
		m_pCollisionGoal->Uninit();
		m_pCollisionGoal = nullptr;
	}

	m_pGoal = nullptr;

	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CGoal::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();

	// プレイヤーの検出
	DetectPlayer();
}

//=====================================================
// プレイヤーの検出
//=====================================================
void CGoal::DetectPlayer(void)
{
	CGoalTimer *pGoalTimer = CGoalTimer::GetInstance();

	if (pGoalTimer != nullptr)
	{
		return;
	}

	if (m_pCollisionGoal != nullptr)
	{
		if (m_pCollisionGoal->SphereCollision(CCollision::TAG_PLAYER))
		{
			// ゴールタイマーの生成
			CGoalTimer::Create();
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void CGoal::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// 制限時間の終了
//=====================================================
void CGoal::DeadLine(void)
{
	m_bFinish = true;

	// リザルトの生成
	CResult *pResult = CResult::Create();

	// 範囲内のプレイヤー検出
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pPlayerManager != nullptr)
	{
		for (int i = 0;i < NUM_PLAYER;i++)
		{
			CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

			if (pPlayer != nullptr)
			{
				if (pResult != nullptr)
				{// リザルトにプレイヤー情報を渡す
					// 座標の差分から距離を計算
					D3DXVECTOR3 pos = GetPosition();
					D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
					D3DXVECTOR3 vecDiff = posPlayer - pos;
					float fDiff = D3DXVec3Length(&vecDiff);
					
					if (fDiff < m_fRadius)
					{
						pResult->SetSurvived(pPlayer);
					}
				}
			}
		}
	}
}