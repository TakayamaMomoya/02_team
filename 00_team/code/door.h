//*****************************************************
//
// �h�A�̏���[door.h]
// Author:���R����
//
//*****************************************************

#ifndef _DOOR_H_
#define _DOOR_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "gimmick.h"

//*****************************************************
// �O���錾
//*****************************************************
class CCollisionCube;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CDoor : public CGimmick
{
public:
	CDoor(int nPriority = 3);	// �R���X�g���N�^
	~CDoor();	// �f�X�g���N�^

	static CDoor *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);

private:
	struct SInfo
	{// ���
		float fLife;	// �̗�
		CCollisionCube *pCollisionCube;	// �����o���̓����蔻��
	};
	void Interact(CObject* pObj);
	void proceed(void);

	SInfo m_info;
};

#endif

