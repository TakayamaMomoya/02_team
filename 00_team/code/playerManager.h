//*****************************************************
//
// �v���C���[�}�l�[�W���[[PlayerManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _PLAYERMANAGER_H_
#define _PLAYERMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayerManager : public CObject
{
public:
	CPlayerManager();	// �R���X�g���N�^
	~CPlayerManager();	// �f�X�g���N�^

	static CPlayerManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayerManager *GetInstance(void) { return m_pPlayerManager; }

private:
	static CPlayerManager *m_pPlayerManager;	// ���g�̃|�C���^
};

#endif
