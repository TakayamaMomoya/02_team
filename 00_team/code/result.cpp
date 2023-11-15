//*****************************************************
//
// ���U���g�̏���[result.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "result.h"
#include "manager.h"
#include "object2D.h"
#include "texture.h"
#include "fade.h"
#include "game.h"
#include "player.h"
#include "number.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const float CAPTION_WIDTH = 918.0f * 0.4f;	// ���o���̕�
	const float CAPTION_HEIGHT = 178.0f * 0.4f;	// ���o���̍���
	const char* CAPTION_PATH = "data\\TEXTURE\\UI\\result.png";	// ���o���̃p�X

	const int NUM_PLACE = 1;	// ����
	const float NUMBER_WIDTH = 25.0f;	// �����̕�
	const float NUMBER_HEIGHT = 55.0f;	// �����̍���
}

//====================================================
// �R���X�g���N�^
//====================================================
CResult::CResult()
{
	m_state = STATE_NONE;
	m_pBg = nullptr;
	m_pCaption = nullptr;
	ZeroMemory(&m_aInfoSurvived[0], sizeof(m_aInfoSurvived));
	m_nNumSuvived = 0;
}

//====================================================
// �f�X�g���N�^
//====================================================
CResult::~CResult()
{

}

//====================================================
// ��������
//====================================================
CResult *CResult::Create(bool bWin)
{
	CResult *pResult = nullptr;

	pResult = new CResult;

	if (pResult != nullptr)
	{
		pResult->Init();

		pResult->Create2D(bWin);
	}

	return pResult;
}

//====================================================
// �QD�I�u�W�F�N�g�̐���
//====================================================
void CResult::Create2D(bool bWin)
{
	int nIdxTexture;

	char *pPathCaption[2] =
	{
		"data\\TEXTURE\\UI\\result.png",
		"data\\TEXTURE\\UI\\result.png",
	};

	// �w�i�̐���
	m_pBg = CObject2D::Create(7);

	if (m_pBg != nullptr)
	{
		m_pBg->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5f, 0.0f));

		m_pBg->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

		m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));

		m_pBg->SetVtx();
	}

	// ���o���̐���
	m_pCaption = CObject2D::Create(7);

	if (m_pCaption != nullptr)
	{
		m_pCaption->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.4f, 0.0f));

		m_pCaption->SetSize(CAPTION_WIDTH, CAPTION_HEIGHT);

		m_pCaption->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		nIdxTexture = CTexture::GetInstance()->Regist(pPathCaption[bWin]);

		m_pCaption->SetIdxTexture(nIdxTexture);

		m_pCaption->SetVtx();
	}
}

//====================================================
// ����������
//====================================================
HRESULT CResult::Init(void)
{
	m_state = STATE_WAIT;

	// �Q�[�������U���g��Ԃɂ���
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		pGame->SetState(CGame::STATE_RESULT);
	}

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CResult::Uninit(void)
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	if (m_pCaption != nullptr)
	{
		m_pCaption->Uninit();
		m_pCaption = nullptr;
	}

	ZeroMemory(&m_aInfoSurvived[0], sizeof(m_aInfoSurvived));

	Release();
}

//====================================================
// �X�V����
//====================================================
void CResult::Update(void)
{
	// ���쏈��
	Input();
}

//====================================================
// ���쏈��
//====================================================
void CResult::Input(void)
{

}

//====================================================
// �`�揈��
//====================================================
void CResult::Draw(void)
{

}

//====================================================
// �����҂̐ݒ�
//====================================================
void CResult::SetSurvived(CPlayer *pPlayer)
{
	if (m_nNumSuvived == NUM_PLAYER - 1)
	{// �ő�ɒB���Ă����ꍇ�̃G���[
		return;
	}

	if (m_aInfoSurvived[m_nNumSuvived].pSuvived == nullptr)
	{
		// ���̕ۑ�
		m_aInfoSurvived[m_nNumSuvived].pSuvived = pPlayer;

		// ���̕\��
		DispSuvived(&m_aInfoSurvived[m_nNumSuvived]);

		m_nNumSuvived++;
	}
	else
	{
		assert(("���U���g�Ńv���C���[���̎󂯎��Ɏ��s", false));
	}
}

//====================================================
// �����҂̕\��
//====================================================
void CResult::DispSuvived(SInfoSuvived *pInfo)
{
	int nIdx = m_nNumSuvived;

	if (pInfo->pSuvived != nullptr)
	{
		int nID = pInfo->pSuvived->GetID();

		if (pInfo->pNumber == nullptr)
		{// ID�\���̐����𐶐�
			pInfo->pNumber = CNumber::Create(NUM_PLACE, nID);

			if (pInfo->pNumber != nullptr)
			{
				pInfo->pNumber->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + NUMBER_HEIGHT * nIdx, 0.0f));
				pInfo->pNumber->SetSizeAll(NUMBER_WIDTH, NUMBER_HEIGHT);
			}
		}
	}
}