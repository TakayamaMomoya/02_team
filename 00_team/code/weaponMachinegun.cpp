//*****************************************************
//
// �}�V���K���̏���[weaponMachinegun.cpp]
// Author:�����V����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "weaponMachinegun.h"
#include "inputjoypad.h"
#include "bullet.h"
#include "player.h"
#include "universal.h"
#include "sound.h"
#include "animEffect3D.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define BULLET_SPEED	(10.0f)	// �e�̑��x

//=====================================================
// �R���X�g���N�^
//=====================================================
CMachinegun::CMachinegun(int nPriority) : CWeapon(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMachinegun::~CMachinegun()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CMachinegun::Init(void)
{
	// �p���N���X�̏�����
	CWeapon::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMachinegun::Uninit(void)
{
	// �p���N���X�̏I��
	CWeapon::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CMachinegun::Update(void)
{
	// �p���N���X�̍X�V
	CWeapon::Update();
}

//=====================================================
// �U������	Autor:�����V
//=====================================================
void CMachinegun::Attack(void)
{
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();
	CUniversal *pUniversal = CUniversal::GetInstance();

	if (pJoypad == nullptr)
	{
		return;
	}

	int nBullet = GetBullet();
	int nID = GetID();

	if (pJoypad->GetPress(CInputJoypad::PADBUTTONS_RB, nID))
	{// �ˌ�
		int nCntShot = GetCntShot();

		if (nBullet > 0 && nCntShot == 0)
		{// �e�̔���
			D3DXMATRIX* pMtx = GetMatrix();

			D3DXVECTOR3 pos =
			{// �����̈ʒu���擾
				pMtx->_41,
				pMtx->_42,
				pMtx->_43,
			};

			D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

			CPlayer* pPlayer = GetPlayer();

			if (pPlayer != nullptr)
			{// �v���C���[�̌����Ɉړ��ʂ�ݒ�
				D3DXVECTOR3 rot = pPlayer->GetRot();

				int nRange = pUniversal->RandRange(10, -10);

				float fRand = nRange * 0.01f;

				rot.y += fRand;

				move =
				{
					sinf(rot.y) * BULLET_SPEED,
					0.0f,
					cosf(rot.y) * BULLET_SPEED,
				};
			}

			// �З͎擾
			float fDamage = GetDamage();

			// �e�𔭎�
			CBullet::Create(pos, -move, 100, CBullet::TYPE_PLAYER, false,2.0f, fDamage);

			CSound* pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				// �}�O�i�����C��
				pSound->Play(pSound->LABEL_SE_GUNSHOT_01);
			}

			// �e�����炷
			nBullet--;
			SetBullet(nBullet);

			// �A�˃J�E���^�[�̃��Z�b�g
			nCntShot = GetRapid();

			SetCntShot(nCntShot);

			// �}�Y���̈ʒu��ݒ�
			D3DXMATRIX mtxMuzzle;
			D3DXMATRIX mtxWorld = *GetMatrix();
			CUniversal::GetInstance()->SetOffSet(&mtxMuzzle, mtxWorld,D3DXVECTOR3(-18.0f,6.0f,0.0f));

			D3DXVECTOR3 posMuzzle= 
			{
				mtxMuzzle._41,
				mtxMuzzle._42,
				mtxMuzzle._43,
			};

			// �G�t�F�N�g�̐���
			CAnimEffect3D *pAnim3D = CAnimEffect3D::GetInstance();

			if (pAnim3D != nullptr)
			{
				pAnim3D->CreateEffect(posMuzzle, CAnimEffect3D::TYPE::TYPE_MUZZLEFLUSH);
			}
		}
		else
		{// �e�؂�̏ꍇ

		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CMachinegun::Draw(void)
{
	// �p���N���X�̕`��
	CWeapon::Draw();
}