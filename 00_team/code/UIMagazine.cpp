//*****************************************************
//
// �c�e���\���̏���[UIMagazine.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "UIMagazine.h"
#include "number.h"

#include "texture.h"

#include "player.h"
#include "playerManager.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int DIG_MAG_NUM = 3;		// ���e���̌���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CUIMagazine::CUIMagazine(int nPriority) : CObject(nPriority)
{
	m_pNumDig = nullptr;

	ZeroMemory(&m_info, sizeof(m_info));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CUIMagazine::~CUIMagazine()
{

}

//=====================================================
// ��������
//=====================================================
CUIMagazine* CUIMagazine::Create(int nIdx)
{
	CUIMagazine *pUIMagazine = nullptr;

	pUIMagazine = new CUIMagazine;

	if (pUIMagazine != nullptr)
	{
		// �v���C���[�ԍ���ݒ�
		pUIMagazine->m_info.nIdxPlayer = nIdx;

		// ���e���i�����j�̐�������
		CNumber* pDigMag = CNumber::Create(DIG_MAG_NUM, 0);

		if (pDigMag != nullptr)
		{
			pUIMagazine->m_pNumDig = pDigMag;
		}

		// ���e��UI�̏�����
		pUIMagazine->Init();
	}

	return pUIMagazine;
}

//=====================================================
// ����������
//=====================================================
HRESULT CUIMagazine::Init(void)
{
	if (m_pNumDig != nullptr)
	{
		// �����l�ݒ菈��
		m_pNumDig->SetSizeAll(50.0f, 100.0f);
		m_pNumDig->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CUIMagazine::Uninit(void)
{
	if (m_pNumDig != nullptr)
	{
		m_pNumDig->Uninit();
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CUIMagazine::Update(void)
{
	if (m_pNumDig != nullptr)
	{
		SetNumMagazine();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CUIMagazine::Draw(void)
{

}

//=====================================================
// �ʒu�ݒ菈��
//=====================================================
void CUIMagazine::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pNumDig != nullptr)
	{
		m_pNumDig->SetPosition(pos);
	}
}

//=====================================================
// �傫���ݒ菈��
//=====================================================
void CUIMagazine::SetSize(float width, float height)
{
	if (m_pNumDig != nullptr)
	{
		m_pNumDig->SetSizeAll(width, height);
	}
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CUIMagazine::SetCol(D3DXCOLOR col)
{
	if (m_pNumDig != nullptr)
	{
		m_pNumDig->SetColor(col);
	}
}

//=====================================================
// ���e���ݒ菈��
//=====================================================
void CUIMagazine::SetNumMagazine(void)
{
	// �|�C���^�̎擾
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();
	CPlayer* pPlayer = nullptr;
	CWeapon* pWeapon = nullptr;

	int nBullet = 0;

	if (pPlayerManager != nullptr)
	{
		// �v���C���[�Ǘ��̎擾
		pPlayer = pPlayerManager->GetPlayer(m_info.nIdxPlayer);
	}

	if (pPlayer != nullptr)
	{
		// �v���C���[�̎擾
		pWeapon = pPlayer->GetWeapon();
	}

	if (pWeapon != nullptr)
	{
		// �v���C���[�̒e���擾
		nBullet = pWeapon->GetBullet();
	}

	if (m_pNumDig != nullptr)
	{
		// �e�𔽉f
		m_pNumDig->SetValue(nBullet, DIG_MAG_NUM);
	}
}