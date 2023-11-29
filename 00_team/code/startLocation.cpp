//*****************************************************
//
// �W�����[meetingPlace.cpp]
// Author:���}���V
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "startLocation.h"
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
int CStartLocation::m_nNumJoinPlayer = 0;
int CStartLocation::m_nInCnt = 0;
bool CStartLocation::m_abJoin[NUM_PLAYER] = {};

//=====================================================
// �R���X�g���N�^
//=====================================================
CStartLocation::CStartLocation(int nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_nInCnt = 0;
	m_state = STATE_NONE;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CStartLocation::~CStartLocation()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CStartLocation::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	int nIdx = CModel::Load("data\\MODEL\\lift.x");
	// ���f���Ǎ�
	BindModel(nIdx);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CStartLocation::Uninit(void)
{
	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CStartLocation::Update(void)
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
void CStartLocation::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// ��������
//=====================================================
CStartLocation* CStartLocation::Create(D3DXVECTOR3 pos,int nPriority)
{
	CStartLocation* pMeetingPlace = nullptr;

	if (pMeetingPlace == nullptr)
	{// �C���X�^���X����
		pMeetingPlace = new CStartLocation(nPriority);

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
HRESULT CStartLocation::Load(void)
{
	return S_OK;
}

//=====================================================
// �͈͓��ɓ������l���̔���
//=====================================================
bool CStartLocation::GetIsIn(void)
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
