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
#include "universal.h"
#include "collision.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define BODY_PATH	"data\\MOTION\\rayleigh.txt"	// �̂̃p�X
#define MOVE_SPEED	(1.0f)	// �ړ����x
#define ROT_SPEED	(0.1f)	// ��]���x

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
	CCharacter::Init();

	// �̂̓Ǎ�
	CCharacter::Load(BODY_PATH);

	// �����蔻��̐���
	if (m_info.pCollisionSphere == nullptr)
	{
		m_info.pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_PLAYER, CCollision::TYPE_SPHERE, this);

		if (m_info.pCollisionSphere != nullptr)
		{
			m_info.pCollisionSphere->SetRadius(5.0f);
		}
	}

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
	
	// �p���N���X�̏I��
	CCharacter::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CPlayer::Update(void)
{
	// �p���N���X�̍X�V
	CCharacter::Update();

	// ����
	Input();

	// �ʒu�̔��f
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	pos += move;
	SetPosition(pos);

	// �����蔻��̒Ǐ]
	if (m_info.pCollisionSphere != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		m_info.pCollisionSphere->SetPosition(pos);
	}

	// �ړ��ʂ̌���
	move *= 0.1f;
	SetMove(move);
}

//=====================================================
// ���͏���
//=====================================================
void CPlayer::Input(void)
{
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

	if (pJoyPad == nullptr)
	{
		return;
	}

	// �v���C���[ID�擾
	int nId = m_info.nID;

	D3DXVECTOR3 vecStickL = 
	{// �X�e�B�b�N�̃x�N�g���擾
		pJoyPad->GetJoyStickLX(nId),
		pJoyPad->GetJoyStickLY(nId),
		0.0f,
	};

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
	// �ˌ�����
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
	int nId = m_info.nID;

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
	pUniversal->LimitRot(&rot.y);

	pUniversal->FactingRot(&rot.y, fAngleDest, ROT_SPEED);

	SetRot(rot);
}

//=====================================================
// �`�揈��
//=====================================================
void CPlayer::Draw(void)
{
	// �p���N���X�̕`��
	CCharacter::Draw();

	// �f�o�b�O�\��
	Debug();
}

//=====================================================
// ����ݒ�
//=====================================================
void CPlayer::SetWeapon(void)
{
	
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
	pDebugProc->Print("\n�v���C���[�̌���[%f,%f,%f]", GetRot().x, GetRot().y, GetRot().z);
}