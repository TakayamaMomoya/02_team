//*****************************************************
//
// �L�����N�^�[�̏���[character.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "character.h"
#include "motion.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define BODY_PATH	"data\\MOTION\\rayleigh.txt"	// �̂̃p�X

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CCharacter::CCharacter(int nPriority)
{
	ZeroMemory(&m_info, sizeof(CCharacter::SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CCharacter::~CCharacter()
{

}

//=====================================================
// ��������
//=====================================================
CCharacter *CCharacter::Create(char *pPath)
{
	CCharacter *pCharacter = nullptr;

	pCharacter = new CCharacter;

	if (pCharacter != nullptr)
	{
		pCharacter->m_info.pPath = pPath;
		pCharacter->Init();
	}

	return pCharacter;
}

//=====================================================
// �Ǎ�����
//=====================================================
void CCharacter::Load(char *pPath)
{
	if (m_info.pBody == nullptr && pPath != nullptr)
	{
		m_info.pBody = CMotion::Create(pPath);
	}
}

//=====================================================
// ����������
//=====================================================
HRESULT CCharacter::Init(void)
{
	// �̂̓Ǎ�
	Load(m_info.pPath);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CCharacter::Uninit(void)
{
	if (m_info.pBody != nullptr)
	{
		m_info.pBody->Uninit();
		m_info.pBody = nullptr;
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CCharacter::Update(void)
{
	if (m_info.pBody != nullptr)
	{// �̂̒Ǐ]
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRot();

		m_info.pBody->SetPosition(pos);
		m_info.pBody->SetRot(rot);
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CCharacter::Draw(void)
{

}