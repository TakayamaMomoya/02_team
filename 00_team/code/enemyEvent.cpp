//*****************************************************
//
// 敵イベントの処理[enemyEvent.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "enemyEvent.h"
#include "manager.h"
#include "light.h"
#include "enemyManager.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float INITIAL_SCALE = 0.5f;	// 初期のタイムスケール
}

//=====================================================
// コンストラクタ
//=====================================================
CEnemyEvent::CEnemyEvent(int nPriority) : CObject(nPriority)
{
	m_fLife = 0.0f;
	m_fDelay = 0.0f;
	m_fScaleTime = 0.0f;
}

//=====================================================
// デストラクタ
//=====================================================
CEnemyEvent::~CEnemyEvent()
{

}

//=====================================================
// 生成処理
//=====================================================
CEnemyEvent *CEnemyEvent::Create(float fLife, float fDelay)
{
	CEnemyEvent *pEnemyEvent = nullptr;

	if (pEnemyEvent == nullptr)
	{
		pEnemyEvent = new CEnemyEvent;

		if (pEnemyEvent != nullptr)
		{
			pEnemyEvent->m_fLife = fLife;
			pEnemyEvent->m_fDelay = fDelay;

			// 初期化
			pEnemyEvent->Init();
		}
	}

	return pEnemyEvent;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyEvent::Init(void)
{
	m_fScaleTime = INITIAL_SCALE;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyEvent::Uninit(void)
{
	// ライトの色を戻す
	CLight *pLight = CManager::GetLight();

	if (pLight != nullptr)
	{
		pLight->ResetColDest();
	}

	// 敵の出現頻度を戻す
	CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager != nullptr)
	{
		pEnemyManager->SetTimeScale(1.0f);
	}

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyEvent::Update(void)
{
	// 寿命での消滅
	float fTick = CManager::GetTick();

	if (m_fDelay > 0.0f)
	{
		// ディレイ
		m_fDelay -= fTick;

		if (m_fDelay <= 0.0f)
		{// イベントの開始
			StartEvent();
		}
	}
	else
	{// イベントの更新
		m_fLife -= fTick;

		if (m_fLife <= 0.0f)
		{
			Uninit();
		}
	}
}

//=====================================================
// イベントの開始
//=====================================================
void CEnemyEvent::StartEvent(void)
{
	// ライトを赤くする
	CLight *pLight = CManager::GetLight();

	if (pLight != nullptr)
	{
		for (int i = 0; i < MAX_LIGHT; i++)
		{
			pLight->SetColDest(i, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	// 敵の出現頻度を変更
	CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager != nullptr)
	{
		pEnemyManager->SetTimeScale(m_fScaleTime);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyEvent::Draw(void)
{

}