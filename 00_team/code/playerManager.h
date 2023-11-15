//*****************************************************
//
// プレイヤーマネージャー[PlayerManager.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _PLAYERMANAGER_H_
#define _PLAYERMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CPlayer;

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayerManager : public CObject
{
public:
	CPlayerManager();	// コンストラクタ
	~CPlayerManager();	// デストラクタ

	static CPlayerManager *Create(void);
	void CreatePlayer(int nNumPlayer);
	void CreateOnePlayer(int nIdx);
	HRESULT Init(void);
	void Uninit(void);
	void ReleasePlayer(int nIdx);
	void Update(void);
	void Draw(void);
	CPlayer *GetPlayer(int nIdx) { return m_apPlayer[nIdx]; }
	static CPlayerManager *GetInstance(void) { return m_pPlayerManager; }

private:
	CPlayer *m_apPlayer[NUM_PLAYER];	// プレイヤーの配列

	static CPlayerManager *m_pPlayerManager;	// 自身のポインタ
};

#endif
