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
#include "collision.h"
#include "number.h"

//*****************************************************
// クラスの定義
//*****************************************************
class CRecord
{
public:

	enum GENRE_TYPE
	{
		GENRE_TYPE_DESTROY = 0,
		GENRE_TYPE_MAX
	};

	CRecord();	// コンストラクタ
	~CRecord();	// デストラクタ

	static CRecord* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void AddDestroy(int nIdx);
	void CheckDeathEnemy(CObject* pObj, int nIdx);
	void CheckDeathEnemyAll(CCollision** ppCollsionMissile, D3DXVECTOR3 posMissile, float fRadiusMissile, int nIdx);

	static CRecord* GetInstance(void) { return m_pRecord; }

	int GetDestroy(int nIdx) { return m_aInfo[nIdx].nDestroy; }
private:

	void Debug(void);
	void SetNumPlayer(void);

	struct SInfo
	{
		int nDestroy;	// 敵の破壊数
	};

	static CRecord* m_pRecord;	// 自身のポインタ
	SInfo m_aInfo[NUM_PLAYER];	// 戦績情報
	int m_nNumSuvived;			// 生存者数
};

#endif
