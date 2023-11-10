//*****************************************************
//
// �S�[���̏���[goal.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "goal.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "fade.h"
#include "goalTimer.h"
#include "playerManager.h"
#include "player.h"
#include "result.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define INFO_PATH	"data\\TEXT\\goal.txt"	// �S�[�����̃e�L�X�g

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CGoal *CGoal::m_pGoal = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CGoal::CGoal(int nPriority) : CObjectX(nPriority)
{
	m_bFinish = false;
	m_fRadius = 0.0f;
	m_pCollisionGoal = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGoal::~CGoal()
{

}

//=====================================================
// ��������
//=====================================================
CGoal *CGoal::Create()
{
	if (m_pGoal == nullptr)
	{
		m_pGoal = new CGoal;

		if (m_pGoal != nullptr)
		{
			// ������
			m_pGoal->Init();
		}
	}

	return m_pGoal;
}

//=====================================================
// ����������
//=====================================================
HRESULT CGoal::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	if (m_pCollisionGoal == nullptr)
	{// ���̓����蔻�萶��
		m_pCollisionGoal = CCollisionSphere::Create(CCollision::TAG_GOAL, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionGoal != nullptr)
		{// ���̐ݒ�
			m_pCollisionGoal->SetPosition(GetPosition());
			m_pCollisionGoal->SetRadius(5);
		}
	}

	// ���ǂݍ���
	Load();

	return S_OK;
}

//=====================================================
// �ǂݍ��ݏ���
//=====================================================
void CGoal::Load(void)
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

			if (strcmp(cTemp, "GOALSET") == 0)
			{// �p�����[�^�[�Ǎ��J�n
				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					// ���p�����[�^�[�ǂݍ���
					ApplyInfo(pFile, &cTemp[0]);

					if (strcmp(cTemp, "END_GOALSET") == 0)
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
}

//=====================================================
// ��񔽉f
//=====================================================
void CGoal::ApplyInfo(FILE* pFile, char* pTemp)
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

		if (m_pCollisionGoal != nullptr)
		{// �����蔻��̈ʒu�ݒ�
			m_pCollisionGoal->SetPosition(pos);
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

		if (m_pCollisionGoal != nullptr)
		{// �����蔻��̈ʒu�ݒ�
			m_pCollisionGoal->SetRadius(fRadius);
		}
	}
}

//=====================================================
// �I������
//=====================================================
void CGoal::Uninit(void)
{
	if (m_pCollisionGoal != nullptr)
	{
		m_pCollisionGoal->Uninit();
		m_pCollisionGoal = nullptr;
	}

	m_pGoal = nullptr;

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CGoal::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	// �v���C���[�̌��o
	DetectPlayer();
}

//=====================================================
// �v���C���[�̌��o
//=====================================================
void CGoal::DetectPlayer(void)
{
	CGoalTimer *pGoalTimer = CGoalTimer::GetInstance();

	if (pGoalTimer != nullptr)
	{
		return;
	}

	if (m_pCollisionGoal != nullptr)
	{
		if (m_pCollisionGoal->SphereCollision(CCollision::TAG_PLAYER))
		{
			// �S�[���^�C�}�[�̐���
			CGoalTimer::Create();
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CGoal::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// �������Ԃ̏I��
//=====================================================
void CGoal::DeadLine(void)
{
	m_bFinish = true;

	// ���U���g�̐���
	CResult *pResult = CResult::Create();

	// �͈͓��̃v���C���[���o
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pPlayerManager != nullptr)
	{
		for (int i = 0;i < NUM_PLAYER;i++)
		{
			CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

			if (pPlayer != nullptr)
			{
				if (pResult != nullptr)
				{// ���U���g�Ƀv���C���[����n��
					// ���W�̍������狗�����v�Z
					D3DXVECTOR3 pos = GetPosition();
					D3DXVECTOR3 posPlayer = pPlayer->GetPosition();
					D3DXVECTOR3 vecDiff = posPlayer - pos;
					float fDiff = D3DXVec3Length(&vecDiff);
					
					if (fDiff < m_fRadius)
					{
						pResult->SetSurvived(pPlayer);
					}
				}
			}
		}
	}
}