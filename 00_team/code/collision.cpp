//*****************************************************
//
// 当たり判定処理[collision.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "collision.h"
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "manager.h"
#include "debugproc.h"
#include "billboard.h"
#include "texture.h"
#include "effect3D.h"
#include "universal.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const int NUM_EDGE = 4;	// 辺の数
	const int NUM_WALL = 2;	// 壁の数
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CCollision *CCollision::m_apCollision[NUM_OBJECT] = {};	// 当たり判定管理用の配列
int CCollision::m_nNumAll = 0;

//=====================================================
// コンストラクタ
//=====================================================
CCollision::CCollision()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_tag = TAG_NONE;
	m_type = TYPE::TYPE_NONE;
	m_nID = -1;
	m_pObjectOwner = nullptr;
	m_pObjectOther = nullptr;

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apCollision[nCnt] == nullptr)
		{// 保管する
			m_apCollision[nCnt] = this;

			// ID記憶
			m_nID = nCnt;

			m_nNumAll++;

			break;
		}
	}
}

//=====================================================
// デストラクタ
//=====================================================
CCollision::~CCollision()
{
	m_nNumAll--;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CCollision::Uninit(void)
{
	if (m_apCollision[m_nID] != nullptr)
	{
		m_apCollision[m_nID] = nullptr;
	}

	if (m_pObjectOwner != nullptr)
	{
		m_pObjectOwner = nullptr;
	}

	if (m_pObjectOther != nullptr)
	{
		m_pObjectOther = nullptr;
	}

	Release();
}

//=====================================================
// 削除処理
//=====================================================
void CCollision::DeleteAll(void)
{
	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (m_apCollision[nCnt] != nullptr)
		{// 削除する
			m_apCollision[nCnt]->Uninit();
		}
	}
}

//=====================================================
// 更新処理
//=====================================================
void CCollision::Update(void)
{

}

//=====================================================
// キューブとのトリガー判定
//=====================================================
bool CCollision::TriggerCube(TAG tag)
{
	// 変数宣言
	bool bHitOld = false;
	bool bHit = false;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;

	// 当たり判定の取得
	CCollision **ppCollision = GetCollision();

	pos = GetOwner()->GetPosition();
	posOld = GetOwner()->GetPositionOld();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE)
			{
				if (ppCollision[nCnt]->GetTag() != tag && tag != TAG_NONE)
				{
					continue;
				}

				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();

				if (pos.y > vtxMin.y && pos.y < vtxMax.y &&
					pos.x > vtxMin.x && pos.x < vtxMax.x &&
					pos.z > vtxMin.z && pos.z < vtxMax.z)
				{// 現在ブロックの中にいる
					if (posOld.y < vtxMin.y || posOld.y > vtxMax.y ||
						posOld.x < vtxMin.x || posOld.x > vtxMax.x ||
						posOld.z < vtxMin.z || posOld.z > vtxMax.z)
					{// 前回ブロックの中にいない
						SetOther(ppCollision[nCnt]->GetOwner());

						bHit = true;
					}
				}
			}
		}
	}

	return bHit;
}

//=====================================================
// キューブが二点間にあるか判定
//=====================================================
bool CCollision::ChckObstclBtwn(CObject *pObj, D3DXVECTOR3 vecDiff)
{
	D3DXVECTOR3 pos,posTarget;
	D3DXVECTOR3 vtxMax, vtxMin;
	D3DXVECTOR3 vtxMaxOwn, vtxMinOwn;
	D3DXVECTOR3 aVector[NUM_EDGE];
	int nIdx;
	float fRate;

	if (pObj == nullptr)
	{
		return false;
	}

	// 受け取ったオブジェクトの位置を取得
	pos = pObj->GetPosition();
	posTarget = pos + vecDiff;

	// 当たり判定の取得
	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE && ppCollision[nCnt] != this)
			{
				if (ppCollision[nCnt]->GetTag() != TAG_BLOCK)
				{// タグに合わなければ繰り返し
					continue;
				}

				// 最大・最小頂点の取得
				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();
				vtxMaxOwn = GetVtxMax();
				vtxMinOwn = GetVtxMin();

				// 四点の位置を設定
				aVector[0] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
				aVector[1] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
				aVector[2] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
				aVector[3] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
				
				// どのベクトルにトリガー判定が入ったのか確認
				for (int nCntEdge = 0; nCntEdge < NUM_EDGE; nCntEdge++)
				{
					nIdx = (nCntEdge + 1) % NUM_EDGE;

					if (IsCross(pos, aVector[nCntEdge], aVector[nIdx], &fRate, vecDiff) &&
						IsCross(posTarget, aVector[nCntEdge], aVector[nIdx], &fRate, vecDiff) == false)
					{
						fRate *= 1;

						if (fRate < 1.0f && fRate > 0.0f)
						{// 線分が辺に接触していたら

							if (pos.y < vtxMax.y)
							{
								return true;
							}
						}
					}

				}
			}
		}
	}

	return false;
}

//=====================================================
// 外積の当たり判定計算
//=====================================================
bool CCollision::IsCross(D3DXVECTOR3 posTarget, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest, float *pRate,D3DXVECTOR3 move)
{
	// 汎用処理取得
	CUniversal *pUniversal = CUniversal::GetInstance();

	bool bHit = false;

	// 壁のベクトル
	D3DXVECTOR3 vecWall = vecDest - vecSorce;

	// 壁と移動ベクトルの外積を計算
	float fArea = pUniversal->CrossProduct(vecWall, move);

	CDebugProc::GetInstance()->Print("fArea：[%f]\n", fArea);
	//CDebugProc::GetInstance()->Print("move：[%f,%f,%f]\n", &fArea);

	if (fArea > 0.0f)
	{// 線分の左にある判定
		if (pRate != nullptr)
		{// 線分上にあるかのチェック
			D3DXVECTOR3 vecToPos = posTarget - vecSorce;

			float fArea2 = pUniversal->CrossProduct(vecToPos, move);

			*pRate = fArea2 / fArea;

			if (*pRate <= 1.0f && *pRate >= 0.0f)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}

//=====================================================
// 外積のトリガー判定計算
//=====================================================
bool CCollision::IsCrossTrigger(D3DXVECTOR3 posTarget, D3DXVECTOR3 posTargetOld, D3DXVECTOR3 vecSorce, D3DXVECTOR3 vecDest)
{
	bool bHit = false;

	D3DXVECTOR3 vecLine = vecDest - vecSorce;

	D3DXVECTOR3 vecToPos = posTarget - vecSorce;
	D3DXVECTOR3 vecToPosOld = posTargetOld - vecSorce;

	if (vecLine.z * vecToPos.x - vecLine.x * vecToPos.z >= 0 &&
		vecLine.z * vecToPosOld.x - vecLine.x * vecToPosOld.z < 0)
	{
		bHit = true;
	}

	return bHit;
}

//=====================================================
// 位置設定
//=====================================================
void CCollision::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
// 生成処理
//=====================================================
CCollision *CCollision::Create(TAG tag, TYPE type, CObject *obj)
{
	CCollision *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// インスタンス生成
		switch (type)
		{
		case TYPE_SPHERE:
			pCollision = new CCollisionSphere;
			break;
		default:
			break;
		}

		if (pCollision != nullptr)
		{
			// 初期化処理
			pCollision->Init();

			// タグ受け取り
			pCollision->m_tag = tag;

			// 持ち主のポインタ
			pCollision->m_pObjectOwner = obj;
		}
	}

	return pCollision;
}

//=====================================================
// コンストラクタ
//=====================================================
CCollisionSphere::CCollisionSphere()
{
	m_fRadius = 0.0f;

	SetType(TYPE_SPHERE);

	m_pBillboard = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CCollisionSphere::~CCollisionSphere()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CCollisionSphere::Init(void)
{
	if (m_pBillboard == nullptr)
	{// ビルボードの生成
		m_pBillboard = CBillboard::Create(GetPosition(),m_fRadius,m_fRadius);

		if (m_pBillboard != nullptr)
		{
			int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\EFFECT\\collision.png");
			m_pBillboard->SetIdxTexture(nIdx);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CCollisionSphere::Uninit(void)
{
	if (m_pBillboard != nullptr)
	{// ビルボードの削除
		m_pBillboard->Uninit();
		m_pBillboard = nullptr;
	}

	CCollision::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CCollisionSphere::Update(void)
{
	if (m_pBillboard != nullptr)
	{// ビルボードの追従
		D3DXVECTOR3 pos = GetPosition();

		m_pBillboard->SetPosition(pos);

		m_pBillboard->SetSize(m_fRadius, m_fRadius);
	}
}

//=====================================================
// 球の当たり判定
//=====================================================
bool CCollisionSphere::SphereCollision(TAG tag)
{
	bool bHit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// 差分取得
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				float fLength = D3DXVec3Length(&vecDiff);

				if (fLength < ppCollision[nCnt]->GetRadius() + GetRadius())
				{
					// ぶつかった相手の持ち主を判別
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bHit;
}

//=====================================================
// 球を通り抜けた判定
//=====================================================
bool CCollisionSphere::IsTriggerExit(TAG tag)
{
	bool bExit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// 差分取得
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				// 差分の長さ
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// 前回の位置との差分
				vecDiff = ppCollision[nCnt]->GetOwner()->GetPositionOld() - GetPositionOld();

				float fLengthOld = D3DXVec3Length(&vecDiff);

				// ぶつかる時の距離
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff >= fLength && fLengthOld < fLength)
				{
					// ぶつかった相手の持ち主を判別
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bExit;
}

//=====================================================
// 球がぶつかった瞬間の判定
//=====================================================
bool CCollisionSphere::IsTriggerEnter(TAG tag)
{
	bool bExit = false;

	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag)
				{
					continue;
				}

				// 差分取得
				D3DXVECTOR3 vecDiff = ppCollision[nCnt]->GetPosition() - GetPosition();

				// 差分の長さ
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// 前回の位置との差分
				vecDiff = ppCollision[nCnt]->GetOwner()->GetPositionOld() - GetPositionOld();

				float fLengthOld = D3DXVec3Length(&vecDiff);

				// ぶつかる時の距離
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff <= fLength && fLengthOld > fLength)
				{
					// ぶつかった相手の持ち主を判別
					SetOther(ppCollision[nCnt]->GetOwner());

					return true;
				}
			}
		}
	}

	return bExit;
}

//=====================================================
// 球の押し出しの判定
//=====================================================
void CCollisionSphere::PushCollision(D3DXVECTOR3* pPos, TAG tag)
{

	CCollision** ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_SPHERE)
			{
				if (tag == TAG_NONE)
				{

				}
				else if (ppCollision[nCnt]->GetTag() != tag || ppCollision[nCnt] == this)
				{
					continue;
				}

				D3DXVECTOR3 pos = { pPos->x,0.0f,pPos->z };
				D3DXVECTOR3 posTarget = { ppCollision[nCnt]->GetPosition().x,0.0f, ppCollision[nCnt]->GetPosition().z };

				// 差分取得
				D3DXVECTOR3 vecDiff = posTarget - pos;

				// 差分の長さ
				float fLengthDiff = D3DXVec3Length(&vecDiff);

				// ぶつかる時の距離
				float fLength = ppCollision[nCnt]->GetRadius() + GetRadius();

				if (fLengthDiff < fLength)
				{
					D3DXVECTOR3 posAfter;	// 押し出し後の座標

					// 差分ベクトルから押し出し後の位置を計算
					D3DXVec3Normalize(&posAfter,&vecDiff);

					posAfter *= -fLength;

					posAfter += posTarget;

					*pPos = posAfter;
				}
			}
		}
	}
}

//=====================================================
// 生成処理
//=====================================================
CCollisionSphere *CCollisionSphere::Create(TAG tag, TYPE type, CObject *obj)
{
	CCollisionSphere *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// インスタンス生成
		pCollision = new CCollisionSphere;

		if (pCollision != nullptr)
		{
			// 初期化処理
			pCollision->Init();

			// タグ受け取り
			pCollision->SetTag(tag);

			// 持ち主のポインタ
			pCollision->SetOwner(obj);
		}
	}

	return pCollision;
}

//=====================================================
// コンストラクタ
//=====================================================
CCollisionCube::CCollisionCube()
{
	m_vtxMax = { 0.0f,0.0f,0.0f };
	m_vtxMin = { 0.0f,0.0f,0.0f };

	SetType(TYPE_CUBE);
}

//=====================================================
// デストラクタ
//=====================================================
CCollisionCube::~CCollisionCube()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CCollisionCube::Init(void)
{
	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CCollisionCube::Uninit(void)
{
	CCollision::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CCollisionCube::Update(void)
{

}

//=====================================================
// 立方体の当たり判定
//=====================================================
bool CCollisionCube::CubeCollision(TAG tag, D3DXVECTOR3 *pMove, CObject **ppObjOther)
{
	// 汎用処理の取得
	CUniversal *pUniversal = CUniversal::GetInstance();

	bool bLand = false;
	CCollision **ppCollision = GetCollision();
	SWall *apWall[NUM_WALL] = {};
	int nNumWall = 0;

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{// 当たった壁の検出
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE)
			{
				if (ppCollision[nCnt]->GetTag() != tag && tag != TAG_NONE)
				{// タグに合わなければ繰り返し
					continue;
				}

				// 自身の位置を取得
				D3DXVECTOR3 posOld = GetOwner()->GetPositionOld();

				// 相手の位置と最大・最小頂点を取得
				D3DXVECTOR3 posTarget = ppCollision[nCnt]->GetPosition();
				D3DXVECTOR3 vtxMax = ppCollision[nCnt]->GetVtxMax();
				D3DXVECTOR3 vtxMin = ppCollision[nCnt]->GetVtxMin();

				// ４頂点の設定
				D3DXVECTOR3 aVector[NUM_EDGE];

				aVector[0] = D3DXVECTOR3(vtxMin.x, 0.0f, vtxMin.z);
				aVector[1] = D3DXVECTOR3(vtxMin.x, 0.0f, vtxMax.z);
				aVector[2] = D3DXVECTOR3(vtxMax.x, 0.0f, vtxMax.z);
				aVector[3] = D3DXVECTOR3(vtxMax.x, 0.0f, vtxMin.z);

				// どのベクトルにトリガー判定が入ったのか確認
				for (int nCntEdge = 0; nCntEdge < NUM_EDGE; nCntEdge++)
				{
					D3DXVECTOR3 posCross;	// 交点の保存用

					// 二つ目の頂点の番号
					int nIdx = (nCntEdge + 1) % NUM_EDGE;

					D3DXVECTOR3 posTemp = GetPosition();

					// 外積の押し出し判定
					bool bHit = CrossProduct(posOld, &posTemp, aVector[nIdx] + posTarget, aVector[nCntEdge] + posTarget, 0.0f,nullptr,&posCross);

					if (bHit)
					{
						if (apWall[nNumWall] == nullptr)
						{// 壁情報の保存
							apWall[nNumWall] = new SWall;

							if (apWall[nNumWall] != nullptr)
							{
								apWall[nNumWall]->posStart = aVector[nIdx] + posTarget;
								apWall[nNumWall]->posEnd = aVector[nCntEdge] + posTarget;
								apWall[nNumWall]->posCross = posCross;

								nNumWall++;
							}
						}
					}
				}
			}
		}
	}

	// 自身の位置を取得
	D3DXVECTOR3 pos = GetOwner()->GetPosition();
	D3DXVECTOR3 posOld = GetOwner()->GetPositionOld();

	//if (nNumWall > 1)
	//{// 複数壁があった場合、ソートする
	//	// 移動角度の取得
	//	D3DXVECTOR3 vecMove = pos - posOld;

	//	float fRotMove = atan2f(vecMove.x, vecMove.z);

	//	// １つ目の角度の差分をはかる
	//	D3DXVECTOR3 vecWall1 = apWall[0]->posEnd - apWall[0]->posStart;
	//	float fRot1 = atan2f(vecWall1.x, vecWall1.z);

	//	float fRotDiff1 = fRotMove - fRot1;

	//	pUniversal->LimitRot(&fRotDiff1);

	//	// ２つ目の角度の差分をはかる
	//	D3DXVECTOR3 vecWall2 = apWall[1]->posEnd - apWall[1]->posStart;
	//	float fRot2 = atan2f(vecWall2.x, vecWall2.z);

	//	float fRotDiff2 = fRotMove - fRot2;

	//	pUniversal->LimitRot(&fRotDiff2);

	//	if (fRot2 * fRot2 < fRot1 * fRot1)
	//	{// 壁情報を入れ替える
	//		SWall *pWallTemp = nullptr;

	//		pWallTemp = apWall[0];

	//		apWall[1] = apWall[0];

	//		apWall[0] = pWallTemp;
	//	}
	//}

	for (int i = 0; i < NUM_WALL; i++)
	{// 当たった壁との当たり判定
		if (apWall[i] != nullptr)
		{
			// 外積の押し出し判定
			CrossProduct(posOld, &pos, apWall[i]->posStart, apWall[i]->posEnd, 0.0f, nullptr, nullptr);
		}
	}

	GetOwner()->SetPosition(pos);

	for (int i = 0; i < NUM_WALL; i++)
	{// 壁情報の破棄
		if (apWall[i] != nullptr)
		{// 情報の破棄
			delete apWall[i];
			apWall[i] = nullptr;
		}
	}
	
	return bLand;
}

//=====================================================
// 頂点設定
//=====================================================
void CCollisionCube::SetVtx(D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	m_vtxMax = vtxMax;
	m_vtxMin = vtxMin;

	m_aVtx[VTX_LD] = { vtxMin.x,0.0f,0.0f };
	m_aVtx[VTX_LU] = { 0.0f,0.0f,0.0f };
	m_aVtx[VTX_RU] = { 0.0f,0.0f,0.0f };
	m_aVtx[VTX_RD] = { 0.0f,0.0f,0.0f };
}

//=====================================================
// 当たったベクトルの取得
//=====================================================
D3DXVECTOR3 CCollisionCube::CollisionVector(CObject *pObj)
{
	D3DXVECTOR3 vecDest = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 vecDiff;
	D3DXVECTOR3 pos, posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 vecToPos;
	D3DXVECTOR3 vtxMax, vtxMin;
	D3DXVECTOR3 vtxMaxOwn, vtxMinOwn;
	D3DXVECTOR3 aVector[NUM_EDGE];
	int nIdx;
	float fLengthSorce;
	float fLengthDest;

	if (pObj == nullptr)
	{
		return vecDest;
	}

	// 受け取ったオブジェクトの位置を取得
	pos = pObj->GetPosition();
	posOld = pObj->GetPositionOld();

	move = pos - posOld;

	// 当たり判定の取得
	CCollision **ppCollision = GetCollision();

	for (int nCnt = 0; nCnt < NUM_OBJECT; nCnt++)
	{
		if (ppCollision[nCnt] != nullptr)
		{
			if (ppCollision[nCnt]->GetType() == TYPE_CUBE && ppCollision[nCnt] != this)
			{
				if (ppCollision[nCnt]->GetTag() != TAG_BLOCK)
				{// タグに合わなければ繰り返し
					continue;
				}

				vtxMax = ppCollision[nCnt]->GetVtxMax() + ppCollision[nCnt]->GetPosition();
				vtxMin = ppCollision[nCnt]->GetVtxMin() + ppCollision[nCnt]->GetPosition();
				vtxMaxOwn = GetVtxMax();
				vtxMinOwn = GetVtxMin();

				if (pos.z >= vtxMin.z - vtxMaxOwn.z &&
					pos.z <= vtxMax.z - vtxMinOwn.z &&
					pos.x >= vtxMin.x - vtxMaxOwn.x &&
					pos.x <= vtxMax.x - vtxMinOwn.x &&
					pos.y >= vtxMin.y - vtxMaxOwn.y &&
					pos.y <= vtxMax.y - vtxMinOwn.y)
				{// 現在ブロックの中にいる
					aVector[0] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);
					aVector[1] = D3DXVECTOR3(vtxMin.x - vtxMaxOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
					aVector[2] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMax.z - vtxMinOwn.z);
					aVector[3] = D3DXVECTOR3(vtxMax.x - vtxMinOwn.x, 0.0f, vtxMin.z - vtxMaxOwn.z);

					// どのベクトルにトリガー判定が入ったのか確認
					for (int nCntEdge = 0; nCntEdge < NUM_EDGE; nCntEdge++)
					{
						nIdx = (nCntEdge + 1) % NUM_EDGE;

						if (IsCrossTrigger(pos, posOld, aVector[nCntEdge], aVector[nIdx]))
						{
							vecDest = aVector[nIdx] - aVector[nCntEdge];

							vecToPos = pos - aVector[nIdx];

							// 割合を算出
							float fAreaMax = (vecDest.z * move.x) - (vecDest.x * move.z);
							float fArea = (vecToPos.z * move.x) - (vecToPos.x * move.z);
							float fRate = fArea / fAreaMax;

							fLengthDest = D3DXVec3Length(&aVector[nIdx]);
							fLengthSorce = D3DXVec3Length(&aVector[nCntEdge]);

							// 最短距離によって目標ベクトル反転
							if (fLengthSorce < fLengthDest)
							{
								vecDest *= -1.0f - fRate;
							}
							else
							{
								vecDest *= -fRate;
							}
						}
					}
				}
			}
		}
	}

	return vecDest;
}

//=====================================================
// 生成処理
//=====================================================
CCollisionCube *CCollisionCube::Create(TAG tag, CObject *obj)
{
	CCollisionCube *pCollision = nullptr;

	if (pCollision == nullptr)
	{
		// インスタンス生成
		pCollision = new CCollisionCube;

		if (pCollision != nullptr)
		{
			// 初期化処理
			pCollision->Init();

			// タグ受け取り
			pCollision->SetTag(tag);

			// 持ち主のポインタ
			pCollision->SetOwner(obj);
		}
	}

	return pCollision;
}

//=====================================================
// 外積による壁の押し出し判定
//=====================================================
bool CCollisionCube::CrossProduct(D3DXVECTOR3 posOld, D3DXVECTOR3 *pos, D3DXVECTOR3 vtxStart, D3DXVECTOR3 vtxEnd, float width, SWall *pWall, D3DXVECTOR3 *pPosCross)
{
	bool bHit = false;

	// 汎用処理取得
	CUniversal *pUniversal = CUniversal::GetInstance();

	D3DXVECTOR3 vecLine = D3DXVECTOR3
	(//一旦Y座標は平面
		vtxEnd.x - vtxStart.x,
		0.0f,
		vtxEnd.z - vtxStart.z
	);

	//一つ目の頂点から現在位置までのベクトル
	D3DXVECTOR3 vecToPos = D3DXVECTOR3
	(
		pos->x - vtxStart.x,
		0.0f,
		pos->z - vtxStart.z
	);

	//移動量ベクトル
	D3DXVECTOR3 vecMove = D3DXVECTOR3
	(
		pos->x - posOld.x,
		0.0f,
		pos->z - posOld.z
	);

	D3DXVECTOR3 vecToPosOld = D3DXVECTOR3
	(// 前回の位置へのベクトル
		posOld.x - vtxStart.x,
		0.0f,
		posOld.z - vtxStart.z
	);

	// 壁の向きを取得
	float fAngle = atan2f(vecLine.x, vecLine.z);

	// 各外積を取得
	float fAreaMax = pUniversal->CrossProduct(vecLine, vecMove);
	float fArea = pUniversal->CrossProduct(vecLine, vecToPos);
	float fArea2 = pUniversal->CrossProduct(vecToPos, vecMove);
	float fAreaOld = pUniversal->CrossProduct(vecLine, vecToPosOld);
	float fRate = fArea2 / fAreaMax;

	if (fAreaMax == 0)
	{
		return bHit;
	}

	if ((fRate > 0.0f) && (fRate < 1.0f))
	{
		if (fArea <= 0.0f && fAreaOld >= 0.0f)
		{// 線分の左にあり、前回がめり込んでいない
			CDebugProc::GetInstance()->Print("\nfRate[%f]", fRate);

			// 壁の長さを計算
			float fLength = sqrtf(vecLine.x * vecLine.x + vecLine.z * vecLine.z) * fRate;

			D3DXVECTOR3 posCross =
			{// 交点
				vtxStart.x + sinf(fAngle) * fLength,
				pos->y,
				vtxStart.z + cosf(fAngle) * fLength
			};

			if (pPosCross != nullptr)
			{
				*pPosCross = posCross;
			}

			// はみ出る差分ベクトルを取得、長さを計算
			D3DXVECTOR3 diffMove;

			diffMove = *pos - posCross;

			// 交点に位置を設定
			*pos = posCross;

			// 交点にエフェクトを出す
			CEffect3D::Create(posCross, 10.0f, 60, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			// 移動の角度取得
			float fAngleMove = atan2f(vecMove.x, vecMove.z);
			float fAngleMid = fAngle + D3DX_PI * 0.5f;

			// 直角度を修正
			if (fAngleMid > D3DX_PI)
			{
				fAngleMid -= 6.28f;
			}
			if (fAngleMid < -D3DX_PI)
			{
				fAngleMid += 6.28f;
			}

			// 差分の角度を取得
			float fAngleDiff = fAngleMove - fAngleMid;

			// 差分角度を修正
			if (fAngleDiff > D3DX_PI)
			{
				fAngleDiff -= 6.28f;
			}
			if (fAngleDiff < -D3DX_PI)
			{
				fAngleDiff += 6.28f;
			}

			// はみ出た分の長さを取得
			float fLengthProtrude = D3DXVec3Length(&diffMove);

			// 壁のベクトルを代入
			if (fAngleDiff <= 0.0f)
			{// 差分角度がプラスの場合
				diffMove = vecLine;
			}
			else
			{// 差分角度がマイナスの場合
				diffMove = -vecLine;
			}

			// 足す分のベクトルを正規化して、移動量の長さにする
			D3DXVec3Normalize(&diffMove, &diffMove);
			diffMove *= fLengthProtrude;

			// ずれる分の位置を足す
			*pos += diffMove;

			bHit = true;
		}
	}

	return bHit;
}