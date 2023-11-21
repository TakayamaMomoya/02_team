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
class CGimmick : public CObjectX
{
public:
	CGimmick(int nPriority = 3);	// コンストラクタ
	~CGimmick();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGimmick *Create(void);
	virtual void Interact(CObject* pObj);
	CCollisionSphere *GetCollisionSphere(void) { return m_pCollisionSphere; }
	void SetEnable(bool bEnable) { m_bEnable = bEnable; }

private:
	CCollisionSphere *m_pCollisionSphere;
	CBillboard *m_pInteract;
	bool m_bEnable;	// インタラクトできるかどうか

	CGimmick *m_pPrev;	// 前のポインタ
	CGimmick *m_pNext;	// 次のポインタ

	static CGimmick *m_pHead;	// 先頭のアドレス
	static CGimmick *m_pTail;	// 最後尾のアドレス
};

#endif

