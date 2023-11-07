//*****************************************************
//
// �S�[���̏���[goal.h]
// Author:���R����
//
//*****************************************************

#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"
#include <stdio.h>

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGoal : public CObjectX
{
public:
	CGoal(int nPriority = 3);	// �R���X�g���N�^
	~CGoal();	// �f�X�g���N�^

	static CGoal* Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Load(void);
	void ApplyInfo(FILE *pFile,char *pTemp);
};

#endif

