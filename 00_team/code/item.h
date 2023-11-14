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
	enum TYPE
	{
		TYPE_MAGNUM = 0,	// マグナム
		TYPE_MACHINEGUN,	// マシンガン
		TYPE_RIFLE,	// ライフル
		TYPE_MAX
	};

	CItem(int nPriority = 3);	// コンストラクタ
	~CItem();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItem *Create(void);
	virtual void GetItem(CObject* pObj);

private:
	CCollisionSphere *m_pCollisionSphere;
	CBillboard *m_pInteract;
};

#endif

