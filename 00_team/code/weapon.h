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
	struct SInfo
	{// 自身の情報
		int nNumBullet;
		int nMaxBullet;
		int nRapid;
		int nCntShot;
		int nIdxHand;
		int nIdxPlayer;
		CPlayer *pPlayer;
		TYPE type;
	};

	CWeapon(int nPriority = 3);	// コンストラクタ
	~CWeapon();	// デストラクタ

	static CWeapon *Create(CWeapon::TYPE type,int nIdxhand);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	virtual void Attack(void) {};
	CPlayer *GetPlayer(void) { return m_info.pPlayer; }
	void SetPlayer(CPlayer *pPlayer);
	int GetID(void) { return m_info.nIdxPlayer; }
	void SetBullet(int nBullet);
	int GetBullet(void) { return m_info.nNumBullet; }
	void SetMaxBullet(int nBullet);
	void SetRapid(int nRapid) { m_info.nRapid = nRapid; }
	int GetRapid(void) { return m_info.nRapid; }
	void SetCntShot(int nCntShot) { m_info.nCntShot = nCntShot; }
	int GetCntShot(void) { return m_info.nCntShot; }

private:
	void FollowPlayerHand(void);

	SInfo m_info;
};

#endif

