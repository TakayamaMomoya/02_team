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
	
	// 演出の種類
	enum DIRECTION_TYPE
	{
		DIRECTION_TYPE_MARCH = 0,	// 行進
		DIRECTION_TYPE_RUN_AWAY,	// 逃げる
		DIRECTION_TYPE_CHASE,		// 追いかける
		DIRECTION_TYPE_MAX
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

	void UpdateDirection(void);
	HRESULT SetDirection(DIRECTION_TYPE type);

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
		CObject3D* pWall;				// 壁
		CMotion* apModelActor[ACTOR_TYPE_MAX];	// プレイヤー
	};

	SInfoVisualUi m_infoVisualUi;	// UIの見た目関連の情報
	SInfoVisualObj m_infoVisualObj;	// オブジェクトの見た目関連の処理
	DIRECTION_TYPE m_typeDirection;	// 演出の種類
	int m_nDirectionCnt;			// 演出カウント
};

#endif