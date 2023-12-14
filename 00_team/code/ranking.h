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

class CObject3D;
class CMotion;

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

	HRESULT InitUi(void);
	HRESULT InitObj(void);

private:

	struct SInfoVisualUi
	{
		CObject2D* pRecordText;		// レコードのテキスト
		CObject2D* pGenreText;		// 種類のテキスト
		CObject2D* pGenreIcon;		// 種類のアイコン 

		CObject2D* apFace[NUM_PLAYER];	// 各プレイヤーの顔
		CNumber* apNumber[NUM_PLAYER];	// 各プレイヤーの戦績
	};

	struct SInfoVisualObj
	{
		CObject3D* pField;				// 地面
		CMotion* apModelPlayer[NUM_PLAYER];	// プレイヤー
	};

	SInfoVisualUi m_infoVisualUi;	// UIの見た目関連の情報
	SInfoVisualObj m_infoVisualObj;	// オブジェクトの見た目関連の処理
};

#endif