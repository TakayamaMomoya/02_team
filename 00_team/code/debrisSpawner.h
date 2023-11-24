//*****************************************************
//
// �j�Џ���[deris.h]
// Author:���}���V
//
//*****************************************************

#ifndef _DERISSPAWNER_H_
#define _DERISSPAWNER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CDebrisSpawner : public CObjectX
{
public:
	CDebrisSpawner(int nPriority = 3);
	~CDebrisSpawner();

	static CDebrisSpawner* Create(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f }, float fGravity = 0.0f, int nPriority = 3);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);	// �Ǎ�
	static void Unload(void);

private:
	int m_nLife;	// ����
	float m_fDecreaseAlpha;	// ���l������
	D3DXVECTOR3 m_move;	// �ړ���
	float m_fGravity;	
};

#endif