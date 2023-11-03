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
// �O���錾
//*****************************************************
class CPlayer;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayerManager : public CObject
{
public:
	CPlayerManager();	// �R���X�g���N�^
	~CPlayerManager();	// �f�X�g���N�^

	static CPlayerManager *Create(void);
	void CreatePlayer(int nNumPlayer);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayerManager *GetInstance(void) { return m_pPlayerManager; }

private:
	CPlayer *m_apPlayer[NUM_PLAYER];	// �v���C���[�̔z��

	static CPlayerManager *m_pPlayerManager;	// ���g�̃|�C���^
};

#endif
