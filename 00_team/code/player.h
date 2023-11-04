//*****************************************************
//
// プレイヤーの処理[player.cpp]
// Author:髙山桃也
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "character.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CMotion;

//*****************************************************
// クラスの定義
//*****************************************************
class CPlayer : public CCharacter
{
public:
	CPlayer(int nPriority = 4);	// コンストラクタ
	~CPlayer();	// デストラクタ

	static CPlayer *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetID(int nID) { m_info.nID = nID; }

private:
	struct SInfo
	{
		int nID;	// 番号
	};

	void Debug(void);

	SInfo m_info;	// 自身の情報
};

#endif