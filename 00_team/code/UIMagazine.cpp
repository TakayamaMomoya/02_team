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

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int DIG_MAG_NUM = 3;		// ���e���̌���
	const int DIG_MAX_MAG_NUM = 3;	// �ő呕�e���̌���
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CUIMagazine::CUIMagazine(int nPriority) : CObject(nPriority)
{
	m_pNumDig = nullptr;
	m_pNumMaxDig = nullptr;

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

		// ���e�ő吔�i�����j�̐�������
		CNumber* pDigMaxMag = CNumber::Create(DIG_MAX_MAG_NUM, 0);

		if (pDigMaxMag != nullptr)
		{
			pUIMagazine->m_pNumMaxDig = pDigMaxMag;
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

	if (m_pNumMaxDig != nullptr)
	{
		// �����l�ݒ菈��
		m_pNumMaxDig->SetSizeAll(50.0f, 100.0f);
		m_pNumMaxDig->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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

	if (m_pNumMaxDig != nullptr)
	{
		m_pNumMaxDig->Uninit();
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CUIMagazine::Update(void)
{
	if (m_pNumDig != nullptr ||
		m_pNumMaxDig != nullptr)
	{
		m_pNumDig->SetValue(0, DIG_MAG_NUM);
		m_pNumMaxDig->SetValue(0, DIG_MAX_MAG_NUM);
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
void CUIMagazine::SetPosition(D3DXVECTOR3 posDig , D3DXVECTOR3 posMaxDig)
{
	if (m_pNumDig != nullptr ||
		m_pNumMaxDig != nullptr)
	{
		m_pNumDig->SetPosition(posDig);
		m_pNumMaxDig->SetPosition(posMaxDig);
	}
}

//=====================================================
// �傫���ݒ菈��
//=====================================================
void CUIMagazine::SetSize(float width, float height)
{
	if (m_pNumDig != nullptr ||
		m_pNumMaxDig != nullptr)
	{
		m_pNumDig->SetSizeAll(width, height);
		m_pNumMaxDig->SetSizeAll(width, height);
	}
}

//=====================================================
// �F�ݒ菈��
//=====================================================
void CUIMagazine::SetCol(D3DXCOLOR col)
{
	if (m_pNumDig != nullptr ||
		m_pNumMaxDig != nullptr)
	{
		m_pNumDig->SetColor(col);
		m_pNumMaxDig->SetColor(col);
	}
}
