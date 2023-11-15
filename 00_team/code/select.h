//*****************************************************
//
// �I������[select.h]
// Author:���}���V
//
//*****************************************************
#ifndef _SELECT_H_
#define _SELECT_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// �O���錾
//*****************************************************
class CObject2D;
class CPlayerManager;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CSelect : public CScene
{
public:
	CSelect();	// �R���X�g���N�^
	~CSelect();	// �f�X�g���N�^

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();

private:
	enum STATE
	{
		STATE_NONE = 0,	// �������ĂȂ����
		STATE_OUT,	// �t�F�[�h�A�E�g���
		START_MAX
	};

	enum MENU
	{
		MENU_FRAME = 0,
		MENU_NUMBER,
		MENU_MAX
	};

	struct MenuData
	{
		CObject2D* pMenu2D[MENU_MAX];
		D3DXCOLOR col;
	};

	void MenuInit(void);
	void MenuUpdate(void);

	MenuData m_aMenuData[NUM_PLAYER];	//�I�����j���[
	CPlayerManager* m_pPlayerManager;	//�v���C���[�Ǘ�
	STATE m_state;	// ���
	bool bJoin[NUM_PLAYER];	//�Q���������ǂ���
};

#endif