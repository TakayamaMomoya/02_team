//*****************************************************
//
// �h�A�̏���[door.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "door.h"
#include "playerManager.h"
#include "player.h"
#include "manager.h"
#include "collision.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const char* BODY_PATH = "data\\MODEL\\gimmick\\door000.x";	// ���f���̃p�X
	const float INITIAL_LIFE = 5.0f;	// �̗�
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CDoor::CDoor(int nPriority) : CGimmick(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CDoor::~CDoor()
{

}

//=====================================================
// ��������
//=====================================================
CDoor *CDoor::Create(void)
{
	CDoor *pDoor = nullptr;

	if (pDoor == nullptr)
	{
		pDoor = new CDoor;

		if (pDoor != nullptr)
		{
			// ������
			pDoor->Init();
		}
	}

	return pDoor;
}

//=====================================================
// ����������
//=====================================================
HRESULT CDoor::Init(void)
{
	// �p���N���X�̏�����
	CGimmick::Init();

	// ���f���̓Ǎ�
	int nIdx = CModel::Load((char*)BODY_PATH);
	SetIdxModel(nIdx);
	BindModel(nIdx);

	// �����蔻��̐���
	if (m_info.pCollisionCube == nullptr)
	{
		m_info.pCollisionCube = CCollisionCube::Create(CCollision::TAG_BLOCK, this);

		m_info.pCollisionCube->SetPosition(GetPosition());

		m_info.pCollisionCube->SetVtx(GetVtxMax(), GetVtxMin());
	}

	// �l�̏�����
	m_info.fLife = INITIAL_LIFE;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CDoor::Uninit(void)
{
	if (m_info.pCollisionCube != nullptr)
	{
		m_info.pCollisionCube->Uninit();
		m_info.pCollisionCube = nullptr;
	}

	// �p���N���X�̏I��
	CGimmick::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CDoor::Update(void)
{
	// �p���N���X�̍X�V
	CGimmick::Update();
}

//=====================================================
// �C���^���N�g
//=====================================================
void CDoor::Interact(CObject *pObj)
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
			{// �v���C���[�̃C���^���N�g���o
				bool bInteract = pPlayer->InputInteractPress();

				if (bInteract)
				{// �s�b�L���O��i�߂�
					proceed();
				}
			}
		}
	}
}

//=====================================================
// �s�b�L���O��i�߂�
//=====================================================
void CDoor::proceed(void)
{
	float fTick = CManager::GetTick();

	m_info.fLife -= fTick;

	if (m_info.fLife < 0.0f)
	{
		Uninit();
	}
}

//=====================================================
// �ʒu�̐ݒ�
//=====================================================
void CDoor::SetPosition(D3DXVECTOR3 pos)
{
	// �p���N���X�̐ݒu
	CObjectX::SetPosition(pos);

	if (m_info.pCollisionCube != nullptr)
	{// �����蔻��̒Ǐ]
		D3DXVECTOR3 pos = GetPosition();

		m_info.pCollisionCube->SetPosition(pos);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CDoor::Draw(void)
{
	// �p���N���X�̕`��
	CGimmick::Draw();
}