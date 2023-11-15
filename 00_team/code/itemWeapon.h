//*****************************************************
//
// 武器アイテムの処理[ItemWeapon.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _ITEMWEAPON_H_
#define _ITEMWEAPON_H_

//*****************************************************
// インクルード
//*****************************************************
#include "item.h"
#include "weapon.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CItemWeapon : public CItem
{
public:
	CItemWeapon(int nPriority = 3);	// コンストラクタ
	~CItemWeapon();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItemWeapon *Create(CWeapon::TYPE type);

private:
	void Load(void);
	void Interact(CObject* pObj);
	void ApplyEffect(CPlayer *pPlayer);

	CWeapon::TYPE m_type;
};

#endif

