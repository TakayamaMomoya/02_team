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
class CPlayerManager
{
public:
	CPlayerManager();	// �R���X�g���N�^
	~CPlayerManager();	// �f�X�g���N�^

	static CPlayerManager *Create(void);
	void CreatePlayer(void);
	CPlayer *BindPlayer(int nIdxJoypad);
	HRESULT Init(void);
	void Uninit(void);
	void ReleasePlayer(int nIdx);
	CPlayer *GetPlayer(int nIdx) { return m_apPlayer[nIdx]; }
	static CPlayerManager *GetInstance(void) { return m_pPlayerManager; }
	int GetNumPlayer(void) { return m_nNumPlayer; }

private:
	int m_nNumPlayer;	// �v���C���[�̐�
	int m_anIDJoypad[NUM_PLAYER];	// �v���C���[�̃R���g���[���[�ԍ�
	CPlayer *m_apPlayer[NUM_PLAYER];	// �v���C���[�̔z��
	static CPlayerManager *m_pPlayerManager;	// ���g�̃|�C���^
};

#endif
