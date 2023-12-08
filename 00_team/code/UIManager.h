//*****************************************************
//
// UIマネージャー[UIManager.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************

#include "object.h"
#include "weapon.h"

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

	void CreateFrame(int nIdx);
	void CreateFace(int nIdx);
	void CreateWeapon(int nIdx);
	void CreateLife(int nIdx);
	void CreateUIMagazine(int nIdx);

	void UpdateUIWeapon(void);
	void UpdateUIColor(void);

	struct SInfo
	{
		float fUIColorAlpha;		// UIのアルファ値
		CWeapon::TYPE weaponType;	// 武器の種類
		bool bIsWeaponNull;			// 武器の有無

		CUI *pUiFrame;				// フレームUI
		CUI *pUiFace;				// 顔のUI			
		CUI *pUiWeapon;				// 武器のUI			
		CLife *pLife;				// ライフUI
		CUIMagazine* pUIMagazine;	// 装弾数UI
	};

	static CUIManager *m_pUIManager;	// 自身のポインタ
	bool m_bDisp;				// UIを表示するかどうか
	SInfo m_aInfo[NUM_PLAYER];	// 自身の情報
};

#endif
