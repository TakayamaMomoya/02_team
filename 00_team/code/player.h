//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "characterDiv.h"
#include "weapon.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CMotion;
class CCollisionSphere;
class CCollisionCube;

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayer : public CCharacterDiv
{
public:
	CPlayer(int nPriority = 4);	// コンストラクタ
	~CPlayer();	// デストラクタ

	static CPlayer *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetWeapon(CWeapon::TYPE type);
	void SetID(int nID);
	void SetIDJoypad(int nID) { m_info.nIDJoypad = nID; }
	int GetIDJoypad(void) { return m_info.nIDJoypad; }
	int GetID(void) { return m_info.nID; }
	void ReleaseWeapon(void) { m_info.pWeapon = nullptr; }
	void Hit(float fDamage);
	bool InputInteract(void);
	bool InputInteractPress(void);
	void EnableWeapon(bool bEnable);

private:
	enum STATE
	{
		STATE_NONE = 0,	// 何でもない状態
		STATE_NORMAL,	// 通常状態
		STATE_DAMAGE,	// ダメージ状態
		STATE_DEATH,	// 死亡状態
		STATE_MAX
	};
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// 待機状態
		MOTION_WALK,		// 歩きモーション
		MOTION_MAX
	};
	struct SInfo
	{
		int nID;	// 番号
		int nIDJoypad;	// コントローラーの番号
		float fLife;	// 体力
		float fTimerState;	// 状態遷移カウンタ
		STATE state;	// 状態
		CCollisionSphere *pCollisionSphere;	// 球の当たり判定
		CCollisionCube *pCollisionCube;	// 立方体の当たり判定
		CWeapon *pWeapon;	// 武器
	};

	void Input(void);
	void InputMove(void);
	void InputAttack(void);
	void Aim(void);
	void ManageState(void);
	void ManageMotion(void);
	void Debug(void);

	SInfo m_info;	// 自身の情報
};

#endif