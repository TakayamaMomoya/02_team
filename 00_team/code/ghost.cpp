//*****************************************************
//
// �H��̏���[ghost.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "ghost.h"
#include "debugproc.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const char* BODY_PATH[NUM_PLAYER] =
{// �v���C���[�����ڂ̃p�X
	"data\\MOTION\\motionPotatoman01.txt",
	"data\\MOTION\\motionPotatoman02.txt",
	"data\\MOTION\\motionPotatoman03.txt",
	"data\\MOTION\\motionPotatoman04.txt",
};
}

//=====================================================
// �R���X�g���N�^
//=====================================================
CGhost::CGhost(int nPriority) : CMotion(nPriority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGhost::~CGhost()
{

}

//=====================================================
// ��������
//=====================================================
CGhost *CGhost::Create(int nIdxPlayer)
{
	CGhost *pGhost = nullptr;

	if (pGhost == nullptr)
	{
		pGhost = new CGhost;

		if (pGhost != nullptr)
		{
			// �̂̓Ǎ�
			pGhost->Load((char*)BODY_PATH[nIdxPlayer]);

			// ������
			pGhost->Init();
		}
	}

	return pGhost;
}

//=====================================================
// ����������
//=====================================================
HRESULT CGhost::Init(void)
{
	// �p���N���X�̏�����
	CMotion::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CGhost::Uninit(void)
{
	// �p���N���X�̏I��
	CMotion::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CGhost::Update(void)
{
	// �p���N���X�̍X�V
	CMotion::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CGhost::Draw(void)
{
	// �p���N���X�̕`��
	CMotion::Draw();

#ifdef _DEBUG
	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}
#endif
}