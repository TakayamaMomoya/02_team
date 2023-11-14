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

//*****************************************************
// �}�N����`
//*****************************************************
#define INFO_PATH	"data\\TEXT\\rocket.txt"	// �S�[�����̃e�L�X�g

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
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "ROCKETSET") == 0)
			{// �p�����[�^�[�Ǎ��J�n
				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

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
		fscanf(pFile, "%s", pTemp);

		D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

		for (int i = 0;i < 3;i++)
		{
			fscanf(pFile, "%f", &pos[i]);
		}

		SetPosition(pos);

		if (m_pCollisionRocket != nullptr)
		{// �����蔻��̈ʒu�ݒ�
			m_pCollisionRocket->SetPosition(pos);
		}
	}

	if (strcmp(pTemp, "MODEL") == 0)
	{// ���f���ǂݍ���
		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%s", pTemp);

		// ���f���̓Ǎ�
		int nIdx = CModel::Load(pTemp);
		SetIdxModel(nIdx);
		BindModel(nIdx);
	}

	if (strcmp(pTemp, "RADIUS") == 0)
	{// ����̑傫��
		float fRadius;

		fscanf(pFile, "%s", pTemp);

		fscanf(pFile, "%f", &fRadius);

		m_fRadius = fRadius;

		if (m_pCollisionRocket != nullptr)
		{// �����蔻��̈ʒu�ݒ�
			m_pCollisionRocket->SetRadius(fRadius);
		}
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
}

//=====================================================
// �`�揈��
//=====================================================
void CRocket::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}