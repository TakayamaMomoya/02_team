//*****************************************************
//
// レンダラーの処理[renderer.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "object.h"
#include <stdio.h>

//=====================================================
// コンストラクタ
//=====================================================
CRenderer::CRenderer()
{
	// 変数のクリア
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//=====================================================
// デストラクタ
//=====================================================
CRenderer::~CRenderer()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;						// ディスプレイモードの設定
	D3DPRESENT_PARAMETERS d3dpp;						//ディスプレイモードの設定

	// Direct3Dオブジェクト生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// パラメーターのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面の幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// 高さ
	d3dpp.BackBufferFormat = d3ddm.Format;							// 形式
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期
	d3dpp.EnableAutoDepthStencil = TRUE;							// デブスとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デブスバッファを16bitで使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

																	// Direct3Dデバイスの生成
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	
	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// オブジェクトのリリース処理
	CObject::ReleaseAll();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CRenderer::Uninit(void)
{
	// オブジェクトのリリース
	CObject::ReleaseAll();

	if (m_pD3DDevice != NULL)
	{// Direct3Dデバイス破棄
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	if (m_pD3D != NULL)
	{// Direct3Dオブジェクトの破棄
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=====================================================
// 更新処理
//=====================================================
void CRenderer::Update(void)
{
	// オブジェクトの更新
	CObject::UpdateAll();
}

//=====================================================
// 描画処理
//=====================================================
void CRenderer::Draw(void)
{
	// 画面クリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// 描画処理
		// FPS表示
		DrawFPS();
		
		// オブジェクトの描画
		CObject::DrawAll();

		CManager::GetDebugProc()->Draw();

		// 描画終了
		m_pD3DDevice->EndScene();
	}

	// バック・フロントバッファを入れ替える
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==================================================================================================
//デバッグ表示処理
//==================================================================================================
void CRenderer::DrawFPS(void)
{

}