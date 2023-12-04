//*****************************************************
//
// ゴールタイマーの処理[goalGoalTimer.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "goalTimer.h"
#include "manager.h"
#include "number.h"
#include "game.h"
#include "debugproc.h"
#include "goal.h"
#include "UI.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define NUM_PLACE	(2)	// 桁数
#define INITIAL_TIME	(10.0f)	// 初期の時間

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CGoalTimer *CGoalTimer::m_pGoalTimer = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CGoalTimer::CGoalTimer()
{
	m_pObjSecond = nullptr;
	m_bStop = false;
	m_fSecond = 0;
}

//=====================================================
// デストラクタ
//=====================================================
CGoalTimer::~CGoalTimer()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CGoalTimer::Init(void)
{
	m_fSecond = INITIAL_TIME;
	
	if (m_pObjSecond == nullptr)
	{// 秒表示の生成
		m_pObjSecond = CNumber::Create(NUM_PLACE, 0);

		if (m_pObjSecond != nullptr)
		{
			m_pObjSecond->SetPosition(D3DXVECTOR3(620.0f, 80.0f, 0.0f));
			m_pObjSecond->SetSizeAll(20.0f, 50.0f);
		}
	}

	if (m_pObjDecimal == nullptr)
	{// 小数点以下表示の生成
		m_pObjDecimal = CNumber::Create(NUM_PLACE, 0);

		if (m_pObjDecimal != nullptr)
		{
			m_pObjDecimal->SetPosition(D3DXVECTOR3(720.0f, 80.0f, 0.0f));
			m_pObjDecimal->SetSizeAll(20.0f, 50.0f);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CGoalTimer::Uninit(void)
{
	if (m_pObjSecond != nullptr)
	{
		m_pObjSecond->Uninit();
		m_pObjSecond = nullptr;
	}

	if (m_pObjDecimal != nullptr)
	{
		m_pObjDecimal->Uninit();
		m_pObjDecimal = nullptr;
	}

	if (m_pPoint != nullptr)
	{
		m_pPoint->Uninit();
		m_pPoint = nullptr;
	}

	m_pGoalTimer = nullptr;

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CGoalTimer::Update(void)
{
	if (CGame::GetState() == CGame::STATE_END || 
		m_bStop)
	{
		return;
	}

	// 秒数を減らす
	float fTick = CManager::GetTick();
	
	m_fSecond -= fTick;

	if (m_fSecond < 0.0f)
	{// タイムアップの処理
		m_fSecond = 0.0f;

		CGoal *pGoal = CGoal::GetInstance();

		if (pGoal != nullptr)
		{
			if (pGoal->IsFinish() == false)
			{
				pGoal->DeadLine();
			}
		}
	}

	int nDecimal = (int)(m_fSecond * 100.0f) % 100;

	if (m_pObjSecond != nullptr)
	{// 秒表示の制御
		m_pObjSecond->SetValue((int)m_fSecond, NUM_PLACE);
	}

	if (m_pObjDecimal != nullptr)
	{// 小数点以下表示の制御
		m_pObjDecimal->SetValue(nDecimal, NUM_PLACE);
	}
}

//=====================================================
// 時間加算
//=====================================================
void CGoalTimer::AddGoalTimer(int nValue)
{
	m_fSecond += nValue;
}

//=====================================================
// 生成処理
//=====================================================
CGoalTimer *CGoalTimer::Create(void)
{
	if (m_pGoalTimer == nullptr)
	{
		m_pGoalTimer = new CGoalTimer;

		m_pGoalTimer->Init();
	}

	return m_pGoalTimer;
}

//=====================================================
// 描画処理
//=====================================================
void CGoalTimer::Draw(void)
{
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\nゴール残り時間[%f]", m_fSecond);
}