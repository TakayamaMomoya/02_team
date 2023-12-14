//*****************************************************
//
// �����L���O�̏���[Ranking.h]
// Author:���R����
//
//*****************************************************

#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************
// �C���N���[�h
//*****************************************************

#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************

class CObject2D;
class CNumber;

class CObject3D;
class CMotion;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRanking : public CScene
{
public:

	CRanking();	// �R���X�g���N�^
	~CRanking();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	HRESULT InitUi(void);
	HRESULT InitObj(void);

private:

	struct SInfoVisualUi
	{
		CObject2D* pRecordText;		// ���R�[�h�̃e�L�X�g
		CObject2D* pGenreText;		// ��ނ̃e�L�X�g
		CObject2D* pGenreIcon;		// ��ނ̃A�C�R�� 

		CObject2D* apFace[NUM_PLAYER];	// �e�v���C���[�̊�
		CNumber* apNumber[NUM_PLAYER];	// �e�v���C���[�̐��
	};

	struct SInfoVisualObj
	{
		CObject3D* pField;				// �n��
		CMotion* apModelPlayer[NUM_PLAYER];	// �v���C���[
	};

	SInfoVisualUi m_infoVisualUi;	// UI�̌����ڊ֘A�̏��
	SInfoVisualObj m_infoVisualObj;	// �I�u�W�F�N�g�̌����ڊ֘A�̏���
};

#endif