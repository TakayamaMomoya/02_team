//*****************************************************
//
// 修理アイテムの処理[ItemRepair.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ITEMREPIR_H_
#define _ITEMREPIR_H_

//*****************************************************
// インクルード
//*****************************************************
#include "item.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CPlayer;

//*****************************************************
// クラスの定義
//*****************************************************
class CItemRepair : public CItem
{
public:
	CItemRepair(int nPriority = 5);	// コンストラクタ
	~CItemRepair();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItemRepair *Create(void);

private:
	void Load(void);
	void GetItem(CObject* pObj);
	void CheckPlayerAlive(void);
	void FollowPlayerHand(void);

	CPlayer *m_pPlayer;
};

#endif

