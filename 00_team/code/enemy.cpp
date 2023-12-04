//*****************************************************
//
// �G�̏���[enemy.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemy.h"
#include "manager.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include <stdio.h>
#include "player.h"
#include "playerManager.h"
#include "game.h"
#include "enemyManager.h"
#include "enemyNormal.h"
#include "motion.h"
#include "universal.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define INITIAL_LIFE	(10.0f)	// �����̗�
#define INITIAL_SPEED	(1.0f)	// �����ړ����x
#define DAMAGE_FRAME	(10)	// �_���[�W��Ԃ̌p���t���[����
#define INITIAL_SCORE	(1000)	// �����X�R�A
#define TIME_DEATH	(30)	// ���S�܂ł̃^�C��

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CEnemy::m_nNumAll = 0;	// ����

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemy::CEnemy()
{
	// �����J�E���g�A�b�v
	m_nNumAll++;

	// �擪�A�Ō���A�h���X�擾
	CEnemyManager *pManager = CEnemyManager::GetInstance();
	CEnemy *pHead = nullptr;
	CEnemy *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	m_fLife = 0;
	m_nScore = 0;
	m_fMoveSpeed = 0.0f;
	m_nTimerState = 0;
	m_pCollisionSphere = nullptr;
	m_pCollisionCube = nullptr;
	m_pShadow = nullptr;
	m_state = STATE_NORMAL;

	// �l�̃N���A
	m_pPrev = nullptr;
	m_pNext = nullptr;
	m_pBlock = nullptr;

	if (pHead == nullptr)
	{// �擪�ƍŌ���A�h���X�̑��
		pManager->SetHead(this);
		pManager->SetTail(this);

		return;
	}

	// �O�̃A�h���X�ɍŌ���̃A�h���X��������
	m_pPrev = pTail;

	// �Ō���̃A�h���X�������ɂ���
	pManager->SetTail(this);

	if (m_pPrev != nullptr)
	{
		// �O�̃I�u�W�F�N�g�̎��̃A�h���X�������ɂ���
		m_pPrev->m_pNext = this;
	}
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemy::~CEnemy()
{
	// �擪�A�Ō���A�h���X�擾
	CEnemyManager *pManager = CEnemyManager::GetInstance();
	CEnemy *pHead = nullptr;
	CEnemy *pTail = nullptr;

	if (pManager != nullptr)
	{
		pHead = pManager->GetHead();
		pTail = pManager->GetTail();
	}

	m_nNumAll--;

	if (pTail != this && pHead != this)
	{// �^�񒆂̃A�h���X�̔j��
		if (m_pPrev != nullptr)
		{
			// �O�̃A�h���X���玟�̃A�h���X���Ȃ�
			m_pPrev->m_pNext = m_pNext;
		}

		if (m_pNext != nullptr)
		{
			// ���̃A�h���X����O�̃A�h���X���Ȃ�
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	if (pHead == this)
	{// �擪�A�h���X�̔j��
		//if (m_pNext != nullptr)
		{// �擪�A�h���X�����̃A�h���X�Ɉ����p��
			pManager->SetHead(m_pNext);

			if (m_pNext != nullptr)
			{
				m_pNext->m_pPrev = nullptr;
			}
		}
	}
	
	if (pTail == this)
	{// �Ō���A�h���X�̔j��
		if (m_pPrev != nullptr)
		{// �Ō���A�h���X��O�̃A�h���X�Ɉ����p��
			pManager->SetTail(m_pPrev);

			m_pPrev->m_pNext = nullptr;
		}
	}
}

//=====================================================
// ��������
//=====================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{// �C���X�^���X����
		switch (type)
		{
		case TYPE_NORMAL:

			pEnemy = new CEnemyNormal;

			pEnemy->Load("data\\Character\\robot00.txt");

			break;
		default:
			break;
		}

		// �ʒu�ݒ�
		pEnemy->SetPosition(pos);

		// ����������
		pEnemy->Init();
	}

	return pEnemy;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemy::Init(void)
{
	// �p���N���X�̏�����
	CCharacter::Init();

	// �^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	if (m_pCollisionSphere == nullptr)
	{// ���̓����蔻�萶��
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ENEMY, CCollision::TYPE_SPHERE,this);

		if (m_pCollisionSphere != nullptr)
		{// ���̐ݒ�
			m_pCollisionSphere->SetPosition(GetPosition());
			m_pCollisionSphere->SetRadius(50.0f);
		}
	}

	if (m_pCollisionCube == nullptr)
	{// �����̂̓����蔻��
		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_ENEMY, this);

		D3DXVECTOR3 vtxMax = { 20,20,20 };
		D3DXVECTOR3 vtxMin = { -20,0.0f,-20 };

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	// �p�����[�^�[�����ݒ�
	m_fLife = INITIAL_LIFE;
	SetMoveSpeed(INITIAL_SPEED);

	// �ʏ��Ԃɂ���
	m_state = STATE_NORMAL;

	m_nScore = INITIAL_SCORE;

	SetPositionOld(GetPosition());

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemy::Uninit(void)
{
	// �����蔻��폜
	DeleteCollision();

	// �p���N���X�̏I��
	CCharacter::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemy::Update(void)
{
	// �p���N���X�̍X�V
	CCharacter::Update();

	// ��ԊǗ�
	ManageState();

	// �����蔻��̊Ǘ�
	ManageCollision();

	// �ڕW�ǐ�
	ChaseTarget();

	// �ړ��ʂ𔽉f
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	SetPositionOld(pos);

	pos += move;
	SetPosition(pos);

	// �ړ��ʂ̌���
	move *= 0.1f;
	SetMove(move);
}

//=====================================================
// �����蔻��̊Ǘ�
//=====================================================
void CEnemy::ManageCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// ���̓����蔻��̊Ǘ�
		CMotion* pBody = GetBody();

		if (pBody != nullptr)
		{
			D3DXVECTOR3 posWaist = pBody->GetMtxPos(0);

			D3DXVECTOR3 pos = GetPosition();

			m_pCollisionSphere->SetPosition(pos);

			m_pCollisionSphere->PushCollision(&pos, CCollision::TAG_PLAYER);
			m_pCollisionSphere->PushCollision(&pos, CCollision::TAG_ENEMY);

			SetPosition(pos);

			m_pCollisionSphere->SetPositionOld(m_pCollisionSphere->GetPosition());

			m_pCollisionSphere->SetPosition(posWaist);
		}
	}

	if (m_pCollisionCube != nullptr)
	{// �����̂̓����蔻��̊Ǘ�
		// �����蔻��̈ʒu�ݒ�
		m_pCollisionCube->SetPositionOld(m_pCollisionCube->GetPosition());
		m_pCollisionCube->SetPosition(GetPosition());

		D3DXVECTOR3 move = GetMove();

		// �����o���̓����蔻��
		m_pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move, (CObject**)&m_pBlock);
		SetMove(move);
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CEnemy::ManageState(void)
{
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_DAMAGE:
		if (m_nTimerState > DAMAGE_FRAME)
		{// �ʏ��Ԃɖ߂�
			m_nTimerState = 0;
			m_state = STATE_NORMAL;

			GetBody()->ResetAllCol();
		}
		else
		{// �J�E���g�A�b�v
			m_nTimerState++;
		}

		break;
	case STATE_DEATH:

		m_nTimerState++;

		// �����ɂȂ�Ȃ��������
		col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);

		col.a = 1.0f - (float)((float)(m_nTimerState) / (TIME_DEATH));

		GetBody()->SetAllCol(col);

		if (m_nTimerState >= TIME_DEATH)
		{// ���S
			Death();
		}

		break;
	default:
		break;
	}
}

//=====================================================
// �ڕW�̒ǐ�
//=====================================================
void CEnemy::ChaseTarget(void)
{
	// �Q�[����Ԃɂ���ĒǐՂ����Ȃ�
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		CGame::STATE state = pGame->GetState();

		if (state != CGame::STATE::STATE_NORMAL)
		{
			return;
		}
	}

	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pPlayerManager == nullptr)
	{
		return;
	}

	D3DXVECTOR3 posTarget = { 0.0f,0.0f,0.0f };

	// �ŉ������̐錾
	float fLengthMax = FLT_MAX;

	for (int i = 0;i < NUM_PLAYER;i++)
	{// �ł��߂��v���C���[���Q��
		CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

		if (pPlayer != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 posPlayer = pPlayer->GetPosition();

			// �����̔�r
			bool bNear = universal::DistCmp(pos, posPlayer, fLengthMax, &fLengthMax);

			if (bNear)
			{
				posTarget = posPlayer;
			}
		}
	}

	// �ړ��ʂ̐ݒ�
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 vecDiff = posTarget - pos;
	D3DXVECTOR3 move = GetMove();

	D3DXVec3Normalize(&vecDiff, &vecDiff);

	vecDiff *= m_fMoveSpeed;

	move += vecDiff;

	SetMove(move);

	// ������ڕW�����ɕ␳
	float fAngleDist = atan2f(vecDiff.x, vecDiff.z);
	D3DXVECTOR3 rot = GetRot();

	fAngleDist += D3DX_PI;

	universal::FactingRot(&rot.y, fAngleDist, 0.1f);

	SetRot(rot);
}

//=====================================================
// �̗͐ݒ�
//=====================================================
void CEnemy::SetLife(float fLife)
{
	m_fLife = fLife;

	if (m_fLife < 0)
	{
		m_fLife = 0;
	}
}

//=====================================================
// �q�b�g����
//=====================================================
void CEnemy::Hit(float fDamage)
{
	if (m_state != STATE_DEATH)
	{
		m_fLife -= fDamage;

		if (m_fLife <= 0.0f)
		{// ���S���
			m_fLife = 0.0f;

			m_state = STATE_DEATH;

			// �X�R�A�Ǘ�
			ManageScore();

			// �����蔻��폜
			DeleteCollision();
		}
		else
		{
			m_state = STATE_DAMAGE;

			// �q�b�g�F
			D3DXCOLOR col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			GetBody()->SetAllCol(col);
		}
	}
}

//=====================================================
// ���S����
//=====================================================
void CEnemy::Death(void)
{
	// ���g�̏I��
	Uninit();
}

//=====================================================
// �����蔻��폜
//=====================================================
void CEnemy::DeleteCollision(void)
{
	if (m_pCollisionSphere != nullptr)
	{// �����蔻��̏���
		m_pCollisionSphere->Uninit();

		m_pCollisionSphere = nullptr;
	}

	if (m_pCollisionCube != nullptr)
	{// �����蔻��̏���
		m_pCollisionCube->Uninit();

		m_pCollisionCube = nullptr;
	}
}

//=====================================================
// �X�R�A�Ǘ�
//=====================================================
void CEnemy::ManageScore(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CEnemy::Draw(void)
{
	// �p���N���X�̕`��
	CCharacter::Draw();

#ifdef _DEBUG
	//CDebugProc::GetInstance()->Print("\n�G�̈ʒu�F[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	//CDebugProc::GetInstance()->Print("\n�G�̈ړ��ʁF[%f,%f,%f]", GetMove().x, GetMove().y, GetMove().z);
#endif
}

//=====================================================
// ���̓����蔻��̈ʒu�ݒ�
//=====================================================
void CEnemy::SetSpherePosition(D3DXVECTOR3 pos)
{
	if (m_pCollisionSphere != nullptr)
	{// �ʒu�ݒ�
		m_pCollisionSphere->SetPosition(pos);
	}
}