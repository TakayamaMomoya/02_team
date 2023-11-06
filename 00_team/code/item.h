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
	static CItem *Create();

private:
	void GetItem(CObject *pObj);

	CCollisionSphere *m_pCollisionSphere;
};

#endif

