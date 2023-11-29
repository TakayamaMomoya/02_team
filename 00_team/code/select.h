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
class CPlayer;
class CContainer;
class CStartLocation;

//*****************************************************
// マクロ定義
//*****************************************************
namespace
{
	const int MAX_CONTAINER(6);
};

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
		FADE_NONE = 0,	// 無し
		FADE_IN,	// フェードイン
		FADE_OUT,	// フェードアウト
		FADE_MAX
	};

	enum PLAYER_STATE
	{
		PLAYER_NONE = 0,	// 無し
		PLAYER_ENTRY,	// 参加状態
		PLAYER_FREE,	// 自由状態
		PLAYER_INGAME,	// ゲームへ入る
		PLAYER_MAX
	};

	enum MENU
	{
		MENU_PLUS = 0,	// プラス
		MENU_CHAR,	// 文字
		MENU_MAX
	};

	struct MenuData
	{
		CBillboard* pMenu2D[MENU_MAX];	//メニュー
		D3DXCOLOR col;	// 色
		FADE_STATE state;	// 状態
	};

	struct PlayerInfo
	{
		CPlayer* pPlayer;	// プライヤー
		PLAYER_STATE state;	// 状態
	};

	struct CContainerInfo
	{
		CContainer* pContainer;
		float fReSpawnTimer;
	};

	void MenuInit(void);
	void MenuDelete(int nPlayer);
	void StartInit(void);
	void ContainerInit(void);
	void ReSetContainer(void);
	void ColorChange(int nPlayer);
	void EntryInput(int nPlayer);
	void MoveLimit(int nPlayer);
	void PlayerShowUp(int nPlayer);

	void rift(void);

	MenuData m_aMenuData[NUM_PLAYER];	// それぞれの選択メニュー
	CObject2D* m_pStartUI;	// Start文字
	CPlayerManager* m_pPlayerManager;	// プレイヤー管理
	PlayerInfo m_apPlayerData[NUM_PLAYER];
	CContainerInfo m_aContainerData[MAX_CONTAINER];
	//CContainer* m_apContainer[MAX_CONTAINER];
	CStartLocation* m_pStartLocation;
	STATE m_state;	// 状態
	bool m_abEntry[NUM_PLAYER];	// 参加したかどうか
	bool m_bRiftCamera;
	bool m_bOk;
};

#endif