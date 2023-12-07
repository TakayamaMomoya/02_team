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
		TYPE_SHOTGUN,	// �V���b�g�K��
		TYPE_RAILGUN,	// ���[���K��
		TYPE_MAX
	};
	struct SInfo
	{// ���g�̏��
		int nNumBullet;	// �e��
		int nMaxBullet;	// �ő�e��
		int nRapid;	// �A��
		float fDamage;	// �З�
		float fLifeBullet;	// �e�̎���
		int nCntShot;	// �A�˃J�E���^
		int nIdxHand;	// ��̔ԍ�
		int nIdxJoypad;	// �R���g���[���[�ԍ�
		bool bEnable;	// �g�p�ł��邩�ǂ���
		CPlayer *pPlayer;	// �������Ă�v���C���[
		TYPE type;	// ���
	};

	CWeapon(int nPriority = 3);	// �R���X�g���N�^
	~CWeapon();	// �f�X�g���N�^

	static CWeapon *Create(CWeapon::TYPE type,int nIdxhand);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	virtual void Attack(void) {};
	CPlayer *GetPlayer(void) { return m_info.pPlayer; }
	void SetPlayer(CPlayer *pPlayer);
	int GetID(void) { return m_info.nIdxJoypad; }
	void SetBullet(int nBullet);
	int GetBullet(void) { return m_info.nNumBullet; }
	void SetMaxBullet(int nBullet);
	void SetRapid(int nRapid) { m_info.nRapid = nRapid; }
	int GetRapid(void) { return m_info.nRapid; }
	void SetCntShot(int nCntShot) { m_info.nCntShot = nCntShot; }
	int GetCntShot(void) { return m_info.nCntShot; }
	void FollowPlayerHand(void);
	void SetEnable(bool bEnable);
	bool IsEnable(void) { return m_info.bEnable; }
	void SetDamage(float fDamage) { m_info.fDamage = fDamage; }
	float GetDamage(void) { return m_info.fDamage; }
	void SetBulletLife(float fBulletLife) { m_info.fLifeBullet = fBulletLife; }
	TYPE GetType(void) { return m_info.type; }
	SInfo GetInfo(void) { return m_info; }
	void SetInfo(SInfo info) { m_info = info; }

protected:
	virtual void ToggleEnable(bool bEnable) {};

private:
	SInfo m_info;
};

#endif

