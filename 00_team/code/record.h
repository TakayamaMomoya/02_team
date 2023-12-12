//*****************************************************
//
// ��я����̃w�b�^�[[record.h]
// Author:����쏟
//
//*****************************************************

#ifndef _RECORD_H_
#define _RECORD_H_

//*****************************************************
// �C���N���[�h
//*****************************************************

#include "object.h"
#include "collision.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRecord
{
public:
	CRecord();	// �R���X�g���N�^
	~CRecord();	// �f�X�g���N�^

	static CRecord* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void AddDestroy(int nIdx);
	void CheckDeathEnemy(CObject* pObj, int nIdx);
	void CheckDeathEnemyAll(CCollision** ppCollsionMissile, D3DXVECTOR3 posMissile, float fRadiusMissile, int nIdx);

	static CRecord* GetInstance(void) { return m_pRecord; }

private:

	void Debug(void);
	void SetNumPlayer(void);

	struct SInfo
	{
		int nDestroy;	// �G�̔j��
	};

	static CRecord* m_pRecord;	// ���g�̃|�C���^
	SInfo m_aInfo[NUM_PLAYER];	// ��я��
	int m_nNumSuvived;			// �����Ґ�
};

#endif
