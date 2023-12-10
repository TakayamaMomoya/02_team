//*****************************************************
//
// ミサイル処理[missile.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _MISSILE_H_
#define _MISSILE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "collision.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define MAX_HIT	(54)	// 最大で覚えられる命中したオブジェクト

//*****************************************************
// 前方宣言
//*****************************************************
class CCollisionSphere;
class COrbit;
class CCollisionSphere;

//*****************************************************
// クラスの定義
//*****************************************************
class CMissile : public CObject
{
public:
	CMissile(int nPriority = 6);	// コンストラクタ
	~CMissile();	// デストラクタ

	static CMissile *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetNumAll(void) { return m_nNumAll; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }

private:
	void Death(void);

	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_posOld;	// 前回の位置
	float m_fLife;	// 寿命
	static int m_nNumAll;	// 総数
	CCollisionSphere *m_pCollisionSphere;	// 球の当たり判定
	float m_fDamage;	// 与ダメージ
};

#endif