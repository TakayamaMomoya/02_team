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
	void SetPosition(D3DXVECTOR3 pos);
	static CContainer *Create(void);

private:
	enum STATE
	{
		STATE_NONE = 0,	// 何でもない状態
		STATE_NORMAL,	// 通常状態
		STATE_OPEN,	// 開いている状態
		STATE_MAX
	};
	struct SInfo
	{// 情報
		CObjectX *pCap;	// 蓋のオブジェクト
		STATE state;	// 状態
	};
	void Load(void);
	void Interact(CObject* pObj);
	void Open(void);

	SInfo m_info;
};

#endif

