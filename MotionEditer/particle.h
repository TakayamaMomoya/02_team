//*****************************************************
//
// パーティクル処理[particle.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// クラス定義
//*****************************************************
class CParticle : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// 何でもない
		TYPE_EXPLOSION,	// 爆発
		TYPE_MAX
	}TYPE;

	CParticle(int nPriority = 3);	// コンストラクタ
	~CParticle();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};
	static CParticle *Create(D3DXVECTOR3 pos, TYPE type);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); }	// 取得処理
	float GetWidth(void) { return 0.0f; }	// サイズ取得
	float GetHeight(void) { return 0.0f; }	// サイズ取得

private:
	D3DXVECTOR3 m_pos;	// 位置
	int m_nLife;	// 寿命
	int m_nNumEffect;	// エフェクトの数
	float m_fSpeed;	// エフェクトの基準スピード
	D3DXCOLOR m_col;	// 色
};

#endif