//*****************************************************
//
// �����L�����N�^�[�̏���[character.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "characterDiv.h"
#include "motion.h"

//*****************************************************
// �}�N����`
//*****************************************************

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CCharacterDiv::CCharacterDiv(int nPriority)
{
	ZeroMemory(&m_info, sizeof(CCharacterDiv::SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCharacterDiv::~CCharacterDiv()
{

}

//=====================================================
// ��������
//=====================================================
CCharacterDiv* CCharacterDiv::Create(char* pPathUpper, char* pPathLower)
{
	CCharacterDiv* pCharacter = nullptr;

	pCharacter = new CCharacterDiv;

	if (pCharacter != nullptr)
	{
		pCharacter->m_info.apPath[PARTS_UPPER] = pPathUpper;
		pCharacter->m_info.apPath[PARTS_LOWER] = pPathLower;
		pCharacter->Init();
	}

	return pCharacter;
}

//=====================================================
// �Ǎ�����
//=====================================================
void CCharacterDiv::Load(char* pPathUpper, char* pPathLower)
{
	if (m_info.apBody[PARTS_UPPER] == nullptr && pPathUpper != nullptr &&
		m_info.apBody[PARTS_LOWER] == nullptr && pPathLower != nullptr)
	{
		m_info.apBody[PARTS_UPPER] = CMotion::Create(pPathUpper);

		if (m_info.apBody[PARTS_UPPER] != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 rot = GetRot();

			m_info.apBody[PARTS_UPPER]->SetPosition(pos);
			m_info.apBody[PARTS_UPPER]->SetRot(rot);

			m_info.apBody[PARTS_UPPER]->MultiplyMtx();
		}

		m_info.apBody[PARTS_LOWER] = CMotion::Create(pPathLower);

		if (m_info.apBody[PARTS_LOWER] != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 rot = GetRot();

			m_info.apBody[PARTS_LOWER]->SetPosition(pos);
			m_info.apBody[PARTS_LOWER]->SetRot(rot);

			m_info.apBody[PARTS_LOWER]->MultiplyMtx();
		}
	}
}

//=====================================================
// ����������
//=====================================================
HRESULT CCharacterDiv::Init(void)
{
	// �̂̓Ǎ�
	Load(m_info.apPath[PARTS_UPPER], m_info.apPath[PARTS_LOWER]);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCharacterDiv::Uninit(void)
{
	if (m_info.apBody[PARTS_UPPER] != nullptr)
	{
		m_info.apBody[PARTS_UPPER]->Uninit();
		m_info.apBody[PARTS_UPPER] = nullptr;
	}

	if (m_info.apBody[PARTS_LOWER] != nullptr)
	{
		m_info.apBody[PARTS_LOWER]->Uninit();
		m_info.apBody[PARTS_LOWER] = nullptr;
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CCharacterDiv::Update(void)
{
	if (m_info.apBody[PARTS_UPPER] != nullptr &&
		m_info.apBody[PARTS_LOWER] != nullptr)
	{// �̂̒Ǐ]
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRot();

		m_info.apBody[PARTS_UPPER]->SetPosition(pos);
		m_info.apBody[PARTS_UPPER]->SetRot(rot);

		m_info.apBody[PARTS_LOWER]->SetPosition(pos);
		m_info.apBody[PARTS_LOWER]->SetRot(rot);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CCharacterDiv::Draw(void)
{

}

//=====================================================
// ���[�V�����ݒ�
//=====================================================
void CCharacterDiv::SetMotion(int nNum, int nMotion)
{
	if (m_info.apBody[nNum] != nullptr)
	{
		m_info.apBody[nNum]->SetMotion(nMotion);
	}
}

//=====================================================
// ���[�V�����擾
//=====================================================
int CCharacterDiv::GetMotion(int nNum)
{
	int nMotion = 0;

	if (m_info.apBody[nNum] != nullptr)
	{
		nMotion = m_info.apBody[nNum]->GetMotion();
	}

	return nMotion;
}