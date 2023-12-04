//*****************************************************
//
// 木箱の処理[box.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "box.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "playerManager.h"
#include "weapon.h"
#include "player.h"
#include "billboard.h"
#include "texture.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define SIZE_INTERACT	(30.0f)	// インタラクト表示のサイズ

//=====================================================
// コンストラクタ
//=====================================================
CBox::CBox(int nPriority) : CObjectX(nPriority)
{
	m_pCollisionSphere = nullptr;
	m_pCollisionCube = nullptr;
}

//=====================================================
// デストラクタ
//=====================================================
CBox::~CBox()
{

}

//=====================================================
// 生成処理
//=====================================================
CBox *CBox::Create(void)
{
	CBox *pItem = nullptr;

	if (pItem == nullptr)
	{
		pItem = new CBox;

		if (pItem != nullptr)
		{
			// 初期化
			pItem->Init();
		}
	}

	return pItem;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBox::Init(void)
{
	// 継承クラスの初期化
	CObjectX::Init();

	if (m_pCollisionSphere == nullptr)
	{// 当たり判定の生成
		m_pCollisionSphere = CCollisionSphere::Create(CCollision::TAG_ITEM, CCollision::TYPE_SPHERE, this);

		if (m_pCollisionSphere != nullptr)
		{
			m_pCollisionSphere->SetRadius(50.0f);
		}
	}

	if (m_pCollisionCube == nullptr)
	{// 当たり判定生成
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 vtxMax = GetVtxMax();
		D3DXVECTOR3 vtxMin = GetVtxMin();

		m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_BLOCK, this);

		if (m_pCollisionCube != nullptr)
		{
			m_pCollisionCube->SetPosition(pos);

			m_pCollisionCube->SetVtx(vtxMax, vtxMin);
		}
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CBox::Uninit(void)
{
	if (m_pCollisionSphere != nullptr)
	{
		m_pCollisionSphere->Uninit();
		m_pCollisionSphere = nullptr;
	}

	if (m_pCollisionCube != nullptr)
	{
		m_pCollisionCube->Uninit();
		m_pCollisionCube = nullptr;
	}

	// 継承クラスの終了
	CObjectX::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CBox::Update(void)
{
	// 継承クラスの更新
	CObjectX::Update();

	if (m_pCollisionSphere != nullptr)
	{
		D3DXVECTOR3 pos = GetPosition();

		m_pCollisionSphere->SetPosition(pos);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CBox::Draw(void)
{
	// 継承クラスの描画
	CObjectX::Draw();
}