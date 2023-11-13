//*****************************************************
//
// ���U���g�̏���[result.h]
// Author:���R����
//
//*****************************************************

#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObject2D;
class CPlayer;

//*****************************************************
// �N���X��`
//*****************************************************
class CResult : CObject
{
public:
	CResult();	// �R���X�g���N�^
	~CResult();	// �f�X�g���N�^

	static CResult *Create(bool bWin = false);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSurvived(CPlayer *pPlayer);

private:
	enum STATE
	{// ���
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_WAIT,	// ���͑ҋ@���
		STATE_CURRENT,	// ���͂��Ă�����
		STATE_MAX
	};

	void Input(void);
	void Create2D(bool bWin);

	CObject2D *m_pBg;	// �w�i�̃|�C���^
	CObject2D *m_pCaption;	// ���o���̃|�C���^
	STATE m_state;	// ���
	CPlayer *m_apSuvived[NUM_PLAYER];	// �����҂̔z��
	int m_nNumSuvived;	// �����Ґ�
};

#endif