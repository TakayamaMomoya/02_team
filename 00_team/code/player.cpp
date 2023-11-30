//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "player.h"
#include "playerManager.h"
#include "motion.h"
#include "debugproc.h"
#include "inputjoypad.h"
#include "inputkeyboard.h"
#include "universal.h"
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "arrow.h"

#include "motionDiv.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const char* BODY_PATH_LOWER[NUM_PLAYER] = 
	{// 下半身のパス
		"data\\MOTION\\motionPotatoman01_lower.txt",
		"data\\MOTION\\motionPotatoman02_lower.txt",
		"data\\MOTION\\motionPotatoman03_lower.txt",
		"data\\MOTION\\motionPotatoman04_lower.txt",
	};

	const char* BODY_PATH_UPPER[NUM_PLAYER] =
	{// 上半身のパス
		"data\\MOTION\\motionPotatoman01_upper.txt",
		"data\\MOTION\\motionPotatoman02_upper.txt",
		"data\\MOTION\\motionPotatoman03_upper.txt",
		"data\\MOTION\\motionPotatoman04_upper.txt",
	};

	const D3DXCOLOR COL_ARROW[NUM_PLAYER] =
	{// 矢印の色
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		D3DXCOLOR(0.0f,1.0f,1.0f,1.0f),
		D3DXCOLOR(1.0f,0.0f,1.0f,1.0f),
		D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),
	};	// 矢印の色

	const float MOVE_SPEED = 3.0f;		// 移動速度
	const float ROT_SPEED = 0.1f;		// 回転速度
	const float INITIAL_LIFE = 30.0f;	// 初期体力
	const float DAMAGE_TIME = 0.5f;		// ダメージ状態の秒数
	const float MOVE_LINE = 0.2f;		// 動いている判断のしきい値
	const float ARROW_POSY = 5.0f;	// 矢印の位置の高さ
	const float ARROW_WIDTH = 30.0f;	// 矢印の幅
	const float ARROW_HEIGHT = 50.0f;	// 矢印の高さ

	const int HAND_PARTS_NUM = 6;		// 手の番号
}

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	ZeroMemory(&m_info, sizeof(CPlayer::SInfo));
}

//=====================================================
// デストラクタ
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// 生成処理
//=====================================================
CPlayer *CPlayer::Create(int nID)
{
	CPlayer *pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->m_info.nID = nID;

		pPlayer->Init();
	}

	return pPlayer;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CPlayer::Init(void)
{
	// 継承クラスの初期化
	CCharacterDiv::Init();

	// 当たり判定の生成
	if (m_info.pCollisionSphere == nullptr)
	{
		m_info.pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE_SPHERE, this);

		if (m_info.pCollisionSphere != nullptr)
		{
			m_info.pCollisionSphere->SetRadius(5.0f);
		}
	}

	if (m_info.pCollisionCube == nullptr)
	{// 当たり判定生成
		m_info.pCollisionCube = CCollisionCube::Create(CCollision::TAG_PLAYER, this);

		if (m_info.pCollisionCube != nullptr)
		{
			D3DXVECTOR3 vtxMax = { 10.0f,10.0f,10.0f };
			D3DXVECTOR3 vtxMin = { -10.0f,0.0f,-10.0f };

			m_info.pCollisionCube->SetPosition(GetPosition());

			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	if (m_info.pArrow == nullptr)
	{// 矢印の生成
		m_info.pArrow = CArrow::Create(GetPosition(), ARROW_WIDTH, ARROW_HEIGHT);

		if (m_info.pArrow != nullptr)
		{
			m_info.pArrow->SetColor(COL_ARROW[m_info.nID]);
		}
	}

	m_info.fLife = INITIAL_LIFE;
	m_info.state = STATE_NORMAL;

	// IDに対応したモデルの設定
	CCharacterDiv::Load((char*)BODY_PATH_LOWER[m_info.nID], (char*)BODY_PATH_UPPER[m_info.nID]);

	// 影の有効化
	for (int nCutPath = 0; nCutPath < CCharacterDiv::PARTS_MAX; nCutPath++)
	{
		CMotionDiv* pBody = GetBody();

		if (pBody != nullptr)
		{
			pBody->SetPosShadow(D3DXVECTOR3(0.0f, 0.5f, 0.0f));
			pBody->EnableShadow(true);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CPlayer::Uninit(void)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pPlayerManager != nullptr)
	{// 保管してある自身のポインタを削除
		pPlayerManager->ReleasePlayer(m_info.nID);
	}

	if (m_info.pCollisionSphere != nullptr)
	{
		m_info.pCollisionSphere->Uninit();
		m_info.pCollisionSphere = nullptr;
	}

	if (m_info.pCollisionCube != nullptr)
	{
		m_info.pCollisionCube->Uninit();
		m_info.pCollisionCube = nullptr;
	}

	if (m_info.pWeapon != nullptr)
	{
		m_info.pWeapon->Uninit();
		m_info.pWeapon = nullptr;
	}
	
	if (m_info.pArrow != nullptr)
	{
		m_info.pArrow->Uninit();
		m_info.pArrow = nullptr;
	}

	// 継承クラスの終了
	CCharacterDiv::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CPlayer::Update(void)
{
	// 継承クラスの更新
	CCharacterDiv::Update();

	// 入力
	Input();

	// 位置の反映
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	
	// 前回の位置を保存
	SetPositionOld(pos);

	pos += move;
	SetPosition(pos);

	// 当たり判定の追従
	if (m_info.pCollisionSphere != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 posWaist = GetBody()->GetMtxPos(CCharacterDiv::PARTS_UPPER,0);
		
		// 敵との接触判定
		m_info.pCollisionSphere->SetPosition(posWaist);

		bool bHit = m_info.pCollisionSphere->SphereCollision(CCollision::TAG_ENEMY);

		if (bHit)
		{
			Hit(5.0f);
		}

		if (m_info.pCollisionSphere != nullptr)
		{
			// 敵との押し出し判定
			m_info.pCollisionSphere->SetPosition(pos);

			m_info.pCollisionSphere->PushCollision(&pos, CCollision::TAG_PLAYER);
			m_info.pCollisionSphere->PushCollision(&pos, CCollision::TAG_ENEMY);

			m_info.pCollisionSphere->SetPositionOld(m_info.pCollisionSphere->GetPosition());
			m_info.pCollisionSphere->SetPosition(pos);

			SetPosition(pos);
		}

		if (m_info.pCollisionCube != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 posCollision = m_info.pCollisionCube->GetPosition();
			D3DXVECTOR3 move = GetMove();

			// 判定の追従
			m_info.pCollisionCube->SetPositionOld(posCollision);
			m_info.pCollisionCube->SetPosition(pos);

			// ブロックとの押し出し判定
			m_info.pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

			SetMove(move);
		}
	}

	// 移動量の減衰
	move *= 0.1f;
	SetMove(move);

	// 状態管理
	ManageState();

	// モーション管理
	ManageMotion();

	// 武器の追従
	if (m_info.pWeapon != nullptr)
	{
		CMotionDiv *pBody = GetBody();

		if (pBody != nullptr)
		{
			pBody->MultiplyMtx();
		}

		m_info.pWeapon->FollowPlayerHand();
	}

	if (m_info.pArrow != nullptr)
	{// 矢印の追従
		D3DXVECTOR3 rot = GetRot();
		D3DXVECTOR3 posArrow = pos;

		posArrow.y = ARROW_POSY;

		m_info.pArrow->SetPosition(posArrow);
		m_info.pArrow->SetRot(rot);
	}
}

//=====================================================
// 入力処理
//=====================================================
void CPlayer::Input(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		CGame::STATE state = pGame->GetState();

		if (state == CGame::STATE_ESCAPE || state == CGame::STATE_RESULT || state == CGame::STATE_END)
		{
			return;
		}
	}

	// 移動処理
	InputMove();

	// 攻撃処理
	InputAttack();

	// エイミングの処理
	Aim();
}

//=====================================================
// 移動の入力
//=====================================================
void CPlayer::InputMove(void)
{
	CInputJoypad *pJoyPad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pJoyPad == nullptr || pKeyboard == nullptr)
	{
		return;
	}

	// プレイヤーID取得
	int nId = m_info.nIDJoypad;

	D3DXVECTOR3 vecStickL = 
	{// スティックのベクトル取得
		pJoyPad->GetJoyStickLX(nId),
		pJoyPad->GetJoyStickLY(nId),
		0.0f,
	};

	if (pKeyboard->GetPress(DIK_W))
	{
		vecStickL.y += MOVE_SPEED;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecStickL.y -= MOVE_SPEED;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecStickL.x -= MOVE_SPEED;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecStickL.x += MOVE_SPEED;
	}

	D3DXVECTOR3 vecMove =
	{// 移動ベクトルの代入
		vecStickL.x,
		0.0f,
		vecStickL.y,
	};

	// 移動速度の設定
	D3DXVECTOR3 move = GetMove();

	D3DXVec3Normalize(&vecMove, &vecMove);
	vecMove *= MOVE_SPEED;

	move += vecMove;

	SetMove(move);
}

//=====================================================
// 攻撃の入力
//=====================================================
void CPlayer::InputAttack(void)
{
	if (m_info.pWeapon != nullptr)
	{// 武器の攻撃
		bool bEnable = m_info.pWeapon->IsEnable();

		if (bEnable)
		{
			m_info.pWeapon->Attack();
		}
	}
	else
	{// 素手の場合の処理

	}
}

//=====================================================
// インタラクトの入力
//=====================================================
bool CPlayer::InputInteract(void)
{
	bool bTrigger = false;

	CInputJoypad* pJoyPad = CInputJoypad::GetInstance();
	int nID = GetIDJoypad();

	if (pJoyPad == nullptr)
	{
		return bTrigger;
	}

	if (pJoyPad->GetTrigger(CInputJoypad::PADBUTTONS_LB, nID))
	{
		bTrigger = true;
	}

	return bTrigger;
}

//=====================================================
// インタラクトの長押し
//=====================================================
bool CPlayer::InputInteractPress(void)
{
	bool bPress = false;

	CInputJoypad* pJoyPad = CInputJoypad::GetInstance();
	int nID = GetIDJoypad();

	if (pJoyPad == nullptr)
	{
		return bPress;
	}

	if (pJoyPad->GetPress(CInputJoypad::PADBUTTONS_LB, nID))
	{
		bPress = true;
	}

	return bPress;
}


//=====================================================
// 武器の有効可
//=====================================================
void CPlayer::EnableWeapon(bool bEnable)
{
	if (m_info.pWeapon != nullptr)
	{
		m_info.pWeapon->SetEnable(bEnable);
	}
}

//=====================================================
// エイミングの処理
//=====================================================
void CPlayer::Aim(void)
{
	CInputJoypad *pJoyPad = CInputJoypad::GetInstance();
	
	if (pJoyPad == nullptr)
	{
		return;
	}

	// プレイヤーID取得
	int nId = m_info.nIDJoypad;

	D3DXVECTOR3 vecStickR =
	{// スティックのベクトル取得
		pJoyPad->GetJoyStickRX(nId),
		pJoyPad->GetJoyStickRY(nId),
		0.0f,
	};

	float fLength = D3DXVec3Length(&vecStickR);

	float fAngleDest = 0.0f;

	if (fLength >= 0.3f)
	{// 右スティックを動かしている場合
		// 角度の取得
		fAngleDest = atan2f(vecStickR.x, vecStickR.y);
	}
	else
	{// 移動だけしている場合
		D3DXVECTOR3 move = GetMove();

		float fLengthMove = D3DXVec3Length(&move);

		if (fLengthMove >= 1.0f)
		{
			// 角度の取得
			fAngleDest = atan2f(move.x, move.z);
		}
		else
		{
			return;
		}
	}

	// 角度補正
	D3DXVECTOR3 rot = GetRot();

	universal::LimitRot(&fAngleDest);

	universal::FactingRot(&rot.y, fAngleDest + D3DX_PI, ROT_SPEED);

	SetRot(rot);
}

//=====================================================
// 状態管理
//=====================================================
void CPlayer::ManageState(void)
{
	switch (m_info.state)
	{
	case STATE_NORMAL:
	{// 通常状態

	}
		break;
	case STATE_DAMAGE:
	{// ダメージ状態
		float fTick = CManager::GetTick();

		m_info.fTimerState -= fTick;

		if (m_info.fTimerState <= 0.0f)
		{
			m_info.state = STATE_NORMAL;

			for (int nCutPath = 0; nCutPath < CCharacterDiv::PARTS_MAX; nCutPath++)
			{
				CMotionDiv* pBody = GetBody();

				if (pBody != nullptr)
				{
					pBody->ResetAllCol();
				}
			}
		}
	}
		break;
	case STATE_DEATH:
	{// 死亡状態

	}
		break;
	default:
		break;
	}
}

//=====================================================
// モーション管理
//=====================================================
void CPlayer::ManageMotion(void)
{
	if (GetBody() == nullptr)
	{
		return;
	}
	
	D3DXVECTOR3 move = GetMove();

	float fSpeed = D3DXVec3Length(&move);

	float fRotPlayer = GetRot().y;
	float fRotMove = atan2f(-move.x, -move.z);
	float fRot = fRotMove - fRotPlayer;
	universal::LimitRot(&fRot);

	int nMotionLower = GetMotion(CCharacterDiv::PARTS_LOWER);
	int nMotionUpper = GetMotion(CCharacterDiv::PARTS_UPPER);

	CDebugProc::GetInstance()->Print("\nスピード[%f]",fSpeed);

	// 下半身のモーション
	{
		// ドア開けるモーション
		if (m_info.motionInfo.bDoorPress)
		{
			if (nMotionLower != MOTION_OPEN_DOOR)
			{
				SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_OPEN_DOOR);
			}
		}
		// 修理アイテム
		else if (m_info.pItemRepair != nullptr)
		{
			if (fSpeed > MOVE_LINE)
			{
				if (fRot >= 0.0f && fRot <= (D3DX_PI * 0.25f) ||
					fRot <= 0.0f && fRot >= -(D3DX_PI * 0.25f))
				{
					if (nMotionLower != MOTION_ITEM_WALK_FRONT)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_ITEM_WALK_FRONT);
					}
				}
				else if (fRot >= (D3DX_PI * 0.75f) && fRot <= D3DX_PI ||
					fRot <= -(D3DX_PI * 0.75f) && fRot >= -D3DX_PI)
				{
					if (nMotionLower != MOTION_ITEM_WALK_BACK)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_ITEM_WALK_BACK);
					}
				}
				else if (fRot >= (D3DX_PI * 0.25f) && fRot <= (D3DX_PI * 0.75f))
				{
					if (nMotionLower != MOTION_ITEM_WALK_RIGHT)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_ITEM_WALK_RIGHT);
					}
				}
				else if (fRot <= -(D3DX_PI * 0.25f) && fRot >= -(D3DX_PI * 0.75f))
				{
					if (nMotionLower != MOTION_ITEM_WALK_LEFT)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_ITEM_WALK_LEFT);
					}
				}
			}
			else
			{
				if (nMotionLower != MOTION_ITEM_NEUTRAL)
				{
					SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_ITEM_NEUTRAL);
				}
			}
		}
		// 所有武器
		else if (m_info.pWeapon != nullptr)
		{
			switch (m_info.pWeapon->GetType())
			{
				// マグナム
			case CWeapon::TYPE_MAGNUM:

				if (fSpeed > MOVE_LINE)
				{
					if (fRot >= 0.0f && fRot <= (D3DX_PI * 0.25f) ||
						fRot <= 0.0f && fRot >= -(D3DX_PI * 0.25f))
					{
						if (nMotionLower != MOTION_MAGNUM_WALK_FRONT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_WALK_FRONT);
						}
					}
					else if (fRot >= (D3DX_PI * 0.75f) && fRot <= D3DX_PI ||
						fRot <= -(D3DX_PI * 0.75f) && fRot >= -D3DX_PI)
					{
						if (nMotionLower != MOTION_MAGNUM_WALK_BACK)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_WALK_BACK);
						}
					}
					else if (fRot >= (D3DX_PI * 0.25f) && fRot <= (D3DX_PI * 0.75f))
					{
						if (nMotionLower != MOTION_MAGNUM_WALK_RIGHT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_WALK_RIGHT);
						}
					}
					else if (fRot <= -(D3DX_PI * 0.25f) && fRot >= -(D3DX_PI * 0.75f))
					{
						if (nMotionLower != MOTION_MAGNUM_WALK_LEFT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_WALK_LEFT);
						}
					}
				}
				else
				{
					if (nMotionLower != MOTION_MAGNUM_NEUTRAL)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_NEUTRAL);
					}
				}

				break;

				// マシンガン
			case CWeapon::TYPE_MACHINEGUN:

				if (fSpeed > MOVE_LINE)
				{
					if (fRot >= 0.0f && fRot <= (D3DX_PI * 0.25f) ||
						fRot <= 0.0f && fRot >= -(D3DX_PI * 0.25f))
					{
						if (nMotionLower != MOTION_MAGNUM_WALK_FRONT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_WALK_FRONT);
						}
					}
					else if (fRot >= (D3DX_PI * 0.75f) && fRot <= D3DX_PI ||
						fRot <= -(D3DX_PI * 0.75f) && fRot >= -D3DX_PI)
					{
						if (nMotionLower != MOTION_MAGNUM_WALK_BACK)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_WALK_BACK);
						}
					}
					else if (fRot >= (D3DX_PI * 0.25f) && fRot <= (D3DX_PI * 0.75f))
					{
						if (nMotionLower != MOTION_MAGNUM_WALK_RIGHT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_WALK_RIGHT);
						}
					}
					else if (fRot <= -(D3DX_PI * 0.25f) && fRot >= -(D3DX_PI * 0.75f))
					{
						if (nMotionLower != MOTION_MAGNUM_WALK_LEFT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_WALK_LEFT);
						}
					}
				}
				else
				{
					if (nMotionLower != MOTION_MAGNUM_NEUTRAL)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_MAGNUM_NEUTRAL);
					}
				}

				break;

				// ショットガン
			case CWeapon::TYPE_SHOTGUN:

				if (fSpeed > MOVE_LINE)
				{
					if (fRot >= 0.0f && fRot <= (D3DX_PI * 0.25f) ||
						fRot <= 0.0f && fRot >= -(D3DX_PI * 0.25f))
					{
						if (nMotionLower != MOTION_RIFLE_WALK_FRONT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_RIFLE_WALK_FRONT);
						}
					}
					else if (fRot >= (D3DX_PI * 0.75f) && fRot <= D3DX_PI ||
						fRot <= -(D3DX_PI * 0.75f) && fRot >= -D3DX_PI)
					{
						if (nMotionLower != MOTION_RIFLE_WALK_BACK)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_RIFLE_WALK_BACK);
						}
					}
					else if (fRot >= (D3DX_PI * 0.25f) && fRot <= (D3DX_PI * 0.75f))
					{
						if (nMotionLower != MOTION_RIFLE_WALK_RIGHT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_RIFLE_WALK_RIGHT);
						}
					}
					else if (fRot <= -(D3DX_PI * 0.25f) && fRot >= -(D3DX_PI * 0.75f))
					{
						if (nMotionLower != MOTION_RIFLE_WALK_LEFT)
						{
							SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_RIFLE_WALK_LEFT);
						}
					}
				}
				else
				{
					if (nMotionLower != MOTION_RIFLE_NEUTRAL)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_RIFLE_NEUTRAL);
					}
				}

				break;
			}
		}
		// 何もなし
		else
		{
			if (fSpeed > MOVE_LINE)
			{
				if (fRot >= 0.0f && fRot <= (D3DX_PI * 0.25f) ||
					fRot <= 0.0f && fRot >= -(D3DX_PI * 0.25f))
				{
					if (nMotionLower != MOTION_WALK_FRONT)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_WALK_FRONT);
					}
				}
				else if (fRot >= (D3DX_PI * 0.75f) && fRot <= D3DX_PI ||
					fRot <= -(D3DX_PI * 0.75f) && fRot >= -D3DX_PI)
				{
					if (nMotionLower != MOTION_WALK_BACK)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_WALK_BACK);
					}
				}
				else if (fRot >= (D3DX_PI * 0.25f) && fRot <= (D3DX_PI * 0.75f))
				{
					if (nMotionLower != MOTION_WALK_RIGHT)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_WALK_RIGHT);
					}
				}
				else if (fRot <= -(D3DX_PI * 0.25f) && fRot >= -(D3DX_PI * 0.75f))
				{
					if (nMotionLower != MOTION_WALK_LEFT)
					{
						SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_WALK_LEFT);
					}
				}
			}
			else
			{
				if (nMotionLower != MOTION_NEUTRAL)
				{
					SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_NEUTRAL);
				}
			}
		}
	}

	// 上半身のモーション
	{
		bool bFinish = GetBody()->IsFinish(CCharacterDiv::PARTS_UPPER);
		int nKey = GetBody()->GetKey(CCharacterDiv::PARTS_UPPER);
		int nNumKey = GetBody()->GetMotionInfo(CCharacterDiv::PARTS_UPPER, nMotionUpper).nNumKey;

		// ドア開けるモーション
		if (m_info.motionInfo.bDoorPress)
		{
			if (nMotionUpper != MOTION_OPEN_DOOR)
			{
				SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_OPEN_DOOR);
			}
		}
		// 物拾う
		else if (m_info.motionInfo.bItemTrigger ||
				 nMotionUpper == MOTION_ITEM_PICK_UP && bFinish == false && nKey != nNumKey)
		{
			if (nMotionUpper != MOTION_ITEM_PICK_UP)
			{
				SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_ITEM_PICK_UP);
			}
		}
		// 所有修理アイテム
		else if (m_info.pItemRepair != nullptr)
		{
			if (fSpeed > MOVE_LINE)
			{
				if (nMotionUpper != MOTION_ITEM_WALK_FRONT)
				{
					SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_ITEM_WALK_FRONT);
				}
			}
			else
			{
				if (nMotionUpper != MOTION_ITEM_NEUTRAL)
				{
					SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_ITEM_NEUTRAL);
				}
			}
		}
		// 所有武器
		else if (m_info.pWeapon != nullptr)
		{
			switch (m_info.pWeapon->GetType())
			{
				// マガジン
			case CWeapon::TYPE_MAGNUM:

				if (nMotionUpper != MOTION_MAGNUM_ATTACK)
				{
					SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_MAGNUM_ATTACK);
				}

				break;

				// マシンガン
			case CWeapon::TYPE_MACHINEGUN:

				if (nMotionUpper != MOTION_MAGNUM_ATTACK)
				{
					SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_MAGNUM_ATTACK);
				}

				break;

				// マシンガン
			case CWeapon::TYPE_SHOTGUN:

				if (nMotionUpper != MOTION_RIFLE_ATTACK)
				{
					SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_RIFLE_ATTACK);
				}

				break;
			}
		}
		// 何もなし
		else
		{
			if (fSpeed > MOVE_LINE)
			{

				if (fRot >= 0.0f && fRot <= (D3DX_PI * 0.25f) ||
					fRot <= 0.0f && fRot >= -(D3DX_PI * 0.25f))
				{
					if (nMotionUpper != MOTION_WALK_FRONT)
					{
						SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_WALK_FRONT);
					}
				}
				else if (fRot >= (D3DX_PI * 0.75f) && fRot <= D3DX_PI ||
						 fRot <= -(D3DX_PI * 0.75f) && fRot >= -D3DX_PI)
				{
					if (nMotionUpper != MOTION_WALK_BACK)
					{
						SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_WALK_BACK);
					}
				}
				else if (fRot >= (D3DX_PI * 0.25f) && fRot <= (D3DX_PI * 0.75f))
				{
					if (nMotionUpper != MOTION_WALK_RIGHT)
					{
						SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_WALK_RIGHT);
					}
				}
				else if (fRot <= -(D3DX_PI * 0.25f) && fRot >= -(D3DX_PI * 0.75f))
				{
					if (nMotionUpper != MOTION_WALK_LEFT)
					{
						SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_WALK_LEFT);
					}
				}
			}
			else
			{
				if (nMotionUpper != MOTION_NEUTRAL)
				{
					SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_NEUTRAL);
				}
			}
		}
	}

	// ドアの入力情報の初期化
	m_info.motionInfo.bDoorPress = false;
	m_info.motionInfo.bItemTrigger = false;
}

//=====================================================
// 描画処理
//=====================================================
void CPlayer::Draw(void)
{
	// 継承クラスの描画
	CCharacterDiv::Draw();

	// デバッグ表示
	Debug();
}

//=====================================================
// 武器設定
//=====================================================
void CPlayer::SetWeapon(CWeapon::TYPE type)
{
	if (m_info.pWeapon != nullptr)
	{
		m_info.pWeapon->Uninit();
		m_info.pWeapon = nullptr;
	}

	m_info.pWeapon = CWeapon::Create(type, HAND_PARTS_NUM);

	if (m_info.pWeapon != nullptr)
	{
		m_info.pWeapon->SetPlayer(this);
	}
}

//=====================================================
// ヒット処理
//=====================================================
void CPlayer::Hit(float fDamage)
{
	if (m_info.state == STATE_NORMAL)
	{
		m_info.fLife -= fDamage;

		if (m_info.fLife <= 0.0f)
		{// 死亡判定
			m_info.fLife = 0.0f;

			m_info.state = STATE_DEATH;

			Uninit();
		}
		else
		{// ダメージ判定
			m_info.state = STATE_DAMAGE;

			m_info.fTimerState = DAMAGE_TIME;

			for (int nCutPath = 0; nCutPath < CCharacterDiv::PARTS_MAX; nCutPath++)
			{
				CMotionDiv* pBody = GetBody();

				if (pBody != nullptr)
				{
					pBody->SetAllCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}
			}
		}
	}
}

//=====================================================
// デバッグ表示
//=====================================================
void CPlayer::Debug(void)
{
#ifndef _DEBUG

	return;

#endif

	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\nプレイヤー番号[%d]", m_info.nID);
	pDebugProc->Print("\nプレイヤーの位置[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	pDebugProc->Print("\nプレイヤーの向き[%f,%f,%f]", GetRot().x, GetRot().y, GetRot().z);

	if (GetBody() != nullptr)
	{
		int nMotion = GetBody()->GetMotion(CCharacterDiv::PARTS_LOWER);

		pDebugProc->Print("\n下半身のモーション[%d]", nMotion);
	}

	if (GetBody() != nullptr)
	{
		int nMotion = GetBody()->GetMotion(CCharacterDiv::PARTS_UPPER);

		pDebugProc->Print("\n上半身のモーション[%d]", nMotion);
	}
}