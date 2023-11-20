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
	struct SInfo
	{// 情報
		float fLife;	// 体力
		CCollisionCube *pCollisionCube;	// 押し出しの当たり判定
	};
	void Interact(CObject* pObj);
	void proceed(void);

	SInfo m_info;
};

#endif

