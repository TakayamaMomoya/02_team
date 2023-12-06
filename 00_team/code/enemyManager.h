//*****************************************************
//
// 敵マネージャー[enemyManager.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"
#include "enemy.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CEnemyManager : public CObject
{
public:
	CEnemyManager();	// コンストラクタ
	~CEnemyManager();	// デストラクタ

	CEnemy *CreateEnemy(D3DXVECTOR3 pos, CEnemy::TYPE type);
	static CEnemyManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CEnemy *GetHead(void) { return m_pHead; }
	CEnemy *GetTail(void) { return m_pTail; }
	void SetHead(CEnemy *pEnemy) { m_pHead = pEnemy; }
	void SetTail(CEnemy *pEnemy) { m_pTail = pEnemy; }
	void ReleaseThief(void) { m_pThief = nullptr; }
	static CEnemyManager *GetInstance(void) { return m_pEnemyManager; }

private:
	void SpawnThief(void);

	CEnemy *m_pHead;	// 先頭のアドレス
	CEnemy *m_pTail;	// 最後尾のアドレス
	int m_nCntSpawn;	// 通常敵スポーンカウンター
	float m_fTimerThief;	// 泥棒敵スポーンタイマー
	float m_fTimeSpawnThief;	// 泥棒敵がスポーンするまでの時間
	CEnemy *m_pThief;	// 泥棒敵のポインタ

	static CEnemyManager *m_pEnemyManager;	// 自身のポインタ
};

#endif
