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

//=====================================================
// �R���X�g���N�^
//=====================================================
CEnemyThief::CEnemyThief()
{

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
}

//=====================================================
// �`�揈��
//=====================================================
void CEnemyThief::Draw(void)
{
	// �p���N���X�̕`��
	CEnemy::Draw();
}