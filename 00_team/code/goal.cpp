//*****************************************************
//
// ゴールの処理[goal.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "goal.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define INFO_PATH	"data\\TEXT\\goal.txt"	// ゴール情報のテキスト

//=====================================================
// コンストラクタ
//=====================================================
CGoal::CGoal(int nPriority) : CObjectX(nPriority)
{
	m_pCollisionGoal = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CGoal::~CGoal()
{

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
// 生成処理
//=====================================================
CGoal *CGoal::Create()
{
	CGoal *pGoal = nullptr;

	if (pGoal == nullptr)
	{
		pGoal = new CGoal;

		if (pGoal != nullptr)
		{
			// 初期化
			pGoal->Init();
		}
	}

	return pGoal;
}