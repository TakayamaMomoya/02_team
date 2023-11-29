//*****************************************************
//
// ドアの処理[door.cpp]
// Author:��山桃也
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
#include "universal.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const char* BODY_PATH = "data\\MODEL\\gimmick\\door000.x";	// モデルのパス
	const float INITIAL_LIFE = 5.0f;	// 体力
	const float ROLL_SPEED = 0.3f;	// 回転速度
	const float OPEN_ANGLE = D3DX_PI * 0.5f;	// 回転制限
	const float OPEN_LINE = 0.1f;	// 開いてるしきい値
	const float OPEN_SPEED = 0.05f;	// 開く速度
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
	m_info.state = STATE_NORMAL;
	m_info.rotDestY = D3DX_PI * 0.5f;

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

	if (m_info.state == STATE_OPEN)
	{// 開く処理
		Open();
	}
}

//=====================================================
// 開く処理
//=====================================================
void CDoor::Open(void)
{
	// 差分角度の取得
	D3DXVECTOR3 rot = GetRot();

	float fRotDiff = (m_info.rotDestY - rot.y);

	universal::LimitRot(&fRotDiff);

	if (fRotDiff * fRotDiff <= OPEN_LINE * OPEN_LINE)
	{// 開ききった判定
		m_info.state = STATE_NONE;
	}

	fRotDiff *= OPEN_SPEED;

	// 角度の反映と判定
	rot.y += fRotDiff;

	SetRot(rot);
}

//=====================================================
// インタラクト
//=====================================================
void CDoor::Interact(CObject *pObj)
{
	if (m_info.state != STATE_NORMAL)
	{
		return;
	}

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

					// プレイヤーのドア入力情報
					pPlayer->SetDoorPress(true);
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
		m_info.state = STATE_OPEN;
		SetEnable(false);

		if (m_info.pCollisionCube != nullptr)
		{// 当たり判定の削除
			m_info.pCollisionCube->Uninit();
			m_info.pCollisionCube = nullptr;
		}
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
// 元の角度設定
//=====================================================
void CDoor::SetOrgRot(float rotY)
{
	m_info.orgRotY = rotY;

	universal::LimitRot(&m_info.rotDestY);

	if (rotY >= 3.0f || rotY <= -3.0f)
	{
		if (m_info.pCollisionCube != nullptr)
		{
			D3DXVECTOR3 vtxMax = GetVtxMax();
			D3DXVECTOR3 vtxMin = GetVtxMin();
			D3DXVECTOR3 vtxTemp = vtxMin;

			vtxMin = { -vtxMax.x,vtxMin.y,vtxMin.z };
			vtxMax = { -vtxTemp.x,vtxMax.y,vtxMax.z };

			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}
	else if (rotY >= 1.0f)
	{
		if (m_info.pCollisionCube != nullptr)
		{
			D3DXVECTOR3 vtxMax = GetVtxMax();
			D3DXVECTOR3 vtxMin = GetVtxMin();
			D3DXVECTOR3 vtxTemp = vtxMin;

			vtxMin = { -vtxMax.z,vtxMin.y,-vtxMax.x };
			vtxMax = { -vtxTemp.z,vtxMax.y,-vtxTemp.x };

			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}
	else if (rotY <= -1.0f)
	{
		if (m_info.pCollisionCube != nullptr)
		{
			D3DXVECTOR3 vtxMax = GetVtxMax();
			D3DXVECTOR3 vtxMin = GetVtxMin();
			D3DXVECTOR3 vtxTemp = vtxMin;

			vtxMin = { -vtxMax.z,vtxMin.y,vtxMin.x };
			vtxMax = { -vtxTemp.z,vtxMax.y,vtxMax.x };

			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}
}

//=====================================================
// 目標の角度設定
//=====================================================
void CDoor::SetDestRot(float fRot)
{
	m_info.rotDestY = fRot;
}

//=====================================================
// 描画処理
//=====================================================
void CDoor::Draw(void)
{
	// 継承クラスの描画
	CGimmick::Draw();
}