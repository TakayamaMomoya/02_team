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
class CItem : public CObjectX
{
public:
	enum TYPE
	{
		TYPE_MAGNUM = 0,	// �}�O�i��
		TYPE_MACHINEGUN,	// �}�V���K��
		TYPE_RIFLE,	// ���C�t��
		TYPE_MAX
	};

	CItem(int nPriority = 3);	// �R���X�g���N�^
	~CItem();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItem *Create(void);
	virtual void GetItem(CObject* pObj);

private:
	CCollisionSphere *m_pCollisionSphere;
	CBillboard *m_pInteract;
};

#endif

