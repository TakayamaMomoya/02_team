//*****************************************************
//
// �����L���O�̏���[Ranking.h]
// Author:����쏟
//
//*****************************************************

#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************
// �C���N���[�h
//*****************************************************

#include "scene.h"

#include "record.h"

//*****************************************************
// �O���錾
//*****************************************************

class CObject2D;
class CNumber;

class CObject3D;
class CMotion;

//*****************************************************
// �萔��`
//*****************************************************
namespace RANK
{
	const int NUM_MAX = 3;	// �ő吔
}

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRanking : public CScene
{
public:
	
	// ���o�̎��
	enum ACTING_TYPE
	{
		ACTING_TYPE_MARCH = 0,	// �s�i
		ACTING_TYPE_RUN_AWAY,	// ������
		ACTING_TYPE_CHASE,		// �ǂ�������
		ACTING_TYPE_MAX
	};

	// ���҂̎��
	enum ACTOR_TYPE
	{
		ACTOR_TYPE_PLAYER_ONE = 0,	// �v���C���[01
		ACTOR_TYPE_PLAYER_TWO,		// �v���C���[02
		ACTOR_TYPE_PLAYER_THREE,	// �v���C���[03
		ACTOR_TYPE_PLAYER_FOUR,		// �v���C���[04
		ACTOR_TYPE_ENEMY_ONE,		// �G01
		ACTOR_TYPE_ENEMY_TWO,		// �G02
		ACTOR_TYPE_ENEMY_THREE,		// �G03
		ACTOR_TYPE_MAX
	};

	CRanking();	// �R���X�g���N�^
	~CRanking();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	HRESULT InitUi(void);
	HRESULT InitObj(void);

	void SetUiRecord(void);
	void SetObjActing(void);

	void UpdateUiRecord(void);
	void UpdateActing(void);
	void UpdateNum(void);

	void SetRank(void);
	void ResetRank(void);
	void SetRankNum(void);
	void SortRank(void);
	void SaveRank(void);
	void LoadRank(void);

private:

	struct SInfoVisualUi
	{
		CObject2D* pRecordText;		// ���R�[�h�̃e�L�X�g
		CObject2D* pGenreText;		// ��ނ̃e�L�X�g
		CObject2D* pGenreIcon;		// ��ނ̃A�C�R�� 

		CObject2D* apFace[NUM_PLAYER];	// �e�v���C���[�̊�
		CNumber* apNumber[NUM_PLAYER];	// �e�v���C���[�̐��

		CObject2D* apFaceRank[RANK::NUM_MAX];	// �����L���O�̊�
		CNumber* apNumRank[RANK::NUM_MAX];		// �����L���O�̐���
	};

	struct SInfoVisualObj
	{
		CObject3D* pField;				// �n��
		CObject3D* pWall;				// ��
		CMotion* apModelActor[ACTOR_TYPE_MAX];	// �v���C���[
	};

	SInfoVisualUi m_infoVisualUi;		// UI�̌����ڊ֘A�̏��
	SInfoVisualObj m_infoVisualObj;		// �I�u�W�F�N�g�̌����ڊ֘A�̏���

	CRecord::GENRE_TYPE m_typeGenre;	// ��т̎��
	ACTING_TYPE m_typeActing;			// ���Z�̎��

	int m_nActingCnt;					// ���Z�J�E���g
	int m_nGenreCnt;					// ��ރJ�E���g

	int m_aRankScore[CRecord::GENRE_TYPE_MAX][RANK::NUM_MAX];	// �����L���O�̒l
	int m_aRankFace[CRecord::GENRE_TYPE_MAX][RANK::NUM_MAX];	// ��̔ԍ�
	int m_aUpdateIdx[CRecord::GENRE_TYPE_MAX][NUM_PLAYER];		// �X�V���������L���O�̔ԍ�
	int m_aUpdateRank[CRecord::GENRE_TYPE_MAX][NUM_PLAYER];		// �����L���O�̍X�V�̗L��
	bool m_aIsAlphaChange[CRecord::GENRE_TYPE_MAX][NUM_PLAYER];	// ���l�̕ω�
};

#endif