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
// �O���錾
//*****************************************************
class CPlayer;

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
	void CheckPlayerAlive(void);
	void FollowPlayerHand(void);

	CPlayer *m_pPlayer;
};

#endif

