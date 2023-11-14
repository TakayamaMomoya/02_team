//*****************************************************
//
// ロケットの処理[rocket.cpp]
// Author:髙山桃也
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

//*****************************************************
// マクロ定義
//*****************************************************
#define INFO_PATH	"data\\TEXT\\rocket.txt"	// ゴール情報のテキスト

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
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "ROCKETSET") == 0)
			{// パラメーター読込開始
				while (true)
				{
					// 文字読み込み
					fscanf(pFile, "%s", &cTemp[0]);

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
		fscanf(pFile, "%s", pTemp);

		D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

		for (int i = 0;i < 3;i++)
		{
			fscanf(pFile, "%f", &pos[i]);
		}

		SetPosition(pos);

		if (m_pCollisionRocket != nullptr)
		{// 当たり判定の位置設定
			m_pCollisionRocket->SetPosition(pos);
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

		if (m_pCollisionRocket != nullptr)
		{// 当たり判定の位置設定
			m_pCollisionRocket->SetRadius(fRadius);
		}
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
}

//=====================================================
// 描画処理
//=====================================================
void CRocket::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}