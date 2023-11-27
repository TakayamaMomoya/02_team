//*****************************************************
//
// �^�C�g������[title.h]
// Author:���R����
//
//*****************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "scene.h"

#include "motion.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMenu;
class CObject2D;

//*****************************************************
// �萔��`
//*****************************************************
namespace ENEMY
{
	const int NUM_ENEMY = 8;	// �G�̍ő吔
}

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CTitle : public CScene
{
public:
	CTitle();	// �R���X�g���N�^
	~CTitle();	// �f�X�g���N�^

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	enum STATE
	{
		STATE_NONE = 0,	// �������ĂȂ����
		STATE_OUT,	// �t�F�[�h�A�E�g���
		START_MAX
	};

	void ManageStart(void);
	void UpdateFade(void);
	void UpdateCamera(void);
	void SetFadeIn(void);

	STATE m_state;	// ���

	CObject2D* m_pLogo;		// �^�C�g�����S�̃|�C���^
	CObject2D *m_pStart;	// �X�^�[�g�\���̃|�C���^

	CMotion* m_apModelPlayer[NUM_PLAYER];		// �v���C���[���f���̃|�C���^
	CMotion* m_apModelEnemy[ENEMY::NUM_ENEMY];	// �G�l�~�[���f���̃|�C���^

	int m_nFadeCnt;			// �t�F�[�h�܂ł̃J�E���g
	bool m_bIsAlphaChange;	// ���l�̕ω�
};

#endif