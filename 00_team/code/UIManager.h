//*****************************************************
//
// UI�}�l�[�W���[[UIManager.h]
// Author:���R����
//
//*****************************************************

#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************

class CUI;
class CLife;
class CUIMagazine;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CUIManager : public CObject
{
public:
	CUIManager();	// �R���X�g���N�^
	~CUIManager();	// �f�X�g���N�^

	static CUIManager *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIManager *GetInstance(void) { return m_pUIManager; }
	bool IsDisp(void) { return m_bDisp; }
	void EnableDisp(bool bDisp) { m_bDisp = bDisp; }
	void SetPlayer(int nIdx);

private:

	CUI* CreateUi(void);
	CLife* CreateLife(int nIdx);
	CUIMagazine* CreateUIMagazine(int nIdx);

	struct SInfo
	{
		CUI *pUiFrame;				// �t���[��UI
		CUI *pUiFace;				// ���UI			
		CUI *pUiWeapon;				// �����UI			
		CLife *pLife;				// ���C�tUI
		CUIMagazine* pUIMagazine;	// ���e��UI
	};

	static CUIManager *m_pUIManager;	// ���g�̃|�C���^
	bool m_bDisp;				// UI��\�����邩�ǂ���
	SInfo m_aInfo[NUM_PLAYER];	// ���g�̏��
};

#endif
