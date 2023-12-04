//*****************************************************
//
// �ؔ��̏���[box.h]
// Author:���R����
//
//*****************************************************

#ifndef _BOX_H_
#define _BOX_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;
class CCollisionCube;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBox : public CObjectX
{
public:
	CBox(int nPriority = 3);	// �R���X�g���N�^
	~CBox();	// �f�X�g���N�^

	static CBox *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CCollisionSphere *GetCollisionSphere(void) { return m_pCollisionSphere; }
	CCollisionCube *GetCollisionCube(void) { return m_pCollisionCube; }

private:
	CCollisionSphere *m_pCollisionSphere;	// �����蔻��
	CCollisionCube *m_pCollisionCube;	// ��`�̓����蔻��
};

#endif

