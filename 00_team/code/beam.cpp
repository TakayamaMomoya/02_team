//*****************************************************
//
// ビームの処理[beam.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "beam.h"
#include "anim3D.h"
#include "animEffect3D.h"
#include "universal.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int NUM_VTX = 4;	// 当たり判定の頂点数
const float INITIAL_WIDTH_ANIM = 50.0f;	// アニメーションの幅
const float INITIAL_WIDTH_LENGTH = 300.0f;	// アニメーションの長さ
}

//=====================================================
// コンストラクタ
//=====================================================
CBeam::CBeam(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// デストラクタ
//=====================================================
CBeam::~CBeam()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBeam::Init(void)
{
	if (m_info.pAnim == nullptr)
	{// アニメーションエフェクトの生成
		CAnimEffect3D *pAnimEffect = CAnimEffect3D::GetInstance();

		if (pAnimEffect != nullptr)
		{
			m_info.pAnim = pAnimEffect->CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CAnimEffect3D::TYPE::TYPE_BEAM);

			if (m_info.pAnim != nullptr)
			{// 位置の設定

			}
		}
	}

	m_info.fWidthAnim = INITIAL_WIDTH_ANIM;
	m_info.fLengthAnim = INITIAL_WIDTH_LENGTH;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CBeam::Uninit(void)
{
	if (m_info.pAnim != nullptr)
	{
		m_info.pAnim->Uninit();
		m_info.pAnim = nullptr;
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CBeam::Update(void)
{
	// アニメーションの頂点位置設定
	SetAnimVtx();
}

//=====================================================
// アニメーションの頂点位置設定
//=====================================================
void CBeam::SetAnimVtx(void)
{
	if (m_info.pAnim == nullptr)
	{
		return;
	}

	// 頂点バッファの取得
	CAnim3D *pAnim = m_info.pAnim;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = pAnim->GetVtxBuff();

	if (pVtxBuff == nullptr)
	{
		return;
	}

	// 頂点情報のポインタ
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点の設定
	D3DXVECTOR3 aPosVtx[NUM_VTX];
	D3DXMATRIX aMtxVtx[NUM_VTX];
	D3DXVECTOR3 aOffset[NUM_VTX] =
	{
		{ -m_info.fLengthAnim,0.0f,m_info.fWidthAnim },
		{ 0.0f,0.0f,m_info.fWidthAnim },
		{ 0.0f,0.0f,-m_info.fWidthAnim },
		{ -m_info.fLengthAnim,0.0f,-m_info.fWidthAnim },
	};

	for (int i = 0; i < NUM_VTX; i++)
	{
		universal::SetOffSet(&aMtxVtx[i], m_info.mtxWorld, aOffset[i]);

		aPosVtx[i] =
		{
			aMtxVtx[i]._41,
			aMtxVtx[i]._42,
			aMtxVtx[i]._43,
		};

		pVtx[0].pos = aPosVtx[i];
	}

	//頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=====================================================
// 描画処理
//=====================================================
void CBeam::Draw(void)
{

}

//=====================================================
// 生成処理
//=====================================================
CBeam *CBeam::Create(void)
{
	CBeam *pBeam = nullptr;

	if (pBeam == nullptr)
	{
		pBeam = new CBeam;

		if (pBeam != nullptr)
		{
			// 初期化
			pBeam->Init();
		}
	}

	return pBeam;
}