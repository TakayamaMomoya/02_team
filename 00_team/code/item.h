//*****************************************************
//
// �A�C�e���̏���[item.h]
// Author:���R����
//
//*****************************************************

#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "objectX.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionSphere;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CItem : public CObjectX
{
public:
	CItem(int nPriority = 3);	// �R���X�g���N�^
	~CItem();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItem *Create();

private:
	void GetItem(CObject *pObj);

	CCollisionSphere *m_pCollisionSphere;
};

#endif

