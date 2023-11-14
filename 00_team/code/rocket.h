//*****************************************************
//
// ���P�b�g�̏���[rocket.h]
// Author:���R����
//
//*****************************************************

#ifndef _ROCKET_H_
#define _ROCKET_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"
#include <stdio.h>

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRocket : public CObjectX
{
public:
	CRocket(int nPriority = 3);	// �R���X�g���N�^
	~CRocket();	// �f�X�g���N�^

	static CRocket *Create(void);
	static CRocket *GetInstance(void) { return m_pRocket; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Load(void);
	void ApplyInfo(FILE *pFile,char *pTemp);

	float m_fRadius;	// ����̔��a
	CCollisionSphere *m_pCollisionRocket;	// �S�[������
	static CRocket *m_pRocket;	// ���g�̃|�C���^
};

#endif

