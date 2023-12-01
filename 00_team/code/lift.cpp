//*****************************************************
//
// 集会所処理[meetingPlace.cpp]
// Author:小笠原彪
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "lift.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "playerManager.h"
#include "player.h"
#include "fade.h"
#include "object2D.h"

#include "debugproc.h"

//*****************************************************
// マクロ定義
//*****************************************************
namespace
{
	const float RANGE(100.0f);
}

//=====================================================
//	静的メンバ変数宣言
//=====================================================
int CLift::m_nNumJoinPlayer = 0;
int CLift::m_nInCnt = 0;
bool CLift::m_abJoin[NUM_PLAYER] = {};

//=====================================================
// コンストラクタ
//=====================================================
CLift::CLift(int nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_nInCnt = 0;
	m_state = STATE_NONE;
}

//=====================================================
// デストラクタ
//=====================================================
CLift::~CLift()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CLift::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	int nIdx = CModel::Load("data\\MODEL\\select\\lift.x");
	// モデル読込
	BindModel(nIdx);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CLift::Uninit(void)
{
	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CLift::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();

	CFade* pFade = CFade::GetInstance();
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();
	CPlayer* pPlayer = nullptr;
	int nInPlayer = 0;

	D3DXVECTOR3 pos = GetPosition();

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		pPlayer = pPlayerManager->GetPlayer(nCnt);

		if (pPlayer == nullptr)
		{
			continue;
		}

		//対象のオブジェクトろの距離を求める
		float fLength = sqrtf(
			(pPlayer->GetPosition().x - GetPosition().x) * (pPlayer->GetPosition().x - GetPosition().x) + 
			(pPlayer->GetPosition().z - GetPosition().z) * (pPlayer->GetPosition().z - GetPosition().z));

		if (GetPosition().x + 100.0f >= pPlayer->GetPosition().x &&
			GetPosition().x - 100.0f <= pPlayer->GetPosition().x &&
			GetPosition().z + 100.0f >= pPlayer->GetPosition().z &&
			GetPosition().z - 100.0f <= pPlayer->GetPosition().z)
		{
			D3DXVECTOR3 playerPos = pPlayer->GetPosition();
			//playerPos.y = playerPos.y;
			pPlayer->SetPosition(playerPos);
			m_abJoin[nCnt] = true;

			nInPlayer++;
		}
		else
		{
			m_abJoin[nCnt] = false;
		}
	}

	m_nInCnt = nInPlayer;

	CDebugProc::GetInstance()->Print("\n開始場所\n");
	CDebugProc::GetInstance()->Print("範囲内プレイヤー[%d]\n", nInPlayer);
}

//=====================================================
// 描画処理
//=====================================================
void CLift::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}

//=====================================================
// 生成処理
//=====================================================
CLift* CLift::Create(D3DXVECTOR3 pos,int nPriority)
{
	CLift* pMeetingPlace = nullptr;

	if (pMeetingPlace == nullptr)
	{// インスタンス生成
		pMeetingPlace = new CLift(nPriority);

		if (pMeetingPlace != nullptr)
		{
			pMeetingPlace->SetPosition(pos);

			// 初期化処理
			pMeetingPlace->Init();
		}
	}

	return pMeetingPlace;
}

//=====================================================
// 読込処理
//=====================================================
HRESULT CLift::Load(void)
{
	return S_OK;
}

int CLift::GetInPlayer(void)
{
	return m_nInCnt;
}

//=====================================================
// 範囲内に入った人数の判定
//=====================================================
bool CLift::GetIsIn(void)
{
	if (m_nNumJoinPlayer <= 0 && m_nInCnt <= 0)
	{
		return false;
	}
	else if (m_nNumJoinPlayer == m_nInCnt)
	{
		return true;
	}

	return false;
}
