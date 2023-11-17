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
	static CContainer *Create(void);

private:
	void Load(void);
	void Interact(CObject* pObj);
};

#endif

