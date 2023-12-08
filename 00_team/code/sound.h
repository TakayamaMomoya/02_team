//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 高山桃也
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		LABEL_BGM000 = 0,				// タイトルBGM
		LABEL_SE_GET_WEAPON,			// 武器取得
		LABEL_SE_GUNSHOT_00,			// 発砲音00
		LABEL_SE_GUNSHOT_01,			// 発砲音01
		LABEL_SE_OPEN_BOX,				// 箱を開く
		LABEL_SE_APPEARE,				// 登場
		LABEL_BGM_SELECT,				// 選択画面bgm
		LABEL_BGM_GAME,					// ゲームbgm
		LABEL_SE_REPAIR,				// 修繕
		LABEL_SE_GUNSHOT_02,			// 発砲音02
		LABEL_SE_START_GAME,			// ゲームスタート
		LABEL_BGM_TITLE,				// タイトル
		LABEL_SE_LUNCH,					// ロケット発射
		LABEL_SE_GUNSHOT_03,			// 発砲音03

		LABEL_SE_GET_MAGNUM,			// マグナム取得時
		LABEL_SE_GET_MACHINEGUN,		// マシンガン取得時
		LABEL_SE_GET_SHOTGUN,			// ショットガン取得時
		LABEL_SE_GET_RAILGUN,			// レールガン取得時

		LABEL_SE_SWING,					// スウィング
		LABEL_SE_DAMAGE,				// ダメージ
		LABEL_SE_HIT,					// ヒット

		LABEL_SE_DOOR_TOUCH,			// ドアのインタラクト
		LABEL_SE_BOX_BROKEN,			// 箱を破壊

		LABEL_SE_RIFT,					// セレクトリフト
		LABEL_SE_RIFTING,				// 物を持ち上げる
		LABEL_SE_DOOR_OPEN,				// ドアが開く

		LABEL_SE_PAUSE_MENU,			// ポーズ
		LABEL_SE_PAUSE_ARROW,			// ポーズ移動
		LABEL_SE_PAUSE_ENTER,			// ポーズ選択

		LABEL_MAX
	} LABEL;

	typedef enum
	{
		FADESTATE_NONE = 0,	//何もしていない状態
		FADESTATE_IN,	//フェードイン状態
		FADESTATE_OUT,	//フェードアウト状態
		FADESTATE_MAX
	}FADESTATE;

	CSound();	// コンストラクタ
	~CSound();	// デストラクタ

	static CSound *Create(HWND hWnd);
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

	void SetVolume(LABEL label, float fVolume);
	void SetFade(LABEL LabelNow, LABEL LabelNext, float fSpeed);

	static CSound *GetInstance(void) { return m_pSound; }

private:
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[LABEL_MAX];	// オーディオデータ
	DWORD m_aSizeAudio[LABEL_MAX];	// オーディオデータサイズ
	FADESTATE m_fadeSound;	// フェード状態
	LABEL m_SoundLabelNow;	// 現在のサウンドラベル
	LABEL m_SoundLabelNext;	// 次のサウンドラベル
	float m_fSpeedFadeSound;	// サウンドがフェードするスピード
	float m_fVolumeSound;	// サウンドのボリューム

	// サウンドの情報
	SOUNDINFO m_aSoundInfo[LABEL_MAX] =
	{
		{ "data/SOUND/BGM/title.wav", -1 },				// タイトル	
		{ "data/SOUND/SE/get_weapon_00.wav",0 },		// 雑魚武器取得
		{ "data/SOUND/SE/gunshot_sound_00.wav",0 },		// マグナム発砲
		{ "data/SOUND/SE/gunshot_sound_01.wav",0 },		// マシンガン発砲
		{ "data/SOUND/SE/open_weaponbox.wav",0 },		// 武器の箱開く
		{ "data/SOUND/SE/Appearance.wav",0 },			// 登場
		{ "data/SOUND/BGM/select.wav",-1 },				// 選択
		{ "data/SOUND/BGM/game.wav",-1 },				// ゲーム
		{ "data/SOUND/SE/repair.wav",0 },				// 修繕
		{ "data/SOUND/SE/gunshot_sound_03.wav",0 },		// ショットガン発砲
		{ "data/SOUND/SE/start_game.wav",0 },			// ゲームスタート
		{ "data/SOUND/BGM/title_BGM.wav",-1 },			// タイトルサウンド	
		{ "data/SOUND/SE/rocket_lunch.wav",0 },			// ロケット発射
		{ "data/SOUND/SE/gunshot_sound_04.wav",0 },		// レールガン発砲

		{ "data/SOUND/SE/get_magnum.wav",0 },			// マグナムボイス
		{ "data/SOUND/SE/get_submachinegun.wav",0 },	// マシンガンボイス
		{ "data/SOUND/SE/get_shotgun.wav",0 },			// ショットガンボイス
		{ "data/SOUND/SE/get_railgun.wav",0 },			// レールガンボイス

		{ "data/SOUND/SE/swing.wav",0 },				// スウィング
		{ "data/SOUND/SE/damage.wav",0 },				// ダメージ
		{ "data/SOUND/SE/hit.wav",0 },					// ヒット

		{ "data/SOUND/SE/door_open.wav",0 },			// ドアのインタラクト
		{ "data/SOUND/SE/box_broken.wav",0 },			// 箱破壊

		{ "data/SOUND/SE/rift.wav",0 },					// リフト
		{ "data/SOUND/SE/lifting.wav",0 },				// 持ち上げる
		{ "data/SOUND/SE/door_enter.wav",0 },			// ドアが開く

		{ "data/SOUND/SE/pause.wav",0 },				// ポーズ
		{ "data/SOUND/SE/pause_arrow.wav",0 },			// 選択
		{ "data/SOUND/SE/pause_enter.wav",0 },			// 決定
	};

	static CSound *m_pSound;	// 自身のポインタ
};

#endif