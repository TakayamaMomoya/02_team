//*****************************************************
//
// ビームの処理[beam.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _BEAM_H_
#define _BEAM_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CAnim3D;

//*****************************************************
// クラスの定義
//*****************************************************
class CBeam : public CObject
{
public:
	CBeam(int nPriority = 3);	// コンストラクタ
	~CBeam();	// デストラクタ

	static CBeam *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetMtx(D3DXMATRIX mtx) { m_info.mtxWorld = mtx; }
	void SetAnimSize(float fWidth, float fLength) { m_info.fWidthAnim = fWidth; m_info.fLengthAnim = fLength; }

private:
	struct SInfo
	{
		CAnim3D *pAnim;	// アニメーションエフェクト
		D3DXMATRIX mtxWorld;	// ワールドマトリックス
		float fWidthAnim;	// アニメーションの幅
		float fLengthAnim;	// アニメーションの長さ
	};

	void SetAnimVtx(void);

	SInfo m_info;
};

#endif
