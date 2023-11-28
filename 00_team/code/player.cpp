//*****************************************************
//
// �v���C���[�̏���[player.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "player.h"
#include "playerManager.h"
#include "motion.h"
#include "debugproc.h"
#include "inputjoypad.h"
#include "inputkeyboard.h"
#include "universal.h"
#include "collision.h"
#include "game.h"
#include "manager.h"

#include "motionDiv.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const char* BODY_PATH_LOWER[NUM_PLAYER] = 
	{// �����g�̃p�X
		"data\\MOTION\\motionPotatoman01_lower.txt",
		"data\\MOTION\\motionPotatoman02_lower.txt",
		"data\\MOTION\\motionPotatoman03_lower.txt",
		"data\\MOTION\\motionPotatoman04_lower.txt",
	};

	const char* BODY_PATH_UPPER[NUM_PLAYER] =
	{// �㔼�g�̃p�X
		"data\\MOTION\\motionPotatoman01_upper.txt",
		"data\\MOTION\\motionPotatoman02_upper.txt",
		"data\\MOTION\\motionPotatoman03_upper.txt",
		"data\\MOTION\\motionPotatoman04_upper.txt",
	};

	const float MOVE_SPEED = 3.0f;	// �ړ����x
	const float ROT_SPEED = 0.1f;	// ��]���x
	const float INITIAL_LIFE = 30.0f;	// �����̗�
	const float DAMAGE_TIME = 0.5f;	// �_���[�W��Ԃ̕b��
	const float MOVE_LINE = 0.2f;	// �����Ă��锻�f�̂������l
}

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CPlayer::CPlayer(int nPriority)
{
	ZeroMemory(&m_info, sizeof(CPlayer::SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CPlayer::~CPlayer()
{

}

//=====================================================
// ��������
//=====================================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->Init();
	}

	return pPlayer;
}

//=====================================================
// ����������
//=====================================================
HRESULT CPlayer::Init(void)
{
	// �p���N���X�̏�����
	CCharacterDiv::Init();

	// �����蔻��̐���
	if (m_info.pCollisionSphere == nullptr)
	{
		m_info.pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE_SPHERE, this);

		if (m_info.pCollisionSphere != nullptr)
		{
			m_info.pCollisionSphere->SetRadius(5.0f);
		}
	}

	if (m_info.pCollisionCube == nullptr)
	{// �����蔻�萶��
		m_info.pCollisionCube = CCollisionCube::Create(CCollision::TAG_PLAYER, this);

		if (m_info.pCollisionCube != nullptr)
		{
			D3DXVECTOR3 vtxMax = { 10.0f,10.0f,10.0f };
			D3DXVECTOR3 vtxMin = { -10.0f,0.0f,-10.0f };

			m_info.pCollisionCube->SetPosition(GetPosition());

			m_info.pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	m_info.fLife = INITIAL_LIFE;
	m_info.state = STATE_NORMAL;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CPlayer::Uninit(void)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pPlayerManager != nullptr)
	{// �ۊǂ��Ă��鎩�g�̃|�C���^���폜
		pPlayerManager->ReleasePlayer(m_info.nID);
	}

	if (m_info.pCollisionSphere != nullptr)
	{
		m_info.pCollisionSphere->Uninit();
		m_info.pCollisionSphere = nullptr;
	}

	if (m_info.pCollisionCube != nullptr)
	{
		m_info.pCollisionCube->Uninit();
		m_info.pCollisionCube = nullptr;
	}

	if (m_info.pWeapon != nullptr)
	{
		m_info.pWeapon->Uninit();
		m_info.pWeapon = nullptr;
	}
	
	// �p���N���X�̏I��
	CCharacterDiv::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CPlayer::Update(void)
{
	// �p���N���X�̍X�V
	CCharacterDiv::Update();

	// ����
	Input();

	// �ʒu�̔��f
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	
	// �O��̈ʒu��ۑ�
	SetPositionOld(pos);

	pos += move;
	SetPosition(pos);

	// �����蔻��̒Ǐ]
	if (m_info.pCollisionSphere != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();
		//D3DXVECTOR3 posWaist = GetBody(CCharacterDiv::PARTS_UPPER)->GetMtxPos(0);
		D3DXVECTOR3 posWaist = GetBody()->GetMtxPos(CCharacterDiv::PARTS_UPPER,0);
		
		// �G�Ƃ̐ڐG����
		m_info.pCollisionSphere->SetPosition(posWaist);

		bool bHit = m_info.pCollisionSphere->SphereCollision(CCollision::TAG_ENEMY);

		if (bHit)
		{
			Hit(5.0f);
		}

		if (m_info.pCollisionSphere != nullptr)
		{
			// �G�Ƃ̉����o������
			m_info.pCollisionSphere->SetPosition(pos);

			m_info.pCollisionSphere->PushCollision(&pos, CCollision::TAG_PLAYER);
			m_info.pCollisionSphere->PushCollision(&pos, CCollision::TAG_ENEMY);

			m_info.pCollisionSphere->SetPositionOld(m_info.pCollisionSphere->GetPosition());
			m_info.pCollisionSphere->SetPosition(pos);

			SetPosition(pos);
		}

		if (m_info.pCollisionCube != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 posCollision = m_info.pCollisionCube->GetPosition();
			D3DXVECTOR3 move = GetMove();

			// ����̒Ǐ]
			m_info.pCollisionCube->SetPositionOld(posCollision);
			m_info.pCollisionCube->SetPosition(pos);

			// �u���b�N�Ƃ̉����o������
			m_info.pCollisionCube->CubeCollision(CCollision::TAG_BLOCK, &move);

			SetMove(move);
		}
	}

	// �ړ��ʂ̌���
	move *= 0.1f;
	SetMove(move);

	// ��ԊǗ�
	ManageState();

	// ���[�V�����Ǘ�
	ManageMotion();

	// ����̒Ǐ]
	if (m_info.pWeapon != nullptr)
	{
		//CMotion* pBody = GetBody(CCharacterDiv::PARTS_UPPER);
		CMotionDiv *pBody = GetBody();

		if (pBody != nullptr)
		{
			pBody->MultiplyMtx();
		}

		m_info.pWeapon->FollowPlayerHand();
	}
}

//=====================================================
// ���͏���
//=====================================================
void CPlayer::Input(void)
{
	CGame *pGame = CGame::GetInstance();

	if (pGame != nullptr)
	{
		CGame::STATE state = pGame->GetState();

		if (state == CGame::STATE_ESCAPE || state == CGame::STATE_RESULT || state == CGame::STATE_END)
		{
			return;
		}
	}

	// �ړ�����
	InputMove();

	// �U������
	InputAttack();

	// �G�C�~���O�̏���
	Aim();
}

//=====================================================
// �ړ��̓���
//=====================================================
void CPlayer::InputMove(void)
{
	CInputJoypad *pJoyPad = CInputJoypad::GetInstance();
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pJoyPad == nullptr || pKeyboard == nullptr)
	{
		return;
	}

	// �v���C���[ID�擾
	int nId = m_info.nIDJoypad;

	D3DXVECTOR3 vecStickL = 
	{// �X�e�B�b�N�̃x�N�g���擾
		pJoyPad->GetJoyStickLX(nId),
		pJoyPad->GetJoyStickLY(nId),
		0.0f,
	};

	if (pKeyboard->GetPress(DIK_W))
	{
		vecStickL.y += MOVE_SPEED;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecStickL.y -= MOVE_SPEED;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecStickL.x -= MOVE_SPEED;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecStickL.x += MOVE_SPEED;
	}

	D3DXVECTOR3 vecMove =
	{// �ړ��x�N�g���̑��
		vecStickL.x,
		0.0f,
		vecStickL.y,
	};

	// �ړ����x�̐ݒ�
	D3DXVECTOR3 move = GetMove();

	D3DXVec3Normalize(&vecMove, &vecMove);
	vecMove *= MOVE_SPEED;

	move += vecMove;

	SetMove(move);
}

//=====================================================
// �U���̓���
//=====================================================
void CPlayer::InputAttack(void)
{
	if (m_info.pWeapon != nullptr)
	{// ����̍U��
		bool bEnable = m_info.pWeapon->IsEnable();

		if (bEnable)
		{
			m_info.pWeapon->Attack();
		}
	}
	else
	{// �f��̏ꍇ�̏���

	}
}

//=====================================================
// �C���^���N�g�̓���
//=====================================================
bool CPlayer::InputInteract(void)
{
	bool bTrigger = false;

	CInputJoypad *pJoyPad = CInputJoypad::GetInstance();
	int nID = GetIDJoypad();

	if (pJoyPad == nullptr)
	{
		return bTrigger;
	}

	if (pJoyPad->GetTrigger(CInputJoypad::PADBUTTONS_LB,nID))
	{
		bTrigger = true;
	}

	return bTrigger;
}

//=====================================================
// �C���^���N�g�̒�����
//=====================================================
bool CPlayer::InputInteractPress(void)
{
	bool bPress = false;

	CInputJoypad *pJoyPad = CInputJoypad::GetInstance();
	int nID = GetIDJoypad();

	if (pJoyPad == nullptr)
	{
		return bPress;
	}

	if (pJoyPad->GetPress(CInputJoypad::PADBUTTONS_LB, nID))
	{
		bPress = true;
	}

	return bPress;
}

//=====================================================
// ����̗L����
//=====================================================
void CPlayer::EnableWeapon(bool bEnable)
{
	if (m_info.pWeapon != nullptr)
	{
		m_info.pWeapon->SetEnable(bEnable);
	}
}

//=====================================================
// �G�C�~���O�̏���
//=====================================================
void CPlayer::Aim(void)
{
	CInputJoypad *pJoyPad = CInputJoypad::GetInstance();
	CUniversal *pUniversal = CUniversal::GetInstance();

	if (pJoyPad == nullptr)
	{
		return;
	}

	// �v���C���[ID�擾
	int nId = m_info.nIDJoypad;

	D3DXVECTOR3 vecStickR =
	{// �X�e�B�b�N�̃x�N�g���擾
		pJoyPad->GetJoyStickRX(nId),
		pJoyPad->GetJoyStickRY(nId),
		0.0f,
	};

	float fLength = D3DXVec3Length(&vecStickR);

	float fAngleDest = 0.0f;

	if (fLength >= 0.3f)
	{// �E�X�e�B�b�N�𓮂����Ă���ꍇ
		// �p�x�̎擾
		fAngleDest = atan2f(vecStickR.x, vecStickR.y);
	}
	else
	{// �ړ��������Ă���ꍇ
		D3DXVECTOR3 move = GetMove();

		float fLengthMove = D3DXVec3Length(&move);

		if (fLengthMove >= 1.0f)
		{
			// �p�x�̎擾
			fAngleDest = atan2f(move.x, move.z);
		}
		else
		{
			return;
		}
	}

	// �p�x�␳
	D3DXVECTOR3 rot = GetRot();

	pUniversal->LimitRot(&fAngleDest);

	pUniversal->FactingRot(&rot.y, fAngleDest + D3DX_PI, ROT_SPEED);

	SetRot(rot);
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CPlayer::ManageState(void)
{
	switch (m_info.state)
	{
	case STATE_NORMAL:
	{// �ʏ���

	}
		break;
	case STATE_DAMAGE:
	{// �_���[�W���
		float fTick = CManager::GetTick();

		m_info.fTimerState -= fTick;

		if (m_info.fTimerState <= 0.0f)
		{
			m_info.state = STATE_NORMAL;

			for (int nCutPath = 0; nCutPath < CCharacterDiv::PARTS_MAX; nCutPath++)
			{
				//CMotion* pBody = GetBody(nCutPath);
				CMotionDiv* pBody = GetBody();

				if (pBody != nullptr)
				{
					pBody->ResetAllCol();
				}
			}
		}
	}
		break;
	case STATE_DEATH:
	{// ���S���

	}
		break;
	default:
		break;
	}
}

//=====================================================
// ���[�V�����Ǘ�
//=====================================================
void CPlayer::ManageMotion(void)
{
	D3DXVECTOR3 move = GetMove();

	float fSpeed = D3DXVec3Length(&move);

	int nMotion = GetMotion(CCharacterDiv::PARTS_LOWER);

	CDebugProc::GetInstance()->Print("\n�X�s�[�h[%f]",fSpeed);

	if (fSpeed > MOVE_LINE)
	{
		if (nMotion != MOTION_WALK)
		{
			SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_WALK);
			SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_WALK);
		}
	}
	else
	{
		if (nMotion != MOTION_NEUTRAL)
		{
			SetMotion(CCharacterDiv::PARTS_LOWER, MOTION_NEUTRAL);
			SetMotion(CCharacterDiv::PARTS_UPPER, MOTION_NEUTRAL);
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CPlayer::Draw(void)
{
	// �p���N���X�̕`��
	CCharacterDiv::Draw();

	// �f�o�b�O�\��
	Debug();
}

//=====================================================
// ����ݒ�
//=====================================================
void CPlayer::SetWeapon(CWeapon::TYPE type)
{
	if (m_info.pWeapon != nullptr)
	{
		m_info.pWeapon->Uninit();
		m_info.pWeapon = nullptr;
	}

	m_info.pWeapon = CWeapon::Create(type,6);

	if (m_info.pWeapon != nullptr)
	{
		m_info.pWeapon->SetPlayer(this);
	}
}

//=====================================================
// ID�ݒ�
//=====================================================
void CPlayer::SetID(int nID)
{
	m_info.nID = nID;

	// ID�ɑΉ��������f���̐ݒ�
	CCharacterDiv::Load((char*)BODY_PATH_LOWER[nID], (char*)BODY_PATH_UPPER[nID]);

	// �e�̗L����
	for (int nCutPath = 0; nCutPath < CCharacterDiv::PARTS_MAX; nCutPath++)
	{
		CMotionDiv* pBody = GetBody();

		if (pBody != nullptr)
		{
			pBody->SetPosShadow(D3DXVECTOR3(0.0f, 0.5f, 0.0f));
			pBody->EnableShadow(true);
		}
	}
}

//=====================================================
// �q�b�g����
//=====================================================
void CPlayer::Hit(float fDamage)
{
	if (m_info.state == STATE_NORMAL)
	{
		m_info.fLife -= fDamage;

		if (m_info.fLife <= 0.0f)
		{// ���S����
			m_info.fLife = 0.0f;

			m_info.state = STATE_DEATH;

			Uninit();
		}
		else
		{// �_���[�W����
			m_info.state = STATE_DAMAGE;

			m_info.fTimerState = DAMAGE_TIME;

			for (int nCutPath = 0; nCutPath < CCharacterDiv::PARTS_MAX; nCutPath++)
			{
				//CMotion* pBody = GetBody(nCutPath);
				CMotionDiv* pBody = GetBody();

				if (pBody != nullptr)
				{
					pBody->SetAllCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}
			}
		}
	}
}

//=====================================================
// �f�o�b�O�\��
//=====================================================
void CPlayer::Debug(void)
{
#ifndef _DEBUG

	return;

#endif

	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\n�v���C���[�ԍ�[%d]", m_info.nID);
	pDebugProc->Print("\n�v���C���[�̈ʒu[%f,%f,%f]", GetPosition().x, GetPosition().y, GetPosition().z);
	pDebugProc->Print("\n�v���C���[�̌���[%f,%f,%f]", GetRot().x, GetRot().y, GetRot().z);

	if (GetBody() != nullptr)
	{
		int nMotion = GetBody()->GetMotion(CCharacterDiv::PARTS_LOWER);

		pDebugProc->Print("\n�����g�̃��[�V����[%d]", nMotion);
	}

	if (GetBody() != nullptr)
	{
		int nMotion = GetBody()->GetMotion(CCharacterDiv::PARTS_UPPER);

		pDebugProc->Print("\n�㔼�g�̃��[�V����[%d]", nMotion);
	}
}