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
#include "manager.h"
#include "collision.h"
#include "debugproc.h"
#include "particle.h"
#include <stdio.h>
#include "player.h"
#include "game.h"
#include "enemyManager.h"
#include "debrisSpawner.h"
#include "block.h"
#include "universal.h"
#include "rocket.h"
#include "motion.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyThief::CEnemyThief()
{
	m_bTakeRepair = false;
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

	if (state == CEnemy::STATE::STATE_DEATH)
	{// ���S���[�V����
		int nMotion = GetMotion();

		if (nMotion != MOTION_DEATH)
		{
			SetMotion(MOTION_DEATH);
		}
	}

	// ���P�b�g��ǂ�����
	ChaseRocket();
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
// �`�揈��
//=====================================================
void CEnemyThief::Draw(void)
{
	// �p���N���X�̕`��
	CEnemy::Draw();
}