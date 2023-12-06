//*****************************************************
//
// �D�_�G�̏���[enemyThief.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "enemyThief.h"
#include <stdio.h>
#include "playerManager.h"
#include "game.h"
#include "block.h"
#include "universal.h"
#include "rocket.h"
#include "motion.h"
#include "itemRepair.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyThief::CEnemyThief()
{
	m_bTakeRepair = false;
	m_state = STATE_NONE;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEnemyThief::~CEnemyThief()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CEnemyThief::Init(void)
{
	// �p���N���X�̏�����
	CEnemy::Init();

	// �������[�V�����ɐݒ�
	CMotion *pBody = GetBody();

	if (pBody != nullptr)
	{
		pBody->SetMotion(MOTION_WALK);
	}

	// �ǐՏ�Ԃɐݒ�
	m_state = STATE_CHASE;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEnemyThief::Uninit(void)
{
	// �p���N���X�̏I��
	CEnemy::Uninit();
}

//=====================================================
// ���S���̏���
//=====================================================
void CEnemyThief::Death(void)
{
	int nMotion = GetMotion();

	if (nMotion != MOTION_DEATH)
	{// ���S���[�V�����̐ݒ�
		SetMotion(MOTION_DEATH);

		if (m_bTakeRepair)
		{// �C���A�C�e���̃h���b�v
			CItemRepair *pRepair = CItemRepair::Create();

			if (pRepair != nullptr)
			{
				D3DXVECTOR3 pos = GetPosition();

				pRepair->SetPosition(pos);
			}
		}
	}

	CEnemy::Death();
}

//=====================================================
// �X�V����
//=====================================================
void CEnemyThief::Update(void)
{
	// �p���N���X�̍X�V
	CEnemy::Update();

	CBlock *pBlock = GetTouchBlock();

	if (pBlock != nullptr)
	{
		pBlock->Hit(5.0f);
	}

	CEnemy::STATE state = GetState();

	// �X�V�����̕���
	SwitchUpdate();
}

//=====================================================
// �X�V�����̕���
//=====================================================
void CEnemyThief::SwitchUpdate(void)
{
	switch (m_state)
	{
	case CEnemyThief::STATE_CHASE:	// ���P�b�g�̒ǐ�
		// ���P�b�g��ǂ�
		ChaseRocket();

		// ���P�b�g�Ƃ̓����蔻��
		CollisionRocket();

		break;
	case CEnemyThief::STATE_ESCAPE:	// �������
		// �����鏈��
		Escape();
		break;
	default:
		break;
	}
}

//=====================================================
// ���P�b�g��ǂ�����
//=====================================================
void CEnemyThief::ChaseRocket(void)
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

	// �ڕW�ʒu�̎擾
	D3DXVECTOR3 posTarget = { 0.0f,0.0f,0.0f };

	CRocket *pRocket = CRocket::GetInstance();

	if (pRocket != nullptr)
	{
		posTarget = pRocket->GetPosition();
	}

	// �ړ��ʂ̐ݒ�
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 vecDiff = posTarget - pos;
	D3DXVECTOR3 move = GetMove();

	D3DXVec3Normalize(&vecDiff, &vecDiff);

	float fSpeed = GetSpeed();

	vecDiff *= fSpeed;

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
// ���P�b�g�Ƃ̓����蔻��
//=====================================================
void CEnemyThief::CollisionRocket(void)
{
	CRocket *pRocket = CRocket::GetInstance();

	if (pRocket == nullptr)
	{
		return;
	}

	// �����������擾
	D3DXVECTOR3 posRocket = pRocket->GetPosition();
	D3DXVECTOR3 posOwn = GetPosition();
	D3DXVECTOR3 vecDiff = posOwn - posRocket;

	float fLegnthDiff = sqrtf(vecDiff.x * vecDiff.x + vecDiff.z * vecDiff.z);
	float fLegnth = pRocket->GetRadius();

	if (fLegnthDiff < fLegnth)
	{// �i�s�󋵂�߂��A������ԂɈڍs
		pRocket->AddProgress(-1);

		m_state = STATE_ESCAPE;

		m_bTakeRepair = true;

		// �J�����C�x���g�̐ݒ�
		CGame *pGame = CGame::GetInstance();

		if (pGame != nullptr)
		{
			D3DXVECTOR3 posV = posOwn;
			posV.x += 100.0f;
			posV.y += 100.0f;

			pGame->SetEventCamera(4.0f, posOwn, posV);
		}
	}
}

//=====================================================
// �����鏈��
//=====================================================
void CEnemyThief::Escape(void)
{
	// �Q�[����Ԃɂ���ē������Ȃ�
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

	for (int i = 0; i < NUM_PLAYER; i++)
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

	float fSpeed = GetSpeed();

	vecDiff *= fSpeed;

	move -= vecDiff;

	SetMove(move);

	// ������ڕW�����ɕ␳
	float fAngleDist = atan2f(vecDiff.x, vecDiff.z);
	D3DXVECTOR3 rot = GetRot();

	universal::FactingRot(&rot.y, fAngleDist, 0.1f);

	SetRot(rot);
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyThief::Draw(void)
{
	// �p���N���X�̕`��
	CEnemy::Draw();
}