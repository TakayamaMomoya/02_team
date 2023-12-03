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
#include "player.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayerManager
{
public:
	CPlayerManager();	// コンストラクタ
	~CPlayerManager();	// デストラクタ

	static CPlayerManager *Create(void);
	void CreatePlayer(void);
	CPlayer *BindPlayer(int nIdxJoypad);
	HRESULT Init(void);
	void Uninit(void);
	void ReleasePlayer(int nIdx);
	CPlayer *GetPlayer(int nIdx) { return m_apPlayer[nIdx]; }
	static CPlayerManager *GetInstance(void) { return m_pPlayerManager; }
	int GetNumPlayer(void) { return m_nNumPlayer; }
	CPlayer::SParam GetPlayerParam(void) { return m_paramPlayer; }

private:
	void LoadParamPlayer(void);

	int m_nNumPlayer;	// プレイヤーの数
	int m_anIDJoypad[NUM_PLAYER];	// プレイヤーのコントローラー番号
	CPlayer *m_apPlayer[NUM_PLAYER];	// プレイヤーの配列
	static CPlayerManager *m_pPlayerManager;	// 自身のポインタ
	CPlayer::SParam m_paramPlayer;	// 保存用プレイヤーパラメーター
};

#endif
