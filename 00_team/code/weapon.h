//*****************************************************
//
// ����̏���[weapon.h]
// Author:���R����
//
//*****************************************************

#ifndef _WEAPON_H_
#define _WEAPON_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �O���錾
//*****************************************************
class CPlayer;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CWeapon : public CObjectX
{
public:
	enum TYPE
	{
		TYPE_MAGNUM = 0,	// �}�O�i��
		TYPE_MACHINEGUN,	// �}�V���K��
		TYPE_MAX
	};

	CWeapon(int nPriority = 3);	// �R���X�g���N�^
	~CWeapon();	// �f�X�g���N�^

	static CWeapon *Create(CWeapon::TYPE type,int nIdxhand);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	virtual void Attack(void) {};
	CPlayer *GetPlayer(void) { return m_pPlayer; }
	void SetPlayer(CPlayer *pPlayer);

private:
	void FollowPlayerHand(void);

	int m_nIdxHand;
	int m_nIdxPlayer;
	CPlayer *m_pPlayer;
};

#endif

