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
	static CItem *Create(TYPE type);

private:
	void Load(void);
	void GetItem(CObject* pObj);
	void ApplyEffect(CPlayer *pPlayer);

	TYPE m_type;
	CCollisionSphere *m_pCollisionSphere;
};

#endif

