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

#include "player.h"
#include "playerManager.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const int DIG_MAG_NUM = 3;		// 装弾数の桁数
}

//=====================================================
// コンストラクタ
//=====================================================
CUIMagazine::CUIMagazine(int nPriority) : CObject(nPriority)
{
	m_pNumDig = nullptr;

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

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CUIMagazine::Update(void)
{
	if (m_pNumDig != nullptr)
	{
		SetNumMagazine();
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
void CUIMagazine::SetPosition(D3DXVECTOR3 pos)
{
	if (m_pNumDig != nullptr)
	{
		m_pNumDig->SetPosition(pos);
	}
}

//=====================================================
// 大きさ設定処理
//=====================================================
void CUIMagazine::SetSize(float width, float height)
{
	if (m_pNumDig != nullptr)
	{
		m_pNumDig->SetSizeAll(width, height);
	}
}

//=====================================================
// 色設定処理
//=====================================================
void CUIMagazine::SetCol(D3DXCOLOR col)
{
	if (m_pNumDig != nullptr)
	{
		m_pNumDig->SetColor(col);
	}
}

//=====================================================
// 装弾数設定処理
//=====================================================
void CUIMagazine::SetNumMagazine(void)
{
	// ポインタの取得
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();
	CPlayer* pPlayer = nullptr;
	CWeapon* pWeapon = nullptr;

	int nBullet = 0;

	if (pPlayerManager != nullptr)
	{
		// プレイヤー管理の取得
		pPlayer = pPlayerManager->GetPlayer(m_info.nIdxPlayer);
	}

	if (pPlayer != nullptr)
	{
		// プレイヤーの取得
		pWeapon = pPlayer->GetWeapon();
	}

	if (pWeapon != nullptr)
	{
		// プレイヤーの弾を取得
		nBullet = pWeapon->GetBullet();
	}

	if (m_pNumDig != nullptr)
	{
		// 弾を反映
		m_pNumDig->SetValue(nBullet, DIG_MAG_NUM);
	}
}