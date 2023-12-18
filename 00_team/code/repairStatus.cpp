//=========================================================
//
// 修理状況処理 [repairStatus.cpp]
// Author = 阿部翔大郎
//
//=========================================================

//===============================================
// インクルード
//===============================================
#include "repairStatus.h"
#include "rocket.h"
#include "texture.h"

//===============================================
// 定数定義
//===============================================
namespace
{
	// 視点カメラの位置
	const D3DXVECTOR3 OBJ_POS = D3DXVECTOR3(170.0f, 110.0f, -90.0f);

	// 注視点カメラの位置
	const D3DXVECTOR3 CAMERA_POSR = D3DXVECTOR3(170.0f, -50.0f, 300.0f);

	// 修理状況のテクスチャのパス
	const char* TEX_PATH = "data\\TEXTURE\\UI\\repair_status.png";

	// 修理状況の横幅
	const float LOGO_WIDTH = 480.0f;

	// 修理状況の縦幅
	const float LOGO_HEIGHT = 270.0f;

	// 修理状況の位置
	const D3DXVECTOR3 LOGO_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 100.0f, 0.0f);

	const float INCREASED_VALUE = 30.0f;
}

//===============================================
// 静的メンバ変数宣言
//===============================================
CRepairStatus* CRepairStatus::m_pRepairStatus = nullptr;	// 自身のポインタ

//===============================================
// コンストラクタ
//===============================================
CRepairStatus::CRepairStatus(int nPriority) : CObject3D(nPriority)
{
	// 値のクリア
	//ZeroMemory(&m_apModelPlayer[0], sizeof(m_apModelPlayer));
}

//===============================================
// デストラクタ
//===============================================
CRepairStatus::~CRepairStatus()
{
	
}

//===============================================
// 生成処理
//===============================================
CRepairStatus *CRepairStatus::Create(int nPriority)
{
	if (m_pRepairStatus == nullptr)
	{
		// 修理状況の生成
		m_pRepairStatus = new CRepairStatus(7);

		if (m_pRepairStatus != nullptr)
		{
			// 初期化処理
			m_pRepairStatus->Init();
		}
		else if (m_pRepairStatus == nullptr)
		{
			return nullptr;
		}
	}

	return m_pRepairStatus;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CRepairStatus::Init()
{
	// インスタンスを取得
	CRocket* pRocket = pRocket->GetInstance();

	if (m_pRepairStatus != nullptr)
	{
		if (pRocket != nullptr)
		{
			D3DXVECTOR3 posRocket = pRocket->GetPosition();

			CObject3D::Init();
			m_pRepairStatus->SetSize(0.0f, 50.0f);
			m_pRepairStatus->SetPosition({ posRocket.x - INCREASED_VALUE * 3, 200.0f, posRocket.z - 50.0f });
			int nIdx = CTexture::GetInstance()->Regist(TEX_PATH);
			m_pRepairStatus->SetIdxTexture(nIdx);
			m_pRepairStatus->EnableBillboard(true);
			m_pRepairStatus->SetVtx();
		}
	}

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CRepairStatus::Uninit(void)
{
	if (m_pRepairStatus != nullptr)
	{
		m_pRepairStatus = nullptr;
	}

	CObject3D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CRepairStatus::Update(void)
{
	// インスタンスを取得
	CRocket* pRocket = pRocket->GetInstance();

	if (pRocket != nullptr)
	{
		int nProgress = pRocket->GetProgress();
		D3DXVECTOR3 posRocket = pRocket->GetPosition();

		m_pRepairStatus->SetSize(nProgress * INCREASED_VALUE, 30.0f);
		m_pRepairStatus->SetPosition({ posRocket.x - INCREASED_VALUE * 3 + nProgress * INCREASED_VALUE, 200.0f, posRocket.z - 50.0f});
	}

	CObject3D::Update();
}

//===============================================
// 描画処理
//===============================================
void CRepairStatus::Draw(void)
{
	CObject3D::Draw();
}