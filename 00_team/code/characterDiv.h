//*****************************************************
//
// 分割キャラクターの処理[characterDiv.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _CHARACTER_DIV_H_
#define _CHARACTER_DIV_H_

//*****************************************************
// インクルード
//*****************************************************
#include "object.h"

//*****************************************************
// 前方宣言
//*****************************************************
class CMotion;

//*****************************************************
// 定数定義
//*****************************************************

//*****************************************************
// クラスの定義
//*****************************************************
class CCharacterDiv : public CObject
{
public:

	CCharacterDiv(int nPriority = 4);	// コンストラクタ
	~CCharacterDiv();					// デストラクタ

	static CCharacterDiv* Create(char* pPathUpper,char* pPathLower);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos) { m_info.pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_info.pos; }
	void SetPositionOld(D3DXVECTOR3 pos) { m_info.posOld = pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_info.posOld; }
	void SetMove(D3DXVECTOR3 move) { m_info.move = move; }
	D3DXVECTOR3 GetMove(void) { return m_info.move; }
	void SetRot(D3DXVECTOR3 rot) { m_info.rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_info.rot; }
	CMotion* GetBody(int nNum) { return m_info.apBody[nNum]; }
	void Load(char* pPathUpper, char* pPathLower);
	void SetMotion(int nNum,int nMotion);
	int GetMotion(int nNum);

private:

	enum Parts
	{
		PARTS_UPPER = 0,	// 上半身
		PARTS_LOWER,		// 下半身
		PARTS_MAX
	};

	struct SInfo
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 posOld;	// 前回の位置
		D3DXVECTOR3 move;	// 移動量
		D3DXVECTOR3 rot;	// 向き
		CMotion* apBody[PARTS_MAX];	// 体
		char* apPath[PARTS_MAX];	// 体のパス
	};

	SInfo m_info;	// 自身の情報
};

#endif