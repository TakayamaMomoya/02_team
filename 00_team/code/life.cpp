//*****************************************************
//
// ���C�t�\���̏���[life.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "life.h"
#include "UI.h"

#include "texture.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const D3DXVECTOR3 POS[NUM_PLAYER] =
	{// �ʒu
		D3DXVECTOR3(SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.975f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.7f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.975f, SCREEN_HEIGHT * 0.7f, 0.0f),
	};

	const float WIDTH = 15.0f;
	const float HEIGHT = 100.0f;
	const D3DXCOLOR COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
}
//=====================================================
// �R���X�g���N�^
//=====================================================
CLife::CLife(int nPriority) : CObject(nPriority)
{
	m_pUi = NULL;
	ZeroMemory(&m_info, sizeof(m_info));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CLife::~CLife()
{

}

//=====================================================
// ��������
//=====================================================
CLife *CLife::Create(int nIdx)
{
	CLife *pLife = nullptr;

	pLife = new CLife;

	if (pLife != nullptr)
	{
		// �v���C���[�ԍ���ݒ�
		pLife->m_info.nIdxPlayer = nIdx;

		if (pLife->m_pUi == NULL)
		{
			// UI�I�u�W�F�N�g�̐�������
			pLife->m_pUi = CUI::Create();
		}

		// ���C�t�̏�����
		pLife->Init();

		// �ݒ菈��
		pLife->SetPosition(POS[nIdx]);
		pLife->SetSize(WIDTH,HEIGHT);
		pLife->SetColor(COLOR);
	}

	return pLife;
}

//=====================================================
// ����������
//=====================================================
HRESULT CLife::Init(void)
{
	if (m_pUi != nullptr)
	{
		// �����l�ݒ菈��
		m_pUi->SetSize(50.0f, 100.0f);
		m_pUi->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// �e�N�X�`���ԍ��擾
	//m_info.nIdxTexture = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\number001.png");

	if (m_pUi != nullptr)
	{
		//m_pUi->SetIdxTexture(m_info.nIdxTexture);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CLife::Uninit(void)
{
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CLife::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CLife::Draw(void)
{

}

//=====================================================
// �̗͐ݒ菈��
//=====================================================
void CLife::SetLife(int nLife)
{
	m_info.nLife = nLife;
}

//=====================================================
// �ʒu�ݒ菈��
//=====================================================
void CLife::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pUi != NULL)
	{
		// �t���[���̈ʒu
		m_pUi->SetPosition(pos);

		m_pUi->SetVtx();
	}
}

//=====================================================
// �傫���ݒ菈��
//=====================================================
void CLife::SetSize(float width, float height)
{
	if (m_pUi != NULL)
	{
		m_pUi->SetSize(width, height);

		m_pUi->SetVtx();
	}
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CLife::SetColor(D3DXCOLOR col)
{
	if (m_pUi != NULL)
	{
		m_pUi->SetCol(col);

		m_pUi->SetVtx();
	}
}