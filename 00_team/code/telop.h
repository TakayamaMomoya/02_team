//*****************************************************
//
// テロップの処理[telop.h]
// Author:小笠原彪
//
//*****************************************************

#ifndef _TELOP_H_
#define _TELOP_H_

#include "main.h"

//*****************************************************
// インクルード
//*****************************************************
class CObject2D;

//*****************************************************
// クラスの定義
//*****************************************************
class CTelop
{
public:
	enum STATE
	{
		STATE_NONE = 0,
		STATE_INIT,
		STATE_END,
		STATE_MAX
	};

public:
	CTelop(int nPriority = 6);	// コンストラクタ
	~CTelop();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTelop* Create(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_pos;
	CObject2D* m_pObjet2D;
	STATE m_state;
	float m_fTimer;
};

#endif

