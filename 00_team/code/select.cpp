//*****************************************************
//
// �^�C�g������[title.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "select.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "manager.h"
#include "motion.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"

#include "playerManager.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define LOGO_PATH	"data\\TEXTURE\\UI\\logo000.png"	// ���S�̃p�X
#define START_WIDTH	(200.0f)	// �X�^�[�g�\���̕�
#define START_HEIGHT	(50.0f)	// �X�^�[�g�\���̍���
#define DEST_WIDTH	(500.0f)	// �X�^�[�g�\���̕�
#define CHANGE_FACT	(0.1f)	// �ω�����W��
#define ALPHA_CHANGE	(0.05f)	// ���l�̕ω���

#define NUMBER_POS	(D3DXVECTOR2(300.0f, 600.0f))
#define SPACE	(220.0f)

//=====================================================
// �R���X�g���N�^
//=====================================================
CSelect::CSelect()
{
	for (int nCntFirst = 0; nCntFirst < NUM_PLAYER; nCntFirst++)
	{
		for (int nCntSecond = 0; nCntSecond < MENU_MAX; nCntSecond++)
		{
			m_aMenuData[nCntFirst].pMenu2D[nCntSecond] = nullptr;
		}
		m_aMenuData[nCntFirst].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		bJoin[nCntFirst] = false;
	}
	m_pPlayerManager = nullptr;
	m_pStart = nullptr;
	m_state = STATE_NONE;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CSelect::~CSelect()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CSelect::Init(void)
{
	// ���S�̐���
	/*CObject2D *pObject2D = CObject2D::Create(7);
	pObject2D->SetSize(875.0f * 0.45f, 320.0f * 0.45f);
	pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.7f, 200.0f, 0.0f));

	int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
	pObject2D->SetIdxTexture(nIdx);
	pObject2D->SetVtx();*/

	// �v���C���[�}�l�[�W���[�̐���
	m_pPlayerManager = CPlayerManager::Create();

	MenuInit();

	return S_OK;
}

//=====================================================
// ���j���[�̏���������
//=====================================================
void CSelect::MenuInit(void)
{
	//�l�����̑I�����j���[�𐶐�
	int aIdx[NUM_PLAYER] = {};

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME] = CObject2D::Create(6);
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER] = CObject2D::Create(7);

		//���j���[�g
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetPosition(D3DXVECTOR3(NUMBER_POS.x + (nCnt * SPACE), NUMBER_POS.y, 0.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetSize(80.0f, 80.0f);
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetIdxTexture(CTexture::GetInstance()->Regist("frame.png"));

		//���j���[����
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetPosition(D3DXVECTOR3(NUMBER_POS.x + (nCnt * SPACE), NUMBER_POS.y, 0.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetSize(50.0f, 50.0f);
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

		switch (nCnt)
		{
		case 0:
			aIdx[nCnt] = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\1st.png");
			m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(aIdx[nCnt]);
			break;
		case 1:
			aIdx[nCnt] = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\2nd.png");
			m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(aIdx[nCnt]);
			break;
		case 2:
			aIdx[nCnt] = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\3rd.png");
			m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(aIdx[nCnt]);
			break;
		case 3:
			aIdx[nCnt] = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\4th.png");
			m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetIdxTexture(aIdx[nCnt]);
			break;

		default:
			break;
		}

		m_aMenuData[nCnt].pMenu2D[MENU_FRAME]->SetVtx();
		m_aMenuData[nCnt].pMenu2D[MENU_NUMBER]->SetVtx();
	}
}

//=====================================================
// �I������
//=====================================================
void CSelect::Uninit(void)
{
	// �I�u�W�F�N�g�S�j��
	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CSelect::Update(void)
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
				pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0))
			{// �t�F�[�h
				if (pFade != nullptr)
				{
					pFade->SetFade(CScene::MODE_GAME);
				}
			}
		}

		MenuUpdate();
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
void CSelect::ManageStart(void)
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
// �X�V
//=====================================================
void CSelect::MenuUpdate(void)
{
	// ���擾
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		if (pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, nCntPlayer))
		{
			if (bJoin[nCntPlayer] == true)
			{
				continue;
			}

			bJoin[nCntPlayer] = true;

			if (m_pPlayerManager != nullptr)
			{
				m_pPlayerManager->CreatePlayer1(nCntPlayer);
			}
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CSelect::Draw(void)
{

}