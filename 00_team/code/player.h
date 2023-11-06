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
#include "character.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CMotion;
class CCollisionSphere;
class CWeapon;

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayer : public CCharacter
{
public:
	CPlayer(int nPriority = 4);	// コンストラクタ
	~CPlayer();	// デストラクタ

	static CPlayer *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetWeapon(void);
	void SetID(int nID) { m_info.nID = nID; }

private:
	struct SInfo
	{
		int nID;	// 番号
		CCollisionSphere *pCollisionSphere;	// 当たり判定
		CWeapon *pWeapon;	// 武器
	};

	void Input(void);
	void InputMove(void);
	void InputAttack(void);
	void Aim(void);
	void Debug(void);

	SInfo m_info;	// 自身の情報
};

#endif