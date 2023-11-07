//*****************************************************
//
// ����}�l�[�W���[[weaponManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _WEAPONMANAGER_H_
#define _WEAPONMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include "weapon.h"
#include <stdio.h>

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CWeaponManager : public CObject
{
public:
	CWeaponManager();	// �R���X�g���N�^
	~CWeaponManager();	// �f�X�g���N�^

	static CWeaponManager*Create(void);
	HRESULT Init(void);
	void LoadParam(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CWeapon::SInfo GetBaseInfo(int nCnt) { return m_aInfo[nCnt]; }
	static CWeaponManager*GetInstance(void) { return m_pWeaponManager; }

private:
	void LoadBaseInfo(FILE *pFile, char* pTemp, int nCntParam);

	CWeapon::SInfo m_aInfo[CWeapon::TYPE_MAX];	// ���̃p�����[�^�[

	static CWeaponManager *m_pWeaponManager;	// ���g�̃|�C���^
};

#endif
