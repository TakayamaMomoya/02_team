//*****************************************************
//
// 選択処理[select.h]
// Author:小笠原彪
//
//*****************************************************
#ifndef _SELECT_H_
#define _SELECT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "scene.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CBillboard;
class CObject2D;
class CPlayerManager;

//*****************************************************
// クラスの定義
//*****************************************************
class CSelect : public CScene
{
public:
	CSelect();	// コンストラクタ
	~CSelect();	// デストラクタ

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update();
	virtual void Draw();

private:
	enum STATE
	{
		STATE_NONE = 0,	// 何もしてない状態
		STATE_OUT,	// フェードアウト状態
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

	MenuData m_aMenuData[NUM_PLAYER];	//それぞれの選択メニュー
	CObject2D* m_pStartUI;
	CPlayerManager* m_pPlayerManager;	//プレイヤー管理
	STATE m_state;	// 状態
	bool m_abJoin[NUM_PLAYER];	//参加したかどうか
};

#endif