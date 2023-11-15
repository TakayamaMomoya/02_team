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
#include "weaponManager.h"
#include "motion.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"

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

	if (pWeapon == nullptr)
	{
		switch (type)
		{
		case CWeapon::TYPE_MAGNUM:
			// �}�O�i���̐���
			pWeapon = new CMagnum;

			break;
		case CWeapon::TYPE_MACHINEGUN:
			// �}�V���K���̐���
			pWeapon = new CMachinegun;

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

	// ���f���̓Ǎ�
	int nIdx = CModel::Load("data\\MODEL\\weapon\\shotgun.x");
	BindModel(nIdx);

	// ���p�����[�^�[�擾
	CWeaponManager* pWeaponManager = CWeaponManager::GetInstance();

	if (pWeaponManager != nullptr)
	{
		CWeapon::SInfo info = pWeaponManager->GetBaseInfo(m_info.type);

		SetMaxBullet(info.nMaxBullet);
		SetRapid(info.nRapid);
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
	CUniversal *pUniversal = CUniversal::GetInstance();

	if (m_info.pPlayer == nullptr)
	{
		return;
	}

	CMotion *pBody = m_info.pPlayer->GetBody();

	if (pBody != nullptr)
	{
		CParts *pParts = pBody->GetParts(m_info.nIdxHand)->pParts;

		if (pParts != nullptr)
		{
			D3DXMATRIX *pMtx = GetMatrix();
			D3DXMATRIX *pMtxPart = pParts->GetMatrix();
			D3DXVECTOR3 offset = { -10.0f,0.0f,0.0f };

			pUniversal->SetOffSet(pMtx, *pMtxPart, offset);
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CWeapon::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::JustDraw();

	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n�ő�e��[%d]", m_info.nMaxBullet);
	pDebugProc->Print("\n�e��[%d]", m_info.nNumBullet);
	pDebugProc->Print("\n�A�˗�[%d]", m_info.nRapid);
}

//=====================================================
// �v���C���[�ݒ�
//=====================================================
void CWeapon::SetPlayer(CPlayer *pPlayer)
{
	m_info.pPlayer = pPlayer;

	if (m_info.pPlayer != nullptr)
	{
		m_info.nIdxPlayer = pPlayer->GetID();
	}
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