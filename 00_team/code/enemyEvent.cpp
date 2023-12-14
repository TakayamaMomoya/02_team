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
const float INITIAL_LIFE = 10.0f;	// 初期寿命
}

//=====================================================
// コンストラクタ
//=====================================================
CEnemyEvent::CEnemyEvent(int nPriority) : CObject(nPriority)
{
	m_fLife = 0.0f;
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
CEnemyEvent *CEnemyEvent::Create(void)
{
	CEnemyEvent *pEnemyEvent = nullptr;

	if (pEnemyEvent == nullptr)
	{
		pEnemyEvent = new CEnemyEvent;

		if (pEnemyEvent != nullptr)
		{
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
	m_fLife = INITIAL_LIFE;

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
		pEnemyManager->SetTimeScale(0.5f);
	}

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

	m_fLife -= fTick;

	if (m_fLife <= 0.0f)
	{
		Uninit();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyEvent::Draw(void)
{

}