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

//*****************************************************
// �}�N����`
//*****************************************************
#define CAPTION_WIDTH	(918.0f * 0.4f)	// ���o���̕�
#define CAPTION_HEIGHT	(178.0f * 0.4f)	// ���o���̍���
#define CAPTION_PATH "data\\TEXTURE\\UI\\caption01.png"	// ���o���̃p�X

//====================================================
// �R���X�g���N�^
//====================================================
CResult::CResult()
{
	m_state = STATE_NONE;
	m_pBg = nullptr;
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
		"data\\TEXTURE\\UI\\caption02.png",
		"data\\TEXTURE\\UI\\caption03.png",
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