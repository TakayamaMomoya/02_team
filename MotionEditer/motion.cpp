//*****************************************************
//
// ���[�V�����̏���[motion.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "motion.h"
#include "model.h"
#include <stdio.h>
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "particle.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MAX_STRING	(256)	// ������̍ő吔
#define ROLL_SPEED	(0.01f)	// �p�[�c����鑬�x
#define MOVE_SPEED	(0.1f)	// �p�[�c�������X�s�[�h
#define NUM_DISP	(10)	// ����\������p�[�c��

//=====================================================
// �R���X�g���N�^
//=====================================================
CMotion::CMotion()
{
	ZeroMemory(&m_aMotionInfo, sizeof(m_aMotionInfo));
	ZeroMemory(&m_aKeyOld, sizeof(m_aKeyOld));
	ZeroMemory(&m_apParts[0], sizeof(m_apParts));
	m_bLoopMotion = false;
	m_motionType = 0;
	m_motionTypeOld = 0;
	m_nCounterMotion = 0;
	m_nKey = 0;
	m_nNumKey = 0;
	m_nNumMotion = 0;
	m_nNumParts = 0;
	m_nIdxParts = 0;
	m_bMotion = false;
	m_bSetUp = false;

	for (int nCntMotion = 0; nCntMotion < m_nNumMotion; nCntMotion++)
	{
		m_aMotionInfo[nCntMotion].pParticle = NULL;
	}
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMotion::~CMotion()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CMotion::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMotion::Uninit(void)
{
	for (int nCntMotion = 0; nCntMotion < m_nNumMotion; nCntMotion++)
	{
		if (m_aMotionInfo[nCntMotion].pParticle != NULL)
		{
			delete m_aMotionInfo[nCntMotion].pParticle;
			m_aMotionInfo[nCntMotion].pParticle = NULL;
		}
	}

	Release();
}

//=====================================================
// ���Z�b�g����
//=====================================================
void CMotion::Reset(void)
{
	for (int nCntParts = 0;nCntParts < m_nNumParts;nCntParts++)
	{
		m_apParts[nCntParts]->m_pParts->SetRot(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}
}

//=====================================================
// �X�V����
//=====================================================
void CMotion::Update(void)
{
	// ���͏�����
	CInputMouse *pMouse = CManager::GetMouse();
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (m_bSetUp)
	{
		m_bMotion = false;
	}

	if (m_bMotion)
	{
		Motion();
	}

	if (pMouse->GetPress(CInputMouse::BUTTON_RMB) == false)
	{// ���͏���
		Input();
	}

	if (pKeyboard->GetTrigger(DIK_F7))
	{// �ۑ�
		SaveMotion();
	}

	DrawMotionState();
}

//=====================================================
// ����
//=====================================================
void CMotion::Input(void)
{
	// �ϐ��錾
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	// ���͏�����
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F2))
	{// ���[�V�������邩�̐؂�ւ�
		m_bMotion = m_bMotion ? false : true;
	}

	if (pKeyboard->GetTrigger(DIK_F3))
	{// �Z�b�g�A�b�v���邩�̐؂�ւ�
		if (m_bSetUp)
		{
			m_bSetUp = false;
		}
		else
		{
			Reset();
			m_bSetUp = true;
		}
	}

	// �I��============================================
	if (pKeyboard->GetTrigger(DIK_UP))
	{// �p�[�c�̑I��
		m_apParts[m_nIdxParts]->m_pParts->SetCurrent(false);

		m_nIdxParts = (m_nIdxParts + m_nNumParts - 1) % m_nNumParts;

		m_apParts[m_nIdxParts]->m_pParts->SetCurrent(true);
	}
	else if (pKeyboard->GetTrigger(DIK_DOWN))
	{
		m_apParts[m_nIdxParts]->m_pParts->SetCurrent(false);

		m_nIdxParts = (m_nIdxParts + 1) % m_nNumParts;

		m_apParts[m_nIdxParts]->m_pParts->SetCurrent(true);
	}

	if (m_bSetUp)
	{// �Z�b�g�A�b�v���ǂ���
		if (pKeyboard->GetPress(DIK_W))
		{// �O�i
			pos.z += MOVE_SPEED;
		}
		if (pKeyboard->GetPress(DIK_A))
		{// ��
			pos.x -= MOVE_SPEED;
		}
		if (pKeyboard->GetPress(DIK_D))
		{// �E
			pos.x += MOVE_SPEED;
		}
		if (pKeyboard->GetPress(DIK_S))
		{// ��O
			pos.z -= MOVE_SPEED;
		}

		if (pKeyboard->GetPress(DIK_E))
		{// ��
			pos.y += MOVE_SPEED;
		}
		if (pKeyboard->GetPress(DIK_Q))
		{// ��
			pos.y -= MOVE_SPEED;
		}

		if (pKeyboard->GetPress(DIK_LSHIFT))
		{// ��
			pos *= 5;
		}

		// �ʒu�ݒ�
		m_apParts[m_nIdxParts]->m_pParts->SetPosOrg(m_apParts[m_nIdxParts]->m_pParts->GetPosOrg() + pos);
		m_apParts[m_nIdxParts]->m_pParts->SetPosition(m_apParts[m_nIdxParts]->m_pParts->GetPosOrg());
	}
	else
	{// ���[�V�������[�h�̓���
		if (pKeyboard->GetTrigger(DIK_RIGHT))
		{// ���[�V�����̑I��
			m_motionType = (m_motionType + 1) % m_nNumMotion;
			SetMotion(m_motionType);

			if (m_bMotion == false)
			{
				// �|�[�Y�����ݒ�
				SetPose();
			}
		}
		else if (pKeyboard->GetTrigger(DIK_LEFT))
		{
			m_motionType = (m_motionType + m_nNumMotion - 1) % m_nNumMotion;
			SetMotion(m_motionType);

			if (m_bMotion == false)
			{
				// �|�[�Y�����ݒ�
				SetPose();
			}
		}

		if (pKeyboard->GetTrigger(DIK_2))
		{// �L�[�̑I��
			m_nKey = (m_nKey + 1) % m_aMotionInfo[m_motionType].nNumKey;

			// �|�[�Y�����ݒ�
			SetPose();
		}
		else if (pKeyboard->GetTrigger(DIK_1))
		{
			m_nKey = (m_nKey + m_aMotionInfo[m_motionType].nNumKey - 1) % m_aMotionInfo[m_motionType].nNumKey;

			// �|�[�Y�����ݒ�
			SetPose();

		}
		// �I��============================================

		// �p�[�c�̓���============================================
		if (pKeyboard->GetPress(DIK_T))
		{// X����]
			rot.x += ROLL_SPEED;

			// �p�[�c�̃g�����X�t�H�[�����ꎞ�ۑ�
			SetTransform();
		}
		else if (pKeyboard->GetPress(DIK_G))
		{
			rot.x -= ROLL_SPEED;

			// �p�[�c�̃g�����X�t�H�[�����ꎞ�ۑ�
			SetTransform();
		}

		if (pKeyboard->GetPress(DIK_Y))
		{// Y����]
			rot.y += ROLL_SPEED;

			// �p�[�c�̃g�����X�t�H�[�����ꎞ�ۑ�
			SetTransform();
		}
		else if (pKeyboard->GetPress(DIK_H))
		{
			rot.y -= ROLL_SPEED;

			// �p�[�c�̃g�����X�t�H�[�����ꎞ�ۑ�
			SetTransform();
		}

		if (pKeyboard->GetPress(DIK_U))
		{// Z����]
			rot.z += ROLL_SPEED;

			// �p�[�c�̃g�����X�t�H�[�����ꎞ�ۑ�
			SetTransform();
		}
		else if (pKeyboard->GetPress(DIK_J))
		{
			rot.z -= ROLL_SPEED;

			// �p�[�c�̃g�����X�t�H�[�����ꎞ�ۑ�
			SetTransform();
		}
		// �p�[�c�̓���============================================
	}

	// �����ݒ�
	m_apParts[m_nIdxParts]->m_pParts->SetRot(m_apParts[m_nIdxParts]->m_pParts->GetRot() + rot);
}

//=====================================================
// ���[�V�����X�V
//=====================================================
void CMotion::Motion(void)
{
	//�ϐ��錾
	int nNextKey;

	// �p�[�c�̃g�����X�t�H�[��
	D3DXVECTOR3 pos, rot;

	if (m_aMotionInfo[m_motionType].pParticle != NULL)
	{
		for (int nCntParticle = 0; nCntParticle < m_aMotionInfo[m_motionType].nNumParticle; nCntParticle++)
		{// �S�Ẵp�[�e�B�N�����m�F
			if (m_nKey == m_aMotionInfo[m_motionType].pParticle[nCntParticle].nKey &&
				m_nCounterMotion == m_aMotionInfo[m_motionType].pParticle[nCntParticle].nFrame)
			{// �p�[�e�B�N������
			 // �e�p�[�c�̈ʒu�擾
				D3DXMATRIX *pMtx = m_apParts[m_aMotionInfo[m_motionType].pParticle[nCntParticle].nIdxParent]->m_pParts->GetMatrix();
				D3DXVECTOR3 pos = D3DXVECTOR3(pMtx->_41, pMtx->_42, pMtx->_43) + m_aMotionInfo[m_motionType].pParticle[nCntParticle].offset;

				CParticle::Create(pos, (CParticle::TYPE)m_aMotionInfo[m_motionType].pParticle[nCntParticle].nType);
			}
		}
	}

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_nKey >= m_aMotionInfo[m_motionType].nNumKey - 1)
		{
			break;
		}

		// �p�[�c�̃g�����X�t�H�[���擾
		pos = m_apParts[nCntParts]->m_pParts->GetPosOrg();
		rot = m_apParts[nCntParts]->m_pParts->GetRot();

		if (m_nKey < m_aMotionInfo[m_motionType].nNumKey - 1)
		{// ���̃L�[�ݒ�
			nNextKey = m_nKey + 1;
		}
		else
		{
			nNextKey = m_aMotionInfo[m_motionType].nNumKey - 1;
		}

		//�O��Ǝ��̃L�[�̍����擾
		float DiffPosX = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fPosX -
			m_aKeyOld[nCntParts].fPosX;

		float DiffPosY = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fPosY -
			m_aKeyOld[nCntParts].fPosY;

		float DiffPosZ = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fPosZ -
			m_aKeyOld[nCntParts].fPosZ;

		float DiffRotX = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fRotX -
			m_aKeyOld[nCntParts].fRotX;

		float DiffRotY = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fRotY -
			m_aKeyOld[nCntParts].fRotY;

		float DiffRotZ = m_aMotionInfo[m_motionType].aKeyInfo[nNextKey].aKey[nCntParts].fRotZ -
			m_aKeyOld[nCntParts].fRotZ;

		//�ړI�̒l=======================================================================================================
		float DestPosX = pos.x + m_aKeyOld[nCntParts].fPosX +
			DiffPosX * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestPosY = pos.y + m_aKeyOld[nCntParts].fPosY +
			DiffPosY * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestPosZ = pos.z + m_aKeyOld[nCntParts].fPosZ +
			DiffPosZ * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestRotX = m_aKeyOld[nCntParts].fRotX +
			DiffRotX * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestRotY = m_aKeyOld[nCntParts].fRotY +
			DiffRotY * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		float DestRotZ = m_aKeyOld[nCntParts].fRotZ +
			DiffRotZ * (float)(1.0f / (float)m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame) * m_nCounterMotion;

		//�p�[�c�̌����E�ʒu�ݒ�
		m_apParts[nCntParts]->m_pParts->SetPosition(D3DXVECTOR3(DestPosX, DestPosY, DestPosZ));

		m_apParts[nCntParts]->m_pParts->SetRot(D3DXVECTOR3(DestRotX, DestRotY, DestRotZ));
	}

	m_nCounterMotion++;

	if (m_nKey >= m_aMotionInfo[m_motionType].nNumKey - 1)
	{// ���[�V�������I�����Ă�����
		m_motionTypeOld = m_motionType;
		SetMotion(m_motionType);
	}

	if (m_nCounterMotion > m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].nFrame)
	{//�L�[�̃t���[�����ɒB������
		if (m_nKey < m_aMotionInfo[m_motionType].nNumKey)
		{
			m_nKey++;

			m_nCounterMotion = 0;

			SetKeyOld();
		}
	}
}

//=====================================================
// �p�[�c�̃g�����X�t�H�[���ݒ�
//=====================================================
void CMotion::SetTransform(void)
{
	// �����̐ݒ�
	m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[m_nIdxParts].fRotX = m_apParts[m_nIdxParts]->m_pParts->GetRot().x;
	m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[m_nIdxParts].fRotY = m_apParts[m_nIdxParts]->m_pParts->GetRot().y;
	m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[m_nIdxParts].fRotZ = m_apParts[m_nIdxParts]->m_pParts->GetRot().z;

	// �ʒu�̐ݒ�
	m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[m_nIdxParts].fPosX = m_apParts[m_nIdxParts]->m_pParts->GetPosition().x - m_apParts[m_nIdxParts]->m_pParts->GetPosOrg().x;
	m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[m_nIdxParts].fPosY = m_apParts[m_nIdxParts]->m_pParts->GetPosition().y - m_apParts[m_nIdxParts]->m_pParts->GetPosOrg().y;
	m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[m_nIdxParts].fPosZ = m_apParts[m_nIdxParts]->m_pParts->GetPosition().z - m_apParts[m_nIdxParts]->m_pParts->GetPosOrg().z;
}

//=====================================================
// ���`��
//=====================================================
void CMotion::DrawMotionState(void)
{
	int nIdx = m_nIdxParts;
	D3DXVECTOR3 pos, rot;

	CManager::GetDebugProc()->Print("[F2]���[�V�����Đ�");
	
	CManager::GetDebugProc()->Print("                                                 ");

	if (m_bSetUp)
	{
		CManager::GetDebugProc()->Print("���[�h[�Z�b�g�A�b�v]\n");
	}
	else
	{
		CManager::GetDebugProc()->Print("���[�h[���[�V����]\n");
	}

	CManager::GetDebugProc()->Print("[F3]�Z�b�g�A�b�v���[�h�Ɉڍs\n");
	CManager::GetDebugProc()->Print("[F7]�ۑ�[data\\motion.txt]\n");

	if (m_bSetUp)
	{
		CManager::GetDebugProc()->Print("[WASD]�p�[�c�����ړ�\n");
		CManager::GetDebugProc()->Print("[QE]�p�[�c�㉺�ړ�\n");
		CManager::GetDebugProc()->Print("[LSHIFT]����\n");
	}

	CManager::GetDebugProc()->Print("�J���������UNREAL�Ɠ���\n");

	CManager::GetDebugProc()->Print("���[�V�����Đ�[%d]\n", m_bMotion);
	CManager::GetDebugProc()->Print("�Z�b�g�A�b�v[%d]\n", m_bSetUp);
	CManager::GetDebugProc()->Print("�I���p�[�c[%d / %d]\n", m_nIdxParts, m_nNumParts - 1);
	CManager::GetDebugProc()->Print("�I�����[�V����[%d / %d]\n", m_motionType, m_nNumMotion - 1);
	CManager::GetDebugProc()->Print("�I���L�[[%d / %d]\n", m_nKey, m_aMotionInfo[m_motionType].nNumKey - 1);

	CManager::GetDebugProc()->Print("//===============================\n");
	CManager::GetDebugProc()->Print("// �p�[�c���\n");
	CManager::GetDebugProc()->Print("//===============================\n");

	for (int nCntModel = 0;nCntModel < NUM_DISP;nCntModel++)
	{// ���f�������̏��\��
		pos = m_apParts[nIdx]->m_pParts->GetPosition();
		rot = m_apParts[nIdx]->m_pParts->GetRot();

		if (nCntModel == 0)
		{
			CManager::GetDebugProc()->Print("  ");
		}
		CManager::GetDebugProc()->Print("[%d]POS %f,%f,%f\n    ROT %f,%f,%f\n",nIdx,pos.x,pos.y,pos.z,rot.x,rot.y,rot.z);

		nIdx = (nIdx + 1) % m_nNumParts;
	}
}

//=====================================================
//���[�V�����ݒ�
//=====================================================
void CMotion::SetMotion(int nMotionType)
{
	// �I�����郂�[�V������ۑ�
	m_motionTypeOld = m_motionType;
	SetKeyOld();

	// ���[�V�������̐ݒ�
	m_motionType = nMotionType;
	m_nKey = 0;
	m_nCounterMotion = 0;
}

//=====================================================
// �|�[�Y�ݒ�
//=====================================================
void CMotion::SetPose(void)
{
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	for (int nCntPart = 0; nCntPart < m_nNumParts; nCntPart++)
	{
		// �����̎擾
		rot.x = m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[nCntPart].fRotX;
		rot.y = m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[nCntPart].fRotY;
		rot.z = m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[nCntPart].fRotZ;
		// �ʒu�̎擾
		pos.x = m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[nCntPart].fPosX + m_apParts[nCntPart]->m_pParts->GetPosOrg().x;
		pos.y = m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[nCntPart].fPosY + m_apParts[nCntPart]->m_pParts->GetPosOrg().y;
		pos.z = m_aMotionInfo[m_motionType].aKeyInfo[m_nKey].aKey[nCntPart].fPosZ + m_apParts[nCntPart]->m_pParts->GetPosOrg().z;

		m_apParts[nCntPart]->m_pParts->SetRot(rot);
		m_apParts[nCntPart]->m_pParts->SetPosition(pos);
	}
}

//=====================================================
// �I������L�[�̏��ۑ�
//=====================================================
void CMotion::SetKeyOld(void)
{
	for (int nCntPart = 0;nCntPart < m_nNumParts;nCntPart++)
	{
		m_aKeyOld[nCntPart].fPosX = m_apParts[nCntPart]->m_pParts->GetPosition().x - m_apParts[nCntPart]->m_pParts->GetPosOrg().x;
		m_aKeyOld[nCntPart].fPosY = m_apParts[nCntPart]->m_pParts->GetPosition().y - m_apParts[nCntPart]->m_pParts->GetPosOrg().y;
		m_aKeyOld[nCntPart].fPosZ = m_apParts[nCntPart]->m_pParts->GetPosition().z - m_apParts[nCntPart]->m_pParts->GetPosOrg().z;

		m_aKeyOld[nCntPart].fRotX = m_apParts[nCntPart]->m_pParts->GetRot().x;
		m_aKeyOld[nCntPart].fRotY = m_apParts[nCntPart]->m_pParts->GetRot().y;
		m_aKeyOld[nCntPart].fRotZ = m_apParts[nCntPart]->m_pParts->GetRot().z;
	}
}

//=====================================================
// �}�g���b�N�X���������킹�鏈��
//=====================================================
void CMotion::MultiplyMtx(void)
{
	// �����_���[�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�ϐ��錾
	D3DXMATRIX mtxRotModel, mtxTransModel;
	D3DXMATRIX *pMtxParent;
	D3DXMATRIX *pMtx;

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntParts = 0;nCntParts < m_nNumParts;nCntParts++)
	{
		// �}�g���b�N�X�̎擾
		pMtx = m_apParts[nCntParts]->m_pParts->GetMatrix();

		//���[���h�}�g���b�N�X������
		D3DXMatrixIdentity(pMtx);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel,
			m_apParts[nCntParts]->m_pParts->GetRot().y, m_apParts[nCntParts]->m_pParts->GetRot().x, m_apParts[nCntParts]->m_pParts->GetRot().z);
		D3DXMatrixMultiply(pMtx, pMtx, &mtxRotModel);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel,
			m_apParts[nCntParts]->m_pParts->GetPosition().x, m_apParts[nCntParts]->m_pParts->GetPosition().y, m_apParts[nCntParts]->m_pParts->GetPosition().z);
		D3DXMatrixMultiply(pMtx, pMtx, &mtxTransModel);
		
		if (m_apParts[nCntParts]->nIdxParent != -1)
		{//�e�p�[�c������ꍇ
			// �e�}�g���b�N�X�̎擾
			pMtxParent = m_apParts[m_apParts[nCntParts]->nIdxParent]->m_pParts->GetMatrix();
		}
		else
		{
			pMtxParent = &m_mtxWorld;
		}

		//�e�p�[�c�ƃp�[�c�̃��[���h�}�g���b�N�X���������킹��
		D3DXMatrixMultiply(pMtx, pMtx, pMtxParent);

		//���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, pMtx);

		m_apParts[nCntParts]->m_pParts->Draw();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CMotion::Draw(void)
{
	// �}�g���b�N�X���������킹�鏈��
	MultiplyMtx();
}

//=====================================================
// �Ǎ�����
//=====================================================
void CMotion::Load(char *pPath)
{
	//�ϐ��錾
	char cTemp[MAX_STRING];
	int nCntModel = 0;

	//�t�@�C������ǂݍ���
	FILE *pFile = fopen(pPath, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			//�����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			//�t�@�C�����ǂݍ���=========================================
			if (strcmp(cTemp, "NUM_MODEL") == 0)
			{
				//"="�ǂݍ���
				fscanf(pFile, "%s", &cTemp[0]);

				//���f�����ǂݍ���
				fscanf(pFile, "%d", &m_nNumParts);

				for (int nCntFile = 0; nCntFile < m_nNumParts;)
				{//�t�@�C�����ǂݍ���

					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "MODEL_FILENAME") == 0)
					{//�t�@�C�����ǂݍ���
						fscanf(pFile, "%s", &cTemp[0]);

						char aPath[MAX_STRING];

						// ���f���p�X�Ǎ�
						fscanf(pFile, "%s", &aPath[0]);

						m_apParts[nCntFile] = new Parts;

						m_apParts[nCntFile]->m_pParts = CParts::Create();

						int nIdx = CModel::Load(&aPath[0]);

						// ���f���Ǎ�
						m_apParts[nCntFile]->m_pParts->SetIdxModel(nIdx);
						m_apParts[nCntFile]->m_pParts->BindModel(m_apParts[nCntFile]->m_pParts->GetIdxModel());

						nCntFile++;
					}
				}
			}
			//===========================================================

			//�L�����N�^�[�ݒ�===========================================
			if (strcmp(cTemp, "CHARACTERSET") == 0)
			{//�L�����N�^�[�X�^�[�g
				nCntModel = 0;

				while (strcmp(cTemp, "END_CHARACTERSET") != 0)
				{//�I���܂ŃL�����N�^�[�ݒ�
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "PARTSSET") == 0)
					{//�p�[�c�X�^�[�g
						while (strcmp(cTemp, "END_PARTSSET") != 0)
						{//�I���܂Ńp�[�c�ݒ�
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "INDEX") == 0)
							{//�ԍ��ǂݍ���
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_apParts[nCntModel]->nIdx);
							}

							if (strcmp(cTemp, "PARENT") == 0)
							{//�e�ԍ��ǂݍ���
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_apParts[nCntModel]->nIdxParent);
							}

							if (strcmp(cTemp, "POS") == 0)
							{//�ʒu�ǂݍ���
								D3DXVECTOR3 pos;

								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntPos = 0; nCntPos < 3; nCntPos++)
								{
									fscanf(pFile, "%f", &pos[nCntPos]);
								}

								m_apParts[nCntModel]->m_pParts->SetPosition(pos);

								m_apParts[nCntModel]->m_pParts->SetPosOrg(pos);
							}

							if (strcmp(cTemp, "ROT") == 0)
							{//�����ǂݍ���
								D3DXVECTOR3 rot;

								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntRot = 0; nCntRot < 3; nCntRot++)
								{
									fscanf(pFile, "%f", &rot[nCntRot]);
								}

								m_apParts[nCntModel]->m_pParts->SetRot(rot);
							}

						}//END_PART

						nCntModel++;
					}
				}//END_CHAR
			}
			//===========================================================

			//�ϐ��錾
			int nCntKey = 0;
			int nCntPart = 0;
			int nCntParticle = 0;

			//���[�V�����ݒ�===========================================
			if (strcmp(cTemp, "MOTIONSET") == 0)
			{//���[�V�����X�^�[�g
				while (strcmp(cTemp, "END_MOTIONSET") != 0)
				{//�I���܂ŃL�����N�^�[�ݒ�

					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "LOOP") == 0)
					{//���[�v���f
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", (int*)&m_aMotionInfo[m_nNumMotion].bLoop);
					}

					if (strcmp(cTemp, "NUM_KEY") == 0)
					{//�L�[�����f
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].nNumKey);
					}

					if (strcmp(cTemp, "NUM_PARTICLE") == 0)
					{//�p�[�e�B�N�������f
						fscanf(pFile, "%s", &cTemp[0]);

						fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].nNumParticle);

						if (m_aMotionInfo[m_nNumMotion].nNumParticle != 0)
						{
							// �p�[�e�B�N�����𐶐�
							m_aMotionInfo[m_nNumMotion].pParticle = new PARTICLE_INFO[m_aMotionInfo[m_nNumMotion].nNumParticle];

							// �p�[�e�B�N����񏉊���
							ZeroMemory(m_aMotionInfo[m_nNumMotion].pParticle, sizeof(PARTICLE_INFO) * m_aMotionInfo[m_nNumMotion].nNumParticle);
						}
					}

					if (strcmp(cTemp, "PARTICLESET") == 0 && m_aMotionInfo[m_nNumMotion].pParticle != 0)
					{// �p�[�e�B�N�����ݒ�
						while (strcmp(cTemp, "END_PARTICLESET") != 0)
						{//�I���܂Ńp�[�e�B�N���ݒ�
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "KEY") == 0)
							{// �Đ��L�[�擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nKey);
							}

							if (strcmp(cTemp, "FRAME") == 0)
							{// �Đ��t���[���擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nFrame);
							}

							if (strcmp(cTemp, "TYPE") == 0)
							{// ��ގ擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nType);
							}

							if (strcmp(cTemp, "POS") == 0)
							{//�ʒu�ǂݍ���
								D3DXVECTOR3 pos;

								fscanf(pFile, "%s", &cTemp[0]);

								for (int nCntPos = 0; nCntPos < 3; nCntPos++)
								{
									fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].offset[nCntPos]);
								}
							}

							if (strcmp(cTemp, "PARENT") == 0)
							{// �e�p�[�c�ԍ��擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].pParticle[nCntParticle].nIdxParent);
							}
						}

						nCntParticle++;
					}

					if (strcmp(cTemp, "KEYSET") == 0)
					{//�L�[�X�^�[�g
						while (strcmp(cTemp, "END_KEYSET") != 0)
						{//�I���܂ŃL�[�ݒ�

							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "FRAME") == 0)
							{//�t���[�����擾
								fscanf(pFile, "%s", &cTemp[0]);

								fscanf(pFile, "%d", &m_aMotionInfo[m_nNumMotion].aKeyInfo[nCntKey].nFrame);
							}

							if (strcmp(cTemp, "KEY") == 0)
							{//�t���[�����擾
								while (strcmp(cTemp, "END_KEY") != 0)
								{//�I���܂ŃL�[�ݒ�
									fscanf(pFile, "%s", &cTemp[0]);

									if (strcmp(cTemp, "POS") == 0)
									{//�ʒu�擾
										fscanf(pFile, "%s", &cTemp[0]);

										fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosX);
										fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosY);
										fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosZ);
									}

									if (strcmp(cTemp, "ROT") == 0)
									{//�����擾
										fscanf(pFile, "%s", &cTemp[0]);

										fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotX);
										fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotY);
										fscanf(pFile, "%f", &m_aMotionInfo[m_nNumMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotZ);
									}
								}

								nCntPart++;

							}//KEYif
						}//ENDKEYwhile

						nCntKey++;
						nCntPart = 0;
					}
				}//MOTIONwhile

				m_nNumMotion++;
			}
			//===========================================================



			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{
				break;
			}
		}//while��
	}
	else
	{
	}
}

//=====================================================
// ��������
//=====================================================
CMotion *CMotion::Create(char *pPath)
{
	CMotion *pCMotion = NULL;

	if (pCMotion == NULL)
	{
		// �C���X�^���X����
		pCMotion = new CMotion;

		// �Ǎ�����
		pCMotion->Load(pPath);

		// ����������
		pCMotion->Init();
	}

	return pCMotion;
}

//=====================================================
// �ۑ�����
//=====================================================
void CMotion::SaveMotion(void)
{
	FILE *pFile = NULL;

	pFile = fopen("data\\motion.txt", "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# ���[�V�����X�N���v�g�t�@�C��[motion.txt]\n");
		fprintf(pFile, "# Author�FMomoya Takayama\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "SCRIPT\n\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "# ���f����\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "NUM_MODEL = %d\n\n", m_nNumParts);

		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "# ���f���t�@�C����\n");
		fprintf(pFile, "#====================================================================\n");

		for (int nCntModel = 0; nCntModel < m_nNumParts; nCntModel++)
		{// �t�@�C���������o��
			fprintf(pFile, "MODEL_FILENAME = %s\n", CModel::GetModelPath(nCntModel));
		}

		fprintf(pFile, "\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "# �L�����N�^�[���\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "CHARACTERSET\n");
		fprintf(pFile, "    NUM_PARTS = %d\n\n", m_nNumParts);

		D3DXVECTOR3 posOrg,pos,rot;

		for (int nCntModel = 0; nCntModel < m_nNumParts; nCntModel++)
		{// �Z�b�g�A�b�v��񏑂��o��
		posOrg = m_apParts[nCntModel]->m_pParts->GetPosOrg();
		fprintf(pFile, "    PARTSSET\n");
		fprintf(pFile, "        INDEX = %d\n", nCntModel);
		fprintf(pFile, "        PARENT = %d\n", m_apParts[nCntModel]->nIdxParent);
		fprintf(pFile, "        POS = %.1f %.1f %.1f\n", posOrg.x, posOrg.y, posOrg.z);
		fprintf(pFile, "        ROT = 0.0 0.0 0.0\n");
		fprintf(pFile, "    END_PARTSSET\n");
		}
		fprintf(pFile, "END_CHARACTERSET\n\n");

		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "# ���[�V�������\n");
		fprintf(pFile, "#====================================================================\n");
		for (int nCntMotion = 0; nCntMotion < m_nNumMotion; nCntMotion++)
		{// ���[�V������񏑂��o��
		fprintf(pFile, "#===============================\n");
		fprintf(pFile, "# [%d]�Ԗڂ̃��[�V����\n", nCntMotion);
		fprintf(pFile, "#===============================\n");
		fprintf(pFile, "MOTIONSET\n");
		fprintf(pFile, "    LOOP = %d\n", (int)m_aMotionInfo[nCntMotion].bLoop);
		fprintf(pFile, "    NUM_KEY = %d\n", m_aMotionInfo[nCntMotion].nNumKey);

		if (m_aMotionInfo[nCntMotion].pParticle != NULL)
		{// �p�[�e�B�N����ݒ肷��Ȃ�
		fprintf(pFile, "    NUM_PARTICLE = %d\n", m_aMotionInfo[nCntMotion].nNumParticle);
		for (int nCntParticle = 0;nCntParticle < m_aMotionInfo[nCntMotion].nNumParticle;nCntParticle++)
		{
			pos =
			{// �ʒu�ۑ�
				m_aMotionInfo[nCntMotion].pParticle[nCntParticle].offset.x,
				m_aMotionInfo[nCntMotion].pParticle[nCntParticle].offset.y,
				m_aMotionInfo[nCntMotion].pParticle[nCntParticle].offset.z,
			};

			fprintf(pFile, "\n");

		fprintf(pFile, "    PARTICLESET\n");
		fprintf(pFile, "        KEY = %d\n", m_aMotionInfo[nCntMotion].pParticle[nCntParticle].nKey);
		fprintf(pFile, "        FRAME = %d\n", m_aMotionInfo[nCntMotion].pParticle[nCntParticle].nFrame);
		fprintf(pFile, "        TYPE = %d\n", m_aMotionInfo[nCntMotion].pParticle[nCntParticle].nType);
		fprintf(pFile, "        POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);
		fprintf(pFile, "        PARENT = %d\n", m_aMotionInfo[nCntMotion].pParticle[nCntParticle].nIdxParent);
		fprintf(pFile, "    END_PARTICLESET\n");
		}
		}

		fprintf(pFile, "\n");


		for (int nCntKey = 0;nCntKey < m_aMotionInfo[nCntMotion].nNumKey;nCntKey++)
		{// �L�[��񏑂��o��
		fprintf(pFile, "    KEYSET     #---<< %d / %d >>\n", nCntKey, m_aMotionInfo[nCntMotion].nNumKey);
		fprintf(pFile, "        FRAME = %d\n", m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
		for (int nCntParts = 0;nCntParts < m_nNumParts;nCntParts++)
		{// �p�[�c���̃L�[��񏑂��o��
		pos =
		{// �p�[�c�̈ʒu�ۑ�
			m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX,
			m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY,
			m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ
		};
		rot =
		{// �p�[�c�̌����ۑ�
			m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX,
			m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY,
			m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ
		};
		fprintf(pFile, "        KEY # -----[%d]----\n", nCntParts);
		fprintf(pFile, "            POS = %.2f %.2f %.2f\n", pos.x, pos.y, pos.z);
		fprintf(pFile, "            ROT = %.2f %.2f %.2f\n", rot.x, rot.y, rot.z);
		fprintf(pFile, "        END_KEY\n");
		}
		fprintf(pFile, "    END_KEYSET\n");
		}
		fprintf(pFile, "END_MOTIONSET\n");
		}

		fprintf(pFile, "END_SCRIPT\n");
	}

	fclose(pFile);
}