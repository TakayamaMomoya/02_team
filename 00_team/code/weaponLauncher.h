//*****************************************************
//
// �����`���[�̏���[weaponLauncher.h]
// Author:���R����
//
//*****************************************************

#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "weapon.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CLauncher : public CWeapon
{
public:
	CLauncher(int nPriority = 3);	// �R���X�g���N�^
	~CLauncher();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Attack(void);
	void Draw(void);

private:
};

#endif

