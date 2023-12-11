//*****************************************************
//
// 戦績処理のヘッター[record.h]
// Author:酒井南勝
//
//*****************************************************

#ifndef _RECORD_H_
#define _RECORD_H_

//*****************************************************
// インクルード
//*****************************************************

#include "object.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CRecord
{
public:
	CRecord();	// コンストラクタ
	~CRecord();	// デストラクタ

	static CRecord* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void SetPlayer(void);
	void AddDestroy(int nIdx);

	static CRecord* GetInstance(void) { return m_pRecord; }

private:

	struct SInfo
	{
		int nDestroy;	// 敵の破壊数
	};

	static CRecord* m_pRecord;	// 自身のポインタ
	SInfo m_aInfo[NUM_PLAYER];	// 戦績情報
	int m_nNumSuvived;			// 生存者数
};

#endif
