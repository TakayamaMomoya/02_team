//*****************************************************
//
// 戦績処理[record.cpp]
// Author:酒井南勝
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "record.h"

#include "playerManager.h"
#include "enemyManager.h"
#include "enemy.h"

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CRecord* CRecord::m_pRecord = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CRecord::CRecord()
{
	ZeroMemory(&m_aInfo[0],sizeof(m_aInfo));
	m_nNumSuvived = 0;
}

//=====================================================
// デストラクタ
//=====================================================
CRecord::~CRecord()
{

}

//=====================================================
// 生成処理
//=====================================================
CRecord* CRecord::Create(void)
{
	if (m_pRecord == nullptr)
	{// インスタンス生成
		m_pRecord = new CRecord;

		// 初期化処理
		m_pRecord->Init();
	}

	return m_pRecord;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CRecord::Init(void)
{
	// プレイヤー数の設定処理
	SetNumPlayer();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CRecord::Uninit(void)
{
	m_pRecord = nullptr;

	delete this;
}

//=====================================================
// プレイヤーの数を設定処理
//=====================================================
void CRecord::SetNumPlayer(void)
{
	CPlayerManager* pPlayerMagazine = CPlayerManager::GetInstance();

	if (pPlayerMagazine != nullptr)
	{
		// 最大生存者数を設定
		m_nNumSuvived = pPlayerMagazine->GetNumPlayer();
	}
}

//=====================================================
// 敵の破壊数を加算処理
//=====================================================
void CRecord::AddDestroy(int nIdx)
{
	// プレイヤー番号が最大数を少ない
	if (m_nNumSuvived > nIdx)
	{
		// 破壊数を加算
		m_aInfo[nIdx].nDestroy++;
	}
}

//=====================================================
// 敵の死亡の有無を判定
//=====================================================
void CRecord::CheckDeathEnemy(CObject* pObj,int nIdx)
{
	CEnemyManager* pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager == nullptr || pObj == nullptr)
	{
		return;
	}

	CEnemy* pEnemy = pEnemyManager->GetHead();

	while (pEnemy != nullptr)
	{
		CEnemy* pEnemyNext = pEnemy->GetNext();

		if ((CObject*)pEnemy == pObj)
		{
			// 敵の有無を判定
			if (pEnemy->GetState() == CEnemy::STATE_DEATH)
			{
				CRecord* pRecord = CRecord::GetInstance();

				if (pRecord != nullptr)
				{
					// 現在のプレイヤーの破壊数を加算
					pRecord->AddDestroy(nIdx);
				}
			}
		}

		pEnemy = pEnemyNext;
	}
}