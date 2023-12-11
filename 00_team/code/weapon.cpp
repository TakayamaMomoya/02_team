//*****************************************************
//
// ����̏���[weapon.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "weapon.h"
#include "weaponMagnum.h"
#include "weaponMachinegun.h"
#include "weaponShotgun.h"
#include "weaponRailgun.h"
#include "weaponMinigun.h"
#include "weaponLauncher.h"
#include "weaponManager.h"
#include "motion.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"
#include "sound.h"

#include "motionDiv.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CWeapon::CWeapon(int nPriority) : CObjectX(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CWeapon::~CWeapon()
{

}

//=====================================================
// ��������
//=====================================================
CWeapon *CWeapon::Create(CWeapon::TYPE type, int nIdxhand)
{
	CWeapon *pWeapon = nullptr;
	CSound* pSound = CSound::GetInstance();

	if (pWeapon == nullptr)
	{
		switch (type)
		{
		case CWeapon::TYPE_MAGNUM:
			// �}�O�i���̐���
			pWeapon = new CMagnum;
			
			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_SE_GET_WEAPON);
				pSound->Play(pSound->LABEL_SE_GET_MAGNUM);
			}

			break;
		case CWeapon::TYPE_MACHINEGUN:
			// �}�V���K���̐���
			pWeapon = new CMachinegun;

			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_SE_GET_WEAPON);
				pSound->Play(pSound->LABEL_SE_GET_MACHINEGUN);
			}

			break;
		case CWeapon::TYPE_SHOTGUN:
			// �V���b�g�K���̐���
			pWeapon = new CShotgun;

			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_SE_GET_WEAPON);
				pSound->Play(pSound->LABEL_SE_GET_SHOTGUN);
			}

			break;
		case CWeapon::TYPE_RAILGUN:
			// ���[���K���̐���
			pWeapon = new CRailgun;

			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_SE_GET_WEAPON);
				pSound->Play(pSound->LABEL_SE_GET_RAILGUN);
			}

			break;
		case CWeapon::TYPE_MINIGUN:
			// �~�j�K���̐���
			pWeapon = new CMinigun;

			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_SE_GET_WEAPON);
				pSound->Play(pSound->LABEL_SE_GET_MINIGUN);
			}

			break;
		case CWeapon::TYPE_LAUNCHER:
			// �����`���[�̐���
			pWeapon = new CLauncher;

			if (pSound != nullptr)
			{
				pSound->Play(pSound->LABEL_SE_GET_WEAPON);
				pSound->Play(pSound->LABEL_SE_GET_LUNCHER);
			}

			break;
		default:
			break;
		}

		if (pWeapon != nullptr)
		{
			pWeapon->m_info.nIdxHand = nIdxhand;
			pWeapon->m_info.type = type;

			// ������
			pWeapon->Init();

			// ���f���̓ǂݍ���
			char* apPath[CWeapon::TYPE_MAX] =
			{
				"data\\MODEL\\weapon\\magnum.x",
				"data\\MODEL\\weapon\\mac10.x",
				"data\\MODEL\\weapon\\shotgun.x",
				"data\\MODEL\\weapon\\railgun.x",
				"data\\MODEL\\weapon\\minigun_000.x",
				"data\\MODEL\\weapon\\ak47.x",
			};

			int nIdx = CModel::Load(apPath[type]);
			pWeapon->SetIdxModel(nIdx);
			pWeapon->BindModel(nIdx);
		}
	}

	return pWeapon;
}

//=====================================================
// ����������
//=====================================================
HRESULT CWeapon::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	// ���p�����[�^�[�擾
	CWeaponManager* pWeaponManager = CWeaponManager::GetInstance();

	if (pWeaponManager != nullptr)
	{
		CWeapon::SInfo info = pWeaponManager->GetBaseInfo(m_info.type);

		SetMaxBullet(info.nMaxBullet);
		SetRapid(info.nRapid);
		SetDamage(info.fDamage);
		SetBulletLife(info.fLifeBullet);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CWeapon::Uninit(void)
{
	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CWeapon::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	if (m_info.nCntShot > 0)
	{
		m_info.nCntShot--;
	}
}

//=====================================================
// �v���C���[�̎��Ǐ]
//=====================================================
void CWeapon::FollowPlayerHand(void)
{
	if (m_info.pPlayer == nullptr)
	{
		return;
	}

	CMotionDiv *pBody = m_info.pPlayer->GetBody();

	if (pBody != nullptr)
	{
		if (m_info.bEnable)
		{// ��ɒǏ]
			CParts *pParts = pBody->GetParts(CCharacterDiv::PARTS_UPPER,m_info.nIdxHand)->pParts;

			if (pParts != nullptr)
			{
				D3DXMATRIX *pMtx = GetMatrix();
				D3DXMATRIX *pMtxPart = pParts->GetMatrix();
				D3DXVECTOR3 offset = { -10.0f,0.0f,0.0f };

				universal::SetOffSet(pMtx, *pMtxPart, offset);
			}
		}
		else
		{// �w���ɒǏ]
			CParts *pParts = pBody->GetParts(CCharacterDiv::PARTS_UPPER,0)->pParts;

			if (pParts != nullptr)
			{
				D3DXMATRIX *pMtx = GetMatrix();
				D3DXMATRIX *pMtxPart = pParts->GetMatrix();
				D3DXVECTOR3 offset = { 0.0f,0.0f,20.0f };
				D3DXVECTOR3 rot = { 0.0f,0.0f,D3DX_PI * 0.3f };

				universal::SetOffSet(pMtx, *pMtxPart, offset, rot);
			}
		}
	}
}

//=====================================================
// �L�����̐؂�ւ�
//=====================================================
void CWeapon::SetEnable(bool bEnable)
{
	m_info.bEnable = bEnable;

	ToggleEnable(bEnable);
}

//=====================================================
// �`�揈��
//=====================================================
void CWeapon::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::JustDraw();

#ifdef _DEBUG
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n�ő�e��[%d]", m_info.nMaxBullet);
	pDebugProc->Print("\n�e��[%d]", m_info.nNumBullet);
	pDebugProc->Print("\n�g�p�\[%d]", m_info.bEnable);
	pDebugProc->Print("\n�З�[%f]", m_info.fDamage);
#endif
}

//=====================================================
// �v���C���[�ݒ�
//=====================================================
void CWeapon::SetPlayer(CPlayer *pPlayer)
{
	m_info.pPlayer = pPlayer;

	if (m_info.pPlayer != nullptr)
	{
		m_info.nIdxJoypad = pPlayer->GetIDJoypad();
	}

	m_info.bEnable = true;
}

//=====================================================
// �e���ݒ�
//=====================================================
void CWeapon::SetBullet(int nBullet)
{
	m_info.nNumBullet = nBullet;

	if (m_info.nNumBullet <= 0)
	{// �e�؂ꂵ���ꍇ�A�j��
		if (m_info.pPlayer != nullptr)
		{
			m_info.pPlayer->ReleaseWeapon();
		}

		Uninit();
	}
	else if (m_info.nNumBullet > m_info.nMaxBullet)
	{// �ő吔���z�����ꍇ�̕␳
		m_info.nNumBullet = m_info.nMaxBullet;
	}
}

//=====================================================
// �ő�e���ݒ�
//=====================================================
void CWeapon::SetMaxBullet(int nBullet)
{
	m_info.nMaxBullet = nBullet;
	m_info.nNumBullet = nBullet;
}