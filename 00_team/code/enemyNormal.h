//*****************************************************
//
// 通常敵の処理[enemyNormal.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMYNORMAL_H_
#define _ENEMYNORMAL_H_

//*****************************************************
// インクルード
//*****************************************************
#include "enemy.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyNormal : public CEnemy
{
public:
	CEnemyNormal();	// コンストラクタ
	~CEnemyNormal();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};

#endif
