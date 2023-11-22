//*****************************************************
//
// 破片処理[deris.h]
// Author:小笠原彪
//
//*****************************************************

#ifndef _DERIS_H_
#define _DERIS_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラス定義
//*****************************************************
class CDebris : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// 何でもない
		TYPE_EXPLOSION,	// 爆発
		TYPE_MAX
	}TYPE;

	CDebris(int nPriority = 3);	// コンストラクタ
	~CDebris();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};
	static CDebris* Create(D3DXVECTOR3 pos, TYPE type, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f }, D3DXVECTOR3* pPosOwner = nullptr, int nPriorityEffect = 5);
	void SetPosition(D3DXVECTOR3 pos);
	static void Load(void);	// 読込処理
	static void Unload(void);	// 破棄処理

private:
	typedef struct
	{// パーティクル情報
		int nLife;	// 寿命
		int nLifeDebris;	// 破片の寿命
		int nNumDebris;	// 破片の数
		float fSpeed;	// 破片の基準スピード
		D3DXCOLOR col;	// 色
		float fGravity;	// 重力
		float fRangeRot;	// 向きのランダム範囲
		int nRot;	// 向きを反映するかどうか
	}PARTICLE_INFO;

	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3* m_pPosOwner;	// 持ち主の位置
	D3DXVECTOR3 m_rot;	// 向き
	int m_nLife;	// 寿命
	static PARTICLE_INFO* m_apDebris[TYPE_MAX + 1];
	TYPE m_type; // 種類
	int m_nPriorityDebris;
};

#endif