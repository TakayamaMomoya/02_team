//*****************************************************
//
// ����A�C�e���̏���[ItemWeapon.h]
// Author:���R����
//
//*****************************************************

#ifndef _ITEMWEAPON_H_
#define _ITEMWEAPON_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gimmick.h"
#include "weapon.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CItemWeapon : public CGimmick
{
public:
	CItemWeapon(int nPriority = 3);	// �R���X�g���N�^
	~CItemWeapon();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItemWeapon *Create(CWeapon::TYPE type);

private:
	void Load(void);
	void Interact(CObject* pObj);
	void ApplyEffect(CPlayer *pPlayer);
	void CollisionField(void);
	void BindEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move);

	CWeapon::TYPE m_type;
};

#endif

