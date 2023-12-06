//*****************************************************
//
// 残弾数表示の処理[UIMagazine.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "UIMagazine.h"
#include "number.h"

#include "texture.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const int DIG_MAG_NUM = 3;		// 装弾数の桁数
	const int DIG_MAX_MAG_NUM = 3;	// 最大装弾数の桁数
}

//=====================================================
// コンストラクタ
//=====================================================
CUIMagazine::CUIMagazine(int nPriority) : CObject(nPriority)
{
	m_pNumDig = nullptr;
	m_pNumMaxDig = nullptr;

	ZeroMemory(&m_info, sizeof(m_info));
}

//=====================================================
// デストラクタ
//=====================================================
CUIMagazine::~CUIMagazine()
{

}

//=====================================================
// 生成処理
//=====================================================
CUIMagazine* CUIMagazine::Create(int nIdx)
{
	CUIMagazine *pUIMagazine = nullptr;

	pUIMagazine = new CUIMagazine;

	if (pUIMagazine != nullptr)
	{
		// プレイヤー番号を設定
		pUIMagazine->m_info.nIdxPlayer = nIdx;

		// 装弾数（数字）の生成処理
		CNumber* pDigMag = CNumber::Create(DIG_MAG_NUM, 0);

		if (pDigMag != nullptr)
		{
			pUIMagazine->m_pNumDig = pDigMag;
		}

		// 装弾最大数（数字）の生成処理
		CNumber* pDigMaxMag = CNumber::Create(DIG_MAX_MAG_NUM, 0);

		if (pDigMaxMag != nullptr)
		{
			pUIMagazine->m_pNumMaxDig = pDigMaxMag;
		}

		// 装弾数UIの初期化
		pUIMagazine->Init();
	}

	return pUIMagazine;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CUIMagazine::Init(void)
{
	if (m_pNumDig != nullptr)
	{
		// 初期値設定処理
		m_pNumDig->SetSizeAll(50.0f, 100.0f);
		m_pNumDig->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	if (m_pNumMaxDig != nullptr)
	{
		// 初期値設定処理
		m_pNumMaxDig->SetSizeAll(50.0f, 100.0f);
		m_pNumMaxDig->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CUIMagazine::Uninit(void)
{
	if (m_pNumDig != nullptr)
	{
		m_pNumDig->Uninit();
	}

	if (m_pNumMaxDig != nullptr)
	{
		m_pNumMaxDig->Uninit();
	}

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CUIMagazine::Update(void)
{
	if (m_pNumDig != nullptr ||
		m_pNumMaxDig != nullptr)
	{
		m_pNumDig->SetValue(0, DIG_MAG_NUM);
		m_pNumMaxDig->SetValue(0, DIG_MAX_MAG_NUM);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CUIMagazine::Draw(void)
{

}
//=====================================================
// 位置設定処理
//=====================================================
void CUIMagazine::SetPosition(D3DXVECTOR3 posDig , D3DXVECTOR3 posMaxDig)
{
	if (m_pNumDig != nullptr ||
		m_pNumMaxDig != nullptr)
	{
		m_pNumDig->SetPosition(posDig);
		m_pNumMaxDig->SetPosition(posMaxDig);
	}
}

//=====================================================
// 大きさ設定処理
//=====================================================
void CUIMagazine::SetSize(float width, float height)
{
	if (m_pNumDig != nullptr ||
		m_pNumMaxDig != nullptr)
	{
		m_pNumDig->SetSizeAll(width, height);
		m_pNumMaxDig->SetSizeAll(width, height);
	}
}

//=====================================================
// 色設定処理
//=====================================================
void CUIMagazine::SetCol(D3DXCOLOR col)
{
	if (m_pNumDig != nullptr ||
		m_pNumMaxDig != nullptr)
	{
		m_pNumDig->SetColor(col);
		m_pNumMaxDig->SetColor(col);
	}
}
