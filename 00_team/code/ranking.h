//*****************************************************
//
// ランキングの処理[Ranking.h]
// Author:酒井南勝
//
//*****************************************************

#ifndef _RANKING_H_
#define _RANKING_H_

//*****************************************************
// インクルード
//*****************************************************

#include "scene.h"

#include "record.h"

//*****************************************************
// 前方宣言
//*****************************************************

class CObject2D;
class CNumber;

class CObject3D;
class CMotion;

//*****************************************************
// 定数定義
//*****************************************************
namespace RANK
{
	const int NUM_MAX = 3;	// 最大数
}

//*****************************************************
// クラスの定義
//*****************************************************
class CRanking : public CScene
{
public:
	
	// 演出の種類
	enum ACTING_TYPE
	{
		ACTING_TYPE_MARCH = 0,	// 行進
		ACTING_TYPE_RUN_AWAY,	// 逃げる
		ACTING_TYPE_CHASE,		// 追いかける
		ACTING_TYPE_MAX
	};

	// 役者の種類
	enum ACTOR_TYPE
	{
		ACTOR_TYPE_PLAYER_ONE = 0,	// プレイヤー01
		ACTOR_TYPE_PLAYER_TWO,		// プレイヤー02
		ACTOR_TYPE_PLAYER_THREE,	// プレイヤー03
		ACTOR_TYPE_PLAYER_FOUR,		// プレイヤー04
		ACTOR_TYPE_ENEMY_ONE,		// 敵01
		ACTOR_TYPE_ENEMY_TWO,		// 敵02
		ACTOR_TYPE_ENEMY_THREE,		// 敵03
		ACTOR_TYPE_MAX
	};

	CRanking();	// コンストラクタ
	~CRanking();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	HRESULT InitUi(void);
	HRESULT InitObj(void);

	void SetUiRecord(void);
	void SetObjActing(void);

	void UpdateUiRecord(void);
	void UpdateActing(void);
	void UpdateNum(void);

	void SetRank(void);
	void ResetRank(void);
	void SetRankNum(void);
	void SortRank(void);
	void SaveRank(void);
	void LoadRank(void);

private:

	struct SInfoVisualUi
	{
		CObject2D* pRecordText;		// レコードのテキスト
		CObject2D* pGenreText;		// 種類のテキスト
		CObject2D* pGenreIcon;		// 種類のアイコン 

		CObject2D* apFace[NUM_PLAYER];	// 各プレイヤーの顔
		CNumber* apNumber[NUM_PLAYER];	// 各プレイヤーの戦績

		CObject2D* apFaceRank[RANK::NUM_MAX];	// ランキングの顔
		CNumber* apNumRank[RANK::NUM_MAX];		// ランキングの数字
	};

	struct SInfoVisualObj
	{
		CObject3D* pField;				// 地面
		CObject3D* pWall;				// 壁
		CMotion* apModelActor[ACTOR_TYPE_MAX];	// プレイヤー
	};

	SInfoVisualUi m_infoVisualUi;		// UIの見た目関連の情報
	SInfoVisualObj m_infoVisualObj;		// オブジェクトの見た目関連の処理

	CRecord::GENRE_TYPE m_typeGenre;	// 戦績の種類
	ACTING_TYPE m_typeActing;			// 演技の種類

	int m_nActingCnt;					// 演技カウント
	int m_nGenreCnt;					// 種類カウント

	int m_aRankScore[CRecord::GENRE_TYPE_MAX][RANK::NUM_MAX];	// ランキングの値
	int m_aRankFace[CRecord::GENRE_TYPE_MAX][RANK::NUM_MAX];	// 顔の番号
	int m_aUpdateIdx[CRecord::GENRE_TYPE_MAX][NUM_PLAYER];		// 更新したランキングの番号
	int m_aUpdateRank[CRecord::GENRE_TYPE_MAX][NUM_PLAYER];		// ランキングの更新の有無
	bool m_aIsAlphaChange[CRecord::GENRE_TYPE_MAX][NUM_PLAYER];	// α値の変化
};

#endif