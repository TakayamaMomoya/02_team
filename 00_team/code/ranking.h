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

private:

	struct SInfoVisual
	{
		CObject2D* pRecordText;		// ���R�[�h�̃e�L�X�g
		CObject2D* pGenreText;		// ��ނ̃e�L�X�g
		CObject2D* pGenreIcon;		// ��ނ̃A�C�R�� 

		CObject2D* apFace[NUM_PLAYER];	// �e�v���C���[�̊�
		CNumber* apNumber[NUM_PLAYER];	// �e�v���C���[�̐��
	};

	SInfoVisual m_infoVisual;	// �����ڊ֘A�̏��
};

#endif