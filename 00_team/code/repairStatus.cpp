//=========================================================
//
// �C���󋵏��� [repairStatus.cpp]
// Author = �����đ�Y
//
//=========================================================

//===============================================
// �C���N���[�h
//===============================================
#include "repairStatus.h"
#include "rocket.h"
#include "texture.h"

//===============================================
// �萔��`
//===============================================
namespace
{
	// ���_�J�����̈ʒu
	const D3DXVECTOR3 OBJ_POS = D3DXVECTOR3(170.0f, 110.0f, -90.0f);

	// �����_�J�����̈ʒu
	const D3DXVECTOR3 CAMERA_POSR = D3DXVECTOR3(170.0f, -50.0f, 300.0f);

	// �C���󋵂̃e�N�X�`���̃p�X
	const char* TEX_PATH = "data\\TEXTURE\\UI\\repair_status.png";

	// �C���󋵂̉���
	const float LOGO_WIDTH = 480.0f;

	// �C���󋵂̏c��
	const float LOGO_HEIGHT = 270.0f;

	// �C���󋵂̈ʒu
	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 100.0f, 0.0f);

	const float INCREASED_VALUE = 30.0f;
}

//===============================================
// �ÓI�����o�ϐ��錾
//===============================================
CRepairStatus* CRepairStatus::m_pRepairStatus = nullptr;	// ���g�̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CRepairStatus::CRepairStatus(int nPriority) : CObject3D(nPriority)
{
	// �l�̃N���A
	//ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
}

//===============================================
// �f�X�g���N�^
//===============================================
CRepairStatus::~CRepairStatus()
{
	
}

//===============================================
// ��������
//===============================================
CRepairStatus *CRepairStatus::Create(int nPriority)
{
	if (m_pRepairStatus == nullptr)
	{
		// �C���󋵂̐���
		m_pRepairStatus = new CRepairStatus(7);

		if (m_pRepairStatus != nullptr)
		{
			// ����������
			m_pRepairStatus->Init();
		}
		else if (m_pRepairStatus == nullptr)
		{
			return nullptr;
		}
	}

	return m_pRepairStatus;
}

//===============================================
// ����������
//===============================================
HRESULT CRepairStatus::Init()
{
	// �C���X�^���X���擾
	CRocket* pRocket = pRocket->GetInstance();

	if (m_pRepairStatus != nullptr)
	{
		if (pRocket != nullptr)
		{
			D3DXVECTOR3 posRocket = pRocket->GetPosition();

			CObject3D::Init();
			m_pRepairStatus->SetSize(0.0f, 50.0f);
			m_pRepairStatus->SetPosition({ posRocket.x - INCREASED_VALUE * 3, 200.0f, posRocket.z - 50.0f });
			int nIdx = CTexture::GetInstance()->Regist(TEX_PATH);
			m_pRepairStatus->SetIdxTexture(nIdx);
			m_pRepairStatus->EnableBillboard(true);
			m_pRepairStatus->SetVtx();
		}
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CRepairStatus::Uninit(void)
{
	if (m_pRepairStatus != nullptr)
	{
		m_pRepairStatus = nullptr;
	}

	CObject3D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CRepairStatus::Update(void)
{
	// �C���X�^���X���擾
	CRocket* pRocket = pRocket->GetInstance();

	if (pRocket != nullptr)
	{
		int nProgress = pRocket->GetProgress();
		D3DXVECTOR3 posRocket = pRocket->GetPosition();

		m_pRepairStatus->SetSize(nProgress * INCREASED_VALUE, 30.0f);
		m_pRepairStatus->SetPosition({ posRocket.x - INCREASED_VALUE * 3 + nProgress * INCREASED_VALUE, 200.0f, posRocket.z - 50.0f});
	}

	CObject3D::Update();
}

//===============================================
// �`�揈��
//===============================================
void CRepairStatus::Draw(void)
{
	CObject3D::Draw();
}