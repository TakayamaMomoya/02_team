//*****************************************************
//
// �S�[���^�C�}�[�̏���[goalGoalTimer.h]
// Author:���R����
//
//*****************************************************

#ifndef _GOALGoalTimer_H_
#define _GOALGoalTimer_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CNumber;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGoalTimer : public CObject
{
public:
	CGoalTimer();	// �R���X�g���N�^
	~CGoalTimer();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGoalTimer *Create(void);
	void AddGoalTimer(int nValue);
	float GetWidth(void) { return 0.0f; }	// �T�C�Y�擾
	float GetHeight(void) { return 0.0f; }	// �T�C�Y�擾
	float GetSecond(void) { return m_fSecond; }	// ���Ԏ擾
	void EnableStop(bool bStop) { m_bStop = bStop; }
	static CGoalTimer *GetInstance(void) { return m_pGoalTimer; }

private:
	CNumber *m_pObjSecond;	// �b�\���̃|�C���^
	CNumber *m_pObjDecimal;	// �����_�ȉ��\���̃|�C���^
	float m_fSecond;	// ���݂̎���(�b)
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	static CGoalTimer *m_pGoalTimer;	// ���g�̃|�C���^
	bool m_bStop;	// �~�߂邩�ǂ���
};

#endif