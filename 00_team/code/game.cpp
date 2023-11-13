//*****************************************************
//
// �Q�[������[game.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "game.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputManager.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "scene.h"
#include "debugproc.h"
#include <stdio.h>
#include "UIManager.h"
#include "object3D.h"
#include "playerManager.h"
#include "texture.h"
#include "skybox.h"
#include "item.h"
#include "weaponManager.h"
#include "enemyManager.h"
#include "goal.h"
#include "edit.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define TRANS_TIME	(60)	// �I���܂ł̗]�C�̃t���[����

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CGame::STATE CGame::m_state = STATE_NONE;	// ���
CGame *CGame::m_pGame = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CGame::CGame()
{
	m_nCntState = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGame::~CGame()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_state = STATE_NORMAL;
	m_bStop = false;

	// UI�}�l�[�W���[�̒ǉ�
	CUIManager::Create();

	CObject3D *pObject = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\field00.jpg");
	pObject->SetIdxTexture(nIdx);

	CSkybox::Create();

	// �v���C���[�̐���
	CPlayerManager *pPlayerManger = CPlayerManager::Create();

	if (pPlayerManger != nullptr)
	{
		pPlayerManger->CreatePlayer(1);
	}

	// ����}�l�[�W���[�̐���
	CWeaponManager::Create();

	// �A�C�e��
	CItem *pItem = CItem::Create(CItem::TYPE_MAGNUM);
	pItem->SetPosition(D3DXVECTOR3(0.0f,0.0f,-40.0f));

	pItem = CItem::Create(CItem::TYPE_MACHINEGUN);
	pItem->SetPosition(D3DXVECTOR3(40.0f, 0.0f, -40.0f));

	// �G�}�l�[�W���[�̐���
	CEnemyManager *pEnemyManager = CEnemyManager::Create();

	// �S�[���̐���
	CGoal::Create();

#ifdef _DEBUG
	// �G�f�B�b�g�̐���
	CEdit::Create();
#endif

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CGame::Uninit(void)
{
	// �I�u�W�F�N�g�S��
	CObject::ReleaseAll();

	m_pGame = nullptr;
}

//=====================================================
// �X�V����
//=====================================================
void CGame::Update(void)
{
	CFade *pFade = CFade::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (m_bStop == false)
	{
		// �V�[���̍X�V
		CScene::Update();
	}
	else
	{
		// �G�f�B�b�g�̍X�V
		CEdit* pEdit = CEdit::GetInstatnce();
		pEdit->Update();
	}

	// �J�����X�V
	UpdateCamera();

	// ��ԊǗ�
	ManageState();

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// �J�����̍X�V
//=====================================================
void CGame::UpdateCamera(void)
{
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	if (m_bStop == false)
	{
		if (m_state == STATE_NORMAL)
		{
			// ����
			pCamera->FollowPlayer();
		}
	}
	else
	{
		// ����
		pCamera->Control();
	}
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CGame::ManageState(void)
{
	CFade *pFade = CFade::GetInstance();

	switch (m_state)
	{
	case CGame::STATE_NORMAL:
		break;
	case CGame::STATE_END:

		m_nCntState++;

		if (m_nCntState >= TRANS_TIME && pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// �f�o�b�O����
//=====================================================
void CGame::Debug(void)
{
	// ���͎擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
	{
		return;
	}

	if (pKeyboard->GetTrigger(DIK_F))
	{
		m_bStop = m_bStop ? false : true;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CGame::Draw(void)
{

}