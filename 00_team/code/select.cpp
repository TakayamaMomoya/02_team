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
#include "model.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"
#include "object2D.h"
#include "objectX.h"
#include "billboard.h"
#include "object3D.h"
#include "playerManager.h"
#include "player.h"
#include "sound.h"

#include "debrisSpawner.h"
#include "debris.h"

#include "lift.h"

#include "container.h"
#include "weaponManager.h"

#include "edit.h"
#include "animEffect3D.h"

#include <stdio.h>

//*****************************************************
// �}�N����`
//*****************************************************
namespace
{
	const D3DXVECTOR3 UI_POS_1P({ -150.0f, 80.0f, -430.0f });	// UI�̈ʒu
	const D3DXVECTOR3 UI_SPACE({ 140.0f, 0.0f, 0.0f });	// UI�Ԃ̊Ԋu

	const float SPOWN_HEIGHT(-100.0f);	//�v���C���[�o������

	const float SPACE(-50.0f);	//UI�Ԃ̍L��
	const float SIZE_PLUS(20.0f);	//UI�̑傫��(+)
	const D3DXVECTOR2 SIZE_FONT(30.0f, 10.0f);	//UI�̑傫��(�Q���FA)
	const float BLINKING_SPEED(0.02f);	//UI�_�ł̑���(�Q���FA)
	const float ADULTWALL_POS_Z(-470.0f);
	const float GRAVITY(5.0f);	//�d��

	const D3DXVECTOR3 CONTAINER_POS({ -150.0, 0.0, -130.0f });	// �R���e�i�̈ʒu
	const D3DXVECTOR3 CONTAINER_SPACE({ 400.0, 0.0, -50.0f });	// �R���e�i�Ԃ̍L��
	const float RESPAWN_TIME(10.0f);	// �R���e�i�����̎���

	const float RIFT_IN(100.0f);	// ���t�g�͈̔�
	const float LIFT_UP(2.0f);	// ���t�g�㏸���x
};

//=====================================================
// �R���X�g���N�^
//=====================================================
CSelect::CSelect()
{
	ZeroMemory(&m_apPlayerData[0], sizeof(CSelect::PlayerInfo));
	ZeroMemory(&m_aContainerData[0], sizeof(CSelect::CContainerInfo));
	m_pStartUI = nullptr;
	m_pPlayerManager = nullptr;
	m_pLift = nullptr;
	m_bRiftCamera = false;
	m_bOk = false;
	m_selectState = SELECT_STATE::STATE_BEFORE;
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

	int nIdx = 0;

	// �v���C���[�}�l�[�W���[�̐���
	m_pPlayerManager = CPlayerManager::Create();

	MenuInit();
	StartInit();
	ContainerInit();

	// �G�f�B�b�g�̐���
	CEdit::Create();

	// �u���b�N�̓ǂݍ���
	CBlock::Load("data\\MAP\\select_map00.bin");

	// �|�e�g�̐Q���̐���
	CObjectX* pObjectX = CObjectX::Create({ 58.0f, 0.5f, -430.5f });
	pObjectX->BindModel(CModel::Load("data\\MODEL\\select\\potato_bed.x"));

	//�n�ʂ̐���
	CObject3D* pObject = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\wood001.jpg");
	pObject->SetIdxTexture(nIdx);
	pObject->SetPosition(D3DXVECTOR3(55.0f, 0.0f, -280.0f));
	pObject->SetSize(300.0f, 300.0f);

	// �J�n�ʒu
	m_pLift = CLift::Create(D3DXVECTOR3(30.0f, 0.5f, 100.0f));
	
	// �T�E���h�C���X�^���X�̎擾
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(pSound->LABEL_BGM_SELECT);
	}

	// �RD�A�j���[�V�����Ǘ��̐���
	CAnimEffect3D::Create();

	// �R���e�i�̃��X�|�[�����Ԃ�ݒ�
	for (int nCnt = 0; nCnt < MAX_CONTAINER; nCnt++)
	{
		m_aContainerData[nCnt].fReSpawnTimer = RESPAWN_TIME;
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

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		// �����̐���
		m_aJoinUiData[nCnt].pUi2D[MENU_PLUS] = CBillboard::Create
		(
			{ // �ʒu
				UI_POS_1P.x + (nCnt * UI_SPACE.x),
				UI_POS_1P.y,
				UI_POS_1P.z 
			},
			// �T�C�Y
			SIZE_PLUS, SIZE_PLUS
		);

		m_aJoinUiData[nCnt].pUi2D[MENU_PLUS]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aJoinUiData[nCnt].pUi2D[MENU_PLUS]->SetIdxTexture(CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\plus.png"));

		// �����̐���
		m_aJoinUiData[nCnt].pUi2D[MENU_CHAR] = CBillboard::Create
		(
			{ // �ʒu
				m_aJoinUiData[nCnt].pUi2D[MENU_PLUS]->GetPosition().x,
				m_aJoinUiData[nCnt].pUi2D[MENU_PLUS]->GetPosition().y + SPACE,
				m_aJoinUiData[nCnt].pUi2D[MENU_PLUS]->GetPosition().z
			},
			// �T�C�Y
			SIZE_FONT.x, SIZE_FONT.y
		);

		// ����
		m_aJoinUiData[nCnt].pUi2D[MENU_CHAR]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aJoinUiData[nCnt].pUi2D[MENU_CHAR]->SetIdxTexture(CTexture::GetInstance()->Regist(apPath[nCnt]));

		// 
		m_aJoinUiData[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aJoinUiData[nCnt].state = FADE_OUT;
	}
}

//=====================================================
// �X�^�[�g�̏���������
//=====================================================
void CSelect::StartInit(void)
{
	//m_pStartUI = CObject2D::Create();
	//m_pStartUI->SetPosition(D3DXVECTOR3(1100.0f, 650.0f, 0.0f));
	//m_pStartUI->SetSize(150.0f, 50.0f);
	//m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\start_game.png");
	//m_pStartUI->SetIdxTexture(nIdx);

	//m_pStartUI->SetVtx();
}

//=====================================================
// �R���e�i�̏���������
//=====================================================
void CSelect::ContainerInit(void)
{
	// ����}�l�[�W���̐���
	CWeaponManager::Create();

	for (int nCnt = 0; nCnt < MAX_CONTAINER; nCnt++)
	{
		// �R���e�i�̐���
		m_aContainerData[nCnt].pContainer = CContainer::Create();

		// �ʒu�ݒ�
		if (nCnt % 2 == 0)
		{
			m_aContainerData[nCnt].pContainer->SetPosition(D3DXVECTOR3
			(
				CONTAINER_POS.x,
				0.0f, 
				CONTAINER_POS.z + (nCnt * CONTAINER_SPACE.z))
			);
		}
		else
		{
			m_aContainerData[nCnt].pContainer->SetPosition(D3DXVECTOR3
			(
				CONTAINER_POS.x + CONTAINER_SPACE.x,
				0.0f + +CONTAINER_SPACE.y,
				CONTAINER_POS.z + (nCnt * CONTAINER_SPACE.z))
			);
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

	int nJoinPlayer = 0;

	// �V�[���̍X�V
	CScene::Update();

	CFade* pFade = CFade::GetInstance();

	if (m_selectState == SELECT_STATE::STATE_BEFORE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr)
		{
			if (CLift::GetIsIn() == true)
			{// �Q�����̑S�����͈͓��ɓ������Ƃ��������������

				if (pKeyboard->GetTrigger(DIK_RETURN) ||
					pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
					pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0))
				{// �t�F�[�h

					for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
					{
						if (m_abEntry[nCntPlayer] == true)
						{
							m_apPlayerData[nCntPlayer].state = PLAYER_INGAME;
						}
					}
					m_bOk = true;

					if (pFade != nullptr && m_abEntry[0] != false)
					{
						pFade->SetFade(CScene::MODE_GAME);
					}
				}

				// StartUI��������悤��
				/*m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_pStartUI->SetVtx();*/
			}
			else
			{
				// Start��UI�������Ȃ��悤��
				/*m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_pStartUI->SetVtx();*/
			}
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		if (m_aJoinUiData[nCntPlayer].pUi2D[MENU_CHAR] != nullptr && m_aJoinUiData[nCntPlayer].pUi2D[MENU_PLUS] != nullptr)
		{	
			// �F�̕ύX
			MenuColorChange(nCntPlayer);
			// �Q������
			EntryInput(nCntPlayer);
		}

		if (m_abEntry[nCntPlayer] == true)
		{
			// �v���C���[�Q��̏���
			PlayerShowUp(nCntPlayer);

			// �s������
			MoveLimit(nCntPlayer);

			nJoinPlayer++;
		}
	}

		Rift();
		// �R���e�i�̍Đݒu
		ReSetContainer();
	

	// �Q���l���̐ݒ�
	CLift::SetjoinPlayer(nJoinPlayer);

#ifdef _DEBUG
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		// ����
		pCamera->Control();
	}

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CDebrisSpawner::Create(D3DXVECTOR3(0.0f, 100.0f, -400.0f), CDebrisSpawner::TYPE::TYPE_WALL, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
		if (m_aContainerData[nCnt].pContainer != nullptr)
		{
			if (m_aContainerData[nCnt].pContainer->GetState() == CContainer::STATE_END)
			{
				m_aContainerData[nCnt].pContainer = nullptr;
				m_aContainerData[nCnt].fReSpawnTimer = RESPAWN_TIME;
			}
		}

		if (m_aContainerData[nCnt].pContainer == nullptr)
		{
			// �o�ߎ��Ԏ擾
			float fTick = CManager::GetTick();

			m_aContainerData[nCnt].fReSpawnTimer -= fTick;

			if (m_aContainerData[nCnt].fReSpawnTimer > 0)
			{
				continue;
			}

			// �R���e�i����
			m_aContainerData[nCnt].pContainer = CContainer::Create();

			if (m_aContainerData[nCnt].pContainer == nullptr)
			{
				continue;
			}

			// �ʒu�ݒ�
			if (nCnt % 2 == 0)
			{
				m_aContainerData[nCnt].pContainer->SetPosition(D3DXVECTOR3
				(
					CONTAINER_POS.x,
					0.0f,
					CONTAINER_POS.z + (nCnt * CONTAINER_SPACE.z))
				);
			}
			else
			{
				m_aContainerData[nCnt].pContainer->SetPosition(D3DXVECTOR3
				(
					CONTAINER_POS.x + CONTAINER_SPACE.x,
					0.0f + +CONTAINER_SPACE.y,
					CONTAINER_POS.z + (nCnt * CONTAINER_SPACE.z))
				);
			}
		}
	}
}

//=====================================================
// UI�_��
//=====================================================
void CSelect::MenuColorChange(int nPlayer)
{
	if (m_aJoinUiData[nPlayer].state == FADE_IN)
	{//�t�F�[�h�C�����
		m_aJoinUiData[nPlayer].col.a -= BLINKING_SPEED;			//�|���S���𓧖��ɂ��Ă���

		if (m_aJoinUiData[nPlayer].col.a <= 0.0f)
		{
			m_aJoinUiData[nPlayer].col.a = 0.0f;

			m_aJoinUiData[nPlayer].state = FADE_OUT;
		}
	}
	else if (m_aJoinUiData[nPlayer].state == FADE_OUT)
	{//�t�F�[�h�A�E�g���
		m_aJoinUiData[nPlayer].col.a += BLINKING_SPEED;			//�|���S����s�����ɂ��Ă���

		if (m_aJoinUiData[nPlayer].col.a >= 1.0f)
		{
			m_aJoinUiData[nPlayer].col.a = 1.0f;

			m_aJoinUiData[nPlayer].state = FADE_IN;
		}
	}

	// �F�̐ݒ�
	m_aJoinUiData[nPlayer].pUi2D[MENU_CHAR]->SetColor(m_aJoinUiData[nPlayer].col);
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

		// �Q����Ԃ�
		m_abEntry[nPlayer] = true;
		m_apPlayerData[nPlayer].state = PLAYER_ENTRY;

		// �v���C���[�𐶐�
		m_apPlayerData[nPlayer].pPlayer = m_pPlayerManager->BindPlayer(nPlayer);

		// �ʒu��UI�̏ꏊ��
		m_apPlayerData[nPlayer].pPlayer->SetPosition(D3DXVECTOR3(
			m_aJoinUiData[nPlayer].pUi2D[MENU_PLUS]->GetPosition().x,
			SPOWN_HEIGHT,
			m_aJoinUiData[nPlayer].pUi2D[MENU_PLUS]->GetPosition().z));

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
	CCamera* pCamera = CManager::GetCamera();

	// ��l�̕ǔ���
	if (m_apPlayerData[nPlayer].state != PLAYER_INGAME)
	{
		// �d��
		move.y -= GRAVITY;

		if (pos.z < ADULTWALL_POS_Z)
		{
			pos.z = ADULTWALL_POS_Z;
		}
	}
	else
	{
		/*if (m_pLift->GetPosition().x + RIFT_IN >= pos.x)
		{
			pos.x = RIFT_IN - 1.0f;
		}
		if (m_pLift->GetPosition().x - RIFT_IN <= pos.x)
		{
			pos.x = RIFT_IN;
		}
		if (m_pLift->GetPosition().z + RIFT_IN >= pos.z)
		{
			pos.z = RIFT_IN;
		}
		if (m_pLift->GetPosition().z - RIFT_IN <= pos.z)
		{
			pos.z = -RIFT_IN;
		}*/
	}

	if (m_apPlayerData[nPlayer].state != PLAYER_ENTRY)
	{
		// ������
		if (pos.y <= 0.0f)
		{
			pos.y = 0.0f;
			move.y = 0.0f;
		};
	}

	//���̔��f
	
	m_apPlayerData[nPlayer].pPlayer->SetPosition(pos);
	m_apPlayerData[nPlayer].pPlayer->SetMove(move);
}

//=====================================================
// �v���C���[�̓o��
//=====================================================
void CSelect::PlayerShowUp(int nPlayer)
{
	if (m_apPlayerData[nPlayer].pPlayer == nullptr)
	{
		return;
	}

	if (m_apPlayerData[nPlayer].state != PLAYER_ENTRY)
	{
		return;
	}

	// ���̎擾
	D3DXVECTOR3 pos = m_apPlayerData[nPlayer].pPlayer->GetPosition();
	D3DXVECTOR3 move = m_apPlayerData[nPlayer].pPlayer->GetMove();

	if (pos.y >= 100.0f)
	{
		m_apPlayerData[nPlayer].state = PLAYER_FREE;
	}

	pos.y += 10.0f;

	m_apPlayerData[nPlayer].pPlayer->SetPosition(pos);
}

//=====================================================
// ���t�g
//=====================================================
void CSelect::Rift(void)
{
	if (m_bOk == true)
	{
		CCamera* pCamera = CManager::GetCamera();

		D3DXVECTOR3 rift = m_pLift->GetPosition();
		rift.y += LIFT_UP;
		m_pLift->SetPosition(rift);

		if (m_bRiftCamera == false)
		{
			pCamera->SetLift();
			m_bRiftCamera = true;
		}
		else
		{
			pCamera->SetUpLift();
		}

		for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
		{
			if (m_abEntry[nCnt] == true)
			{
				D3DXVECTOR3 pos = m_apPlayerData[nCnt].pPlayer->GetPosition();
				D3DXVECTOR3 move = m_apPlayerData[nCnt].pPlayer->GetMove();

				pos = m_apPlayerData[nCnt].pPlayer->GetPosition();
				pos.y += LIFT_UP;
				m_apPlayerData[nCnt].pPlayer->SetPosition(pos);
			}
		}
	}
}

//=====================================================
// ���j���[����������
//=====================================================
void CSelect::MenuDelete(int nPlayer)
{
	for (int nCntMenu = 0; nCntMenu < MENU_MAX; nCntMenu++)
	{
		m_aJoinUiData[nPlayer].pUi2D[nCntMenu]->Uninit();
		m_aJoinUiData[nPlayer].pUi2D[nCntMenu] = nullptr;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CSelect::Draw(void)
{

}