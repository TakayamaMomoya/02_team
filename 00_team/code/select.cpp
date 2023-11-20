//*****************************************************
//
// �l���I������[select.cpp]
// Author:���}���V
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
#include "debugproc.h"
#include "motion.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"
#include "object2D.h"
#include "billboard.h"
#include "object3D.h"
#include "playerManager.h"
#include "player.h"

#include "edit.h"

#include <stdio.h>

//*****************************************************
// �}�N����`
//*****************************************************
namespace
{
	const D3DXVECTOR3 NUMBER_POS(D3DXVECTOR3(-120.0f, 80.0f, -114.0f));	//UI�̈ʒu
	const float SPACE(115.0f);	//UI�Ԃ̍L��
	const float SIZE_PLUS(20.0f);	//UI�̑傫��(+)
	const D3DXVECTOR2 SIZE_FONT(20.0f, 10.0f);	//UI�̑傫��(�Q���FA)
	const float BLINKING_SPEED(0.02f);	//UI�_�ł̑���(�Q���FA)
};

//=====================================================
// �R���X�g���N�^
//=====================================================
CSelect::CSelect()
{
	for (int nCntFirst = 0; nCntFirst < NUM_PLAYER; nCntFirst++)
	{
		m_apPlayer[nCntFirst] = nullptr;

		for (int nCntSecond = 0; nCntSecond < MENU_MAX; nCntSecond++)
		{
			m_aMenuData[nCntFirst].pMenu2D[nCntSecond] = nullptr;
		}
		m_aMenuData[nCntFirst].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		m_aMenuData[nCntFirst].state = FADE_OUT;
		m_abJoin[nCntFirst] = false;
	}
	m_pStartUI = nullptr;
	m_pPlayerManager = nullptr;
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
	CCamera* pCamera = CManager::GetCamera();

	pCamera->SetSelect();

	// �v���C���[�}�l�[�W���[�̐���
	m_pPlayerManager = CPlayerManager::Create();

	MenuInit();
	StartInit();

	// �G�f�B�b�g�̐���
	CEdit::Create();

	// �u���b�N�̓ǂݍ���
	CBlock::Load("data\\MAP\\select_map00.bin");

	return S_OK;
}

//=====================================================
// ���j���[�̏���������
//=====================================================
void CSelect::MenuInit(void)
{
	char *apPath[NUM_PLAYER] =
	{
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
	};

	//�n�ʂ̐���
	CObject3D* pObject = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\MATERIAL\\concrete_02.jpg");
	pObject->SetIdxTexture(nIdx);

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		m_aMenuData[nCnt].pMenu2D[MENU_PLUS] = CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0), SIZE_PLUS, SIZE_PLUS);
		m_aMenuData[nCnt].pMenu2D[MENU_CHAR] = CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0), SIZE_FONT.x, SIZE_FONT.y);
		m_aMenuData[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// +�\��
		m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetPosition(D3DXVECTOR3(NUMBER_POS.x + (nCnt * SPACE), NUMBER_POS.y, NUMBER_POS.z));
		m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetIdxTexture(CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\plus.png"));

		// ����
		m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetPosition(D3DXVECTOR3(NUMBER_POS.x + (nCnt * SPACE), NUMBER_POS.y - 30.0f, NUMBER_POS.z));
		m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		int nIdx = CTexture::GetInstance()->Regist(apPath[nCnt]);
		m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetIdxTexture(nIdx);
	}
}

//=====================================================
// �X�^�[�g�̏���������
//=====================================================
void CSelect::StartInit(void)
{
	m_pStartUI = CObject2D::Create();
	m_pStartUI->SetPosition(D3DXVECTOR3(1100.0f, 650.0f, 0.0f));
	m_pStartUI->SetSize(150.0f, 50.0f);

	int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\start.png");
	m_pStartUI->SetIdxTexture(nIdx);

	m_pStartUI->SetVtx();
}

//=====================================================
// �I������
//=====================================================
void CSelect::Uninit(void)
{
	// �u���b�N�̔j��
	CBlock::DeleteAll();

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

	// �V�[���̍X�V
	CScene::Update();
	
	CFade *pFade = CFade::GetInstance();

	if (m_state == STATE_NONE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr)
		{
			if (/*pKeyboard->GetTrigger(DIK_RETURN) ||*/
				//pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
				pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0))
			{// �t�F�[�h

				if (pFade != nullptr && m_abJoin[0] != false)
				{
					m_pStartUI->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					pFade->SetFade(CScene::MODE_GAME);
				}
			}
		}

		for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
		{
			if (m_aMenuData[nCntPlayer].pMenu2D[MENU_CHAR] != nullptr && m_aMenuData[nCntPlayer].pMenu2D[MENU_PLUS] != nullptr)
			{
				// �F�̕ύX
				ColorChange(nCntPlayer);
				// �Q������
				EntryInput(nCntPlayer);
			}

			if (m_abJoin[nCntPlayer] == true)
			{
				MoveLimit(nCntPlayer);
			}
		}
	}
	else if(m_state == STATE_OUT)
	{

	}

#ifdef _DEBUG
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		// ����
		pCamera->Control();
	}
#endif
}

//=====================================================
// UI�_��
//=====================================================
void CSelect::ColorChange(int nPlayer)
{
	if (m_aMenuData[nPlayer].state == FADE_IN)
	{//�t�F�[�h�C�����
		m_aMenuData[nPlayer].col.a -= BLINKING_SPEED;			//�|���S���𓧖��ɂ��Ă���

		if (m_aMenuData[nPlayer].col.a <= 0.0f)
		{
			m_aMenuData[nPlayer].col.a = 0.0f;

			m_aMenuData[nPlayer].state = FADE_OUT;
		}
	}
	else if (m_aMenuData[nPlayer].state == FADE_OUT)
	{//�t�F�[�h�A�E�g���
		m_aMenuData[nPlayer].col.a += BLINKING_SPEED;			//�|���S����s�����ɂ��Ă���

		if (m_aMenuData[nPlayer].col.a >= 1.0f)
		{
			m_aMenuData[nPlayer].col.a = 1.0f;

			m_aMenuData[nPlayer].state = FADE_IN;
		}
	}

	// �F�̐ݒ�
	m_aMenuData[nPlayer].pMenu2D[MENU_CHAR]->SetColor(m_aMenuData[nPlayer].col);
}

//=====================================================
// �Q������
//=====================================================
void CSelect::EntryInput(int nPlayer)
{
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();
	
	if (pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, nPlayer))
	{
		if (m_abJoin[nPlayer] == true || m_apPlayer[nPlayer] != nullptr || m_pPlayerManager == nullptr)
		{
			return;
		}

		// �Q������
		m_abJoin[nPlayer] = true;

		// �v���C���[�𐶐�
		m_apPlayer[nPlayer] = m_pPlayerManager->BindPlayer(nPlayer);

		// �ʒu��UI�̏ꏊ��
		m_apPlayer[nPlayer]->SetPosition(D3DXVECTOR3(
			m_aMenuData[nPlayer].pMenu2D[MENU_PLUS]->GetPosition().x,
			0.0f,
			m_aMenuData[nPlayer].pMenu2D[MENU_PLUS]->GetPosition().z));

		// UI�폜
		MenuDelete(nPlayer);
	}
}

//=====================================================
// �����ȕ�
//=====================================================
void CSelect::MoveLimit(int nPlayer)
{
	if (m_apPlayer[nPlayer] == nullptr)
	{
		return;
	}

	// ���̎擾
	D3DXVECTOR3 pos = m_apPlayer[nPlayer]->GetPosition();
	D3DXVECTOR3 move = m_apPlayer[nPlayer]->GetMove();

	if (pos.z < -470.0f)
	{
		pos.z = -470.0f;
	}

	 //���̔��f
	m_apPlayer[nPlayer]->SetPosition(pos);
	m_apPlayer[nPlayer]->SetMove(move);
}

//=====================================================
// ���j���[����������
//=====================================================
void CSelect::MenuDelete(int nPlayer)
{
	for (int nCntMenu = 0; nCntMenu < MENU_MAX; nCntMenu++)
	{
		m_aMenuData[nPlayer].pMenu2D[nCntMenu]->Uninit();
		m_aMenuData[nPlayer].pMenu2D[nCntMenu] = nullptr;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CSelect::Draw(void)
{

}