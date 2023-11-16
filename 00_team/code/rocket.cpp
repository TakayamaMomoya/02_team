//*****************************************************
//
// ���P�b�g�̏���[rocket.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "rocket.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "fade.h"
#include "playerManager.h"
#include "player.h"
#include "result.h"
#include "goal.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const char* INFO_PATH = "data\\TEXT\\rocket.txt";	// ���P�b�g���̃e�L�X�g
	const int MAX_PROGRESS = 3;	// �ő�̐i�s��
	const int MIN_PROGRESS = 0;	// �ő�̐i�s��
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CRocket *CRocket::m_pRocket = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CRocket::CRocket(int nPriority) : CObjectX(nPriority)
{
	m_fRadius = 0.0f;
	m_fSpeed = 0.0f;
	m_fDeleteHeight = 0.0f;
	m_nProgress = 0;
	m_state = STATE_NONE;
	m_pCollisionRocket = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CRocket::~CRocket()
{

}

//=====================================================
// ��������
//=====================================================
CRocket *CRocket::Create()
{
	if (m_pRocket == nullptr)
	{
		m_pRocket = new CRocket;

		if (m_pRocket != nullptr)
		{
			// ������
			m_pRocket->Init();
		}
	}

	return m_pRocket;
}

//=====================================================
// ����������
//=====================================================
HRESULT CRocket::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	if (m_pCollisionRocket == nullptr)
	{// ���̓����蔻�萶��
		m_pCollisionRocket = CCollisionSphere::Create(CCollision::TAG_ROCKET, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionRocket != nullptr)
		{// ���̐ݒ�
			m_pCollisionRocket->SetPosition(GetPosition());
			m_pCollisionRocket->SetRadius(5);
		}
	}

	// ���ǂݍ���
	Load();

	m_state = STATE_NORMAL;

	return S_OK;
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CRocket::Load(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntParam = 0;

	// �t�@�C������ǂݍ���
	FILE* pFile = fopen(INFO_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			(void)(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "ROCKETSET") == 0)
			{// �p�����[�^�[�Ǎ��J�n
				while (true)
				{
					// �����ǂݍ���
					(void)fscanf(pFile, "%s", &cTemp[0]);

					// ���p�����[�^�[�ǂݍ���
					ApplyInfo(pFile, &cTemp[0]);

					if (strcmp(cTemp, "END_ROCKETSET") == 0)
					{// �p�����[�^�[�Ǎ��I��
						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// �ǂݍ��݂̏I��
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		assert(("���P�b�g���̓ǂݍ��݂Ɏ��s", false));
	}
}

//=====================================================
// ��񔽉f
//=====================================================
void CRocket::ApplyInfo(FILE* pFile, char* pTemp)
{
	if (strcmp(pTemp, "POS") == 0)
	{// �ʒu
		(void)fscanf(pFile, "%s", pTemp);

		D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

		for (int i = 0;i < 3;i++)
		{
			(void)fscanf(pFile, "%f", &pos[i]);
		}

		SetPosition(pos);

		if (m_pCollisionRocket != nullptr)
		{// �����蔻��̈ʒu�ݒ�
			m_pCollisionRocket->SetPosition(pos);
		}
	}

	if (strcmp(pTemp, "MODEL") == 0)
	{// ���f���ǂݍ���
		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%s", pTemp);

		// ���f���̓Ǎ�
		int nIdx = CModel::Load(pTemp);
		SetIdxModel(nIdx);
		BindModel(nIdx);
	}

	if (strcmp(pTemp, "RADIUS") == 0)
	{// ����̑傫��
		float fRadius;

		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%f", &fRadius);

		m_fRadius = fRadius;

		if (m_pCollisionRocket != nullptr)
		{// �����蔻��̈ʒu�ݒ�
			m_pCollisionRocket->SetRadius(fRadius);
		}
	}

	if (strcmp(pTemp, "SPEED") == 0)
	{// �㏸���x
		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%f", &m_fSpeed);
	}

	if (strcmp(pTemp, "DELETE_HEIGHT") == 0)
	{// �폜���鍂��
		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%f", &m_fDeleteHeight);
	}
}

//=====================================================
// �I������
//=====================================================
void CRocket::Uninit(void)
{
	if (m_pCollisionRocket != nullptr)
	{
		m_pCollisionRocket->Uninit();
		m_pCollisionRocket = nullptr;
	}

	m_pRocket = nullptr;

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CRocket::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	if (m_state == STATE::STATE_ESCAPE)
	{// �E�o��Ԃ̍X�V
		UpdateEscape();
	}
}

//=====================================================
// �E�o�̍X�V
//=====================================================
void CRocket::UpdateEscape(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	// �㏸�ʂ̉��Z
	move.y += m_fSpeed;

	// �ړ��ʂ̔��f
	pos += move;

	SetPosition(pos);
	SetMove(move);

	if (pos.y >= m_fDeleteHeight)
	{
		Uninit();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CRocket::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// �i�s�󋵂̉��Z
//=====================================================
void CRocket::AddProgress(int nProgress)
{
	if (m_state != STATE_NORMAL)
	{// �ʏ��Ԃ̂ݐi�s�\
		return;
	}

	// �i�s�󋵉��Z
	m_nProgress += nProgress;

	// �ő�A�ŏ��l�̕␳
	if (m_nProgress < MIN_PROGRESS)
	{
		m_nProgress = MIN_PROGRESS;
	}
	if (m_nProgress >= MAX_PROGRESS)
	{
		m_nProgress = MAX_PROGRESS;

		// �S�[���̐���
		CGoal *pGoal = CGoal::Create();

		D3DXVECTOR3 pos = GetPosition();
		pGoal->SetPosition(pos);
	}

	// ���P�b�g���f���̕ω�
	SwapModel(m_nProgress);
}

//=====================================================
// ���f���̒u������
//=====================================================
void CRocket::SwapModel(int nProgress)
{
	char *apPath[MAX_PROGRESS + 1] = 
	{
		"data\\MODEL\\rocket\\rocket00.x",
		"data\\MODEL\\rocket\\rocket01.x",
		"data\\MODEL\\rocket\\rocket02.x",
		"data\\MODEL\\rocket\\rocket03.x",
	};

	// ���f���̓Ǎ�
	int nIdx = CModel::Load(apPath[nProgress]);
	SetIdxModel(nIdx);
	BindModel(nIdx);
}