//*****************************************************
//
// モーションの処理[motion.h]
// Author:��山桃也
//
//*****************************************************

#ifndef _MOTION_H_
#define _MOTION_H_

//*****************************************************
// インクルード
//*****************************************************
#include "parts.h"
#include "object.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define MAX_PARTS	(20)	// パーツの最大数
#define MAX_MOTION	(20)	// モーションの最大数

//*****************************************************
// クラスの定義
//*****************************************************
class CMotion : public CObject
{
public:
	//キーの構造体
	typedef struct
	{
		float fPosX;				//位置X
		float fPosY;				//位置Y
		float fPosZ;				//位置Z
		float fRotX;				//向きX
		float fRotY;				//向きY
		float fRotZ;				//向きZ
	}KEY;

	//キー情報構造体
	typedef struct
	{
		int nFrame;					//再生フレーム
		KEY aKey[MAX_PARTS];			//各モデルのキー要素
	}KEY_INFO;

	// パーティクル情報構造体
	typedef struct
	{
		int nKey;	//生成するキー
		int nFrame;	//生成するフレーム
		int nType;	// 種類
		D3DXVECTOR3 offset;	// オフセット位置
		int nIdxParent;	// 親となるパーツの番号
	}PARTICLE_INFO;

	//モーション情報の構造体
	typedef struct
	{
		bool bLoop;						//ループするかどうか
		int nNumKey;					//キーの総数
		KEY_INFO aKeyInfo[MAX_PARTS];	//キー情報
		int nNumParticle;	// パーティクルの数
		PARTICLE_INFO *pParticle;	// パーティクルのポインタ
	}MOTION_INFO;

	// パーツの構造体
	typedef struct
	{
		int nIdx;
		int nIdxParent;
		CParts *m_pParts;
	}Parts;

	// メンバ関数
	CMotion();	// コンストラクタ
	~CMotion();	// デストラクタ
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(char *pPath);
	void MultiplyMtx(void);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	// 設定処理
	void SetPositionOld(D3DXVECTOR3 pos) { m_posOld = pos; }	// 設定処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	// 取得処理
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }	// 取得処理
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetMotion(int nMotionType);
	int GetMotion(void) { return m_motionType; }
	void SetKeyOld(void);
	static CMotion *Create(char *pPath);
	void Motion(void);
	void Input(void);

private:
	void DrawMotionState(void);
	void SetPose(void);
	void SetTransform(void);
	void SaveMotion(void);
	void Reset(void);

	Parts *m_apParts[MAX_PARTS];	// パーツの構造体
	MOTION_INFO m_aMotionInfo[MAX_MOTION];	//モーション情報の構造体
	KEY m_aKeyOld[MAX_PARTS];	// 前回のキー情報の構造体
	int m_nNumMotion;	//モーションの総数
	int m_motionType;	//モーションの種類
	int m_motionTypeOld;	//前回のモーションの種類
	bool m_bLoopMotion;	//ループするかどうか
	int m_nNumKey;	//キーの総数
	int m_nKey;	//現在のキー
	int m_nCounterMotion;	//モーションカウンター
	int m_nNumParts;	// パーツの数
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_posOld;	// 前回の位置
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR3 m_rot;	//	向き
	D3DXMATRIX m_mtxWorld;	// マトリックス
	int m_nIdxParts;
	bool m_bMotion;
	bool m_bSetUp;
};

#endif