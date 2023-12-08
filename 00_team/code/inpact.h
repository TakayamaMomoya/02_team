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
	struct SInfo
	{
		float fRadiusDiff;	// 半径にどれだけ差をつけるか
		float fLife;	// 寿命
		float fLifeInitial;	// 初期寿命
	};

	void SetVtx(void);
	void ManageLife(void);

	SInfo m_info;
};
#endif