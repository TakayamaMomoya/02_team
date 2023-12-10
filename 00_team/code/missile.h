//*****************************************************
//
// �~�T�C������[missile.h]
// Author:���R����
//
//*****************************************************

#ifndef _MISSILE_H_
#define _MISSILE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "collision.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_HIT	(54)	// �ő�Ŋo�����閽�������I�u�W�F�N�g

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class COrbit;
class CCollisionSphere;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CMissile : public CObject
{
public:
	CMissile(int nPriority = 6);	// �R���X�g���N�^
	~CMissile();	// �f�X�g���N�^

	static CMissile *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetNumAll(void) { return m_nNumAll; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }

private:
	void Death(void);

	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
	float m_fLife;	// ����
	static int m_nNumAll;	// ����
	CCollisionSphere *m_pCollisionSphere;	// ���̓����蔻��
	float m_fDamage;	// �^�_���[�W
};

#endif