//*****************************************************
//
// 残弾数UIの処理[UIMagazine.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _UI_MAGAZINE_H_
#define _UI_MAGAZINE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************

class CUI;
class CNumber;

//*****************************************************
// クラスの定義
//*****************************************************
class CUIMagazine : public CObject
{
public:

	CUIMagazine(int nPriority = 7);	// コンストラクタ
	~CUIMagazine();	// デストラクタ

	static CUIMagazine* Create(int nIdx);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 posDig, D3DXVECTOR3 posMaxDig);
	void SetSize(float width, float height);
	void SetCol(D3DXCOLOR col);

private:

	struct Sinfo
	{
		int nIdxPlayer;		// 参照するプレイヤーの番号
		int nIdxTexture;					// テクスチャ番号
		static LPDIRECT3DTEXTURE9 pTexture;	// テクスチャへのポインタ
	};

	CNumber* m_pNumDig;			// 装弾数（数字）のポインタ
	CNumber* m_pNumMaxDig;		// 最大装弾数（数字）のポインタ
	Sinfo m_info;	// 自身の情報
};

#endif
