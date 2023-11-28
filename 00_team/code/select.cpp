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
#include "sound.h"

#include "debrisSpawner.h"
#include "debris.h"

#include "startLocation.h"

#include "container.h"
#include "weaponManager.h"

#include "edit.h"

#include <stdio.h>

//*****************************************************
// �}�N����`
//*****************************************************
namespace
{
	const D3DXVECTOR3 UI_POS_1P(D3DXVECTOR3(-168.0f, 80.0f, -72.0f));	//UI�̈ʒu
	const D3DXVECTOR3 UI_POS_2P(D3DXVECTOR3(-18.0f, 80.0f, -72.0f));	//UI�̈ʒu
	const D3DXVECTOR3 UI_POS_3P(D3DXVECTOR3(132.0f, 80.0f, -72.0f));	//UI�̈ʒu
	const D3DXVECTOR3 UI_POS_4P(D3DXVECTOR3(282.0f, 80.0f, -72.0f));	//UI�̈ʒu

	const float SPOWN_HEIGHT(20.0f);	//�v���C���[�o������

	const float SPACE(115.0f);	//UI�Ԃ̍L��
	const float SIZE_PLUS(20.0f);	//UI�̑傫��(+)
	const D3DXVECTOR2 SIZE_FONT(20.0f, 10.0f);	//UI�̑傫��(�Q���FA)
	const float BLINKING_SPEED(0.02f);	//UI�_�ł̑���(�Q���FA)

	const float GRAVITY(1.0f);	//�d��
};

//=====================================================
// �R���X�g���N�^
//=====================================================
CSelect::CSelect()
{
	for (int nCntFirst = 0; nCntFirst < NUM_PLAYER; nCntFirst++)
	{
		m_apPlayerData[nCntFirst].pPlayer = nullptr;
		m_apPlayerData[nCntFirst].state = PLAYER_NONE;

		for (int nCntSecond = 0; nCntSecond < MENU_MAX; nCntSecond++)
		{
			m_aMenuData[nCntFirst].pMenu2D[nCntSecond] = nullptr;
		}
		m_aMenuData[nCntFirst].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		m_aMenuData[nCntFirst].state = FADE_OUT;
		m_abEntry[nCntFirst] = false;
	}
	m_pStartUI = nullptr;
	m_pPlayerManager = nullptr;
	m_state = STATE_NONE;

	for (int nCnt = 0; nCnt < MAX_CONTAINER; nCnt++)
	{
		m_apContainer[nCnt] = nullptr;
	}
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
	// �J�������̎擾
	CCamera* pCamera = CManager::GetCamera();
	pCamera->SetSelect();

	// �v���C���[�}�l�[�W���[�̐���
	m_pPlayerManager = CPlayerManager::Create();

	MenuInit();
	StartInit();
	ContainerInit();

	// �G�f�B�b�g�̐���
	//CEdit::Create();

	// �u���b�N�̓ǂݍ���
	CBlock::Load("data\\MAP\\select_map00.bin");

	CStartLocation::Create(D3DXVECTOR3(0.0f, 10.0f, -300.0f));

	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(pSound->LABEL_BGM_SELECT);
	}

	return S_OK;
}

//=====================================================
// ���j���[�̏���������
//=====================================================
void CSelect::MenuInit(void)
{
	char* apPath[NUM_PLAYER] =
	{
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
	};

	int nIdx = 0;

	//�n�ʂ̐���
	CObject3D* pObject = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\MATERIAL\\concrete_02.jpg");
	pObject->SetIdxTexture(nIdx);

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		m_aMenuData[nCnt].pMenu2D[MENU_PLUS] = CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0), SIZE_PLUS, SIZE_PLUS);
		m_aMenuData[nCnt].pMenu2D[MENU_CHAR] = CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0), SIZE_FONT.x, SIZE_FONT.y);
		m_aMenuData[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (nCnt)
		{
		case 0:
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetPosition(D3DXVECTOR3(UI_POS_1P.x, UI_POS_1P.y, UI_POS_1P.z));
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetIdxTexture(CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\plus.png"));

			// ����
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetPosition(D3DXVECTOR3(UI_POS_1P.x, UI_POS_1P.y - 30.0f, UI_POS_1P.z));
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			nIdx = CTexture::GetInstance()->Regist(apPath[nCnt]);
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetIdxTexture(nIdx);
			break;

		case 1:
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetPosition(D3DXVECTOR3(UI_POS_2P.x, UI_POS_2P.y, UI_POS_2P.z));
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetIdxTexture(CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\plus.png"));

			// ����
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetPosition(D3DXVECTOR3(UI_POS_2P.x, UI_POS_2P.y - 30.0f, UI_POS_2P.z));
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			nIdx = CTexture::GetInstance()->Regist(apPath[nCnt]);
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetIdxTexture(nIdx);
			break;

		case 2:
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetPosition(D3DXVECTOR3(UI_POS_3P.x, UI_POS_3P.y, UI_POS_3P.z));
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetIdxTexture(CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\plus.png"));

			// ����
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetPosition(D3DXVECTOR3(UI_POS_3P.x, UI_POS_3P.y - 30.0f, UI_POS_3P.z));
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			nIdx = CTexture::GetInstance()->Regist(apPath[nCnt]);
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetIdxTexture(nIdx);
			break;

		case 3:
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetPosition(D3DXVECTOR3(UI_POS_4P.x, UI_POS_4P.y, UI_POS_4P.z));
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_aMenuData[nCnt].pMenu2D[MENU_PLUS]->SetIdxTexture(CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\plus.png"));

			// ����
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetPosition(D3DXVECTOR3(UI_POS_4P.x, UI_POS_4P.y - 30.0f, UI_POS_4P.z));
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			nIdx = CTexture::GetInstance()->Regist(apPath[nCnt]);
			m_aMenuData[nCnt].pMenu2D[MENU_CHAR]->SetIdxTexture(nIdx);
			break;
		default:
			assert(("�l��UI�̐ݒ莸�s", false));
			break;
		}
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
	m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\start_game.png");
	m_pStartUI->SetIdxTexture(nIdx);

	m_pStartUI->SetVtx();
}

//=====================================================
// �R���e�i�̏���������
//=====================================================
void CSelect::ContainerInit(void)
{
	CWeaponManager::Create();

	for (int nCnt = 0; nCnt < MAX_CONTAINER; nCnt++)
	{
		m_apContainer[nCnt] = CContainer::Create();

		switch (nCnt)
		{
		case 0:
			m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(130.0f, 0.0f, -250.0f));
			break;
		case 1:
			m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(-130.0f, 0.0f, -250.0f));
			break;
		case 2:
			m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(130.0f, 0.0f, -300.0f));
			break;
		case 3:
			m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(-130.0f, 0.0f, -300.0f));
			break;
		case 4:
			m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(130.0f, 0.0f, -350.0f));
			break;
		case 5:
			m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(-130.0f, 0.0f, -350.0f));
			break;
		default:
			assert(("�R���e�i�ݒ�̎��s(select.cpp)", false));
			break;
		}
	}
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
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	D3DXCOLOR col = { 0.0f, 0.0f, 0.0f, 0.0f };

	int nJoinPlayer = 0;

	// �V�[���̍X�V
	CScene::Update();

	CFade* pFade = CFade::GetInstance();

	if (m_state == STATE_NONE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr)
		{
			if (CStartLocation::GetIsIn() == true)
			{// �Q�����̑S�����͈͓��ɓ������Ƃ��������������
				if (/*pKeyboard->GetTrigger(DIK_RETURN) ||*/
				//pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
					pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0))
				{// �t�F�[�h

					if (pFade != nullptr && m_abEntry[0] != false)
					{
						pFade->SetFade(CScene::MODE_GAME);
					}
				}

				// StartUI��������悤��
				m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_pStartUI->SetVtx();
			}
			else
			{
				// Start��UI�������Ȃ��悤��
				m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_pStartUI->SetVtx();
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

			if (m_abEntry[nCntPlayer] == true)
			{
				MoveLimit(nCntPlayer);

				nJoinPlayer++;
			}
		}

		// �R���e�i�̍Đݒu
		ReSetContainer();
	}
	else if (m_state == STATE_OUT)
	{

	}

	// �Q���l���̐ݒ�
	CStartLocation::SetjoinPlayer(nJoinPlayer);

#ifdef _DEBUG
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		// ����
		pCamera->Control();
	}

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CDebrisSpawner::Create(D3DXVECTOR3(0.0f, 100.0f, -400.0f), CDebrisSpawner::TYPE::TYPE_EXPLOSION, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	CDebugProc::GetInstance()->Print("\n�Q���l��[%d]\n", nJoinPlayer);
#endif
}

//=====================================================
// �Đݒ�
//=====================================================
void CSelect::ReSetContainer(void)
{
	for (int nCnt = 0; nCnt < MAX_CONTAINER; nCnt++)
	{
		if (m_apContainer[nCnt]->GetState() == CContainer::STATE_END)
		{
			m_apContainer[nCnt] = nullptr;
		}

		if (m_apContainer[nCnt] == nullptr)
		{
			m_apContainer[nCnt] = CContainer::Create();

			switch (nCnt)
			{
			case 0:
				m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(130.0f, 0.0f, -250.0f));
				break;
			case 1:
				m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(-130.0f, 0.0f, -250.0f));
				break;
			case 2:
				m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(130.0f, 0.0f, -300.0f));
				break;
			case 3:
				m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(-130.0f, 0.0f, -300.0f));
				break;
			case 4:
				m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(130.0f, 0.0f, -350.0f));
				break;
			case 5:
				m_apContainer[nCnt]->SetPosition(D3DXVECTOR3(-130.0f, 0.0f, -350.0f));
				break;
			default:
				assert(("�R���e�i�ݒ�̎��s(select.cpp)", false));
				break;
			}
		}
	}
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
		if (m_abEntry[nPlayer] == true || m_apPlayerData[nPlayer].pPlayer != nullptr || m_pPlayerManager == nullptr)
		{
			return;
		}

		// �T�E���h�C���X�^���X�̎擾
		CSound* pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(pSound->LABEL_SE_APPEARE);
		}

		// �Q������
		m_abEntry[nPlayer] = true;
		m_apPlayerData[nPlayer].state = PLAYER_ENTRY;

		// �v���C���[�𐶐�
		m_apPlayerData[nPlayer].pPlayer = m_pPlayerManager->BindPlayer(nPlayer);

		// �ʒu��UI�̏ꏊ��
		m_apPlayerData[nPlayer].pPlayer->SetPosition(D3DXVECTOR3(
			m_aMenuData[nPlayer].pMenu2D[MENU_PLUS]->GetPosition().x,
			SPOWN_HEIGHT,
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
	if (m_apPlayerData[nPlayer].pPlayer == nullptr)
	{
		return;
	}

	// ���̎擾
	D3DXVECTOR3 pos = m_apPlayerData[nPlayer].pPlayer->GetPosition();
	D3DXVECTOR3 move = m_apPlayerData[nPlayer].pPlayer->GetMove();

	move.y -= GRAVITY;

	if (pos.z < -470.0f)
	{
		pos.z = -470.0f;
	}

	if (pos.y <= 0.0f)
	{
		pos.y = 0.0f;
		move.y = 0.0f;
	}

	//���̔��f
	m_apPlayerData[nPlayer].pPlayer->SetPosition(pos);
	m_apPlayerData[nPlayer].pPlayer->SetMove(move);
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