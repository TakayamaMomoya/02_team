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
// 前方宣言
//*****************************************************
class CCollisionCube;

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
	void SetPosition(D3DXVECTOR3 pos);

private:
	enum STATE
	{
		STATE_NONE = 0,	// 何もしていない状態
		STATE_NORMAL,	// 通常状態
		STATE_OPEN,	// 開いている状態
		STATE_MAX
	};
	struct SInfo
	{// 情報
		float fLife;	// 体力
		CCollisionCube *pCollisionCube;	// 押し出しの当たり判定
		STATE state;	// 状態
	};
	void Interact(CObject* pObj);
	void proceed(void);
	void Open(void);

	SInfo m_info;
};

#endif

