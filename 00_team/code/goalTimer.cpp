//*****************************************************
//
// �S�[���^�C�}�[�̏���[goalGoalTimer.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "goalTimer.h"
#include "manager.h"
#include "number.h"
#include "game.h"
#include "debugproc.h"
#include "goal.h"
#include "UI.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_PLACE	(2)	// ����
#define INITIAL_TIME	(10.0f)	// �����̎���

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CGoalTimer *CGoalTimer::m_pGoalTimer = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CGoalTimer::CGoalTimer()
{
	m_pObjSecond = nullptr;
	m_bStop = false;
	m_fSecond = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGoalTimer::~CGoalTimer()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CGoalTimer::Init(void)
{
	m_fSecond = INITIAL_TIME;
	
	if (m_pObjSecond == nullptr)
	{// �b�\���̐���
		m_pObjSecond = CNumber::Create(NUM_PLACE, 0);

		if (m_pObjSecond != nullptr)
		{
			m_pObjSecond->SetPosition(D3DXVECTOR3(620.0f, 80.0f, 0.0f));
			m_pObjSecond->SetSizeAll(20.0f, 50.0f);
		}
	}

	if (m_pObjDecimal == nullptr)
	{// �����_�ȉ��\���̐���
		m_pObjDecimal = CNumber::Create(NUM_PLACE, 0);

		if (m_pObjDecimal != nullptr)
		{
			m_pObjDecimal->SetPosition(D3DXVECTOR3(720.0f, 80.0f, 0.0f));
			m_pObjDecimal->SetSizeAll(20.0f, 50.0f);
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CGoalTimer::Uninit(void)
{
	if (m_pObjSecond != nullptr)
	{
		m_pObjSecond->Uninit();
		m_pObjSecond = nullptr;
	}

	if (m_pObjDecimal != nullptr)
	{
		m_pObjDecimal->Uninit();
		m_pObjDecimal = nullptr;
	}

	if (m_pPoint != nullptr)
	{
		m_pPoint->Uninit();
		m_pPoint = nullptr;
	}

	m_pGoalTimer = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CGoalTimer::Update(void)
{
	if (CGame::GetState() == CGame::STATE_END || 
		m_bStop)
	{
		return;
	}

	// �b�������炷
	float fTick = CManager::GetTick();
	
	m_fSecond -= fTick;

	if (m_fSecond < 0.0f)
	{// �^�C���A�b�v�̏���
		m_fSecond = 0.0f;

		CGoal *pGoal = CGoal::GetInstance();

		if (pGoal != nullptr)
		{
			if (pGoal->IsFinish() == false)
			{
				pGoal->DeadLine();
			}
		}
	}

	int nDecimal = (int)(m_fSecond * 100.0f) % 100;

	if (m_pObjSecond != nullptr)
	{// �b�\���̐���
		m_pObjSecond->SetValue((int)m_fSecond, NUM_PLACE);
	}

	if (m_pObjDecimal != nullptr)
	{// �����_�ȉ��\���̐���
		m_pObjDecimal->SetValue(nDecimal, NUM_PLACE);
	}
}

//=====================================================
// ���ԉ��Z
//=====================================================
void CGoalTimer::AddGoalTimer(int nValue)
{
	m_fSecond += nValue;
}

//=====================================================
// ��������
//=====================================================
CGoalTimer *CGoalTimer::Create(void)
{
	if (m_pGoalTimer == nullptr)
	{
		m_pGoalTimer = new CGoalTimer;

		m_pGoalTimer->Init();
	}

	return m_pGoalTimer;
}

//=====================================================
// �`�揈��
//=====================================================
void CGoalTimer::Draw(void)
{
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n�S�[���c�莞��[%f]", m_fSecond);
}