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

//=====================================================
// �R���X�g���N�^
//=====================================================
CLife::CLife(int nPriority) : CObject(nPriority)
{
	m_pUILife = nullptr;
	m_pUILifeFrame = nullptr;
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
	CLife *pLife = new CLife;

	if (pLife != nullptr)
	{
		// �v���C���[�ԍ���ݒ�
		pLife->m_info.nIdxPlayer = nIdx;

		if (pLife->m_pUILifeFrame == nullptr)
		{
			// ���C�t�g�̐�������
			pLife->m_pUILifeFrame = CUI::Create();
		}

		if (pLife->m_pUILife == nullptr)
		{
			// ���C�t�̐�������
			pLife->m_pUILife = CUI::Create();
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
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		// �����l�ݒ菈��
		m_pUILife->SetSize(50.0f, 100.0f);
		m_pUILife->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pUILifeFrame->SetSize(50.0f, 100.0f);
		m_pUILifeFrame->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CLife::Uninit(void)
{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		m_pUILife->Uninit();
		m_pUILifeFrame->Uninit();
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

	if (pPlayerManager != nullptr )
	{
		if (pPlayer != nullptr)
		{
			// ���݂̗̑͂��擾
			float fLife = pPlayer->GetLife();

			// �̗͂̏����l���擾
			float fMaxLife = pPlayerManager->GetPlayerParam().fInitialLife;

			// �Q�[�W�̏���ʂ��v�Z
			float fLifeRatio = (1.0f - (fLife / fMaxLife));
			m_info.fHeightSub = fLifeRatio * m_info.fHeight;

			m_pUILife->SetTex(D3DXVECTOR2(0.0f, fLifeRatio), D3DXVECTOR2(1.0f, 1.0f));
			SetVtxGage();
			m_pUILifeFrame->SetVtx();
		}
		else
		{
			// �̗͂͂Ȃ�
			float fLife = 0.0f;

			// �̗͂̏����l���擾
			float fMaxLife = pPlayerManager->GetPlayerParam().fInitialLife;

			// �Q�[�W�̏���ʂ��v�Z
			float fLifeRatio = (1.0f - (fLife / fMaxLife));
			m_info.fHeightSub = fLifeRatio * m_info.fHeight;

			m_pUILife->SetTex(D3DXVECTOR2(0.0f, fLifeRatio), D3DXVECTOR2(1.0f, 1.0f));
			SetVtxGage();
			m_pUILifeFrame->SetVtx();
		}
	}
}

//=====================================================
// �ʒu�ݒ菈��
//=====================================================
void CLife::SetPosition(D3DXVECTOR3 posLife, D3DXVECTOR3 posLifeFrame)

{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		m_info.posLife = posLife;
		m_info.posLifeFrame = posLifeFrame;
		
		m_pUILife->SetPosition(posLife);
		m_pUILifeFrame->SetPosition(posLifeFrame);

		SetVtxGage();
		m_pUILifeFrame->SetVtx();
	}
}

//=====================================================
// �傫���ݒ菈��
//=====================================================
void CLife::SetSize(float width, float height)
{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		m_info.fWidth = width;
		m_info.fHeight = height;

		m_pUILife->SetSize(width, height);
		m_pUILifeFrame->SetSize(width, height);

		SetVtxGage();
		m_pUILifeFrame->SetVtx();
	}
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CLife::SetCol(D3DXCOLOR colLife, D3DXCOLOR colLifeFrame)
{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		m_info.colLife = colLife;
		m_info.colLifeFrame = colLifeFrame;

		m_pUILife->SetCol(colLife);
		m_pUILifeFrame->SetCol(colLifeFrame);

		SetVtxGage();
		m_pUILifeFrame->SetVtx();
	}
}

//=====================================================
// �e�N�X�`���ݒ菈��
//=====================================================
void CLife::SetTexture(const char* pFileName)
{
	if (m_pUILife != nullptr &&
		m_pUILifeFrame != nullptr)
	{
		CTexture* pTexture = CTexture::GetInstance();

		if (pTexture != nullptr)
		{
			m_info.nIdxTexture = pTexture->Regist(pFileName);
		}

		m_pUILife->SetIdxTexture(m_info.nIdxTexture);
		m_pUILifeFrame->SetIdxTexture(m_info.nIdxTexture);

		SetVtxGage();
		m_pUILifeFrame->SetVtx();
	}
}

//=====================================================
// �Q�[�W�p�̒��_���ݒ菈��
//=====================================================
void CLife::SetVtxGage(void)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	if (m_pUILife != nullptr)
	{
		if (m_pUILife->GetVtxBuff() != nullptr)
		{
			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_pUILife->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

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
				m_info.posLife.x + sinf(0.0f - D3DX_PI + fAngleUp) * fLengthUp,
				m_info.posLife.y + cosf(0.0f - D3DX_PI + fAngleUp) * ((fLengthUp * 2.0f) - (fLengthSub * 2.0f)),
				0.0f
			);
			pVtx[1].pos = D3DXVECTOR3
			(
				m_info.posLife.x + sinf(0.0f + D3DX_PI - fAngleUp) * fLengthUp,
				m_info.posLife.y + cosf(0.0f + D3DX_PI - fAngleUp) * ((fLengthUp * 2.0f) - (fLengthSub * 2.0f)),
				0.0f
			);
			pVtx[2].pos = D3DXVECTOR3
			(
				m_info.posLife.x + sinf(0.0f - fAngleUp) * fLengthUp,
				m_info.posLife.y + cosf(0.0f - fAngleUp),
				0.0f
			);
			pVtx[3].pos = D3DXVECTOR3
			(
				m_info.posLife.x + sinf(0.0f + fAngleUp) * fLengthUp,
				m_info.posLife.y + cosf(0.0f + fAngleUp),
				0.0f
			);


			// ���_�o�b�t�@�̃A�����b�N
			m_pUILife->GetVtxBuff()->Unlock();
		}
	}
}