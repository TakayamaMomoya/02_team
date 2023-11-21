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
class CPlayer;
class CContainer;

//*****************************************************
// �}�N����`
//*****************************************************
namespace
{
	const int MAX_CONTAINER(6);
};

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
		FADE_NONE = 0,	// ����
		FADE_IN,	// �t�F�[�h�C��
		FADE_OUT,	// �t�F�[�h�A�E�g
		FADE_MAX
	};

	enum PLAYER_STATE
	{
		PLAYER_NONE = 0,	// ����
		PLAYER_ENTRY,	// �Q�����
		PLAYER_FREE,	// ���R���
		PLAYER_MAX
	};

	enum MENU
	{
		MENU_PLUS = 0,	// �v���X
		MENU_CHAR,	// ����
		MENU_MAX
	};

	struct MenuData
	{
		CBillboard* pMenu2D[MENU_MAX];	//���j���[
		D3DXCOLOR col;	// �F
		FADE_STATE state;	// ���
	};

	struct PlayerInfo
	{
		CPlayer* pPlayer;	// �v���C���[
		PLAYER_STATE state;	// ���
	};

	void MenuInit(void);
	void MenuDelete(int nPlayer);
	void StartInit(void);
	void ContainerInit(void);
	void ReSetContainer(void);
	void ColorChange(int nPlayer);
	void EntryInput(int nPlayer);
	void MoveLimit(int nPlayer);

	MenuData m_aMenuData[NUM_PLAYER];	// ���ꂼ��̑I�����j���[
	CObject2D* m_pStartUI;	// Start����
	CPlayerManager* m_pPlayerManager;	// �v���C���[�Ǘ�
	PlayerInfo m_apPlayerData[NUM_PLAYER];
	CContainer* m_apContainer[MAX_CONTAINER];
	STATE m_state;	// ���
	bool m_abEntry[NUM_PLAYER];	// �Q���������ǂ���
};

#endif