//*****************************************************
//
// UIマネージャー[UIManager.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************

class CUI;
class CLife;
class CUIMagazine;

//*****************************************************
// クラスの定義
//*****************************************************
class CUIManager : public CObject
{
public:
	CUIManager();	// コンストラクタ
	~CUIManager();	// デストラクタ

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

	CUI* CreateFrame(void);
	CLife* CreateLife(int nIdx);
	CUIMagazine* CreateUIMagazine(int nIdx);

	struct SInfo
	{
		CUI *pFrame;				// フレームUI
		CLife *pLife;				// ライフUI
		CUIMagazine* pUIMagazine;	// 装弾数UI
	};

	static CUIManager *m_pUIManager;	// 自身のポインタ
	bool m_bDisp;				// UIを表示するかどうか
	SInfo m_aInfo[NUM_PLAYER];	// 自身の情報
};

#endif
