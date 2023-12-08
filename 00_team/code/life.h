//*****************************************************
//
// ライフ表示の処理[life.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CUI;

//*****************************************************
// クラスの定義
//*****************************************************
class CLife : public CObject
{
public:

	CLife(int nPriority = 7);	// コンストラクタ
	~CLife();	// デストラクタ

	static CLife *Create(int nIdx);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetLife(void);
	void SetPosition(D3DXVECTOR3 posLife, D3DXVECTOR3 posLifeFrame);
	void SetSize(float width, float height);
	void SetCol(D3DXCOLOR colLife, D3DXCOLOR colLifeFrame);
	void SetTexture(const char* pFileName);
	void SetVtxGage(void);

	D3DXCOLOR GetColLife(void) { return m_info.colLife; }
	D3DXCOLOR GetColLifeFrame(void) { return m_info.colLifeFrame; }

private:

	struct Sinfo
	{
		int nIdxPlayer;		// 参照するプレイヤーの番号

		D3DXVECTOR3 posLife;		// 位置
		D3DXVECTOR3 posLifeFrame;	// 位置枠
		float fWidth;				// 横幅
		float fHeight;				// 縦幅
		float fWidthSub;			// 減算する横幅
		float fHeightSub;			// 減算する縦幅
		D3DXCOLOR colLife;			// 色
		D3DXCOLOR colLifeFrame;		// 色枠

		int nIdxTexture;					// テクスチャ番号
		static LPDIRECT3DTEXTURE9 pTexture;	// テクスチャへのポインタ
	};

	CUI* m_pUILife;			// ライフのUI
	CUI* m_pUILifeFrame;	// ライフの枠UI
	Sinfo m_info;			// 自身の情報
};

#endif
