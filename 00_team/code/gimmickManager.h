//*****************************************************
//
// ギミックマネージャー[gimmickManager.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _GIMMICKMANAGER_H_
#define _GIMMICKMANAGER_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"
#include <stdio.h>

//*****************************************************
// クラスの定義
//*****************************************************
class CGimmickManager : public CObject
{
public:
	CGimmickManager();	// コンストラクタ
	~CGimmickManager();	// デストラクタ

	static CGimmickManager*Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGimmickManager*GetInstance(void) { return m_pGimmickManager; }

private:
	void Load(void);
	void CreateGimmick(FILE *pFile, char *pTemp);
	void LoadDoor(FILE *pFile, char *pTemp);
	void LoadContainer(FILE *pFile, char *pTemp);
	void LoadRepair(FILE *pFile, char *pTemp);
	void LoadBox(FILE *pFile, char *pTemp);

	static CGimmickManager *m_pGimmickManager;	// 自身のポインタ
};

#endif
