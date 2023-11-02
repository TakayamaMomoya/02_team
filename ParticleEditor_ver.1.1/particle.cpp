//*****************************************************
//
// �p�[�e�B�N������[particle.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "particle.h"
#include "effect3D.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "manager.h"
#include "debugproc.h"
#include <stdio.h>

//*****************************************************
// �}�N����`
//*****************************************************
#define ADD_SPEED	(0.01f)	// FLOAT�^�̉��Z��
#define ADD_INT	(1)	// INT�^�̉��Z��
#define ADD_COLOR	(0.002f)	// �F�̉��Z��

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
int CParticle::m_nLife = 5;	// ����
int CParticle::m_nRate = 2;	// ���Z�{��
int CParticle::m_nCurrentCol = 0;	// �F�̑I��v�f
int CParticle::m_nLifeEffect = 10;	// �G�t�F�N�g�̎���
float CParticle::m_fRadiusEffect = 5.0f;	// �G�t�F�N�g�̔��a
int CParticle::m_nNumEffect = 5;	// �G�t�F�N�g�̐�
float CParticle::m_fRangeSpeed = 10.0f;	// �X�s�[�h�̕�
float CParticle::m_fRangeRadius = 20.0f;	// �T�C�Y�̕�
float CParticle::m_fSpeed = 5.0f;	// �G�t�F�N�g�̊�X�s�[�h
float CParticle::m_fGravity = 0.0f;	// �G�t�F�N�g�̊�X�s�[�h
D3DXCOLOR CParticle::m_col = { 1.0f,1.0f,1.0f,1.0f };	// �F
int CParticle::m_bAdd = true;	// ���Z���������邩�ǂ���
int CParticle::m_bRot = true;	// �����𔽉f���邩�ǂ���
bool CParticle::m_bLoop = true;	// ���[�v���邩�ǂ���
bool CParticle::m_bTurn = true;	// ���]���邩�ǂ���
D3DXVECTOR3 CParticle::m_rot = { 0.0f,0.0f,0.0f };	// ����
float CParticle::m_fRangeRot = 0.0f;	// �����̃����_����
float CParticle::m_fDecrease = 0.0f;	// ���a������
int CParticle::m_nNumAll = 0;	// ����

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
	m_nNumAll++;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CParticle::~CParticle()
{
	m_nNumAll--;
}

//=====================================================
// ����������
//=====================================================
HRESULT CParticle::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CParticle::Uninit(void)
{
	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CParticle::Update(void)
{
	if (m_nLifeParticle < 0)
	{
		if (m_bLoop)
		{// �Đ���������
			Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), CParticle::TYPE_NONE);
		}

		// ���g�̔j��
		Uninit();

		return;
	}

	// �ϐ��錾
	float fRot,fRot2,fMove = 0.0f,fRadius = 0.0f;
	int nLife = 0;
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };
	CEffect3D *pEffect3D = NULL;

	for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
	{
		if (m_bRot)
		{// �����̔��f
			if (m_fRangeRot > 0.01f)
			{
				fRot = m_rot.x + (float)(rand() % (int)(m_fRangeRot * 100.0f) - m_fRangeRot * 50.0f) / 100.0f;
				fRot2 = m_rot.y + (float)(rand() % (int)(m_fRangeRot * 100.0f) - m_fRangeRot * 50.0f) / 100.0f * 2;
			}
			else
			{
				fRot = m_rot.x + (rand() % (int)(0.1f * 100.0f) - 0.1f * 50.0f) / 100.0f;
				fRot2 = m_rot.y + (rand() % (int)(0.1f * 100.0f) - 0.1f * 50.0f) / 100.0f;
			}
		}
		else
		{// �S����
			fRot = rand() % 628 - 314 / 100.0f;
			fRot2 = rand() % 628 - 314 / 100.0f;
		}

		if (m_fSpeed > 0.1f)
		{
			fMove = (float)(rand() % (int)(m_fSpeed * 10)) * 0.1f + m_fSpeed * 0.5f;
		}
		if (m_fRadiusEffect > 0.1f)
		{
			fRadius = (float)(rand() % (int)(m_fRadiusEffect * 10)) * 0.1f + m_fRadiusEffect * 0.5f;
		}
		if (m_nLifeEffect != 0)
		{
			nLife = rand() % m_nLifeEffect + m_nLifeEffect / 2;
		}

		move.x = sinf(fRot) * sinf(fRot2) * fMove;
		move.y = cosf(fRot) * fMove;
		move.z = sinf(fRot) * cosf(fRot2) * fMove;

		if (m_bTurn)
		{
			// �G�t�F�N�g����
			pEffect3D = CEffect3D::Create(move * nLife, fRadius, nLife, m_col, -move, m_fGravity, m_bAdd, m_fDecrease);
		}
		else
		{
			// �G�t�F�N�g����
			pEffect3D = CEffect3D::Create(m_pos, fRadius, nLife, m_col, move, m_fGravity, m_bAdd, m_fDecrease);
		}

	}

	// ��������
	m_nLifeParticle--;
}

//=====================================================
//	�ʒu�ݒ菈��
//=====================================================
void CParticle::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
//	��������
//=====================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, TYPE type)
{
	CParticle *pParticle = NULL;

	if (pParticle == NULL)
	{// �C���X�^���X����
		pParticle = new CParticle;

		if (pParticle != NULL)
		{
			pParticle->m_nLifeParticle = m_nLife;

			pParticle->m_pos = pos;
		}
	}

	return pParticle;
}

//=====================================================
// �Ǎ�����
//=====================================================
void CParticle::Load(void)
{
	// �ϐ��錾
	char cTemp[256];

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen("data\\particle.txt", "r");

	if (pFile != NULL)
	{// �t�@�C�����J�����ꍇ
		while (1)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);
			
			if (strcmp(cTemp, "LIFE_PARTICLE") == 0)
			{// �p�[�e�B�N�������擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nLife);
			}

			if (strcmp(cTemp, "NUM_EFFECT") == 0)
			{// �G�t�F�N�g���擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nNumEffect);
			}

			if (strcmp(cTemp, "LIFE_EFFECT") == 0)
			{// �G�t�F�N�g�����擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nLifeEffect);
			}

			if (strcmp(cTemp, "RADIUS_EFFECT") == 0)
			{// �G�t�F�N�g���a�擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%f", &m_fRadiusEffect);
			}

			if (strcmp(cTemp, "SPEED_EFFECT") == 0)
			{// �G�t�F�N�g���x�擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%f", &m_fSpeed);
			}

			if (strcmp(cTemp, "GRAVITY") == 0)
			{// �d�͎擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%f", &m_fGravity);
			}

			if (strcmp(cTemp, "DECREASE") == 0)
			{// �d�͎擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%f", &m_fDecrease);
			}

			if (strcmp(cTemp, "RANGEROT") == 0)
			{// �����̃����_�����擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%f", &m_fRangeRot);
			}

			if (strcmp(cTemp, "IS_ADD") == 0)
			{// ���Z�������ǂ����擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_bAdd);
			}

			if (strcmp(cTemp, "IS_ROT") == 0)
			{// ���Z�������ǂ����擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_bRot);
			}

			if (strcmp(cTemp, "IS_TURN") == 0)
			{// ���Z�������ǂ����擾
				fscanf(pFile, "%s", &cTemp[0]);
				fscanf(pFile, "%s", &cTemp[0]);

				if (strcmp(cTemp, "1") == 0)
				{
					m_bTurn = true;
				}
				else
				{
					m_bTurn = false;
				}
			}

			if (strcmp(cTemp, "COLOR") == 0)
			{// �F�擾
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%f", &m_col.r);
				fscanf(pFile, "%f", &m_col.g);
				fscanf(pFile, "%f", &m_col.b);
				fscanf(pFile, "%f", &m_col.a);
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// �I������
				break;
			}
		}

		fclose(pFile);
	}
}

//=====================================================
// �ۑ�����
//=====================================================
void CParticle::Save(void)
{
	FILE *pFile = NULL;

	pFile = fopen("data\\particle.txt", "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# �p�[�e�B�N���X�N���v�g�t�@�C��[particle.txt]\n");
		fprintf(pFile, "# Author�FMomoya Takayama\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#====================================================================\n");
		fprintf(pFile, "SCRIPT\n\n");

		fprintf(pFile, "    LIFE_PARTICLE = %d\n", m_nLife);
		fprintf(pFile, "    NUM_EFFECT = %d\n", m_nNumEffect);
		fprintf(pFile, "    LIFE_EFFECT = %d\n", m_nLifeEffect);
		fprintf(pFile, "    RADIUS_EFFECT = %.2f\n", m_fRadiusEffect);
		fprintf(pFile, "    SPEED_EFFECT = %.2f\n", m_fSpeed);
		fprintf(pFile, "    GRAVITY = %.2f\n", m_fGravity);
		fprintf(pFile, "    DECREASE = %.2f\n", m_fDecrease);
		fprintf(pFile, "    RANGEROT = %.2f\n", m_fRangeRot);
		fprintf(pFile, "    IS_ADD = %d\n", (int)m_bAdd);
		fprintf(pFile, "    IS_ROT = %d\n", (int)m_bRot);
		fprintf(pFile, "    IS_TURN = %d\n", (int)m_bTurn);
		fprintf(pFile, "    COLOR = %.2f %.2f %.2f %.2f\n", m_col.r,m_col.g,m_col.b,m_col.a);

		fprintf(pFile, "\nEND_SCRIPT\n");

		fclose(pFile);
	}
}

//=====================================================
// ���͏���
//=====================================================
void CParticle::Input(void)
{
	int nRate = 1;

	// ���擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputMouse *pMouse = CManager::GetMouse();
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	pDebugProc->Print("//=========================\n");
	pDebugProc->Print("// �p�����[�^�[\n");
	pDebugProc->Print("//=========================\n");
	pDebugProc->Print("[%d]�p�[�e�B�N���̎���:[QA]\n", m_nLife);
	pDebugProc->Print("[%d]�G�t�F�N�g�̐�:[WS]\n", m_nNumEffect);
	pDebugProc->Print("[%d]�G�t�F�N�g�̎���:[ED]\n", m_nLifeEffect);
	pDebugProc->Print("[%f]�G�t�F�N�g�̔��a:[RF]\n", m_fRadiusEffect);
	pDebugProc->Print("[%f]�G�t�F�N�g�̑��x:[����]\n", m_fSpeed);
	pDebugProc->Print("[%f]�d��:[IK]\n", m_fGravity);
	pDebugProc->Print("[%f]���a������:[56]\n", m_fDecrease);
	pDebugProc->Print("[%f]�����̃����_����:[OL]\n", m_fRangeRot);
	pDebugProc->Print("[%d]���Z�������邩�ǂ���:[1]\n", m_bAdd);
	pDebugProc->Print("[%d]���[�v���邩�ǂ���:[2]\n", m_bLoop);
	pDebugProc->Print("[%d]�����𔽉f���邩�ǂ���:[4]\n", m_bRot);
	pDebugProc->Print("[%d]���]���邩�ǂ���:[7]\n", m_bTurn);
	pDebugProc->Print("[%f,%f,%f]�F:[TG,YH,UJ]\n", m_col.r, m_col.g, m_col.b);
	pDebugProc->Print("[%f,%f,%f]����:[ZM,CV,BN]\n", m_rot.x, m_rot.y, m_rot.z);
	pDebugProc->Print("[%d]����\n",m_nNumAll);

	pDebugProc->Print("\n");

	pDebugProc->Print("//=========================\n");
	pDebugProc->Print("// ������@\n");
	pDebugProc->Print("//=========================\n");
	pDebugProc->Print("[F2] �ۑ�\n");
	pDebugProc->Print("[F3] �Ǎ�\n");
	pDebugProc->Print("[RMB] ���_����\n");
	pDebugProc->Print("[LMB,ENTER] �p�[�e�B�N������\n");

	if (pMouse != NULL)
	{
		if (pKeyboard != NULL)
		{
			if (pKeyboard->GetTrigger(DIK_RETURN) || pMouse->GetTrigger(CInputMouse::BUTTON_LMB))
			{// �p�[�e�B�N������
				if (m_bLoop == false)
				{// ���[�v���͐����ł��Ȃ�
					Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), CParticle::TYPE_NONE);
				}
			}
		}

		if (pMouse->GetPress(CInputMouse::BUTTON_RMB))
		{// ���_���쎞
			pDebugProc->Print("[WASD] �ړ�\n");
			pDebugProc->Print("[QE] �㉺�ړ�\n");

			return;
		}
	}

	if (pKeyboard != NULL)
	{
		if (pKeyboard->GetPress(DIK_LSHIFT))
		{
			nRate *= 2;
		}

		if (pKeyboard->GetTrigger(DIK_Q))
		{// �p�[�e�B�N���������Z
			m_nLife += ADD_INT * nRate;
		}
		else if (pKeyboard->GetTrigger(DIK_A))
		{// �p�[�e�B�N���������Z
			m_nLife -= ADD_INT * nRate;
		}

		if (pKeyboard->GetTrigger(DIK_W))
		{// �G�t�F�N�g�����Z
			m_nNumEffect += ADD_INT * nRate;
		}
		else if (pKeyboard->GetTrigger(DIK_S))
		{// �G�t�F�N�g�����Z
			m_nNumEffect -= ADD_INT * nRate;
		}

		if (pKeyboard->GetTrigger(DIK_E))
		{// �G�t�F�N�g�������Z
			m_nLifeEffect += ADD_INT * nRate;
		}
		else if (pKeyboard->GetTrigger(DIK_D))
		{// �G�t�F�N�g�������Z
			m_nLifeEffect -= ADD_INT * nRate;
		}

		if (pKeyboard->GetPress(DIK_R))
		{// �G�t�F�N�g���a���Z
			m_fRadiusEffect += ADD_SPEED * nRate;
		}
		else if (pKeyboard->GetPress(DIK_F))
		{// �G�t�F�N�g���a���Z
			m_fRadiusEffect -= ADD_SPEED * nRate;
		}

		if (pKeyboard->GetPress(DIK_T))
		{// �ԉ��Z
			m_col.r += ADD_COLOR * nRate;
		}
		else if (pKeyboard->GetPress(DIK_G))
		{// �Ԍ��Z
			m_col.r -= ADD_COLOR * nRate;
		}

		if (pKeyboard->GetPress(DIK_Y))
		{// �Ή��Z
			m_col.g += ADD_COLOR * nRate;
		}
		else if (pKeyboard->GetPress(DIK_H))
		{// �Ό��Z
			m_col.g -= ADD_COLOR * nRate;
		}

		if (pKeyboard->GetPress(DIK_U))
		{// ���Z
			m_col.b += ADD_COLOR * nRate;
		}
		else if (pKeyboard->GetPress(DIK_J))
		{// ���Z
			m_col.b -= ADD_COLOR * nRate;
		}

		if (pKeyboard->GetPress(DIK_I))
		{// �d�͉��Z
			m_fGravity += ADD_COLOR * nRate;
		}
		else if (pKeyboard->GetPress(DIK_K))
		{// �d�͌��Z
			m_fGravity -= ADD_COLOR * nRate;
		}

		if (pKeyboard->GetPress(DIK_O))
		{// ���������_�������Z
			m_fRangeRot += ADD_SPEED * nRate;
		}
		else if (pKeyboard->GetPress(DIK_L))
		{// ���������_�������Z
			m_fRangeRot -= ADD_SPEED * nRate;
		}

		if (pKeyboard->GetPress(DIK_UP))
		{// �X�s�[�h���Z
			m_fSpeed += ADD_SPEED * nRate;
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{// �X�s�[�h���Z
			m_fSpeed -= ADD_SPEED * nRate;
		}

		if (pKeyboard->GetPress(DIK_5))
		{// �����ʉ��Z
			m_fDecrease += ADD_SPEED * nRate;
		}
		else if (pKeyboard->GetPress(DIK_6))
		{// �����ʌ��Z
			m_fDecrease -= ADD_SPEED * nRate;
		}

		if (pKeyboard->GetTrigger(DIK_1))
		{// ���Z�����؂�ւ�
			m_bAdd = m_bAdd ? false : true;
		}

		if (pKeyboard->GetTrigger(DIK_2))
		{// ���[�v�؂�ւ�
			m_bLoop = m_bLoop ? false : true;

			if (m_bLoop)
			{
				Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), CParticle::TYPE_NONE);
			}
		}

		if (pKeyboard->GetTrigger(DIK_4))
		{// �������f�؂�ւ�
			m_bRot = m_bRot ? false : true;
		}

		if (pKeyboard->GetTrigger(DIK_7))
		{// ���Z�����؂�ւ�
			m_bTurn = m_bTurn ? false : true;
		}

		// ��]=====================================
		if (pKeyboard->GetPress(DIK_Z))
		{// X����]
			m_rot.x += ADD_SPEED * nRate;
		}
		else if (pKeyboard->GetPress(DIK_X))
		{
			m_rot.x -= ADD_SPEED * nRate;
		}

		if (pKeyboard->GetPress(DIK_C))
		{// Y����]
			m_rot.y += ADD_SPEED * nRate;
		}
		else if (pKeyboard->GetPress(DIK_V))
		{
			m_rot.y -= ADD_SPEED * nRate;
		}

		if (pKeyboard->GetPress(DIK_B))
		{// Z����]
			m_rot.z += ADD_SPEED * nRate;
		}
		else if (pKeyboard->GetPress(DIK_N))
		{
			m_rot.z -= ADD_SPEED * nRate;
		}

		if (pKeyboard->GetTrigger(DIK_F2))
		{// �ۑ�
			Save();
		}
		else if (pKeyboard->GetTrigger(DIK_F3))
		{// �Ǎ�
			Load();
		}
	}
}