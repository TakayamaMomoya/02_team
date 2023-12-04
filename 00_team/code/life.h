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

	void SetLife(int nLife);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float width, float height);
	void SetColor(D3DXCOLOR col);

private:

	struct Sinfo
	{
		int nIdxPlayer;		// 参照するプレイヤーの番号
		int nLife;			// 体力の値
		int nIdxTexture;					// テクスチャ番号
		static LPDIRECT3DTEXTURE9 pTexture;	// テクスチャへのポインタ
	};

	CUI* m_pUi;		// 2Dオブジェクトのポインタ
	Sinfo m_info;	// 自身の情報
};

#endif
