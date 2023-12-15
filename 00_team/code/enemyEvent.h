//*****************************************************
//
// 敵イベントの処理[enemyEvent.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMYEVENT_H_
#define _ENEMYEVENT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyEvent : public CObject
{
public:
	CEnemyEvent(int nPriority = 6);	// コンストラクタ
	~CEnemyEvent();	// デストラクタ

	static CEnemyEvent *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	float m_fLife;	// 寿命
};

#endif
