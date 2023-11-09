//*****************************************************
//
// アイテムの処理[item.h]
// Author:��山桃也
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
	static CItem *Create(TYPE type);

private:
	void Load(void);
	void GetItem(CObject* pObj);
	void ApplyEffect(CPlayer *pPlayer);

	TYPE m_type;
	CCollisionSphere *m_pCollisionSphere;
};

#endif

