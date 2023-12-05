//*****************************************************
//
// 修理アイテムの処理[ItemRepair.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "ItemRepair.h"
#include "playerManager.h"
#include "player.h"
#include "universal.h"
#include "parts.h"
#include "motion.h"
#include "collision.h"
#include "rocket.h"
#include "sound.h"
#include "manager.h"
#include "fan3D.h"
#include "motionDiv.h"

//=====================================================
// コンストラクタ
//=====================================================
CItemRepair::CItemRepair(int nPriority) : CGimmick(nPriority)
{
	m_pPlayer = nullptr;
	m_pGauge = nullptr;
	m_bInRocket = false;
	m_fCntRepair = 0.0f;
}

//=====================================================
// デストラクタ
//=====================================================
CItemRepair::~CItemRepair()
{

}

//=====================================================
// 生成処理
//=====================================================
CItemRepair *CItemRepair::Create(void)
{
	CItemRepair *pItemRepair = nullptr;

	if (pItemRepair == nullptr)
	{
		pItemRepair = new CItemRepair;

		if (pItemRepair != nullptr)
		{
			// 初期化
			pItemRepair->Init();
		}
	}

	return pItemRepair;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CItemRepair::Init(void)
{
	// 継承クラスの初期化
	CGimmick::Init();

	// 読み込み
	Load();

	return S_OK;
}

//=====================================================
// 読み込み処理
//=====================================================
void CItemRepair::Load(void)
{
	// モデルの読込
	int nIdx = CModel::Load("data\\MODEL\\item\\repairKit.x");
	SetIdxModel(nIdx);
	BindModel(nIdx);
}

//=====================================================
// 終了処理
//=====================================================
void CItemRepair::Uninit(void)
{
	m_pPlayer = nullptr;

	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	// 継承クラスの終了
	CGimmick::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CItemRepair::Update(void)
{
	bool bRelease = false;

	if (m_pPlayer != nullptr && m_bInRocket == false)
	{
		bRelease = m_pPlayer->InputInteract();

		if (bRelease)
		{// 持ち上げているプレイヤーの検出
			// 武器を有効化する
			m_pPlayer->EnableWeapon(true);
			
			// プレイヤーの修理アイテムポインタを初期化
			m_pPlayer->ReleaseItemRepair();

			m_pPlayer = nullptr;

			SetEnable(true);
		}
		else
		{

		}
	}
	
	if (bRelease == false)
	{
		// 継承クラスの更新
		CGimmick::Update();
	}

	// プレイヤーの生存確認
	CheckPlayerAlive();

	if (m_pPlayer == nullptr)
	{// 持ち上げていない状態
		// 移動量反映
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 move = GetMove();

		// 重力の反映
		move.y -= 0.98f;

		pos += move;

		// 床との判定
		if (pos.y <= 0.0f)
		{
			pos.y = 0.0f;
			move.y = 0.0f;
		}

		SetPosition(pos);
	}
	else
	{// 持ち上げられている場合
		FollowPlayerHand();
	}

	// ロケットとの当たり判定
	CollisionRocket();
}

//=====================================================
// プレイヤーの手を追従
//=====================================================
void CItemRepair::FollowPlayerHand(void)
{
	

	if (m_pPlayer == nullptr)
	{
		return;
	}

	CMotionDiv *pBody = m_pPlayer->GetBody();

	if (pBody != nullptr)
	{
		CParts *pParts = pBody->GetParts(CMotionDiv::DIV_BODY_UPPER, 6)->pParts;

		if (pParts != nullptr)
		{
			// オフセットの設定
			D3DXMATRIX *pMtx = GetMatrix();
			D3DXMATRIX *pMtxPart = pParts->GetMatrix();
			D3DXVECTOR3 offset = { -10.0f,0.0f,0.0f };

			universal::SetOffSet(pMtx, *pMtxPart, offset);

			// 手に追従する
			D3DXVECTOR3 posHand =
			{
				pMtx->_41,
				pMtx->_42,
				pMtx->_43,
			};
			D3DXVECTOR3 rot = m_pPlayer->GetRot();

			SetPosition(posHand);
			SetRot(rot);
		}
	}
}

//=====================================================
// アイテム入手時の処理
//=====================================================
void CItemRepair::Interact(CObject *pObj)
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
			{// プレイヤー検出
				bool bGet = pPlayer->InputInteract();

				if (bGet)
				{// 持ち上げる
					m_pPlayer = pPlayer;

					// 武器を無効化する
					pPlayer->EnableWeapon(false);

					// プレイヤーに修理アイテムのポインタ設定
					pPlayer->SetItemRepair(this);

					// プレイヤーの修理アイテム入力情報
					pPlayer->SetItemTrigger(true);

					SetEnable(false);
				}
			}
		}
	}
}

//=====================================================
// ロケットとの当たり判定
//=====================================================
void CItemRepair::CollisionRocket(void)
{
	CCollisionSphere *pCollisionSphere = GetCollisionSphere();

	if (pCollisionSphere != nullptr)
	{
		m_bInRocket = pCollisionSphere->SphereCollision(CCollision::TAG_ROCKET);

		if (m_bInRocket)
		{
			//　サウンドインスタンスの取得
			CSound* pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_SE_REPAIR);
			}

			// ロケット修理タイマー加算
			CRocket *pRocket = CRocket::GetInstance();

			if (pRocket != nullptr && m_pPlayer != nullptr)
			{
				bool bInteract = m_pPlayer->InputInteractPress();

				if (bInteract)
				{
					float fTime = pRocket->GetTime();

					if (m_pGauge == nullptr)
					{// ゲージの生成
						D3DXVECTOR3 pos = GetPosition();

						pos.y += 150.0f;
						pos.x += 50.0f;

						m_pGauge = CFan3D::Create();
						m_pGauge->SetPosition(pos);
						m_pGauge->SetRadius(30.0f);
						m_pGauge->EnableBillboard(true);
						m_pGauge->EnableZtest(true);

						m_pGauge->SetVtx();
					}

					if (m_pGauge != nullptr)
					{// ゲージの角度設定
						float fRate = m_fCntRepair / fTime;
						m_pGauge->SetAngleMax(fRate);
						m_pGauge->SetVtx();
					}

					// カウンターを加算
					float fTick = CManager::GetTick();

					m_fCntRepair += fTick;

					if (fTime <= m_fCntRepair)
					{
						// 武器を有効化する
						m_pPlayer->EnableWeapon(true);

						// プレイヤーの修理アイテムポインタを初期化
						m_pPlayer->ReleaseItemRepair();

						// 修理進行
						pRocket->AddProgress(1);

						Uninit();
					}
				}
				else
				{
					if (m_pGauge != nullptr)
					{// ゲージの破棄
						m_pGauge->Uninit();
						m_pGauge = nullptr;
					}
				}
			}
		}
	}
}

//=====================================================
// 持ち主のプレイヤーが生存しているかの確認
//=====================================================
void CItemRepair::CheckPlayerAlive(void)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pPlayerManager == nullptr || m_pPlayer == nullptr)
	{
		return;
	}

	bool bAlive = false;

	// プレイヤー取得
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

		if (pPlayer != nullptr)
		{
			if (pPlayer == m_pPlayer)
			{// プレイヤー検出
				bAlive = true;
			}
		}
	}

	if (bAlive == false)
	{// プレイヤーが検出できなかった場合、床に落ちる
		m_pPlayer = nullptr;
	}
}

//=====================================================
// 描画処理
//=====================================================
void CItemRepair::Draw(void)
{
	// 継承クラスの描画
	CGimmick::Draw();
}