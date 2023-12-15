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

#include <stdio.h>

#include "manager.h"
#include "camera.h"
#include "record.h"

#include "object2D.h"
#include "number.h"

#include "object3D.h"
#include "motion.h"

#include "texture.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "inputmouse.h"
#include "sound.h"

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
	const D3DXVECTOR3 RECORD_TEXT_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.15f, 0.0f);	// ��ѕ��̈ʒu
	const float RECORD_TEXT_SIZE = 250.0f;										// ��ѕ��̑傫��
	const float RECORD_TEXT_WIDTH = 1.0f * RECORD_TEXT_SIZE;					// ��ѕ��̕�
	const float RECORD_TEXT_HEIGHT = 0.2f * RECORD_TEXT_SIZE;					// ��ѕ��̍���
	const char* RECORD_TEXT_TEX = "data\\TEXTURE\\UI\\renk_text_record.png";	// ��ѕ��̃p�X

	// ��ю�ރA�C�R��
	const D3DXVECTOR3 GENRE_ICON_POS[CRecord::GENRE_TYPE_MAX] =
	{// �ʒu[���]
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.55f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.55f, 0.0f),
	};
	const float GENRE_ICON_SIZE[CRecord::GENRE_TYPE_MAX] =
	{// �傫��[���]
		250.0f,
		250.0f,
	};
	const float GENRE_ICON_WIDTH[CRecord::GENRE_TYPE_MAX] =
	{// ����[���]
		0.5f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
		0.5f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const float GENRE_ICON_HEIGHT[CRecord::GENRE_TYPE_MAX] =
	{// �c��[���]
		0.4f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
		0.6f * GENRE_ICON_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const char* GENRE_ICON_TEX[CRecord::GENRE_TYPE_MAX] =
	{// �e�N�X�`���̃p�X[���]
		"data\\TEXTURE\\UI\\Icon_destroyer.png",
		"data\\TEXTURE\\UI\\Icon_madman.png",
	};

	// ��ю�ޕ�
	const D3DXVECTOR3 GENRE_TEXT_POS[CRecord::GENRE_TYPE_MAX] =
	{// �ʒu[���]
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.35f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.35f, 0.0f),
	};
	const float GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_MAX] =
	{// �傫��[���]
		175.0f,
		175.0f,
	};
	const float GENRE_TEXT_WIDTH[CRecord::GENRE_TYPE_MAX] =
	{// ����[���]
		1.0f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
		1.0f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const float GENRE_TEXT_HEIGHT[CRecord::GENRE_TYPE_MAX] =
	{// �c��[���]
		0.2f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
		0.2f * GENRE_TEXT_SIZE[CRecord::GENRE_TYPE_DESTROY],
	};
	const char* GENRE_TEXT_TEX[CRecord::GENRE_TYPE_MAX] =
	{// �e�N�X�`���̃p�X[���]
		"data\\TEXTURE\\UI\\rank_text_destroyer.png",
		"data\\TEXTURE\\UI\\rank_text_madman.png",
	};

	// ��\��
	const D3DXVECTOR3 FACE_POS[NUM_PLAYER] =
	{// �ʒu[�v���C���[�ԍ�]
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.3f,  0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.425f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.550f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.675f,0.0f),
	};
	const float FACE_SIZE = 70.0f;
	const float FACE_WIDTH = 0.5f * FACE_SIZE;
	const float FACE_HEIGHT = 0.6f * FACE_SIZE;
	const char* FACE_FILE_NAME[NUM_PLAYER] =
	{// �t�@�C���� [�v���C���[�ԍ�]
		"data\\TEXTURE\\UI\\player01.png",
		"data\\TEXTURE\\UI\\player02.png",
		"data\\TEXTURE\\UI\\player03.png",
		"data\\TEXTURE\\UI\\player04.png",
	};

	// ����
	const D3DXVECTOR3 NUMBER_POS[NUM_PLAYER] =
	{// �ʒu[�v���C���[�ԍ�]
		D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.3f,  0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.425f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.550f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.675f,0.0f),
	};
	const float NUMBER_SIZE = 25.0f;
	const float NUMBER_WIDTH = 1.0f * NUMBER_SIZE;
	const float NUMBER_HEIGHT = 1.0f * NUMBER_SIZE;
	const char* NUMBER_TEX = nullptr;

	// �t�B�[���h
	const float FIELD_WIDTH = 1000.0f;		// �t�B�[���h�̕�
	const float FIELD_HEIGHT = 500.0f;		// �t�B�[���h�̍���
	const char* FIELD_FILE_NAME = "data\\TEXTURE\\MATERIAL\\WodenWall_00.jpg";	// �t�B�[���h�̃p�X

	// �E�H�[��
	const float WALL_WIDTH = 800.0f;		// �E�H�[���̕�
	const float WALL_HEIGHT = 500.0f;		// �E�H�[���̍���
	const char* WALL_FILE_NAME = "data\\TEXTURE\\MATERIAL\\concrete_00.jpg";	// �E�H�[���̃p�X

	// �J����
	const D3DXVECTOR3 CAMERA_POS_V = D3DXVECTOR3(0.0f, 200.0f, -800.0f);
	const D3DXVECTOR3 CAMERA_POS_R = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	const D3DXVECTOR3 CAMERA_MOVE = D3DXVECTOR3(0.0f, 0.0f, 7.0f);

	// ����
	const char* PLAYER_BODY_PATH[CRanking::ACTOR_TYPE_MAX] =
	{// ���҂̑̂̃p�X[���Ҕԍ�]
		"data\\MOTION\\motionRanking01.txt",
		"data\\MOTION\\motionRanking02.txt",
		"data\\MOTION\\motionRanking03.txt",
		"data\\MOTION\\motionRanking04.txt",
		"data\\MOTION\\motionEnemy00.txt",
		"data\\MOTION\\motionEnemy00.txt",
		"data\\MOTION\\motionEnemy00.txt",
	};
	const D3DXVECTOR3 PLAYER_POS[CRanking::DIRECTION_TYPE_MAX][CRanking::ACTOR_TYPE_MAX] =
	{// ���҂̈ʒu[���Ҕԍ�][���o�ԍ�]

		// �s�i
		D3DXVECTOR3(500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(600.0f, 0.0f, 0.0f),
		D3DXVECTOR3(700.0f, 0.0f, 0.0f),
		D3DXVECTOR3(800.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�

		// ������
		D3DXVECTOR3(500.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(600.0f, 0.0f, 0.0f),
		D3DXVECTOR3(650.0f, 0.0f, 30.0f),
		D3DXVECTOR3(675.0f, 0.0f, -30.0f),

		// �ǂ�������
		D3DXVECTOR3(-600.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(1000.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(1050.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(-500.0f, 0.0f,  0.0f),

	};
	const D3DXVECTOR3 PLAYER_ROT[CRanking::DIRECTION_TYPE_MAX][CRanking::ACTOR_TYPE_MAX] =
	{// ���҂̌���[���Ҕԍ�][���o�ԍ�]

		// �s�i
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�

		// ������
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),

		// �ǂ�������
		D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f),

	};
	const D3DXVECTOR3 PLAYER_MOVE[CRanking::DIRECTION_TYPE_MAX][CRanking::ACTOR_TYPE_MAX] =
	{// ���҂̈ړ���[���Ҕԍ�][���o�ԍ�]

		// �s�i
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�

		// ������
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(-4.0f, 0.0f, 0.0f),

		// �ǂ�������
		D3DXVECTOR3(4.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �o�ԂȂ�
		D3DXVECTOR3(4.0f, 0.0f, 0.0f),
	};

	const int DIRECTION_CHANGE_COUNT = 300;	// ���o��ς���܂ł̎���
	const int GENRE_CHANGE_COUNT = 300;		// ��ނ�ς���܂ł̎���

	const char* RANKING_BIN_FILE = "data\\BINARY\\ranking";	// �����L���O�̃t�@�C����

	// �����L���O�̐���
	const D3DXVECTOR3 RANK_NUM_POS[RANK::NUM_MAX] =
	{// �ʒu[���]
		D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.6f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.7f, 0.0f),
	};
	const D3DXVECTOR3 RANK_POS_PLUS = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	const float RANK_NUM_SIZE = 50.0f;
	const float RANK_NUM_WIDTH = 0.5f * RANK_NUM_SIZE;
	const float RANK_NUM_HEIGHT = 0.4f * RANK_NUM_SIZE;
	const char* RANK_NUM_TEX[RANK::NUM_MAX] =
	{// �e�N�X�`���̃p�X[���]
		"data\\TEXTURE\\UI\\1st.png",
		"data\\TEXTURE\\UI\\2nd.png",
		"data\\TEXTURE\\UI\\3rd.png",
	};
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CRanking::CRanking()
{
	ZeroMemory(&m_infoVisualUi, sizeof(m_infoVisualUi));
	ZeroMemory(&m_infoVisualObj,sizeof(m_infoVisualObj)); 
	m_typeDirection = (DIRECTION_TYPE)0;
	m_typeGenre = (CRecord::GENRE_TYPE)0;
	m_nDirectionCnt = 0;
	m_nGenreCnt = 0;

	for (int nCount = 0; nCount < CRecord::GENRE_TYPE_MAX; nCount++)
	{
		ZeroMemory(&m_aRankScore[nCount][0], sizeof(m_aRankScore[nCount]));
		ZeroMemory(&m_aRankFace[nCount][0], sizeof(m_aRankScore[nCount]));
	}

	ZeroMemory(&m_aUpdateIdx[0], sizeof(m_aUpdateIdx));
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
	// ��т̃|�C���^���擾
	CRecord* pRecord = CRecord::GetInstance();

	if (pRecord != nullptr)
	{
		// ��т̃\�[�g
		pRecord->AllSort();
	}

	// UI�̏���������
	if (InitUi() != S_OK)
	{
		return E_FAIL;
	}
	
	// �I�u�W�F�N�g�̏���������
	if (InitObj() != S_OK)
	{
		return E_FAIL;
	}

	// �����ݒ�
	ResetRank();
	SortRank();

	// �擾�����X�R�A�Ń����L���O�ݒ�
	SetRank();

	// �ۑ�
	SaveRank();

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(pSound->LABEL_BGM_RANKING);
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

	// ���o�̍X�V
	UpdateDirection();

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

//=====================================================
// UI�̏���������
//=====================================================
HRESULT CRanking::InitUi(void)
{
	// �e�N�X�`���̃|�C���^���擾
	CTexture* pTexture = CTexture::GetInstance();

	// ��т̃|�C���^���擾
	CRecord* pRecord = CRecord::GetInstance();

	// ���R�[�h�e�L�X�g�̐���
	m_infoVisualUi.pRecordText = CObject2D::Create(7);

	if (m_infoVisualUi.pRecordText != nullptr)
	{
		m_infoVisualUi.pRecordText->SetPosition(RECORD_TEXT_POS);
		m_infoVisualUi.pRecordText->SetSize(RECORD_TEXT_WIDTH, RECORD_TEXT_HEIGHT);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(RECORD_TEXT_TEX);
			m_infoVisualUi.pRecordText->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pRecordText->SetVtx();
	}
	if (m_infoVisualUi.pRecordText == nullptr)
	{
		return E_FAIL;
	}

	// ��ރA�C�R���̐���
	m_infoVisualUi.pGenreIcon = CObject2D::Create(7);

	if (m_infoVisualUi.pGenreIcon != nullptr)
	{
		m_infoVisualUi.pGenreIcon->SetPosition(GENRE_ICON_POS[CRecord::GENRE_TYPE_DESTROY]);
		m_infoVisualUi.pGenreIcon->SetSize(GENRE_ICON_WIDTH[CRecord::GENRE_TYPE_DESTROY], GENRE_ICON_HEIGHT[CRecord::GENRE_TYPE_DESTROY]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_ICON_TEX[CRecord::GENRE_TYPE_DESTROY]);
			m_infoVisualUi.pGenreIcon->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pGenreIcon->SetVtx();
	}
	if (m_infoVisualUi.pGenreIcon == nullptr)
	{
		return E_FAIL;
	}

	// ��ނ̃e�L�X�g�̐���
	m_infoVisualUi.pGenreText = CObject2D::Create(7);

	if (m_infoVisualUi.pGenreText != nullptr)
	{
		m_infoVisualUi.pGenreText->SetPosition(GENRE_TEXT_POS[CRecord::GENRE_TYPE_DESTROY]);
		m_infoVisualUi.pGenreText->SetSize(GENRE_TEXT_WIDTH[CRecord::GENRE_TYPE_DESTROY], GENRE_TEXT_HEIGHT[CRecord::GENRE_TYPE_DESTROY]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_TEXT_TEX[CRecord::GENRE_TYPE_DESTROY]);
			m_infoVisualUi.pGenreText->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pGenreText->SetVtx();
	}
	if (m_infoVisualUi.pGenreText == nullptr)
	{
		return E_FAIL;
	}

	if (pRecord != nullptr)
	{
		int nMaxPlayer = pRecord->GetNumSuvived();

		for (int nCount = 0; nCount < nMaxPlayer; nCount++)
		{
			// �v���C���[��̐���
			m_infoVisualUi.apFace[nCount] = CObject2D::Create(7);

			if (m_infoVisualUi.apFace[nCount] != nullptr)
			{
				if (pRecord != nullptr)
				{
					int nRankNum = pRecord->GetDestroyRank(nCount);

					m_infoVisualUi.apFace[nCount]->SetPosition(FACE_POS[nRankNum]);
					m_infoVisualUi.apFace[nCount]->SetSize(FACE_WIDTH, FACE_HEIGHT);
				}

				if (pTexture != nullptr)
				{
					int nIdx = pTexture->Regist(FACE_FILE_NAME[nCount]);
					m_infoVisualUi.apFace[nCount]->SetIdxTexture(nIdx);
				}

				m_infoVisualUi.apFace[nCount]->SetVtx();
			}
			if (m_infoVisualUi.apFace[nCount] == nullptr)
			{
				return E_FAIL;
			}

			// �����̐���
			m_infoVisualUi.apNumber[nCount] = CNumber::Create(4, 0);

			if (m_infoVisualUi.apNumber[nCount] != nullptr)
			{
				if (pRecord != nullptr)
				{
					int nRankNum = pRecord->GetDestroyRank(nCount);

					m_infoVisualUi.apNumber[nCount]->SetPosition(NUMBER_POS[nRankNum]);
					m_infoVisualUi.apNumber[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_WIDTH);
				}

				m_infoVisualUi.apNumber[nCount]->SetValue(pRecord->GetDestroy(nCount), 4);

				if (pTexture != nullptr)
				{
					//int nIdx = pTexture->Regist();
					//m_infoVisualUi.apNumber[nCount]->SetIdxTexture(nIdx);
					//m_infoVisualUi.apNumber[nCount]->SetVtx();
				}
			}
			if (m_infoVisualUi.apNumber[nCount] == nullptr)
			{
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

//=====================================================
// �I�u�W�F�N�g�̏���������
//=====================================================
HRESULT CRanking::InitObj(void)
{
	// ���擾
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		// �����L���O�̐ݒ�
		pCamera->SetRanking();
	}
	else if (pCamera == nullptr)
	{
		return E_FAIL;
	}

	// �n�ʂ̐���
	m_infoVisualObj.pField = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (m_infoVisualObj.pField != nullptr)
	{
		m_infoVisualObj.pField->SetSize(FIELD_WIDTH, FIELD_HEIGHT);
		int nIdx = CTexture::GetInstance()->Regist(FIELD_FILE_NAME);
		m_infoVisualObj.pField->SetIdxTexture(nIdx);
	}
	else if (m_infoVisualObj.pField == nullptr)
	{
		return E_FAIL;
	}

	// �n�ʂ̐���
	m_infoVisualObj.pWall = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (m_infoVisualObj.pWall != nullptr)
	{
		m_infoVisualObj.pWall->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
		m_infoVisualObj.pWall->SetSize(WALL_WIDTH, WALL_HEIGHT);
		m_infoVisualObj.pWall->SetRot(D3DXVECTOR3(D3DX_PI * -0.5f, 0.0f, 0.0f));
		int nIdx = CTexture::GetInstance()->Regist(WALL_FILE_NAME);
		m_infoVisualObj.pWall->SetIdxTexture(nIdx);
	}
	else if (m_infoVisualObj.pWall == nullptr)
	{
		return E_FAIL;
	}

	for (int nCount = 0; nCount < ACTOR_TYPE_MAX; nCount++)
	{
		// ���҂̐���
		m_infoVisualObj.apModelActor[nCount] = CMotion::Create((char*)PLAYER_BODY_PATH[nCount]);

		if (m_infoVisualObj.apModelActor[nCount] != nullptr)
		{
			m_infoVisualObj.apModelActor[nCount]->SetPosition(PLAYER_POS[m_typeDirection][nCount]);
			m_infoVisualObj.apModelActor[nCount]->SetRot(PLAYER_ROT[m_typeDirection][nCount]);
			m_infoVisualObj.apModelActor[nCount]->SetMotion(1);
		}
		else if (m_infoVisualObj.apModelActor[nCount] == nullptr)
		{
			return E_FAIL;
		}
	}

	// �����L���O�̐����̐���
	for (int nCount = 0; nCount < ACTOR_TYPE_MAX; nCount++)
	{
		if (m_infoVisualUi.apNumRank[nCount] == nullptr)
		{
			m_infoVisualUi.apNumRank[nCount] = CNumber::Create(4, m_aRankScore[m_typeGenre][nCount]);
		}
	}

	// �����L���O���l�̐ݒ菈��
	SetRankNum();

	return S_OK;
}

//=====================================================
// �e��т̐ݒ菈��
//=====================================================
void CRanking::SetRecordGenre(void)
{
	// �e�N�X�`���̃|�C���^���擾
	CTexture* pTexture = CTexture::GetInstance();

	// ��т̃|�C���^���擾
	CRecord* pRecord = CRecord::GetInstance();

	// ��уA�C�R���̐ݒ菈��
	if (m_infoVisualUi.pGenreIcon != nullptr)
	{
		m_infoVisualUi.pGenreIcon->SetPosition(GENRE_ICON_POS[m_typeGenre]);
		m_infoVisualUi.pGenreIcon->SetSize(GENRE_ICON_WIDTH[m_typeGenre], GENRE_ICON_HEIGHT[m_typeGenre]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_ICON_TEX[m_typeGenre]);
			m_infoVisualUi.pGenreIcon->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pGenreIcon->SetVtx();
	}

	// ��уe�L�X�g�̐ݒ菈��
	if (m_infoVisualUi.pGenreText != nullptr)
	{
		m_infoVisualUi.pGenreText->SetPosition(GENRE_TEXT_POS[m_typeGenre]);
		m_infoVisualUi.pGenreText->SetSize(GENRE_TEXT_WIDTH[m_typeGenre], GENRE_TEXT_HEIGHT[m_typeGenre]);

		if (pTexture != nullptr)
		{
			int nIdx = pTexture->Regist(GENRE_TEXT_TEX[m_typeGenre]);
			m_infoVisualUi.pGenreText->SetIdxTexture(nIdx);
		}

		m_infoVisualUi.pGenreText->SetVtx();
	}

	if (pRecord != nullptr)
	{
		int nMaxPlayer = pRecord->GetNumSuvived();

		for (int nCount = 0; nCount < nMaxPlayer; nCount++)
		{
			if (pRecord != nullptr)
			{
				int nRank = 0;		// ����
				int nNumRank = 0;	// ���ʂł̒l

				// ��ނ��Ƃɐ�т̏��ʂ��擾
				switch (m_typeGenre)
				{
				case CRecord::GENRE_TYPE_DESTROY:

					nRank = pRecord->GetDestroyRank(nCount);
					nNumRank = pRecord->GetDestroy(nCount);

					break;
				case CRecord::GENRE_TYPE_MADMAN:

					nRank = pRecord->GetMadmanRank(nCount);
					nNumRank = pRecord->GetMadman(nCount);

					break;
				}

				// ��UI�̐ݒ菈��
				if (m_infoVisualUi.apFace[nCount] != nullptr)
				{
					// ��UI�����ʂ̈ʒu�ɕύX
					m_infoVisualUi.apFace[nCount]->SetPosition(FACE_POS[nRank]);
					m_infoVisualUi.apFace[nCount]->SetSize(FACE_WIDTH, FACE_HEIGHT);

					if (pTexture != nullptr)
					{
						int nIdx = pTexture->Regist(FACE_FILE_NAME[nCount]);
						m_infoVisualUi.apFace[nCount]->SetIdxTexture(nIdx);
					}

					m_infoVisualUi.apFace[nCount]->SetVtx();
				}

				// �����̐ݒ菈��
				if (m_infoVisualUi.apNumber[nCount] != nullptr)
				{
					m_infoVisualUi.apNumber[nCount]->SetPosition(NUMBER_POS[nRank]);
					m_infoVisualUi.apNumber[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_WIDTH);

					m_infoVisualUi.apNumber[nCount]->SetValue(nNumRank, 4);

					if (pTexture != nullptr)
					{
						//int nIdx = pTexture->Regist();
						//m_infoVisualUi.apNumber[nCount]->SetIdxTexture(nIdx);
						//m_infoVisualUi.apNumber[nCount]->SetVtx();
					}
				}
			}
		}
	}
}

//=====================================================
// ���o�̍X�V
//=====================================================
void CRanking::UpdateDirection(void)
{
	// ���o�J�E���g���ݒ�l�ȉ�
	if (m_nDirectionCnt <= DIRECTION_CHANGE_COUNT)
	{
		// �J�E���g�����Z
		m_nDirectionCnt++;
	}
	else
	{
		// �J�E���g�̏�����
		m_nDirectionCnt = 0;

		// ���o�ԍ��𑝂₷
		m_typeDirection = (DIRECTION_TYPE)(m_typeDirection + 1);

		// ���o���ő吔
		if (m_typeDirection >= DIRECTION_TYPE_MAX)
		{
			// ���o��������
			m_typeDirection = (DIRECTION_TYPE)0;
		}

		// ���o��ݒ�
		SetDirection();
	}

	// ��ރJ�E���g���ݒ�l�ȉ�
	if (m_nGenreCnt <= GENRE_CHANGE_COUNT)
	{
		// �J�E���g�𑝂₷
		m_nGenreCnt++;
	}
	else
	{
		// �J�E���g��������
		m_nGenreCnt = 0;

		// ��ю�ނ𑝂₷
		m_typeGenre = (CRecord::GENRE_TYPE)(m_typeGenre + 1);

		// ��ю�ނ��ő�l
		if (m_typeGenre >= CRecord::GENRE_TYPE_MAX)
		{
			// ��ю�ނ�������
			m_typeGenre = (CRecord::GENRE_TYPE)0;
		}

		// ��ю�ނ̐ݒ�
		SetRecordGenre();

		// �����N�̐�����\��
		SetRankNum();
	}

	for (int nCount = 0; nCount < ACTOR_TYPE_MAX; nCount++)
	{
		if (m_infoVisualObj.apModelActor[nCount] != nullptr)
		{
			D3DXVECTOR3 playerMove = m_infoVisualObj.apModelActor[nCount]->GetPosition() + PLAYER_MOVE[m_typeDirection][nCount];

			m_infoVisualObj.apModelActor[nCount]->SetPosition(playerMove);
		}
	}
}

//=====================================================
// ���o�̐ݒ菈��
//=====================================================
HRESULT CRanking::SetDirection(void)
{
	for (int nCount = 0; nCount < ACTOR_TYPE_MAX; nCount++)
	{
		if (m_infoVisualObj.apModelActor[nCount] != nullptr)
		{
			m_infoVisualObj.apModelActor[nCount]->SetPosition(PLAYER_POS[m_typeDirection][nCount]);
			m_infoVisualObj.apModelActor[nCount]->SetRot(PLAYER_ROT[m_typeDirection][nCount]);
			m_infoVisualObj.apModelActor[nCount]->SetMotion(1);
		}
		else if (m_infoVisualObj.apModelActor[nCount] == nullptr)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=====================================================
// �ݒ菈��
//=====================================================
void CRanking::SetRank(void)
{
	// �ϐ��錾
	bool bNewRank = false;

	// ��т̎擾
	CRecord* pRecord = CRecord::GetInstance();

	// �\�[�g
	SortRank();

	for (int nCntGenre = 0; nCntGenre < CRecord::GENRE_TYPE_MAX; nCntGenre++)
	{
		for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
		{
			if (pRecord != nullptr)
			{
				int nNewScore = 0;

				switch (nCntGenre)
				{
				case CRecord::GENRE_TYPE_DESTROY:

					nNewScore = pRecord->GetDestroy(nCount);

					break;

				case CRecord::GENRE_TYPE_MADMAN:

					nNewScore = pRecord->GetMadman(nCount);

					break;
				}

				if (nNewScore > m_aRankScore[nCntGenre][RANK::NUM_MAX - 1])
				{// �ŏ��l���z��������
					m_aRankScore[nCntGenre][RANK::NUM_MAX - 1] = nNewScore;

					// �ă\�[�g
					SortRank();

					bNewRank = true;
				}
			}
		}
	}

	for (int nCntGenre = 0; nCntGenre < CRecord::GENRE_TYPE_MAX; nCntGenre++)
	{
		for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
		{
			if (pRecord != nullptr &&
				bNewRank == true)
			{
				int nNewScore = 0;

				switch (nCntGenre)
				{
				case CRecord::GENRE_TYPE_DESTROY:

					nNewScore = pRecord->GetDestroy(nCount);

					break;

				case CRecord::GENRE_TYPE_MADMAN:

					nNewScore = pRecord->GetMadman(nCount);

					break;
				}

				for (int nCnt = 0; nCnt < RANK::NUM_MAX; nCnt++)
				{// �������l�ƍ��v����L�^��T��
					if (nNewScore == m_aRankScore[nCntGenre][nCnt])
					{// �j���[���R�[�h�ԍ����L�^
						m_aUpdateIdx[nCount] = nCnt;
					}
				}
			}
		}
	}

	// �����N�̐�����\��
	SetRankNum();

	// �ۑ�����
#ifndef _DEBUG
	SaveRank();
#endif
}

//=====================================================
// �����L���O���l�̐ݒ菈��
//=====================================================
void CRanking::SetRankNum(void)
{
	// �����̐ݒ�
	for (int nCount = 0; nCount < RANK::NUM_MAX; nCount++)
	{
		if (m_infoVisualUi.apNumRank[nCount] != nullptr)
		{
			// �l�̐ݒ�
			m_infoVisualUi.apNumRank[nCount]->SetValue(m_aRankScore[m_typeGenre][nCount],4);
			m_infoVisualUi.apNumRank[nCount]->SetPosition(RANK_NUM_POS[nCount]);
			m_infoVisualUi.apNumRank[nCount]->SetSizeAll(NUMBER_WIDTH, NUMBER_HEIGHT);

			// ���ʂ̐���
			CObject2D* pObject2D = CObject2D::Create();
			pObject2D->SetPosition(RANK_NUM_POS[nCount] + RANK_POS_PLUS);
			pObject2D->SetSize(RANK_NUM_WIDTH, RANK_NUM_HEIGHT);

			int nIdx = CTexture::GetInstance()->Regist(RANK_NUM_TEX[nCount]);
			pObject2D->SetIdxTexture(nIdx);
			pObject2D->SetVtx();
		}
	}
}

//=====================================================
// �����L���O�\�[�g
//=====================================================
void CRanking::SortRank(void)
{
	for (int nCntGenre = 0; nCntGenre < CRecord::GENRE_TYPE_MAX ; nCntGenre++)
	{
		for (int nCntRanking = 0; nCntRanking < RANK::NUM_MAX - 1; nCntRanking++)
		{//�����L���O���\�[�g

			// ���[�̒l���ő�l�Ƃ���
			int nTop = nCntRanking;

			for (int nCount2 = nCntRanking + 1; nCount2 < RANK::NUM_MAX; nCount2++)
			{//���̒l�ƑΏۂ̒l���r
				if (m_aRankScore[nCntGenre][nTop] < m_aRankScore[nCntGenre][nCount2])
				{//������r����������������������
					nTop = nCount2;
				}
			}

			//�v�f�̓���ւ�
			int nTemp = m_aRankScore[nCntGenre][nCntRanking];
			m_aRankScore[nCntGenre][nCntRanking] = m_aRankScore[nCntGenre][nTop];
			m_aRankScore[nCntGenre][nTop] = nTemp;
		}
	}
}

//=====================================================
// �����L���O��񃊃Z�b�g
//=====================================================
void CRanking::ResetRank(void)
{
	//�O���t�@�C���ǂݍ���
	LoadRank();
}

//=====================================================
// �����L���O���ۑ�
//=====================================================
void CRanking::SaveRank(void)
{
	//�|�C���^�錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(RANKING_BIN_FILE, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		for (int nCount = 0; nCount < CRecord::GENRE_TYPE_MAX; nCount++)
		{
			//�o�C�i���t�@�C���ɏ�������
			fwrite(&m_aRankScore[nCount][0], sizeof(int), RANK::NUM_MAX, pFile);
			fwrite(&m_aRankFace[nCount][0], sizeof(int), RANK::NUM_MAX, pFile);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		assert(("�����L���O�ۑ��Ɏ��s", false));
	}
}

//=====================================================
//�����L���O���ǂݍ���
//=====================================================
void CRanking::LoadRank(void)
{
	//�|�C���^�錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(RANKING_BIN_FILE, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		//�o�C�i���t�@�C������ǂݍ���
		for (int nCount = 0; nCount < CRecord::GENRE_TYPE_MAX; nCount++)
		{
			fread(&m_aRankScore[nCount][0], sizeof(int), RANK::NUM_MAX, pFile);
			fread(&m_aRankFace[nCount][0], sizeof(int), RANK::NUM_MAX, pFile);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		assert(("�����L���O�ǂݍ��݂Ɏ��s", false));
	}
}