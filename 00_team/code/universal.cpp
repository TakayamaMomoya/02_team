//*****************************************
//
//いろいろ汎用処理詰め込み
//Author:髙山桃也
//
//*****************************************

//*****************************************
//インクルード
//*****************************************
#include "manager.h"
#include "renderer.h"
#include "universal.h"
#include <stdio.h>

//*****************************************
// 静的メンバ変数宣言
//*****************************************
CUniversal *CUniversal::m_pUniversal = nullptr;	// 自身のポインタ

//=========================================
// コンストラクタ
//=========================================
CUniversal::CUniversal()
{

}

//=========================================
// デストラクタ
//=========================================
CUniversal::~CUniversal()
{

}

//=========================================
// 生成処理
//=========================================
CUniversal *CUniversal::Create(void)
{
	if (m_pUniversal == nullptr)
	{
		m_pUniversal = new CUniversal;
	}

	return m_pUniversal;
}

//=========================================
// 終了処理
//=========================================
void CUniversal::Uninit(void)
{
	delete this;
}

//=========================================
//回転制御処理
//=========================================
void CUniversal::LimitRot(float *fRot)
{
	if (*fRot > D3DX_PI)
	{
		*fRot -= 6.28f;
	}
	if (*fRot < -D3DX_PI)
	{
		*fRot += 6.28f;
	}
}

//========================================
//オフセット設定処理
//========================================
void CUniversal::SetOffSet(D3DXMATRIX *pMtxWorldOffset, D3DXMATRIX mtxWorldOwner, D3DXVECTOR3 posOffset, D3DXVECTOR3 rot)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(pMtxWorldOffset);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, posOffset.x, posOffset.y, posOffset.z);
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxTrans);

	//マトリックスをかけ合わせる
	D3DXMatrixMultiply(pMtxWorldOffset, pMtxWorldOffset, &mtxWorldOwner);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, pMtxWorldOffset);
}

//========================================
// 向き補正処理
//========================================
void CUniversal::FactingRot(float *pfRot, float fRotDest, float rotateFact)
{
	// 引数の角度の補正
	LimitRot(pfRot);
	LimitRot(&fRotDest);

	//差分角度を取得
	float fRotDiff = fRotDest - *pfRot;

	//角度の修正
	LimitRot(&fRotDiff);

	//角度補正
	*pfRot += fRotDiff * rotateFact;

	LimitRot(pfRot);
}

//========================================
// 距離の比較
//========================================
bool CUniversal::DistCmp(D3DXVECTOR3 posOwn, D3DXVECTOR3 posTarget, float fLengthMax, float *fDiff)
{
	D3DXVECTOR3 vecDiff = posTarget - posOwn;
	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength < fLengthMax)
	{
		if (fDiff != nullptr)
		{
			*fDiff = fLength;
		}

		return true;
	}
	else
	{
		return false;
	}
}

//========================================
// 外積の計算
//========================================
float CUniversal::CrossProduct(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	return pos1.z * pos2.x - pos1.x * pos2.z;
}

//========================================
// 範囲内のランダム数値を返す処理
//========================================
int CUniversal::RandRange(int nMax, int nMin)
{
	int nRange = nMax - nMin;
	int nRand = rand() % nRange + nMin;

	return nRand;
}