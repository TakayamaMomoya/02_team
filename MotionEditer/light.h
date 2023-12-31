//*****************************************************
//
// ライトの処理[light.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************
// マクロ定義
//*****************************************************
#define MAX_LIGHT				(3)			//ライトの最大数

//*****************************************************
// クラス定義
//*****************************************************
class CLight
{
public:
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];
};

#endif