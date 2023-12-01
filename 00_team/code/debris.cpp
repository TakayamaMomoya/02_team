//*****************************************************
//
// �j�Џ���[debris.cpp]
// Author:���}���V
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "debris.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//*****************************************************
// �}�N����`
//*****************************************************
namespace
{
	const float GEOWND = 10.0f;	// ������̍���
	const float BOUNCE = 4.0f;	// ���˕Ԃ�̋���
	const float ROT_VELOCITY = 0.05f;	// ��]���x�̐���
	const float SPEED_SHRINK = 0.05f;	// �k�ޑ��x
	const float LINE_SHRINK = 0.1f;	// �k�ޏ�ԂɂȂ邵�����l
};

//=====================================================
// �R���X�g���N�^
//=====================================================
CDebris::CDebris(int nPriority)
{
	m_rotVelocity = { 0.0f,0.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_nLife = 0;
	m_fGravity = 0.0f;
	m_state = STATE_NONE;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CDebris::~CDebris()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CDebris::Init(void)
{
	CObjectX::Init();

	// ��]���x�̐ݒ�
	m_rotVelocity.x = (float)(rand() % 629 - 314) / 100.0f;
	m_rotVelocity.y = (float)(rand() % 629 - 314) / 100.0f;
	m_rotVelocity.z = (float)(rand() % 629 - 314) / 100.0f;

	// ���f���Ǎ�
	int nIdx = CModel::Load("data\\MODEL\\debris\\soil00.x");
	BindModel(nIdx);

	// �l�̏�����
	m_state = STATE_NORMAL;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CDebris::Uninit(void)
{
	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CDebris::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();

	D3DXVECTOR3 pos = GetPosition();

	// ��������
	m_nLife--;

	// �d�͉��Z
	m_move.y -= m_fGravity;

	// �ړ��ʂ̌���
	m_move.x *= 0.98f;
	m_move.z *= 0.98f;

	if (pos.y > 10.0f)
	{
		// ��]
		D3DXVECTOR3 rot = GetRot();
		rot.x += m_rotVelocity.x * ROT_VELOCITY;
		rot.y += m_rotVelocity.y * ROT_VELOCITY;
		rot.z += m_rotVelocity.z * ROT_VELOCITY;
		SetRot(rot);
	}
	else
	{
		pos.y = GEOWND;

		if (m_move.x < 0.4f && m_move.z < 0.4f) 
		{
			m_move.x = 0.0f;
			m_move.z = 0.0f;
		}
		else
		{
			m_move.y += BOUNCE;
		}
	}

	// �k�܂��邩�̔���
	float fSpeed = sqrtf(m_move.x * m_move.x + m_move.z * m_move.z);

	if (fSpeed <= LINE_SHRINK)
	{
		m_state = STATE_SHRINK;
	}

	// �ʒu�X�V
	SetPosition(pos + m_move);

	if (m_state == STATE_SHRINK)
	{// �k�ޏ���
		Shrink();
	}
}

//=====================================================
// �k�ޏ���
//=====================================================
void CDebris::Shrink(void)
{
	float fScale = GetScale();

	// �k��
	fScale -= SPEED_SHRINK;

	if (fScale <= 0.0f)
	{
		fScale = 0.0f;

		Uninit();
	}

	// �X�P�[���ݒ�
	SetScale(fScale);
}

//=====================================================
// �`�揈��
//=====================================================
void CDebris::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// ��������
//=====================================================
CDebris* CDebris::Create(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move, float fGravity, int nPriority)
{
	CDebris* pDebtisSpawner = nullptr;

	if (pDebtisSpawner == nullptr)
	{// �C���X�^���X����
		pDebtisSpawner = new CDebris(nPriority);

		if (pDebtisSpawner != nullptr)
		{
			pDebtisSpawner->SetPosition(pos);

			// ����������
			pDebtisSpawner->Init();

			pDebtisSpawner->m_nLife = nLife;

			pDebtisSpawner->m_move = move;

			pDebtisSpawner->m_fGravity = fGravity;
		}
	}

	return pDebtisSpawner;
}