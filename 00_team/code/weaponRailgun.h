//*****************************************************
//
// ���[���K���̏���[weaponRailgun.h]
// Author:���R����
//
//*****************************************************

#ifndef _RAILGUN_H_
#define _RAILGUN_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "weapon.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRailgun : public CWeapon
{
public:
	CRailgun(int nPriority = 3);	// �R���X�g���N�^
	~CRailgun();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Attack(void);
	void Draw(void);

private:
	void Shot(void);
};

#endif

