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
class CBillboard;
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
		MENU_PLUS = 0,
		MENU_CHAR,
		MENU_MAX
	};

	struct MenuData
	{
		CBillboard* pMenu2D[MENU_MAX];
		D3DXCOLOR col;
	};

	void MenuInit(void);
	void MenuUpdate(void);

	MenuData m_aMenuData[NUM_PLAYER];	//���ꂼ��̑I�����j���[
	CPlayerManager* m_pPlayerManager;	//�v���C���[�Ǘ�
	STATE m_state;	// ���
	bool bJoin[NUM_PLAYER];	//�Q���������ǂ���
};

#endif