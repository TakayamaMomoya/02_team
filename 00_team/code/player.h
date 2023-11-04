//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "character.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMotion;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CPlayer : public CCharacter
{
public:
	CPlayer(int nPriority = 4);	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	static CPlayer *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetID(int nID) { m_info.nID = nID; }

private:
	struct SInfo
	{
		int nID;	// �ԍ�
	};

	void Debug(void);

	SInfo m_info;	// ���g�̏��
};

#endif