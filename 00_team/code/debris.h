//*****************************************************
//
// �j�Џ���[deris.h]
// Author:���}���V
//
//*****************************************************

#ifndef _DERIS_H_
#define _DERIS_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CDebris : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_EXPLOSION,	// ����
		TYPE_MAX
	}TYPE;

	CDebris(int nPriority = 3);	// �R���X�g���N�^
	~CDebris();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};
	static CDebris* Create(D3DXVECTOR3 pos, TYPE type, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f }, D3DXVECTOR3* pPosOwner = nullptr, int nPriorityEffect = 5);
	void SetPosition(D3DXVECTOR3 pos);
	static void Load(void);	// �Ǎ�����
	static void Unload(void);	// �j������

private:
	typedef struct
	{// �p�[�e�B�N�����
		int nLife;	// ����
		int nLifeDebris;	// �j�Ђ̎���
		int nNumDebris;	// �j�Ђ̐�
		float fSpeed;	// �j�Ђ̊�X�s�[�h
		D3DXCOLOR col;	// �F
		float fGravity;	// �d��
		float fRangeRot;	// �����̃����_���͈�
		int nRot;	// �����𔽉f���邩�ǂ���
	}PARTICLE_INFO;

	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3* m_pPosOwner;	// ������̈ʒu
	D3DXVECTOR3 m_rot;	// ����
	int m_nLife;	// ����
	static PARTICLE_INFO* m_apDebris[TYPE_MAX + 1];
	TYPE m_type; // ���
	int m_nPriorityDebris;
};

#endif