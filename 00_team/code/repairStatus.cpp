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
	// �C���󋵂̃e�N�X�`���̃p�X
	const char* TEX_PATH = "data\\TEXTURE\\UI\\repair_status.png";

	// �C���󋵂̃t���[���e�N�X�`���̃p�X
	const char* FRAME_PATH = "data\\TEXTURE\\UI\\repair_status_frame.png";

	// �����̈ʒu
	const float POS_Y = 300.0f;

	// �C�������Ƃ��̕ϓ���
	const float INCREASED_VALUE = 25.0f;
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
	ZeroMemory(&m_pFrame, sizeof(m_pFrame));
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
		m_pRepairStatus = new CRepairStatus();

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

			// �������̐ݒ�
			CObject3D::Init();
			m_pRepairStatus->SetSize(0.0f, 50.0f);
			m_pRepairStatus->SetPosition({ posRocket.x - INCREASED_VALUE * 3, POS_Y, posRocket.z - 50.0f });
			int nIdx = CTexture::GetInstance()->Regist(TEX_PATH);
			m_pRepairStatus->SetIdxTexture(nIdx);
			m_pRepairStatus->SetColor({0.0f, 1.0f, 0.0f, 1.0f});
			m_pRepairStatus->EnableBillboard(true);
			m_pRepairStatus->SetVtx();

			if (m_pFrame == nullptr)
			{// �g�̏��ݒ�
				m_pFrame = CObject3D::Create({ posRocket.x, 250.0f, posRocket.z - 50.0f });
				m_pFrame->SetSize(3 * INCREASED_VALUE + INCREASED_VALUE * 0.1f, 20.0f + INCREASED_VALUE * 0.1f);
				m_pFrame->SetPosition({ posRocket.x, POS_Y, posRocket.z - 50.0f });
				int nIdx = CTexture::GetInstance()->Regist(FRAME_PATH);
				m_pFrame->SetIdxTexture(nIdx);
				m_pFrame->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
				m_pFrame->EnableBillboard(true);
				m_pFrame->SetVtx();
			}
		}
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CRepairStatus::Uninit(void)
{
	m_pRepairStatus = nullptr;
	m_pFrame = nullptr;

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
	{// �C���󋵂ɂ���ăQ�[�W�̏�Ԃ�ς���
		int nProgress = pRocket->GetProgress();
		D3DXVECTOR3 posRocket = pRocket->GetPosition();

		m_pRepairStatus->SetSize(nProgress * INCREASED_VALUE, 20.0f);
		m_pRepairStatus->SetPosition({ posRocket.x - INCREASED_VALUE * 3 + nProgress * INCREASED_VALUE, POS_Y, posRocket.z - 50.0f});
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