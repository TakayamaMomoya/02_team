//*****************************************************
//
// 武器アイテムの処理[ItemWeapon.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _ITEMWEAPON_H_
#define _ITEMWEAPON_H_

//*****************************************************
// インクルード
//*****************************************************
#include "gimmick.h"
#include "weapon.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CItemWeapon : public CGimmick
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
	struct SInfo
	{
		D3DXVECTOR3 posDest;	// 目標位置
		float fScaleDest;	// 目標スケール
		float fTimer;	// タイマー
	};

	void Load(void);
	void Interact(CObject* pObj);
	void ApplyEffect(CPlayer *pPlayer);
	void ManageScale(void);
	void ManageTransform(void);

	CWeapon::TYPE m_type;
	SInfo m_info;
};

#endif

