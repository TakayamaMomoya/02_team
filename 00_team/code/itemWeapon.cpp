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

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float GRAVITY = 0.3f;	// �d��
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CItemWeapon::CItemWeapon(int nPriority) : CItem(nPriority)
{
	m_type = CWeapon::TYPE_MAGNUM;
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
	CItem::Init();

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
	CItem::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CItemWeapon::Update(void)
{
	// �p���N���X�̍X�V
	CItem::Update();

	// �ړ��ʂ��ʒu�ɔ��f
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	move.y -= GRAVITY;

	pos += move;
	SetPosition(pos);
	SetMove(move);

	// ���Ƃ̓����蔻��
	CollisionField();
}

//=====================================================
// ���Ƃ̓����蔻��
//=====================================================
void CItemWeapon::CollisionField(void)
{
	D3DXVECTOR3 pos = GetPosition();

	if (pos.y <= 0.0f)
	{
		pos.y = 0.0f;
	}

	SetPosition(pos);
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

	switch (m_type)
	{
	case CWeapon::TYPE_MAGNUM:

		pPlayer->SetWeapon(CWeapon::TYPE_MAGNUM);

		break;
	case CWeapon::TYPE_MACHINEGUN:

		pPlayer->SetWeapon(CWeapon::TYPE_MACHINEGUN);

		break;
	default:
		break;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CItemWeapon::Draw(void)
{
	// �p���N���X�̕`��
	CItem::Draw();
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