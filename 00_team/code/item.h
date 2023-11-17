//*****************************************************
//
// アイテムの処理[item.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************
// インクルード
//*****************************************************
#include "objectX.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionSphere;
class CBillboard;

//*****************************************************
// クラスの定義
//*****************************************************
class CItem : public CObjectX
{
public:
	CItem(int nPriority = 3);	// コンストラクタ
	~CItem();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItem *Create(void);
	virtual void Interact(CObject* pObj);
	CCollisionSphere *GetCollisionSphere(void) { return m_pCollisionSphere; }

private:
	CCollisionSphere *m_pCollisionSphere;
	CBillboard *m_pInteract;
};

#endif

