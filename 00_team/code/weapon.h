//*****************************************************
//
// 武器の処理[weapon.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _WEAPON_H_
#define _WEAPON_H_

//*****************************************************
// インクルード
//*****************************************************
#include "objectX.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CPlayer;

//*****************************************************
// クラスの定義
//*****************************************************
class CWeapon : public CObjectX
{
public:
	enum TYPE
	{
		TYPE_MAGNUM = 0,	// マグナム
		TYPE_MACHINEGUN,	// マシンガン
		TYPE_MAX
	};

	CWeapon(int nPriority = 3);	// コンストラクタ
	~CWeapon();	// デストラクタ

	static CWeapon *Create(CWeapon::TYPE type,int nIdxhand);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	virtual void Attack(void) {};
	CPlayer *GetPlayer(void) { return m_pPlayer; }
	void SetPlayer(CPlayer *pPlayer);

private:
	void FollowPlayerHand(void);

	int m_nIdxHand;
	int m_nIdxPlayer;
	CPlayer *m_pPlayer;
};

#endif

