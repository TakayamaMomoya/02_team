//*****************************************************
//
// ����A�C�e���̏���[ItemWeaponWeapon.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "ItemWeapon.h"
#include "manager.h"
#include "renderer.h"
#include "playerManager.h"
#include "weapon.h"
#include "player.h"

#include "effect3D.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float GRAVITY = 0.3f;	// �d��

	D3DXCOLOR WEPONCOL[CWeapon::TYPE_MAX] =
	{// ���킲�Ƃ̃G�t�F�N�g�̐F
		{1.0f, 1.0f, 1.0f, 0.35f},	// �}�O�i��
		{1.0f, 1.0f, 1.0f, 0.35f},	// �}�V���K��
		{1.0f, 0.8f, 0.0f, 0.35f},	// �V���b�g�K��
		{1.0f, 0.0f, 0.0f, 0.35f},	// ���[���K��
		{1.0f, 0.0f, 0.0f, 0.35f},	// �~�j�K��
		{1.0f, 0.0f, 0.0f, 0.35f},	// ���P����
	};
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CItemWeapon::CItemWeapon(int nPriority) : CGimmick(nPriority)
{
	m_type = CWeapon::TYPE_MAGNUM;
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CItemWeapon::~CItemWeapon()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CItemWeapon::Init(void)
{
	// �p���N���X�̏�����
	CGimmick::Init();

	// �ǂݍ���
	Load();

	// �������ɂ���
	D3DXVECTOR3 rot = GetRot();

	rot.x = D3DX_PI * 0.5f;

	SetRot(rot);

	return S_OK;
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CItemWeapon::Load(void)
{
	char* apPath[CWeapon::TYPE_MAX] =
	{
		"data\\MODEL\\weapon\\magnum.x",
		"data\\MODEL\\weapon\\mac10.x",
		"data\\MODEL\\weapon\\shotgun.x",
		"data\\MODEL\\weapon\\railgun.x",
		"data\\MODEL\\weapon\\minigun_000.x",
		"data\\MODEL\\weapon\\launcher.x",
	};

	// ���f���̓Ǎ�
	int nIdx = CModel::Load(apPath[m_type]);
	SetIdxModel(nIdx);
	BindModel(nIdx);
}

//=====================================================
// �I������
//=====================================================
void CItemWeapon::Uninit(void)
{
	// �p���N���X�̏I��
	CGimmick::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CItemWeapon::Update(void)
{
	// �p���N���X�̍X�V
	CGimmick::Update();
}

//=====================================================
// �A�C�e�����莞�̏���
//=====================================================
void CItemWeapon::Interact(CObject *pObj)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pObj == nullptr || pPlayerManager == nullptr)
	{
		return;
	}

	// �v���C���[�擾
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

		if (pPlayer != nullptr)
		{
			if ((CObject*)pPlayer == pObj)
			{// �v���C���[���o
				bool bGet = pPlayer->InputInteract();

				if (bGet)
				{
					// ���ʂ̕t�^
					ApplyEffect(pPlayer);

					Uninit();
				}
			}
		}
	}
}

//=====================================================
// ���ʂ�K�p���鏈��
//=====================================================
void CItemWeapon::ApplyEffect(CPlayer* pPlayer)
{
	if (pPlayer == nullptr)
	{
		return;
	}

	pPlayer->SetWeapon(m_type);
}

//=====================================================
// �`�揈��
//=====================================================
void CItemWeapon::Draw(void)
{
	// �p���N���X�̕`��
	CGimmick::Draw();
}

//=====================================================
// ��������
//=====================================================
CItemWeapon *CItemWeapon::Create(CWeapon::TYPE type)
{
	if (type >= CWeapon::TYPE_MAX || type < 0)
	{
		assert(("�z��O�̕�����o�����Ƃ��Ă܂�",false));
	}

	CItemWeapon *pItemWeapon = nullptr;

	if (pItemWeapon == nullptr)
	{
		pItemWeapon = new CItemWeapon;

		if (pItemWeapon != nullptr)
		{
			pItemWeapon->m_type = type;

			// ������
			pItemWeapon->Init();
		}
	}

	return pItemWeapon;
}