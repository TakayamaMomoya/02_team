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
#include "debugproc.h"

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
	ZeroMemory(&m_aInfo[0], sizeof(m_aInfo));
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
// �X�V����
//=====================================================
void CRecord::Update(void)
{
	// �f�o�b�N����
	Debug();
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
// �G�̎��S���菈��
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

//=====================================================
// �����������ׂĂ̓G�̎��S���菈��
//=====================================================
void CRecord::CheckDeathEnemyAll(CCollision** ppCollsionMissile,D3DXVECTOR3 posMissile,float fRadiusMissile, int nIdx)
{
	bool bHit = false;

	CCollision** ppCollision = ppCollsionMissile;

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == CCollision::TYPE_SPHERE)
			{
				if (CCollision::TAG_ENEMY == CCollision::TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != CCollision::TAG_ENEMY)
				{
					continue;
				}

				// �����擾
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - posMissile;

				float fLength = D3DXVec3Length(&vecDiff);

				if (fLength < ppCollision[nCnt]->GetRadius() + fRadiusMissile)
				{
					CRecord* pRecord = CRecord::GetInstance();

					if (pRecord != nullptr)
					{
						// ���݂̃v���C���[�̔j�󐔂����Z
						pRecord->AddDestroy(nIdx);
					}
				}
			}
		}
	}
}

//=====================================================
// �f�o�b�O�\��
//=====================================================
void CRecord::AllSort(void)
{
	// �G�̔j�󐔂̃\�[�g
	for (int nCutRank = 0; nCutRank < NUM_PLAYER; nCutRank++)
	{
		//�u�������ԍ��ɗv�f1�̃f�[�^�ԍ�����
		for (int nCutScoreRank = 0; nCutScoreRank < NUM_PLAYER; nCutScoreRank++)
		{
			//�v�f2�ɉ��̐��l����
			if (m_aInfo[nCutRank].nDestroy < m_aInfo[nCutScoreRank].nDestroy)
			{
				// �u�������ԍ���萔�l���Ⴂ�ꍇ���ʂ�������
				m_aInfo[nCutRank].nDestroyRank++;
			}
		}
	}
}

//=====================================================
// �f�o�b�O�\��
//=====================================================
void CRecord::Debug(void)
{
#ifndef _DEBUG

	return;

#endif

	CDebugProc* pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\nP1�̓G�̔j��[%d]", m_aInfo[0].nDestroy);
	pDebugProc->Print("\nP2�̓G�̔j��[%d]", m_aInfo[1].nDestroy);
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