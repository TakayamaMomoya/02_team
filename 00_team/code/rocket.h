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
	enum STATE
	{
		STATE_NONE = 0,	// �������Ă��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_ESCAPE,	// �E�o���
		STATE_MAX
	};

	CRocket(int nPriority = 3);	// �R���X�g���N�^
	~CRocket();	// �f�X�g���N�^

	static CRocket *Create(void);
	static CRocket *GetInstance(void) { return m_pRocket; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetProgress(void) { return m_nProgress; }
	void AddProgress(int nProgress);
	void SetState(STATE state) { m_state = state; }

private:
	void Load(void);
	void ApplyInfo(FILE *pFile,char *pTemp);
	void UpdateEscape(void);

	float m_fRadius;	// ����̔��a
	float m_fSpeed;	// �㏸���x
	int m_nProgress;	// �i�s��
	STATE m_state;	// ���
	CCollisionSphere *m_pCollisionRocket;	// �S�[������
	static CRocket *m_pRocket;	// ���g�̃|�C���^
};

#endif

