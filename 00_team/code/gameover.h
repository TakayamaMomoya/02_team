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
#include "motion.h"

//===============================================
// 定数定義
//===============================================
namespace
{
	const int NUM_ENEMY = 1;		// 生成する敵の総数
}

//===============================================
// ゲームオーバークラス
//===============================================
class CGameover
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CGameover();						// デフォルトコンストラクタ
	~CGameover();						// デストラクタ

	static CGameover* Create(int nPriority = 3);

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(const D3DXVECTOR3 pos, const bool bMove);

private:	// 自分のみアクセス可能 [アクセス指定子]
	CMotion* m_apModelPlayer[NUM_PLAYER];		// プレイヤーモデルのポインタ
	CMotion* m_apModelEnemy[NUM_ENEMY];			// エネミーモデルのポインタ
};

#endif