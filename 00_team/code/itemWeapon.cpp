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
#include "debugproc.h"
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

	const float SPEED_SCALING = 0.1f;	// �X�P�[�����傫���Ȃ鑬�x
	const float INITIAL_DESTSCALE = 1.5f;	// �����̖ڕW�X�P�[��
	const float INITIAL_HEIGHT_BASE = 70.0f;	// �����̊����
	const float RANGE_FLOAT = 50.0f;	// �������݂���͈�
	const float SPEED_ROTATE = 0.01f;	// ��]���x
	const float SPEED_MOVE = 0.2f;	// �Ǐ]���x
	const float SPEED_FLOAT = 0.03f;	// �������݂��鑬�x
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

	// �X�P�[�������ݒ�
	SetScale(0.0f);

	// �������ɂ���
	D3DXVECTOR3 rot = GetRot();

	rot.x = D3DX_PI * 0.5f;

	SetRot(rot);

	m_info.fScaleDest = INITIAL_DESTSCALE;

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

	// �X�P�[���̊Ǘ�
	ManageScale();

	// �񂷏���
	ManageTransform();
}

//=====================================================
// �X�P�[���̊Ǘ�
//=====================================================
void CItemWeapon::ManageScale(void)
{
	float fScale = GetScale();

	fScale += (m_info.fScaleDest - fScale) * SPEED_SCALING;

	SetScale(fScale);
}

//=====================================================
// �g�����X�t�H�[���̊Ǘ�
//=====================================================
void CItemWeapon::ManageTransform(void)
{
	// ��]
	D3DXVECTOR3 rot = GetRot();

	rot.y += SPEED_ROTATE;

	universal::LimitRot(&rot.y);

	SetRot(rot);

	// �ڕW�ʒu�Ɉړ�
	D3DXVECTOR3 pos = GetPosition();
	pos.y = 0.0f;
	D3DXVECTOR3 posDest = m_info.posDest + pos;

	pos += (posDest - pos) * SPEED_MOVE;

	SetPosition(pos);

	// �������݂�����
	m_info.fTimer += SPEED_FLOAT;

	universal::LimitRot(&m_info.fTimer);

	float fDiff = sinf(m_info.fTimer) * RANGE_FLOAT;

	m_info.posDest.y = INITIAL_HEIGHT_BASE + fDiff;
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

	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n�A�C�e���̖ڕW�ʒu[%f,%f,%f]", m_info.posDest.x, m_info.posDest.y, m_info.posDest.z);
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