//*****************************************************
//
// �����L���O�̏���[Ranking.cpp]
// Author:����쏟
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************

#include "ranking.h"
#include "main.h"

#include "object2D.h"
#include "number.h"
#include "record.h"

#include "texture.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "inputmouse.h"

#include "fade.h"

//*****************************************************
// �}�N����`
//*****************************************************

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	// ��ѕ�
	const D3DXVECTOR3 RECORD_TEXT_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f);	// ��ѕ��̈ʒu
	const float RECORD_TEXT_SIZE = 200.0f;								// ��ѕ��̑傫��
	const float RECORD_TEXT_WIDTH = 1.0f * RECORD_TEXT_SIZE;			// ��ѕ��̕�
	const float RECORD_TEXT_HEIGHT = 0.2f * RECORD_TEXT_SIZE;			// ��ѕ��̍���
	const char* RECORD_TEXT_TEX = "data\\TEXTURE\\UI\\gamestart.png";	// ��ѕ��̃p�X

	// ��ю�ރA�C�R��
	const D3DXVECTOR3 GENRE_ICON_POS[CRecord::GENRE_TYPE_MAX] =
	{// �ʒu[���]
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, 0.0f),
	};
	const float GENRE_ICON_SIZE[NUM_PLAYER] =
	{// �傫��[���]
		250.0f,
	};
	const float GENRE_ICON_WIDTH[NUM_PLAYER] =
	{// ����[���]
		1.0f * GENRE_ICON_SIZE[NUM_PLAYER],
	};
	const float GENRE_ICON_HEIGHT[NUM_PLAYER] =
	{// �c��[���]
		0.2f * GENRE_ICON_SIZE[NUM_PLAYER],
	};
	const char* GENRE_ICON_TEX[NUM_PLAYER] =
	{// �e�N�X�`���̃p�X[���]
		"data\\TEXTURE\\UI\\GenreIcon000",
	};

	// ��ю�ޕ�
	const D3DXVECTOR3 GENRE_TEXT_POS[CRecord::GENRE_TYPE_MAX] =
	{// �ʒu[���]
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.3f, 0.0f),
	};
	const float GENRE_TEXT_SIZE[NUM_PLAYER] =
	{// �傫��[���]
		250.0f,
	};
	const float GENRE_TEXT_WIDTH[NUM_PLAYER] =
	{// ����[���]
		1.0f * GENRE_TEXT_SIZE[NUM_PLAYER],
	};
	const float GENRE_TEXT_HEIGHT[NUM_PLAYER] =
	{// �c��[���]
		0.2f * GENRE_TEXT_SIZE[NUM_PLAYER],
	};
	const char* GENRE_TEXT_TEX[NUM_PLAYER] =
	{// �e�N�X�`���̃p�X[���]
		"data\\TEXTURE\\UI\\GenreIcon000",
	};

	// ��\��
	const D3DXVECTOR3 FACE_POS[NUM_PLAYER] =
	{// �ʒu[�v���C���[�ԍ�]
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.85f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.85f, 0.0f),
	};
	const float FACE_SIZE[NUM_PLAYER] =
	{// �傫��[�v���C���[�ԍ�]
		250.0f,
		250.0f,
		250.0f,
		250.0f,
	};
	const float FACE_WIDTH[NUM_PLAYER] =
	{// ����[�v���C���[�ԍ�]
		1.0f * FACE_SIZE[NUM_PLAYER],
		1.0f * FACE_SIZE[NUM_PLAYER],
		1.0f * FACE_SIZE[NUM_PLAYER],
		1.0f * FACE_SIZE[NUM_PLAYER],
	};
	const float FACE_HEIGHT[NUM_PLAYER] =
	{// �c��[�v���C���[�ԍ�]
		0.2f * FACE_SIZE[NUM_PLAYER],
		0.2f * FACE_SIZE[NUM_PLAYER],
		0.2f * FACE_SIZE[NUM_PLAYER],
		0.2f * FACE_SIZE[NUM_PLAYER],
	};
	const char* FACE_TEX[NUM_PLAYER] =
	{// �e�N�X�`���̃p�X[�v���C���[�ԍ�]
		"data\\TEXTURE\\UI\\GenreIcon000",
		"data\\TEXTURE\\UI\\GenreIcon000",
		"data\\TEXTURE\\UI\\GenreIcon000",
		"data\\TEXTURE\\UI\\GenreIcon000",
	};

	// ����
	const D3DXVECTOR3 NUMBER_POS[NUM_PLAYER] =
	{// �ʒu[�v���C���[�ԍ�]
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.50f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.60f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.70f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.80f, 0.0f),
	};
	const float NUMBER_SIZE = 25.0f;
	const float NUMBER_WIDTH = 1.0f * NUMBER_SIZE;
	const float NUMBER_HEIGHT = 1.0f * NUMBER_SIZE;
	const char* NUMBER_TEX = "data\\TEXTURE\\UI\\GenreIcon000";
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CRanking::CRanking()
{
	m_infoVisual = {};
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CRanking::~CRanking()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CRanking::Init(void)
{
	// �e�N�X�`���̃|�C���^���擾
	//CTexture* pTexture = CTexture::GetInstance();
	CTexture* pTexture = nullptr;

	// ���R�[�h�e�L�X�g�̐���
	m_infoVisual.pRecordText = CObject2D::Create(7);

	if (m_infoVisual.pRecordText != nullptr)
	{
		m_infoVisual.pRecordText->SetPosition(RECORD_TEXT_POS);
		m_infoVisual.pRecordText->SetSize(RECORD_TEXT_WIDTH,RECORD_TEXT_HEIGHT);
		
		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(RECORD_TEXT_TEX);
			m_infoVisual.pRecordText->SetIdxTexture(nIdx);
			m_infoVisual.pRecordText->SetVtx();
		}

		m_infoVisual.pRecordText->SetVtx();
	}
	if (m_infoVisual.pRecordText == nullptr)
	{
		return E_FAIL;
	}

	// ��ރA�C�R���̐���
	m_infoVisual.pGenreIcon = CObject2D::Create(7);

	if (m_infoVisual.pGenreIcon != nullptr)
	{
		m_infoVisual.pGenreIcon->SetPosition(GENRE_ICON_POS[CRecord::GENRE_TYPE_DESTROY]);
		m_infoVisual.pGenreIcon->SetSize(GENRE_ICON_WIDTH[CRecord::GENRE_TYPE_DESTROY],GENRE_ICON_HEIGHT[CRecord::GENRE_TYPE_DESTROY]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_ICON_TEX[CRecord::GENRE_TYPE_DESTROY]);
			m_infoVisual.pGenreIcon->SetIdxTexture(nIdx);
			m_infoVisual.pGenreIcon->SetVtx();
		}

		m_infoVisual.pGenreIcon->SetVtx();
	}
	if (m_infoVisual.pGenreIcon == nullptr)
	{
		return E_FAIL;
	}

	// ��ނ̃e�L�X�g�̐���
	m_infoVisual.pGenreText = CObject2D::Create(7);

	if (m_infoVisual.pGenreText != nullptr)
	{
		m_infoVisual.pGenreText->SetPosition(GENRE_TEXT_POS[CRecord::GENRE_TYPE_DESTROY]);
		m_infoVisual.pGenreText->SetSize(GENRE_TEXT_WIDTH[CRecord::GENRE_TYPE_DESTROY],GENRE_TEXT_HEIGHT[CRecord::GENRE_TYPE_DESTROY]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_TEXT_TEX[CRecord::GENRE_TYPE_DESTROY]);
			m_infoVisual.pGenreText->SetIdxTexture(nIdx);
			m_infoVisual.pGenreText->SetVtx();
		}

		m_infoVisual.pGenreText->SetVtx();
	}
	if (m_infoVisual.pGenreText == nullptr)
	{
		return E_FAIL;

	}

	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		// �v���C���[��̐���
		m_infoVisual.apFace[nCount] = CObject2D::Create(7);

		if (m_infoVisual.apFace[nCount] != nullptr)
		{
			m_infoVisual.apFace[nCount]->SetPosition(FACE_POS[nCount]);
			m_infoVisual.apFace[nCount]->SetSize(FACE_WIDTH[nCount],FACE_HEIGHT[nCount]);

			if (pTexture != nullptr)
			{
				int nIdx = pTexture->Regist(FACE_TEX[nCount]);
				m_infoVisual.apFace[nCount]->SetIdxTexture(nIdx);
				m_infoVisual.apFace[nCount]->SetVtx();
			}
		}
		if (m_infoVisual.apFace[nCount] == nullptr)
		{
			return E_FAIL;
		}
		m_infoVisual.apFace[nCount]->SetVtx();

		// �����̐���
		m_infoVisual.apNumber[nCount] = CNumber::Create(4,0);

		if (m_infoVisual.apNumber[nCount] != nullptr)
		{
			m_infoVisual.apNumber[nCount]->SetPosition(NUMBER_POS[nCount]);
			m_infoVisual.apNumber[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_WIDTH);

			if (pTexture != nullptr)
			{
				//int nIdx = pTexture->Regist();
				//m_infoVisual.apNumber[nCount]->SetIdxTexture(nIdx);
				//m_infoVisual.apNumber[nCount]->SetVtx();
			}
		}
		if (m_infoVisual.apNumber[nCount] == nullptr)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CRanking::Uninit(void)
{
	// ��т̏I������
	CRecord* pRecord = CRecord::GetInstance();

	if (pRecord != nullptr)
	{
		pRecord->Uninit();
	}

	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CRanking::Update(void)
{
	// ���͏��擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	CFade *pFade = CFade::GetInstance();

	// �V�[���̍X�V
	CScene::Update();

	// ��ʑJ��==========================================
	if (pKeyboard->GetTrigger(DIK_RETURN) ||
		pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{//ENTER�L�[�������ꂽ��
		//�^�C�g���Ɉڍs
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_TITLE);
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CRanking::Draw(void)
{

}