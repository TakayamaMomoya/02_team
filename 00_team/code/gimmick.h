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
class CBillboard;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CGimmick : public CObjectX
{
public:
	CGimmick(int nPriority = 3);	// �R���X�g���N�^
	~CGimmick();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGimmick *Create(void);
	virtual void Interact(CObject* pObj);
	CCollisionSphere *GetCollisionSphere(void) { return m_pCollisionSphere; }
	void SetEnable(bool bEnable) { m_bEnable = bEnable; }

private:
	CCollisionSphere *m_pCollisionSphere;
	CBillboard *m_pInteract;
	bool m_bEnable;	// �C���^���N�g�ł��邩�ǂ���

	CGimmick *m_pPrev;	// �O�̃|�C���^
	CGimmick *m_pNext;	// ���̃|�C���^

	static CGimmick *m_pHead;	// �擪�̃A�h���X
	static CGimmick *m_pTail;	// �Ō���̃A�h���X
};

#endif

