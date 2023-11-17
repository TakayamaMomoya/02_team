//*****************************************************
//
// �R���e�i�̏���[container.h]
// Author:���R����
//
//*****************************************************

#ifndef _CONTAINER_H_
#define _CONTAINER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "item.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CContainer : public CItem
{
public:
	CContainer(int nPriority = 3);	// �R���X�g���N�^
	~CContainer();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	static CContainer *Create(void);

private:
	enum STATE
	{
		STATE_NONE = 0,	// ���ł��Ȃ����
		STATE_NORMAL,	// �ʏ���
		STATE_OPEN,	// �J���Ă�����
		STATE_MAX
	};
	struct SInfo
	{// ���
		CObjectX *pCap;	// �W�̃I�u�W�F�N�g
		STATE state;	// ���
	};
	void Load(void);
	void Interact(CObject* pObj);
	void Open(void);

	SInfo m_info;
};

#endif

