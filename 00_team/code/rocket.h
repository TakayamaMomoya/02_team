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
	enum STATE
	{
		STATE_NONE = 0,	// 何もしていない状態
		STATE_NORMAL,	// 通常状態
		STATE_ESCAPE,	// 脱出状態
		STATE_MAX
	};

	CRocket(int nPriority = 3);	// コンストラクタ
	~CRocket();	// デストラクタ

	static CRocket *Create(void);
	static CRocket *GetInstance(void) { return m_pRocket; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetProgress(void) { return m_nProgress; }
	void AddProgress(int nProgress);
	void SetState(STATE state) { m_state = state; }
	float GetTime(void) { return m_fTimeRapir; }
	float GetRadius(void) { return m_fRadius; }

private:
	void Load(void);
	void ApplyInfo(FILE *pFile,char *pTemp);
	void UpdateEscape(void);
	void SwapModel(int nProgress);
	void Debug(void);

	float m_fRadius;	// 判定の半径
	float m_fSpeed;	// 上昇速度
	float m_fDeleteHeight;	// 削除する高さ
	float m_fTimeRapir;	// 修理にかかる時間
	int m_nProgress;	// 進行状況
	STATE m_state;	// 状態
	CCollisionSphere *m_pCollisionRocket;	// ゴール判定
	static CRocket *m_pRocket;	// 自身のポインタ
};

#endif

