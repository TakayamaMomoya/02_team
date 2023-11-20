//*****************************************************
//
// ドアの処理[door.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _DOOR_H_
#define _DOOR_H_

//*****************************************************
// インクルード
//*****************************************************
#include "gimmick.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CDoor : public CGimmick
{
public:
	CDoor(int nPriority = 3);	// コンストラクタ
	~CDoor();	// デストラクタ

	static CDoor *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	struct SInfo
	{// 情報
		float fLife;
	};

	SInfo m_info;
};

#endif

