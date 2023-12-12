//*****************************************************
//
// ��я���[record.cpp]
// Author:����쏟
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "record.h"

#include "playerManager.h"
#include "enemyManager.h"
#include "enemy.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CRecord* CRecord::m_pRecord = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CRecord::CRecord()
{
	ZeroMemory(&m_aInfo[0],sizeof(m_aInfo));
	m_nNumSuvived = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CRecord::~CRecord()
{

}

//=====================================================
// ��������
//=====================================================
CRecord* CRecord::Create(void)
{
	if (m_pRecord == nullptr)
	{// �C���X�^���X����
		m_pRecord = new CRecord;

		// ����������
		m_pRecord->Init();
	}

	return m_pRecord;
}

//=====================================================
// ����������
//=====================================================
HRESULT CRecord::Init(void)
{
	// �v���C���[���̐ݒ菈��
	SetNumPlayer();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CRecord::Uninit(void)
{
	m_pRecord = nullptr;

	delete this;
}

//=====================================================
// �v���C���[�̐���ݒ菈��
//=====================================================
void CRecord::SetNumPlayer(void)
{
	CPlayerManager* pPlayerMagazine = CPlayerManager::GetInstance();

	if (pPlayerMagazine != nullptr)
	{
		// �ő吶���Ґ���ݒ�
		m_nNumSuvived = pPlayerMagazine->GetNumPlayer();
	}
}

//=====================================================
// �G�̔j�󐔂����Z����
//=====================================================
void CRecord::AddDestroy(int nIdx)
{
	// �v���C���[�ԍ����ő吔�����Ȃ�
	if (m_nNumSuvived > nIdx)
	{
		// �j�󐔂����Z
		m_aInfo[nIdx].nDestroy++;
	}
}

//=====================================================
// �G�̎��S�̗L���𔻒�
//=====================================================
void CRecord::CheckDeathEnemy(CObject* pObj,int nIdx)
{
	CEnemyManager* pEnemyManager = CEnemyManager::GetInstance();

	if (pEnemyManager == nullptr || pObj == nullptr)
	{
		return;
	}

	CEnemy* pEnemy = pEnemyManager->GetHead();

	while (pEnemy != nullptr)
	{
		CEnemy* pEnemyNext = pEnemy->GetNext();

		if ((CObject*)pEnemy == pObj)
		{
			// �G�̗L���𔻒�
			if (pEnemy->GetState() == CEnemy::STATE_DEATH)
			{
				CRecord* pRecord = CRecord::GetInstance();

				if (pRecord != nullptr)
				{
					// ���݂̃v���C���[�̔j�󐔂����Z
					pRecord->AddDestroy(nIdx);
				}
			}
		}

		pEnemy = pEnemyNext;
	}
}