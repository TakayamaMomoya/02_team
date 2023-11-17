//*****************************************************
//
// コンテナの処理[container.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _CONTAINER_H_
#define _CONTAINER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "item.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CContainer : public CItem
{
public:
	CContainer(int nPriority = 3);	// コンストラクタ
	~CContainer();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CContainer *Create(void);

private:
	void Load(void);
	void Interact(CObject* pObj);
};

#endif

