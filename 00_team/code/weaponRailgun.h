//*****************************************************
//
// レールガンの処理[weaponRailgun.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _RAILGUN_H_
#define _RAILGUN_H_

//*****************************************************
// インクルード
//*****************************************************
#include "weapon.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CRailgun : public CWeapon
{
public:
	struct SInfoRailgun
	{
		float fWidth;	// 判定の幅
		float fLength;	// 判定の長さ
	};

	CRailgun(int nPriority = 3);	// コンストラクタ
	~CRailgun();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Attack(void);
	void Draw(void);

private:
	void Shot(void);

	SInfoRailgun m_info;
};

#endif

