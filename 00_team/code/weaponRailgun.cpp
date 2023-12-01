//*****************************************************
//
// ���[���K���̏���[weaponRailgun.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "weaponRailgun.h"
#include "inputjoypad.h"
#include "bullet.h"
#include "player.h"
#include "sound.h"
#include "animEffect3D.h"
#include "universal.h"
#include "debugproc.h"
#include "playerManager.h"
#include "effect3D.h"
#include "enemyManager.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const int NUM_VTX = 4;	// �����蔻��̒��_��
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CRailgun::CRailgun(int nPriority) : CWeapon(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CRailgun::~CRailgun()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CRailgun::Init(void)
{
	// �p���N���X�̏�����
	CWeapon::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CRailgun::Uninit(void)
{
	// �p���N���X�̏I��
	CWeapon::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CRailgun::Update(void)
{
	// �p���N���X�̍X�V
	CWeapon::Update();
}

//=====================================================
// �U������
//=====================================================
void CRailgun::Attack(void)
{
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	if (pJoypad == nullptr)
	{
		return;
	}

	int nBullet = GetBullet();
	int nID = GetID();

	if (pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_RB,nID))
	{// �ˌ�
		int nCntShot = GetCntShot();

		if (nBullet > 0 && nCntShot == 0)
		{// �e�̔���
			

			// �����蔻��̔���

			// �e�����炷
			nBullet--;
			SetBullet(nBullet);

			// �A�˃J�E���^�[�̃��Z�b�g
			nCntShot = GetRapid();

			SetCntShot(nCntShot);
		}
		else
		{// �e�؂�̏ꍇ

		}
	}
}

//=====================================================
// �ˌ�����
//=====================================================
void CRailgun::Shot(void)
{
	// �}�Y���̈ʒu��ݒ�
	D3DXMATRIX* pMtxWeapon = GetMatrix();
	D3DXMATRIX mtxMuzzle;
	universal::SetOffSet(&mtxMuzzle, *pMtxWeapon, D3DXVECTOR3(-18.0f, 6.0f, 0.0f));

	D3DXVECTOR3 posMuzzle =
	{
		mtxMuzzle._41,
		mtxMuzzle._42,
		mtxMuzzle._43,
	};

	// ���_�̐ݒ�
	D3DXVECTOR3 aPosVtx[NUM_VTX];
	D3DXMATRIX aMtxVtx[NUM_VTX];
	D3DXVECTOR3 aOffset[NUM_VTX] =
	{
		{ 0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f },
		{ 0.0f,0.0f,0.0f },
	};

	for (int i = 0; i < NUM_VTX; i++)
	{
		universal::SetOffSet(&aMtxVtx[i], mtxMuzzle, aOffset[i]);

		D3DXVECTOR3 aPosVtx =
		{
			aMtxVtx[i]._41,
			aMtxVtx[i]._42,
			aMtxVtx[i]._43,
		};
	}

	// �G�Ƃ̐ڐG�𔻒肷��
	CEnemyManager *pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager == nullptr)
	{
		return;
	}

	// �擪�I�u�W�F�N�g����
	CEnemy* pEnemy = pEnemyManager->GetHead();

	while (pEnemy != nullptr)
	{
		// ���̃A�h���X��ۑ�
		CEnemy* pEnemyNext = pEnemy->GetNext();

		if (pEnemy != nullptr)
		{
			D3DXVECTOR3 posEnemy = pEnemy->GetPosition();

			bool bHit = universal::CubeCrossProduct(aPosVtx[0], aPosVtx[1], aPosVtx[2], aPosVtx[3], posEnemy);

			if (bHit)
			{
				pEnemy->Hit(5.0f);
			}
		}

		// ���̃A�h���X����
		pEnemy = pEnemyNext;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CRailgun::Draw(void)
{
	// �p���N���X�̕`��
	CWeapon::Draw();
}