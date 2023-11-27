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
#include "objectX.h"

//*****************************************************
// クラス定義
//*****************************************************
class CDebris : public CObjectX
{
public:
	CDebris(int nPriority = 3);
	~CDebris();

	static CDebris* Create(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move = { 0.0f,0.0f,0.0f }, float fGravity = 0.0f, int nPriority = 3);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);	// 読込
	static void Unload(void);

private:
	int m_nLife;	// 寿命
	float m_fDecreaseAlpha;	// α値減少量
	D3DXVECTOR3 m_move;	// 移動量
	float m_fGravity;
};

#endif