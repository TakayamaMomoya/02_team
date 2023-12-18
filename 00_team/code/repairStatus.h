//=========================================================
//
// �C���󋵕\������ [repairStatus.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _REPAIRSTATUS_H_     // ���̃}�N����`������ĂȂ�������
#define _REPAIRSTATUS_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

//===============================================
// �C���N���[�h
//===============================================
#include "main.h"
#include "object3D.h"

//===============================================
// �O���錾
//===============================================
class CUI;

//===============================================
// �C���󋵃N���X
//===============================================
class CRepairStatus : public CObject3D
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CRepairStatus(int nPriority = 3);						// �f�t�H���g�R���X�g���N�^
	~CRepairStatus();						// �f�X�g���N�^

	static CRepairStatus* Create(int nPriority = 3);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//static CRepairStatus* GetInstance(void) { return m_pRepairStatus; }

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]
	static CRepairStatus* m_pRepairStatus;	// ���g�̃|�C���^
	CObject3D* m_pFrame;					// �g�̃|�C���^
};

#endif