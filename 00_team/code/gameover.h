//=========================================================
//
// ゲームオーバー処理 [gameover.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _GAMEOVER_H_     // このマクロ定義がされてなかったら
#define _GAMEOVER_H_     // 2重インクルード防止のマクロ定義する

//===============================================
// インクルード
//===============================================
#include "main.h"

//===============================================
// ゲームオーバークラス
//===============================================
class CGameover
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CGameover();						// デフォルトコンストラクタ
	~CGameover();						// デストラクタ

	static CGameover* Create(int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(const D3DXVECTOR3 pos, const bool bMove);

private:	// 自分のみアクセス可能 [アクセス指定子]
};

#endif