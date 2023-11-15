//*****************************************************
//
// ロケットの処理[rocket.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "rocket.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "fade.h"
#include "playerManager.h"
#include "player.h"
#include "result.h"
#include "goal.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const char* INFO_PATH = "data\\TEXT\\rocket.txt";	// ロケット情報のテキスト
	const int MAX_PROGRESS = 3;	// 最大の進行状況
	const int MIN_PROGRESS = 0;	// 最大の進行状況
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CRocket *CRocket::m_pRocket = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CRocket::CRocket(int nPriority) : CObjectX(nPriority)
{
	m_fRadius = 0.0f;
	m_fSpeed = 0.0f;
	m_nProgress = 0;
	m_state = STATE_NONE;
	m_pCollisionRocket = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CRocket::~CRocket()
{

}

//=====================================================
// 生成処理
//=====================================================
CRocket *CRocket::Create()
{
	if (m_pRocket == nullptr)
	{
		m_pRocket = new CRocket;

		if (m_pRocket != nullptr)
		{
			// 初期化
			m_pRocket->Init();
		}
	}

	return m_pRocket;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CRocket::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	if (m_pCollisionRocket == nullptr)
	{// 球の当たり判定生成
		m_pCollisionRocket = CCollisionSphere::Create(CCollision::TAG_ROCKET, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionRocket != nullptr)
		{// 情報の設定
			m_pCollisionRocket->SetPosition(GetPosition());
			m_pCollisionRocket->SetRadius(5);
		}
	}

	// 情報読み込み
	Load();

	m_state = STATE_NORMAL;

	return S_OK;
}

//=====================================================
// 読み込み処理
//=====================================================
void CRocket::Load(void)
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
			(void)(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "ROCKETSET") == 0)
			{// パラメーター読込開始
				while (true)
				{
					// 文字読み込み
					(void)fscanf(pFile, "%s", &cTemp[0]);

					// 基底パラメーター読み込み
					ApplyInfo(pFile, &cTemp[0]);

					if (strcmp(cTemp, "END_ROCKETSET") == 0)
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
	else
	{
		assert(("ロケット情報の読み込みに失敗", false));
	}
}

//=====================================================
// 情報反映
//=====================================================
void CRocket::ApplyInfo(FILE* pFile, char* pTemp)
{
	if (strcmp(pTemp, "POS") == 0)
	{// 位置
		(void)fscanf(pFile, "%s", pTemp);

		D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

		for (int i = 0;i < 3;i++)
		{
			(void)fscanf(pFile, "%f", &pos[i]);
		}

		SetPosition(pos);

		if (m_pCollisionRocket != nullptr)
		{// 当たり判定の位置設定
			m_pCollisionRocket->SetPosition(pos);
		}
	}

	if (strcmp(pTemp, "MODEL") == 0)
	{// モデル読み込み
		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%s", pTemp);

		// モデルの読込
		int nIdx = CModel::Load(pTemp);
		SetIdxModel(nIdx);
		BindModel(nIdx);
	}

	if (strcmp(pTemp, "RADIUS") == 0)
	{// 判定の大きさ
		float fRadius;

		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%f", &fRadius);

		m_fRadius = fRadius;

		if (m_pCollisionRocket != nullptr)
		{// 当たり判定の位置設定
			m_pCollisionRocket->SetRadius(fRadius);
		}
	}

	if (strcmp(pTemp, "SPEED") == 0)
	{// 上昇速度
		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%f", &m_fSpeed);

	}
}

//=====================================================
// 終了処理
//=====================================================
void CRocket::Uninit(void)
{
	if (m_pCollisionRocket != nullptr)
	{
		m_pCollisionRocket->Uninit();
		m_pCollisionRocket = nullptr;
	}

	m_pRocket = nullptr;

	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CRocket::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();

	if (m_state == STATE::STATE_ESCAPE)
	{// 脱出状態の更新
		UpdateEscape();
	}
}

//=====================================================
// 脱出の更新
//=====================================================
void CRocket::UpdateEscape(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	// 上昇量の加算
	move.y += m_fSpeed;

	// 移動量の反映
	pos += move;

	SetPosition(pos);
	SetMove(move);
}

//=====================================================
// 描画処理
//=====================================================
void CRocket::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// 進行状況の加算
//=====================================================
void CRocket::AddProgress(int nProgress)
{
	if (m_state != STATE_NORMAL)
	{// 通常状態のみ進行可能
		return;
	}

	// 進行状況加算
	m_nProgress += nProgress;

	// 最大、最小値の補正
	if (m_nProgress < MIN_PROGRESS)
	{
		m_nProgress = MIN_PROGRESS;
	}
	if (m_nProgress >= MAX_PROGRESS)
	{
		m_nProgress = MAX_PROGRESS;

		// ゴールの生成
		CGoal *pGoal = CGoal::Create();

		D3DXVECTOR3 pos = GetPosition();
		pGoal->SetPosition(pos);
	}

	// ロケットモデルの変化
}