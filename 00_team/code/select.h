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
class CLift;

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const int MAX_CONTAINER(2);
};

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CSelect : public CScene
{
public:
	CSelect();	// �R���X�g���N�^
	~CSelect();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update();
	void Draw();

private:
	enum SELECT_STATE
	{
		STATE_BEFORE = 0,
		STATE_GO,
		STATE_MAX
	};
	// �t�F�[�h�̎��(UI�_�ŗp)
	enum FADE_STATE
	{
		FADE_NONE = 0,	// ����
		FADE_IN,	// �t�F�[�h�C��
		FADE_OUT,	// �t�F�[�h�A�E�g
		FADE_MAX
	};
	// �v���C���[��Ԃ̎��
	enum PLAYER_STATE
	{
		PLAYER_NONE = 0,	// ����
		PLAYER_ENTRY,	// �Q�����
		PLAYER_FREE,	// ���R���
		PLAYER_INGAME,	// �Q�[���֓���
		PLAYER_MAX
	};
	// ���j���[�̎��
	enum JOIN_UI
	{
		MENU_PLUS = 0,	// �v���X
		MENU_CHAR,	// ����
		MENU_MAX
	};
	// ���j���[�̍\����
	struct SJoinUi_info
	{
		CBillboard* pUi2D[MENU_MAX];	//���j���[
		D3DXCOLOR col;	// �F
		FADE_STATE state;	// ���
	};
	// �v���C���[���̍\����
	struct PlayerInfo
	{
		CPlayer* pPlayer;	// �v���C���[
		PLAYER_STATE state;	// ���
	};
	// �R���e�i���̍\����
	struct CContainerInfo
	{
		CContainer* pContainer;
		float fReSpawnTimer;
	};

	void MenuInit(void);	// ���j���[�̏����ݒ�
	void MenuDelete(int nPlayer);	// ���j���[�̍폜
	void MenuColorChange(int nPlayer);	// ���j���[�F�̕ύX

	void StartInit(void);	// �X�^�[�g�̏����ݒ�

	void ContainerInit(void);	// �R���e�i�̏����ݒ�
	void ReSetContainer(void);	// �R���e�i�̍Đݒu

	void EntryInput(int nPlayer);	// �Q���̓���
	void MoveLimit(int nPlayer);	// �s������
	void PlayerShowUp(int nPlayer);	// �v���C���[�̓o��

	void Rift(void);	// ���t�g�̐ݒ�

	SJoinUi_info m_aJoinUiData[NUM_PLAYER];	// ���ꂼ��̑I�����j���[
	CObject2D* m_pStartUI;	// Start����
	CPlayerManager* m_pPlayerManager;	// �v���C���[�Ǘ�
	PlayerInfo m_apPlayerData[NUM_PLAYER];	// �v���C���[���
	CContainerInfo m_aContainerData[MAX_CONTAINER];	// �R���e�i
	CLift* m_pLift;	// ���t�g�̈ʒu
	SELECT_STATE m_selectState;	// �l���I���̏��
	bool m_abEntry[NUM_PLAYER];	// �Q���������ǂ���
	bool m_bRiftCamera;
	bool m_bOk;
};

#endif