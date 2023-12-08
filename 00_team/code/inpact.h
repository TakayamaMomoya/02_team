//*****************************************************
//
// 衝撃波の処理[inpact.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _INPACT_H_
#define _INPACT_H_

//*****************************************************
// インクルード
//*****************************************************
#include "meshcylinder.h"

//*****************************************************
// クラス定義
//*****************************************************
class CInpact : public CMeshCylinder
{
public:
	CInpact(int nPriority = 5);	// コンストラクタ
	~CInpact();	// デストラクタ
	static CInpact *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif