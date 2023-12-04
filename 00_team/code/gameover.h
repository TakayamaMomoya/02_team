//=========================================================
//
// �Q�[���I�[�o�[���� [gameover.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _GAMEOVER_H_     // ���̃}�N����`������ĂȂ�������
#define _GAMEOVER_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

//===============================================
// �C���N���[�h
//===============================================
#include "main.h"

//===============================================
// �Q�[���I�[�o�[�N���X
//===============================================
class CGameover
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CGameover();						// �f�t�H���g�R���X�g���N�^
	~CGameover();						// �f�X�g���N�^

	static CGameover* Create(int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(const D3DXVECTOR3 pos, const bool bMove);

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]
};

#endif