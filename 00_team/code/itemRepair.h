//*****************************************************
//
// 修理アイテムの処理[ItemRepair.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _ITEMREPIR_H_
#define _ITEMREPIR_H_

//*****************************************************
// インクルード
//*****************************************************
#include "gimmick.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CPlayer;

//*****************************************************
// クラスの定義
//*****************************************************
class CItemRepair : public CGimmick
{
public:
	CItemRepair(int nPriority = 5);	// コンストラクタ
	~CItemRepair();	// デストラクタ

	static CItemRepair *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Load(void);
	void Interact(CObject* pObj);
	void CollisionRocket(void);
	void CheckPlayerAlive(void);
	void FollowPlayerHand(void);

	bool m_bInRocket;
	CPlayer *m_pPlayer;
};

#endif

