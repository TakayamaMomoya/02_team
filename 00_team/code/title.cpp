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
	const char* BODY_PATH[NUM_PLAYER] =
	{// �̂̃p�X
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
		D3DXVECTOR3(0.0f, D3DX_PI * 0.10f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f),
	};

	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f);	// ���S�̈ʒu
	const float LOGO_WIDTH = 875.0f * 0.35f;	// ���S�̕�
	const float LOGO_HEIGHT = 320.0f * 0.35f;	// ���S�̍���
	const char* LOGO_PATH = "data\\TEXTURE\\UI\\logo000.png";	// ���S�̃p�X

	const D3DXVECTOR3 STATE_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f);	// ���S�̈ʒu
	const float START_WIDTH = 200.0f;	// �X�^�[�g�\���̕�
	const float START_HEIGHT = 50.0f;	// �X�^�[�g�\���̍���
	const char* START_PATH = "data\\TEXTURE\\UI\\start.png";	// �X�^�[�g�\���̃p�X

	const float DEST_WIDTH = 500.0f;	// �X�^�[�g�\���̕�
	const float CHANGE_FACT = 0.1f;		// �ω�����W��
	const float ALPHA_CHANGE = 0.05f;	// ���l�̕ω���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CTitle::CTitle()
{
	m_pStart = nullptr;
	ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
	m_state = STATE_NONE;
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
	CObject2D *pLogo = CObject2D::Create(7);
	pLogo->SetSize(LOGO_WIDTH, LOGO_HEIGHT);
	pLogo->SetPosition(LOGO_POS);

	int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
	pLogo->SetIdxTexture(nIdx);
	pLogo->SetVtx();

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
	nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\field00.jpg");
	pField->SetIdxTexture(nIdx);

	// �^�C�g�����f���̐���
	CObjectX* pTitleModel = CObjectX::Create();
	nIdx = CModel::Load("data\\MODEL\\title\\title_model.x");
	pTitleModel->BindModel(nIdx);

	for (int nCount = 0; nCount < NUM_PLAYER; nCount++)
	{
		// �L�����N�^�[�̐�������
		m_apModelPlayer[nCount] = CMotion::Create((char*)BODY_PATH[nCount]);

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
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse *pMouse = CInputMouse::GetInstance();
	CInputJoypad *pJoypad = CInputJoypad::GetInstance();

	CCamera *pCamera = CManager::GetCamera();

	// �V�[���̍X�V
	CScene::Update();
	
	CFade *pFade = CFade::GetInstance();

	if (m_state == STATE_NONE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr)
		{
			if (pKeyboard->GetTrigger(DIK_RETURN) ||
				pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
				pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
			{// �t�F�[�h
				if (pFade != nullptr)
				{
					pFade->SetFade(CScene::MODE_SELECT);
				}
			}
		}
	}
	else if(m_state == STATE_OUT)
	{
		// �X�^�[�g�\���̊Ǘ�
		ManageStart();
	}
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

	float fWidth = m_pStart->GetWidth();
	float fHeight = m_pStart->GetHeight();
	float fDiffWidth;
	float fDiffHeight;

	// �������̌v�Z
	fDiffWidth = (DEST_WIDTH - fWidth) * CHANGE_FACT;
	fDiffHeight = (0.0f - fHeight) * CHANGE_FACT;

	// �����ɂ���
	D3DXCOLOR col = m_pStart->GetCol();

	col.a -= ALPHA_CHANGE;

	if (col.a <= 0.0f)
	{
		col.a = 0.0f;
	}

	m_pStart->SetCol(col);

	// �T�C�Y�ݒ�
	m_pStart->SetSize(fWidth + fDiffWidth, fHeight + fDiffHeight);
	m_pStart->SetVtx();
}

//=====================================================
// �`�揈��
//=====================================================
void CTitle::Draw(void)
{

}