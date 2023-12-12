//*****************************************************
//
// ランキングの処理[Ranking.h]
// Author:髙山桃也
//
//*****************************************************

#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************
// インクルード
//*****************************************************

#include "scene.h"

//*****************************************************
// 前方宣言
//*****************************************************

class CObject2D;
class CNumber;

//*****************************************************
// クラスの定義
//*****************************************************
class CRanking : public CScene
{
public:

	CRanking();	// コンストラクタ
	~CRanking();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	struct SInfoVisual
	{
		CObject2D* pRecordText;		// レコードのテキスト
		CObject2D* pGenreText;		// 種類のテキスト
		CObject2D* pGenreIcon;		// 種類のアイコン 

		CObject2D* apFace[NUM_PLAYER];	// 各プレイヤーの顔
		CNumber* apNumber[NUM_PLAYER];	// 各プレイヤーの戦績
	};

	SInfoVisual m_infoVisual;	// 見た目関連の情報
};

#endif