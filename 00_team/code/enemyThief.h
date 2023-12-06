//*****************************************************
//
// 泥棒敵の処理[enemyThief.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMYThief_H_
#define _ENEMYThief_H_

//*****************************************************
// インクルード
//*****************************************************
#include "enemy.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyThief : public CEnemy
{
public:
	CEnemyThief();	// コンストラクタ
	~CEnemyThief();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// 待機モーション
		MOTION_WALK,	// 歩きモーション
		MOTION_DEATH,	// 死亡モーション
		MOTION_DANCE,	// ダンスモーション
		MOTION_MAX
	};

	void ChaseRocket(void);

	bool m_bTakeRepair;
};

#endif
