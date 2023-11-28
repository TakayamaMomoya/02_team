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
#include "characterDiv.h"
#include "weapon.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMotion;
class CCollisionSphere;
class CCollisionCube;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CCharacterDiv
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
	void SetID(int nID);
	void SetIDJoypad(int nID) { m_info.nIDJoypad = nID; }
	int GetIDJoypad(void) { return m_info.nIDJoypad; }
	int GetID(void) { return m_info.nID; }
	void ReleaseWeapon(void) { m_info.pWeapon = nullptr; }
	void Hit(float fDamage);
	bool InputInteract(void);
	bool InputInteractPress(void);
	void EnableWeapon(bool bEnable);

private:
	enum STATE
	{
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_DAMAGE,	// �_���[�W���
		STATE_DEATH,	// ���S���
		STATE_MAX
	};
	enum MOTION
	{
		MOTION_NEUTRAL = 0,	// �ҋ@���
		MOTION_WALK,		// �������[�V����
		MOTION_MAX
	};
	struct SInfo
	{
		int nID;	// �ԍ�
		int nIDJoypad;	// �R���g���[���[�̔ԍ�
		float fLife;	// �̗�
		float fTimerState;	// ��ԑJ�ڃJ�E���^
		STATE state;	// ���
		CCollisionSphere *pCollisionSphere;	// ���̓����蔻��
		CCollisionCube *pCollisionCube;	// �����̂̓����蔻��
		CWeapon *pWeapon;	// ����
	};

	void Input(void);
	void InputMove(void);
	void InputAttack(void);
	void Aim(void);
	void ManageState(void);
	void ManageMotion(void);
	void Debug(void);

	SInfo m_info;	// ���g�̏��
};

#endif