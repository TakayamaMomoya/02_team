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
		{ "data/SOUND/SE/repair.wav",0}					// 修繕
	};

	static CSound *m_pSound;	// 自身のポインタ
};

#endif