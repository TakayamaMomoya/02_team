//*****************************************************
//
// �}�O�i���̏���[MagnumMagnum.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "weaponMagnum.h"
#include "inputjoypad.h"
#include "bullet.h"
#include "player.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define BULLET_SPEED	(10.0f)	// �e�̑��x

//=====================================================
// �R���X�g���N�^
//=====================================================
CMagnum::CMagnum(int nPriority) : CWeapon(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMagnum::~CMagnum()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CMagnum::Init(void)
{
	// �p���N���X�̏�����
	CWeapon::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMagnum::Uninit(void)
{
	// �p���N���X�̏I��
	CWeapon::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CMagnum::Update(void)
{
	// �p���N���X�̍X�V
	CWeapon::Update();
}

//=====================================================
// �U������
//=====================================================
void CMagnum::Attack(void)
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
			CBullet::Create(pos, -move, 100, CBullet::TYPE_PLAYER, false, 2.0f, fDamage);

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
// �`�揈��
//=====================================================
void CMagnum::Draw(void)
{
	// �p���N���X�̕`��
	CWeapon::Draw();
}