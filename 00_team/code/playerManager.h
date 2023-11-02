//*****************************************************
//
// プレイヤーマネージャー[PlayerManager.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _PLAYERMANAGER_H_
#define _PLAYERMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayerManager : public CObject
{
public:
	CPlayerManager();	// コンストラクタ
	~CPlayerManager();	// デストラクタ

	static CPlayerManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayerManager *GetInstance(void) { return m_pPlayerManager; }

private:
	static CPlayerManager *m_pPlayerManager;	// 自身のポインタ
};

#endif
