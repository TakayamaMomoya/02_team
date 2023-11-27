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
#define SPEED_MOVE	(7.0f)	// �ړ����x

//=====================================================
// �R���X�g���N�^
//=====================================================
CDebris::CDebris(int nPriority)
{
	m_nLife = 0;
	m_fDecreaseAlpha = 0.0f;
	m_move = { 0.0f,0.0f,0.0f };
	m_fGravity = 0.0f;
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
	// �p���N���X�̏�����
	CObjectX::Init();

	int nIdx = CModel::Load("data\\MODEL\\sample_debris.x");

	// ���f���Ǎ�
	BindModel(nIdx);

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

	// ���̌���


	if (pos.y <= 10.0f)
	{
		pos.y = 10.0f;
	}

	// �ʒu�X�V
	SetPosition(pos + m_move);

	if (m_nLife < 0)
	{// �����̍폜
		Uninit();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CDebris::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

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

			// X�t�@�C���̓Ǎ�


			pDebtisSpawner->m_nLife = nLife;

			pDebtisSpawner->m_move = move;

			pDebtisSpawner->m_fDecreaseAlpha = 1.0f / nLife;

			pDebtisSpawner->m_fGravity = fGravity;
		}
	}

	return pDebtisSpawner;
}

//=====================================================
// �Ǎ�����
//=====================================================
HRESULT CDebris::Load(void)
{
	return S_OK;
}

//=====================================================
// �e�N�X�`���j��
//=====================================================
void CDebris::Unload(void)
{

}