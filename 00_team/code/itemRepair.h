//*****************************************************
//
// �C���A�C�e���̏���[ItemRepair.h]
// Author:���R����
//
//*****************************************************

#ifndef _ITEMREPIR_H_
#define _ITEMREPIR_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "item.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CItemRepair : public CItem
{
public:
	CItemRepair(int nPriority = 5);	// �R���X�g���N�^
	~CItemRepair();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItemRepair *Create(void);

private:
	void Load(void);
	void GetItem(CObject* pObj);
};

#endif

