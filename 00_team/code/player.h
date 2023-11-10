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
#include "weapon.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMotion;
class CCollisionSphere;

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
	void SetWeapon(CWeapon::TYPE type);
	void SetID(int nID) { m_info.nID = nID; }
	int GetID(void) { return m_info.nID; }
	void ReleaseWeapon(void) { m_info.pWeapon = nullptr; }
	void Hit(float fDamage);

private:
	enum STATE
	{
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_DAMAGE,	// �_���[�W���
		STATE_DEATH,	// ���S���
		STATE_MAX
	};
	struct SInfo
	{
		int nID;	// �ԍ�
		float fLife;	// �̗�
		float fTimerState;	// ��ԑJ�ڃJ�E���^
		STATE state;	// ���
		CCollisionSphere *pCollisionSphere;	// �����蔻��
		CWeapon *pWeapon;	// ����
	};

	void Input(void);
	void InputMove(void);
	void InputAttack(void);
	void Aim(void);
	void ManageState(void);
	void Debug(void);

	SInfo m_info;	// ���g�̏��
};

#endif