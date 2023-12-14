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
	
	// ���o�̎��
	enum DIRECTION_TYPE
	{
		DIRECTION_TYPE_MARCH = 0,	// �s�i
		DIRECTION_TYPE_RUN_AWAY,	// ������
		DIRECTION_TYPE_CHASE,		// �ǂ�������
		DIRECTION_TYPE_MAX
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

	void UpdateDirection(void);
	HRESULT SetDirection(DIRECTION_TYPE type);

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
		CObject3D* pWall;				// ��
		CMotion* apModelActor[ACTOR_TYPE_MAX];	// �v���C���[
	};

	SInfoVisualUi m_infoVisualUi;	// UI�̌����ڊ֘A�̏��
	SInfoVisualObj m_infoVisualObj;	// �I�u�W�F�N�g�̌����ڊ֘A�̏���
	DIRECTION_TYPE m_typeDirection;	// ���o�̎��
	int m_nDirectionCnt;			// ���o�J�E���g
};

#endif