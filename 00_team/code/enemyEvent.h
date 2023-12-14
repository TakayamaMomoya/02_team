//*****************************************************
//
// �G�C�x���g�̏���[enemyEvent.h]
// Author:���R����
//
//*****************************************************

#ifndef _ENEMYEVENT_H_
#define _ENEMYEVENT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CEnemyEvent : public CObject
{
public:
	CEnemyEvent(int nPriority = 6);	// �R���X�g���N�^
	~CEnemyEvent();	// �f�X�g���N�^

	static CEnemyEvent *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	float m_fLife;	// ����
};

#endif
