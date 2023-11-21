//*****************************************************
//
// �M�~�b�N�}�l�[�W���[[gimmickManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _GIMMICKMANAGER_H_
#define _GIMMICKMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include <stdio.h>

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGimmickManager : public CObject
{
public:
	CGimmickManager();	// �R���X�g���N�^
	~CGimmickManager();	// �f�X�g���N�^

	static CGimmickManager*Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGimmickManager*GetInstance(void) { return m_pGimmickManager; }

private:
	void Load(void);
	void CreateGimmick(FILE *pFile, char *pTemp);
	void LoadDoor(FILE *pFile, char *pTemp);
	void LoadContainer(FILE *pFile, char *pTemp);
	void LoadRepair(FILE *pFile, char *pTemp);

	static CGimmickManager *m_pGimmickManager;	// ���g�̃|�C���^
};

#endif