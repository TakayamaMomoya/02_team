//*****************************************************
//
// �^�C�g������[title.cpp]
// Author:����쏟
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "title.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "manager.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"

#include "object3D.h"
#include "objectX.h"

//*****************************************************
// �}�N����`
//*****************************************************

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const char* PLAYER_BODY_PATH[NUM_PLAYER] =
	{// �G�̑̂̃p�X
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman02.txt",
		"data\\MOTION\\motionPotatoman03.txt",
		"data\\MOTION\\motionPotatoman04.txt",
	};
	const D3DXVECTOR3 PLAYER_POS[NUM_PLAYER] =
	{// �v���C���[�̈ʒu
		D3DXVECTOR3(-100.0f, 0.0f, -200.0f),
		D3DXVECTOR3( -50.0f, 0.0f, -150.0f),
		D3DXVECTOR3(  50.0f, 0.0f, -150.0f),
		D3DXVECTOR3( 100.0f, 0.0f, -200.0f),
	};
	const D3DXVECTOR3 PLAYER_ROT[NUM_PLAYER] =
	{// �v���C���[�̌���
		D3DXVECTOR3(0.0f, D3DX_PI * -0.25f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.10f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI *  0.10f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI *  0.25f, 0.0f),
	};
	const D3DXVECTOR3 PLAYER_ESC_MOVE = D3DXVECTOR3(0.0f, 0.0f, 8.0f);	// �v���C���[�̓�����Ƃ��̈ړ��� 
	const D3DXVECTOR3 PLAYER_ESC_ROT = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// �v���C���[�̓�����Ƃ��̌���

	const char* ENEMY_BODY_PATH[ENEMY::NUM_ENEMY] =
	{// �G�̑̂̃p�X
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman01.txt",
	};
	const D3DXVECTOR3 ENEMY_POS[ENEMY::NUM_ENEMY] =
	{// �G�̈ʒu
		D3DXVECTOR3(-250.0f, 0.0f, -600.0f),
		D3DXVECTOR3(-150.0f,  0.0f, -450.0f),
		D3DXVECTOR3(-90.0f,  0.0f, -850.0f),
		D3DXVECTOR3(-30.0f, 0.0f, -600.0f),
		D3DXVECTOR3( 40.0f, 0.0f, -800.0f),
		D3DXVECTOR3( 80.0f,  0.0f, -950.0f),
		D3DXVECTOR3( 120.0f,  0.0f, -750.0f),
		D3DXVECTOR3( 250.0f, 0.0f, -500.0f),
	};
	const D3DXVECTOR3 ENEMY_ROT = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// �G�̌���
	const D3DXVECTOR3 ENEMY_MOVE = D3DXVECTOR3(0.0f, 0.0f, 7.5f);	// �G�̈ړ���

	const float FIELD_WIDTH = 10000.0f;		// �t�B�[���h�̕�
	const float FIELD_HEIGHT = 10000.0f;	// �t�B�[���h�̍���

	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f);	// ���S�̈ʒu
	const float LOGO_WIDTH = 875.0f * 0.35f;	// ���S�̕�
	const float LOGO_HEIGHT = 320.0f * 0.35f;	// ���S�̍���
	const char* LOGO_PATH = "data\\TEXTURE\\UI\\logo000.png";	// ���S�̃p�X

	const D3DXVECTOR3 STATE_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f);	// ���S�̈ʒu
	const float START_WIDTH = 200.0f;	// �X�^�[�g�\���̕�
	const float START_HEIGHT = 50.0f;	// �X�^�[�g�\���̍���
	const char* START_PATH = "data\\TEXTURE\\UI\\start.png";	// �X�^�[�g�\���̃p�X

	const float DEST_WIDTH = 500.0f;	// �X�^�[�g�\���̕�

	const int FADE_COUNT = 120;			// �t�F�[�h�܂ł̎���

	const float ALPHA_UPPER = 1.0f;			// ���l�̏����
	const float ALPHA_LOWER = 0.25f;		// ���l�̉�����
	const float ALPHA_CHANGE = 0.1f;		// ���l�̕ω���
	const float ALPHA_CHANGE_LOGO = 0.01f;	// ���l�̕ω���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTitle::CTitle()
{
	m_state = STATE_NONE;
	m_pStart = nullptr;
	ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
	ZeroMemory(&m_apModelEnemy[0], sizeof(m_apModelEnemy));
	m_nFadeCnt = 0;
	m_bIsAlphaChange = false;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CTitle::~CTitle()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CTitle::Init(void)
{
	// ���擾
	CCamera* pCamera = CManager::GetCamera();

	// �J�����̐ݒ�
	pCamera->SetTitle();

	// ���S�̐���
	m_pLogo = CObject2D::Create(7);
	m_pLogo->SetSize(LOGO_WIDTH, LOGO_HEIGHT);
	m_pLogo->SetPosition(LOGO_POS);

	int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
	m_pLogo->SetIdxTexture(nIdx);
	m_pLogo->SetVtx();

	// �X�^�[�g�\���̐���
	m_pStart = CObject2D::Create(7);

	if (m_pStart != nullptr)
	{
		m_pStart->SetSize(START_WIDTH, START_HEIGHT);
		m_pStart->SetPosition(STATE_POS);

		int nIdx = CTexture::GetInstance()->Regist(START_PATH);
		m_pStart->SetIdxTexture(nIdx);
		m_pStart->SetVtx();
	}

	// �n�ʂ̐���
	CObject3D* pField = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pField->SetSize(FIELD_WIDTH, FIELD_HEIGHT);
	nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\field00.jpg");
	pField->SetIdxTexture(nIdx);

	// �^�C�g�����f���̐���
	CObjectX* pTitleModel = CObjectX::Create();
	nIdx = CModel::Load("data\\MODEL\\title\\title_model.x");
	pTitleModel->BindModel(nIdx);

	// �L�����N�^�[�̐�������
	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		m_apModelPlayer[nCount] = CMotion::Create((char*)PLAYER_BODY_PATH[nCount]);

		m_apModelPlayer[nCount]->SetPosition(PLAYER_POS[nCount]);
		m_apModelPlayer[nCount]->SetRot(PLAYER_ROT[nCount]);
		m_apModelPlayer[nCount]->SetMotion(0);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CTitle::Uninit(void)
{
	// �I�u�W�F�N�g�S�j��
	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CTitle::Update(void)
{
	// ���擾
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	CCamera* pCamera = CManager::GetCamera();

	// �V�[���̍X�V
	CScene::Update();

	// �J�����̍X�V
	UpdateCamera();

	if (m_state == STATE_NONE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr)
		{
			if (pKeyboard->GetTrigger(DIK_RETURN) ||
				pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
				pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
			{// �t�F�[�h�J�n

				// �t�F�[�h�ݒ�
				SetFadeIn();
			}
		}
	}
	else if (m_state == STATE_OUT)
	{
		// �t�F�[�h�X�V����
		UpdateFade();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CTitle::Draw(void)
{

}

//=====================================================
// �X�^�[�g�\���̊Ǘ�
//=====================================================
void CTitle::ManageStart(void)
{
	if (m_pStart == nullptr)
	{
		return;
	}

	// �F�̏��擾
	D3DXCOLOR colStart = m_pStart->GetCol();
	D3DXCOLOR colLogo = m_pLogo->GetCol();

	if (m_bIsAlphaChange == false)
	{
		colStart.a -= ALPHA_CHANGE;
	}
	else if (m_bIsAlphaChange == true)
	{
		colStart.a += ALPHA_CHANGE;
	}

	if (colStart.a <= ALPHA_LOWER)
	{
		m_bIsAlphaChange = true;
	}
	else if (colStart.a >= ALPHA_UPPER)
	{
		m_bIsAlphaChange = false;
	}

	if (colLogo.a >= 0.0f)
	{
		// ���S�̃��l������
		colLogo.a -= ALPHA_CHANGE_LOGO;
	}

	// �ݒ菈��
	m_pStart->SetCol(colStart);
	m_pStart->SetVtx();
	m_pLogo->SetCol(colLogo);
	m_pLogo->SetVtx();

}

//=====================================================
// �t�F�[�h�̍X�V����
//=====================================================
void CTitle::UpdateFade(void)
{
	// ���擾
	CFade* pFade = CFade::GetInstance();

	// �X�^�[�g�\���̊Ǘ�
	ManageStart();

	// �t�F�[�h�J�E���g�i�߂�
	m_nFadeCnt++;

	// �v���C���[�̐ݒ菈��
	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		D3DXVECTOR3 posPlayer = m_apModelPlayer[nCount]->GetPosition();
		m_apModelPlayer[nCount]->SetPosition(posPlayer + PLAYER_ESC_MOVE);
		m_apModelPlayer[nCount]->SetRot(PLAYER_ESC_ROT);
	}

	// �G�̐ݒ菈��
	for (int nCount = 0; nCount < ENEMY::NUM_ENEMY; nCount++)
	{
		D3DXVECTOR3 posEnemy = m_apModelEnemy[nCount]->GetPosition();
		m_apModelEnemy[nCount]->SetPosition(posEnemy + ENEMY_MOVE);
	}

	if (m_nFadeCnt == FADE_COUNT)
	{
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_SELECT);
		}
	}
}

//=====================================================
// �J�����̍X�V����
//=====================================================
void CTitle::UpdateCamera(void)
{
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	if (m_state == STATE_NONE)
	{
		// �^�C�g���̃J�����X�V
		pCamera->UpdateTitle();
	}
	else if (m_state == STATE_OUT)
	{
		// �^�C�g���̓�����Ƃ��̃J�����X�V
		pCamera->UpdateTitleEsc();
	}
}

//=====================================================
// �t�F�[�h�ݒ�
//=====================================================
void CTitle::SetFadeIn(void)
{
	// ���擾
	CCamera* pCamera = CManager::GetCamera();

	// �t�F�[�h�A�E�g�ɐݒ�
	m_state = STATE_OUT;

	// �J�����̓�����Ƃ��ݒ�
	pCamera->SetTitleEsc();

	// �v���C���[�̃��[�V�����ݒ菈���i�ړ��j
	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		m_apModelPlayer[nCount]->SetMotion(1);
	}

	// �G�̐�������
	for (int nCount = 0; nCount < ENEMY::NUM_ENEMY; nCount++)
	{
		m_apModelEnemy[nCount] = CMotion::Create((char*)ENEMY_BODY_PATH[nCount]);

		m_apModelEnemy[nCount]->SetPosition(ENEMY_POS[nCount]);
		m_apModelEnemy[nCount]->SetRot(ENEMY_ROT);
		m_apModelEnemy[nCount]->SetMotion(1);
	}
}