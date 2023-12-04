//*****************************************************
//
// �ؔ��̏���[box.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "box.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "playerManager.h"
#include "weapon.h"
#include "player.h"
#include "billboard.h"
#include "texture.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define SIZE_INTERACT	(30.0f)	// �C���^���N�g�\���̃T�C�Y

//=====================================================
// �R���X�g���N�^
//=====================================================
CBox::CBox(int nPriority) : CObjectX(nPriority)
{
	m_pCollisionSphere = nullptr;
	m_pCollisionCube = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBox::~CBox()
{

}

//=====================================================
// ��������
//=====================================================
CBox *CBox::Create(void)
{
	CBox *pItem = nullptr;

	if (pItem == nullptr)
	{
		pItem = new CBox;

		if (pItem != nullptr)
		{
			// ������
			pItem->Init();
		}
	}

	return pItem;
}

//=====================================================
// ����������
//=====================================================
HRESULT CBox::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	if (m_pCollisionSphere == nullptr)
	{// �����蔻��̐���
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ITEM, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionSphere != nullptr)
		{
			m_pCollisionSphere->SetRadius(50.0f);
		}
	}

	if (m_pCollisionCube == nullptr)
	{// �����蔻�萶��
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 vtxMax = GetVtxMax();
		D3DXVECTOR3 vtxMin = GetVtxMin();

		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_BLOCK, this);

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetPosition(pos);

			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBox::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->Uninit();
		m_pCollisionSphere = nullptr;
	}

	if (m_pCollisionCube != nullptr)
	{
		m_pCollisionCube->Uninit();
		m_pCollisionCube = nullptr;
	}

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CBox::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	if (m_pCollisionSphere != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		m_pCollisionSphere->SetPosition(pos);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CBox::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}