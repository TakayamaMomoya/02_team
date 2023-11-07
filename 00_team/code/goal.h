//*****************************************************
//
// ゴールの処理[goal.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************
// インクルード
//*****************************************************
#include "objectX.h"
#include <stdio.h>

//*****************************************************
// クラスの定義
//*****************************************************
class CGoal : public CObjectX
{
public:
	CGoal(int nPriority = 3);	// コンストラクタ
	~CGoal();	// デストラクタ

	static CGoal* Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Load(void);
	void ApplyInfo(FILE *pFile,char *pTemp);
};

#endif

