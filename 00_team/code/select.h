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

	enum FADE_STATE
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
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
		FADE_STATE state;
	};

	void MenuInit(void);
	void MenuDelete(int nPlayer);
	void StartInit(void);
	void ColorChange(int nPlayer);
	void EntryInput(int nPlayer);

	MenuData m_aMenuData[NUM_PLAYER];	//���ꂼ��̑I�����j���[
	CObject2D* m_pStartUI;
	CPlayerManager* m_pPlayerManager;	//�v���C���[�Ǘ�
	STATE m_state;	// ���
	bool m_abJoin[NUM_PLAYER];	//�Q���������ǂ���
};

#endif