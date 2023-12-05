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

//===============================================
// �萔��`
//===============================================
namespace
{
	// �G�̑̂̃p�X
	const char* PLAYER_BODY_PATH[NUM_PLAYER] =
	{
		"data\\MOTION\\motionPotatoman01.txt",
		"data\\MOTION\\motionPotatoman02.txt",
		"data\\MOTION\\motionPotatoman03.txt",
		"data\\MOTION\\motionPotatoman04.txt",
	};

	// �v���C���[�̈ʒu
	const D3DXVECTOR3 PLAYER_POS[NUM_PLAYER] =
	{
		D3DXVECTOR3(0.0f, 0.0f, -150.0f),
		D3DXVECTOR3(-125.0f, 0.0f, -100.0f),
		D3DXVECTOR3(100.0f, 0.0f,  -50.0f),
		D3DXVECTOR3(-75.0f, 0.0f,  100.0f),
	};

	// �v���C���[�̌���
	const D3DXVECTOR3 PLAYER_ROT[NUM_PLAYER] =
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.25f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * -0.10f, 0.0f),
	};

	// �G�̑̂̃p�X
	const char* ENEMY_BODY_PATH = "data\\MOTION\\motionEnemy00.txt";

	// �G�̈ʒu
	const D3DXVECTOR3 ENEMY_POS[NUM_ENEMY] =
	{
		D3DXVECTOR3(0.0f, 0.0f, -150.0f),
	};

	// �G�̌���
	const D3DXVECTOR3 ENEMY_ROT[NUM_ENEMY] =
	{
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
	};
}

//===============================================
// �ÓI�����o�ϐ�
//===============================================

//===============================================
// �R���X�g���N�^
//===============================================
CGameover::CGameover()
{
	// �l�̃N���A
	ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
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
	CGameover *pGameover;

	// �Q�[���I�[�o�[�̐���
	pGameover = new CGameover;

	if (pGameover != nullptr)
	{
		// ����������
		pGameover->Init();
	}
	else if(pGameover == nullptr)
	{
		return nullptr;
	}

	return pGameover;
}

//===============================================
// ����������
//===============================================
HRESULT CGameover::Init()
{
	// �C���X�^���X���擾
	CEnemyManager* pEnemyManager = CEnemyManager::GetInstance();
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();

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
	
}

//===============================================
// �X�V����
//===============================================
void CGameover::Update(void)
{
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	// �J���������P�b�g�t�߂ֈړ�



	// �Q�[���I�[�o�[�̕\��

	CFade* pFade = CFade::GetInstance();

	if (pKeyboard->GetTrigger(DIK_RETURN) ||
		pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, 0))
	{//ENTER�L�[�������ꂽ��
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);	// �����L���O�ɑJ��
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CGameover::Draw(void)
{
	
}

//===============================================
// �ݒ菈��
//===============================================
void CGameover::Set(const D3DXVECTOR3 pos, const bool bMove)
{
	
}