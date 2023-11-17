//*****************************************************
//
// 武器マネージャー[weaponManager.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _WEAPONMANAGER_H_
#define _WEAPONMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"
#include "weapon.h"
#include <stdio.h>

//*****************************************************
// クラスの定義
//*****************************************************
class CWeaponManager : public CObject
{
public:
	CWeaponManager();	// コンストラクタ
	~CWeaponManager();	// デストラクタ

	static CWeaponManager*Create(void);
	HRESULT Init(void);
	void LoadParam(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CWeapon::SInfo GetBaseInfo(int nCnt) { return m_aInfo[nCnt]; }
	int GetProb(int nIdx) { return m_anProb[nIdx]; }
	static CWeaponManager*GetInstance(void) { return m_pWeaponManager; }

private:
	void LoadBaseInfo(FILE *pFile, char* pTemp, int nCntParam);

	CWeapon::SInfo m_aInfo[CWeapon::TYPE_MAX];	// 基底のパラメーター
	int m_anProb[CWeapon::TYPE_MAX];	// 確率の配列

	static CWeaponManager *m_pWeaponManager;	// 自身のポインタ
};

#endif
