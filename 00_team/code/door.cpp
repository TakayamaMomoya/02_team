//*****************************************************
//
// ドアの処理[door.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "door.h"
#include "playerManager.h"
#include "player.h"
#include "manager.h"
#include "collision.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const char* BODY_PATH = "data\\MODEL\\gimmick\\door000.x";	// モデルのパス
	const float INITIAL_LIFE = 5.0f;	// 体力
}

//=====================================================
// コンストラクタ
//=====================================================
CDoor::CDoor(int nPriority) : CGimmick(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// デストラクタ
//=====================================================
CDoor::~CDoor()
{

}

//=====================================================
// 生成処理
//=====================================================
CDoor *CDoor::Create(void)
{
	CDoor *pDoor = nullptr;

	if (pDoor == nullptr)
	{
		pDoor = new CDoor;

		if (pDoor != nullptr)
		{
			// 初期化
			pDoor->Init();
		}
	}

	return pDoor;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CDoor::Init(void)
{
	// 継承クラスの初期化
	CGimmick::Init();

	// モデルの読込
	int nIdx = CModel::Load((char*)BODY_PATH);
	SetIdxModel(nIdx);
	BindModel(nIdx);

	// 当たり判定の生成
	if (m_info.pCollisionCube == nullptr)
	{
		m_info.pCollisionCube = CCollisionCube::Create(CCollision::TAG_BLOCK, this);

		m_info.pCollisionCube->SetPosition(GetPosition());

		m_info.pCollisionCube->SetVtx(GetVtxMax(), GetVtxMin());
	}

	// 値の初期化
	m_info.fLife = INITIAL_LIFE;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CDoor::Uninit(void)
{
	if (m_info.pCollisionCube != nullptr)
	{
		m_info.pCollisionCube->Uninit();
		m_info.pCollisionCube = nullptr;
	}

	// 継承クラスの終了
	CGimmick::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CDoor::Update(void)
{
	// 継承クラスの更新
	CGimmick::Update();
}

//=====================================================
// インタラクト
//=====================================================
void CDoor::Interact(CObject *pObj)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pObj == nullptr || pPlayerManager == nullptr)
	{
		return;
	}

	// プレイヤー取得
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

		if (pPlayer != nullptr)
		{
			if ((CObject*)pPlayer == pObj)
			{// プレイヤーのインタラクト検出
				bool bInteract = pPlayer->InputInteractPress();

				if (bInteract)
				{// ピッキングを進める
					proceed();
				}
			}
		}
	}
}

//=====================================================
// ピッキングを進める
//=====================================================
void CDoor::proceed(void)
{
	float fTick = CManager::GetTick();

	m_info.fLife -= fTick;

	if (m_info.fLife < 0.0f)
	{
		Uninit();
	}
}

//=====================================================
// 位置の設定
//=====================================================
void CDoor::SetPosition(D3DXVECTOR3 pos)
{
	// 継承クラスの設置
	CObjectX::SetPosition(pos);

	if (m_info.pCollisionCube != nullptr)
	{// 当たり判定の追従
		D3DXVECTOR3 pos = GetPosition();

		m_info.pCollisionCube->SetPosition(pos);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CDoor::Draw(void)
{
	// 継承クラスの描画
	CGimmick::Draw();
}