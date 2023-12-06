//=========================================================
//
// �Q�[���I�[�o�[���� [gameover.cpp]
// Author = �����đ�Y
//
//=========================================================

//===============================================
// �C���N���[�h
//===============================================
#include "gameover.h"
#include "enemyManager.h"
#include "playerManager.h"
#include "particle.h"
#include "scene.h"
#include "fade.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "camera.h"
#include "manager.h"
#include "goalTimer.h"
#include "UIManager.h"
#include "goal.h"
#include "texture.h"
#include "game.h"

//===============================================
// �萔��`
//===============================================
namespace
{
	// �v���C���[�̑̂̃p�X
	const char* PLAYER_BODY_PATH[NUM_PLAYER] =
	{
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman02.txt",
		"data\\MOTION\\motionPotatoman03.txt",
		"data\\MOTION\\motionPotatoman04.txt"
	};

	// �v���C���[�̈ʒu
	const D3DXVECTOR3 PLAYER_POS[NUM_PLAYER] =
	{
		D3DXVECTOR3(150.0f, 0.0f, 100.0f),
		D3DXVECTOR3(200.0f, 0.0f, 100.0f),
		D3DXVECTOR3(250.0f, 0.0f, 100.0f),
		D3DXVECTOR3(100.0f, 0.0f, 100.0f)
	};

	// �v���C���[�̌���
	const D3DXVECTOR3 PLAYER_ROT[NUM_PLAYER] =
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.15f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.15f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.10f, 0.0f)
	};

	// �G�̑̂̃p�X
	const char* ENEMY_BODY_PATH = "data\\MOTION\\motionEnemy00.txt";

	// �G�̈ʒu
	const D3DXVECTOR3 ENEMY_POS[NUM_ENEMY] =
	{
		D3DXVECTOR3(170.0f, 0.0f, 200.0f),
	};

	// �G�̌���
	const D3DXVECTOR3 ENEMY_ROT[NUM_ENEMY] =
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
	};

	// ���_�J�����̈ʒu
	const D3DXVECTOR3 CAMERA_POSV = D3DXVECTOR3(170.0f, 120.0f, -50.0f);

	// �����_�J�����̈ʒu
	const D3DXVECTOR3 CAMERA_POSR = D3DXVECTOR3(170.0f, -50.0f, 300.0f);

	// �Q�[���I�[�o�[�̃e�N�X�`���̃p�X
	const char* LOGO_PATH = "data\\TEXTURE\\UI\\start_game.png";

	// �Q�[���I�[�o�[�̉���
	const float LOGO_WIDTH = 300.0f;

	// �Q�[���I�[�o�[�̏c��
	const float LOGO_HEIGHT = 100.0f;

	// �Q�[���I�[�o�[�̈ʒu
	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f);
}

//===============================================
// �ÓI�����o�ϐ��錾
//===============================================
CGameover* CGameover::m_pGameover = nullptr;	// ���g�̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CGameover::CGameover()
{
	// �l�̃N���A
	ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
	ZeroMemory(&m_apModelEnemy[0], sizeof(m_apModelEnemy));
	m_pLogo = nullptr;
}

//===============================================
// �f�X�g���N�^
//===============================================
CGameover::~CGameover()
{
	
}

//===============================================
// ��������
//===============================================
CGameover *CGameover::Create(int nPriority)
{
	if (m_pGameover == nullptr)
	{
		// �Q�[���I�[�o�[�̐���
		m_pGameover = new CGameover;

		if (m_pGameover != nullptr)
		{
			// ����������
			m_pGameover->Init();
		}
		else if (m_pGameover == nullptr)
		{
			return nullptr;
		}
	}

	return m_pGameover;
}

//===============================================
// ����������
//===============================================
HRESULT CGameover::Init()
{
	// �C���X�^���X���擾
	CEnemyManager* pEnemyManager = CEnemyManager::GetInstance();
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();
	CGame* pGame = CGame::GetInstance();

	if (pEnemyManager != nullptr)
	{
		// �擪�I�u�W�F�N�g����
		CEnemy* pEnemy = pEnemyManager->GetHead();

		// ���ݏo�����Ă���G���폜
		while (pEnemy != nullptr)
		{
			// ���̃A�h���X��ۑ�
			CEnemy* pEnemyNext = pEnemy->GetNext();

			// �G�t�F�N�g�𐶐�
			//CParticle::Create(pEnemy->GetPosition(), CParticle::TYPE_EXPLOSION);

			// �I������
			pEnemy->Uninit();

			// ���̃A�h���X����
			pEnemy = pEnemyNext;
		}

		// �Q�[���I�[�o�[��Ԃɂ��ēG�̃X�|�[�����~����
		if (pGame != nullptr)
		{
			pGame->SetState(CGame::STATE_GAMEOVER);
		}

		// �G�𐶐�
		for (int nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
		{
			m_apModelEnemy[nCntEnemy] = CMotion::Create((char*)ENEMY_BODY_PATH);

			// �G�̏��̐ݒ�
			m_apModelEnemy[nCntEnemy]->SetPosition(ENEMY_POS[nCntEnemy]);	// �ʒu
			m_apModelEnemy[nCntEnemy]->SetRot(ENEMY_ROT[nCntEnemy]);		// ����
			m_apModelEnemy[nCntEnemy]->SetMotion(0);						// ���[�V����
		}
	}
	else if (pEnemyManager == nullptr)
	{
		return E_FAIL;
	}

	// �v���C���[�̐���
	if (pPlayerManager != nullptr)
	{
		// �v���C���[�����񂾂Ƃ���player�Ȃǂ��琔���擾

		//int nNumPlayer = pPlayerManager->GetNumPlayer();
		int nNumPlayer = 4;

		if (nNumPlayer >= 0)
		{
			for (int nCntPlayer = 0; nCntPlayer < nNumPlayer; nCntPlayer++)
			{
				m_apModelPlayer[nCntPlayer] = CMotion::Create((char*)PLAYER_BODY_PATH[nCntPlayer]);	// ����

				// �v���C���[�̏��̐ݒ�
				m_apModelPlayer[nCntPlayer]->SetPosition(PLAYER_POS[nCntPlayer]);	// �ʒu
				m_apModelPlayer[nCntPlayer]->SetRot(PLAYER_ROT[nCntPlayer]);		// ����
				m_apModelPlayer[nCntPlayer]->SetMotion(5);							// ���[�V����
			}
		}
	}
	else if (pPlayerManager == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CGameover::Uninit(void)
{
	m_pGameover = nullptr;

	delete this;
}

//===============================================
// �X�V����
//===============================================
void CGameover::Update(void)
{
	// �C���X�^���X���擾
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();
	CCamera* pCamera = CManager::GetCamera();
	CGoalTimer* pGoalTimer = CGoalTimer::GetInstance();
	CUIManager* pUIManager = CUIManager::GetInstance();
	CGoal* pGoal = CGoal::GetInstance();

	// UI���\��
	if (pUIManager != nullptr)
	{
		pUIManager->EnableDisp(false);
	}
	if (pGoal != nullptr)
	{
		pGoal->Uninit();
	}

	// �J���������P�b�g�t�߂ֈړ�
	if (pCamera != nullptr)
	{
		// �J�����̐ݒ�
		pCamera->UpdateGameover(CAMERA_POSV, CAMERA_POSR);
	}

	// �Q�[���I�[�o�[�̕\��
	if (m_pLogo == nullptr)
	{
		m_pLogo = CObject2D::Create(7);
	}

	if (m_pLogo != nullptr)
	{
		m_pLogo->SetSize(LOGO_WIDTH, LOGO_HEIGHT);
		m_pLogo->SetPosition(LOGO_POS);
		int nIdx = CTexture::GetInstance()->Regist(LOGO_PATH);
		m_pLogo->SetIdxTexture(nIdx);
		m_pLogo->SetVtx();
	}

	CFade* pFade = CFade::GetInstance();

	if (pKeyboard->GetTrigger(DIK_RETURN) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{//ENTER�L�[�������ꂽ��
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);	// �����L���O�ɑJ��

			// �v���C���[�}�l�[�W���[�̏I��
			CPlayerManager *pPlayerManger = CPlayerManager::GetInstance();

			if (pPlayerManger != nullptr)
			{
				pPlayerManger->Uninit();
			}
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CGameover::Draw(void)
{
	
}