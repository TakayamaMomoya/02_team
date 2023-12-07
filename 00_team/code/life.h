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
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float width, float height);
	void SetCol(D3DXCOLOR col);
	void SetTexture(const char* pFileName);
	void SetVtxGage(void);

	D3DXCOLOR GetCol(void) { return m_info.col; }

private:

	struct Sinfo
	{
		int nIdxPlayer;		// 参照するプレイヤーの番号

		D3DXVECTOR3 pos;		// 位置
		float fWidth;			// 横幅
		float fHeight;			// 縦幅
		float fWidthSub;		// 減算する横幅
		float fHeightSub;		// 減算する縦幅
		D3DXCOLOR col;			// 色

		int nIdxTexture;					// テクスチャ番号
		static LPDIRECT3DTEXTURE9 pTexture;	// テクスチャへのポインタ
	};

	CUI* m_pUi;		// 2Dオブジェクトのポインタ
	Sinfo m_info;	// 自身の情報
};

#endif
