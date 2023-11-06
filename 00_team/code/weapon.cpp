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
#include "motion.h"
#include "player.h"
#include "universal.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CWeapon::CWeapon(int nPriority) : CObjectX(nPriority)
{
	m_nIdxHand = 0;
	m_nIdxPlayer = 0;
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
			break;
		default:
			break;
		}

		if (pWeapon != nullptr)
		{
			pWeapon->m_nIdxHand = nIdxhand;

			// ������
			pWeapon->Init();
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

	SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���f���̓Ǎ�
	int nIdx = CModel::Load("data\\MODEL\\weapon\\shotgun.x");
	SetIdxModel(nIdx);
	BindModel(nIdx);

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

	// �v���C���[�̎�ƃ}�g���b�N�X���������킹��
	FollowPlayerHand();
}

//=====================================================
// �v���C���[�̎��Ǐ]
//=====================================================
void CWeapon::FollowPlayerHand(void)
{
	CUniversal *pUniversal = CUniversal::GetInstance();

	if (m_pPlayer == nullptr)
	{
		return;
	}

	CMotion *pBody = m_pPlayer->GetBody();

	if (pBody != nullptr)
	{
		CParts *pParts = pBody->GetParts(m_nIdxHand)->pParts;

		if (pParts != nullptr)
		{
			D3DXMATRIX *pMtx = GetMatrix();
			D3DXMATRIX *pMtxPart = pParts->GetMatrix();
			D3DXVECTOR3 offset = { 0.0f,0.0f,0.0f };

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
}

//=====================================================
// �v���C���[�ݒ�
//=====================================================
void CWeapon::SetPlayer(CPlayer *pPlayer)
{
	m_pPlayer = pPlayer;

	if (m_pPlayer != nullptr)
	{
		m_nIdxPlayer = pPlayer->GetID();
	}
}