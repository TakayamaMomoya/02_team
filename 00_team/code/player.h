//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "character.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMotion;
class CCollisionSphere;
class CWeapon;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CCharacter
{
public:
	CPlayer(int nPriority = 4);	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	static CPlayer *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetWeapon(void);
	void SetID(int nID) { m_info.nID = nID; }

private:
	struct SInfo
	{
		int nID;	// �ԍ�
		CCollisionSphere *pCollisionSphere;	// �����蔻��
		CWeapon *pWeapon;	// ����
	};

	void Input(void);
	void InputMove(void);
	void InputAttack(void);
	void Aim(void);
	void Debug(void);

	SInfo m_info;	// ���g�̏��
};

#endif