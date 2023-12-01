//*****************************************************
//
// �W�����[meetingPlace.cpp]
// Author:���}���V
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "lift.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "playerManager.h"
#include "player.h"
#include "fade.h"
#include "object2D.h"

#include "debugproc.h"

//*****************************************************
// �}�N����`
//*****************************************************
namespace
{
	const float RANGE(100.0f);
}

//=====================================================
//	�ÓI�����o�ϐ��錾
//=====================================================
int CLift::m_nNumJoinPlayer = 0;
int CLift::m_nInCnt = 0;
bool CLift::m_abJoin[NUM_PLAYER] = {};

//=====================================================
// �R���X�g���N�^
//=====================================================
CLift::CLift(int nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_nInCnt = 0;
	m_state = STATE_NONE;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CLift::~CLift()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CLift::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	int nIdx = CModel::Load("data\\MODEL\\select\\lift.x");
	// ���f���Ǎ�
	BindModel(nIdx);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CLift::Uninit(void)
{
	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CLift::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	CFade* pFade = CFade::GetInstance();
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();
	CPlayer* pPlayer = nullptr;
	int nInPlayer = 0;

	D3DXVECTOR3 pos = GetPosition();

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		pPlayer = pPlayerManager->GetPlayer(nCnt);

		if (pPlayer == nullptr)
		{
			continue;
		}

		//�Ώۂ̃I�u�W�F�N�g��̋��������߂�
		float fLength = sqrtf(
			(pPlayer->GetPosition().x - GetPosition().x) * (pPlayer->GetPosition().x - GetPosition().x) + 
			(pPlayer->GetPosition().z - GetPosition().z) * (pPlayer->GetPosition().z - GetPosition().z));

		if (GetPosition().x + 100.0f >= pPlayer->GetPosition().x &&
			GetPosition().x - 100.0f <= pPlayer->GetPosition().x &&
			GetPosition().z + 100.0f >= pPlayer->GetPosition().z &&
			GetPosition().z - 100.0f <= pPlayer->GetPosition().z)
		{
			D3DXVECTOR3 playerPos = pPlayer->GetPosition();
			//playerPos.y = playerPos.y;
			pPlayer->SetPosition(playerPos);
			m_abJoin[nCnt] = true;

			nInPlayer++;
		}
		else
		{
			m_abJoin[nCnt] = false;
		}
	}

	m_nInCnt = nInPlayer;

	CDebugProc::GetInstance()->Print("\n�J�n�ꏊ\n");
	CDebugProc::GetInstance()->Print("�͈͓��v���C���[[%d]\n", nInPlayer);
}

//=====================================================
// �`�揈��
//=====================================================
void CLift::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// ��������
//=====================================================
CLift* CLift::Create(D3DXVECTOR3 pos,int nPriority)
{
	CLift* pMeetingPlace = nullptr;

	if (pMeetingPlace == nullptr)
	{// �C���X�^���X����
		pMeetingPlace = new CLift(nPriority);

		if (pMeetingPlace != nullptr)
		{
			pMeetingPlace->SetPosition(pos);

			// ����������
			pMeetingPlace->Init();
		}
	}

	return pMeetingPlace;
}

//=====================================================
// �Ǎ�����
//=====================================================
HRESULT CLift::Load(void)
{
	return S_OK;
}

int CLift::GetInPlayer(void)
{
	return m_nInCnt;
}

//=====================================================
// �͈͓��ɓ������l���̔���
//=====================================================
bool CLift::GetIsIn(void)
{
	if (m_nNumJoinPlayer <= 0 && m_nInCnt <= 0)
	{
		return false;
	}
	else if (m_nNumJoinPlayer == m_nInCnt)
	{
		return true;
	}

	return false;
}
