//*****************************************************
//
// ロケットの処理[rocket.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ROCKET_H_
#define _ROCKET_H_

//*****************************************************
// インクルード
//*****************************************************
#include "objectX.h"
#include <stdio.h>

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionSphere;

//*****************************************************
// クラスの定義
//*****************************************************
class CRocket : public CObjectX
{
public:
	CRocket(int nPriority = 3);	// コンストラクタ
	~CRocket();	// デストラクタ

	static CRocket *Create(void);
	static CRocket *GetInstance(void) { return m_pRocket; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Load(void);
	void ApplyInfo(FILE *pFile,char *pTemp);

	float m_fRadius;	// 判定の半径
	CCollisionSphere *m_pCollisionRocket;	// ゴール判定
	static CRocket *m_pRocket;	// 自身のポインタ
};

#endif

