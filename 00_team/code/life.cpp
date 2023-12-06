//*****************************************************
//
// ���C�t�\���̏���[life.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "life.h"
#include "UI.h"

#include "texture.h"

#include "player.h"
#include "playerManager.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
}
//=====================================================
// �R���X�g���N�^
//=====================================================
CLife::CLife(int nPriority) : CObject(nPriority)
{
	m_pUi = NULL;
	ZeroMemory(&m_info, sizeof(m_info));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CLife::~CLife()
{

}

//=====================================================
// ��������
//=====================================================
CLife *CLife::Create(int nIdx)
{
	CLife *pLife = nullptr;

	pLife = new CLife;

	if (pLife != nullptr)
	{
		// �v���C���[�ԍ���ݒ�
		pLife->m_info.nIdxPlayer = nIdx;

		if (pLife->m_pUi == NULL)
		{
			// UI�I�u�W�F�N�g�̐�������
			pLife->m_pUi = CUI::Create();
		}

		// ���C�t�̏�����
		pLife->Init();
	}

	return pLife;
}

//=====================================================
// ����������
//=====================================================
HRESULT CLife::Init(void)
{
	if (m_pUi != nullptr)
	{
		// �����l�ݒ菈��
		m_pUi->SetSize(50.0f, 100.0f);
		m_pUi->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CLife::Uninit(void)
{
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CLife::Update(void)
{
	// �v���C���[�̗̑�
	SetLife();
}

//=====================================================
// �`�揈��
//=====================================================
void CLife::Draw(void)
{

}

//=====================================================
// �ʒu�ݒ菈��
//=====================================================
void CLife::SetLife(void)
{
	// �v���C���[�Ǘ��̎擾
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();
	CPlayer* pPlayer = nullptr;

	if (pPlayerManager != nullptr)
	{
		// �v���C���[�̎擾
		pPlayer = pPlayerManager->GetPlayer(m_info.nIdxPlayer);
	}

	if (pPlayerManager != nullptr &&
		pPlayer != nullptr)
	{
		// ���݂̗̑͂��擾
		float fLife = pPlayer->GetLife();

		// �̗͂̏����l���擾
		float fMaxLife = pPlayerManager->GetPlayerParam().fInitialLife;

		// �Q�[�W�̏���ʂ��v�Z
		m_info.fHeightSub = (1.0f - (fLife / fMaxLife)) * m_info.fHeight;

		SetVtxGage();
	}
	else
	{
		// �̗͂͂Ȃ�
		float fLife = 0.0f;

		// �̗͂̏����l���擾
		float fMaxLife = pPlayerManager->GetPlayerParam().fInitialLife;

		// �Q�[�W�̏���ʂ��v�Z
		m_info.fHeightSub = (1.0f - (fLife / fMaxLife)) * m_info.fHeight;

		SetVtxGage();
	}
}

//=====================================================
// �ʒu�ݒ菈��
//=====================================================
void CLife::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pUi != nullptr)
	{
		m_info.pos = pos;

		m_pUi->SetPosition(pos);

		SetVtxGage();
	}
}

//=====================================================
// �傫���ݒ菈��
//=====================================================
void CLife::SetSize(float width, float height)
{
	if (m_pUi != NULL)
	{
		m_info.fWidth = width;
		m_info.fHeight = height;

		m_pUi->SetSize(width, height);

		SetVtxGage();
	}
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CLife::SetCol(D3DXCOLOR col)
{
	if (m_pUi != NULL)
	{
		m_info.col = col;

		m_pUi->SetCol(col);

		SetVtxGage();
	}
}

//=====================================================
// �e�N�X�`���ݒ菈��
//=====================================================
void CLife::SetTexture(const char *pFileName)
{
	m_info.nIdxTexture = CTexture::GetInstance()->Regist(pFileName);

	if (m_pUi != nullptr)
	{
		m_pUi->SetIdxTexture(m_info.nIdxTexture);

		SetVtxGage();
	}
}

//=====================================================
// �Q�[�W�p�̒��_���ݒ菈��
//=====================================================
void CLife::SetVtxGage(void)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	if (m_pUi != nullptr)
	{
		if (m_pUi->GetVtxBuff() != nullptr)
		{
			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_pUi->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

			// �Ίp���̊p�x�擾
			float fAngleUp = atan2f(m_info.fWidth, m_info.fHeight);
			// �����̎擾
			float fLengthUp = sqrtf(m_info.fWidth * m_info.fWidth + m_info.fHeight * m_info.fHeight);
			float fLengthSub = sqrtf(m_info.fWidthSub * m_info.fWidthSub + m_info.fHeightSub * m_info.fHeightSub);

			if (fLengthUp - fLengthSub <= 1.0f)
			{
				fLengthUp = 0.0f;
				fLengthSub = 0.0f;
			}

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3
			(
				m_info.pos.x + sinf(0.0f - D3DX_PI + fAngleUp) * fLengthUp,
				m_info.pos.y + cosf(0.0f - D3DX_PI + fAngleUp) * ((fLengthUp * 2.0f) - (fLengthSub * 2.0f)),
				0.0f
			);
			pVtx[1].pos = D3DXVECTOR3
			(
				m_info.pos.x + sinf(0.0f + D3DX_PI - fAngleUp) * fLengthUp,
				m_info.pos.y + cosf(0.0f + D3DX_PI - fAngleUp) * ((fLengthUp * 2.0f) - (fLengthSub * 2.0f)),
				0.0f
			);
			pVtx[2].pos = D3DXVECTOR3
			(
				m_info.pos.x + sinf(0.0f - fAngleUp) * fLengthUp,
				m_info.pos.y + cosf(0.0f - fAngleUp),
				0.0f
			);
			pVtx[3].pos = D3DXVECTOR3
			(
				m_info.pos.x + sinf(0.0f + fAngleUp) * fLengthUp,
				m_info.pos.y + cosf(0.0f + fAngleUp),
				0.0f
			);

			// ���_�o�b�t�@�̃A�����b�N
			m_pUi->GetVtxBuff()->Unlock();
		}
	}
}