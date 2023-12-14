//*****************************************************
//
// 武器アイテムの処理[ItemWeaponWeapon.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "ItemWeapon.h"
#include "manager.h"
#include "renderer.h"
#include "playerManager.h"
#include "weapon.h"
#include "player.h"
#include "debugproc.h"
#include "effect3D.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
	const float GRAVITY = 0.3f;	// 重力

	D3DXCOLOR WEPONCOL[CWeapon::TYPE_MAX] =
	{// 武器ごとのエフェクトの色
		{1.0f, 1.0f, 1.0f, 0.35f},	// マグナム
		{1.0f, 1.0f, 1.0f, 0.35f},	// マシンガン
		{1.0f, 0.8f, 0.0f, 0.35f},	// ショットガン
		{1.0f, 0.0f, 0.0f, 0.35f},	// レールガン
		{1.0f, 0.0f, 0.0f, 0.35f},	// ミニガン
		{1.0f, 0.0f, 0.0f, 0.35f},	// ロケラン
	};

	const float SPEED_SCALING = 0.1f;	// スケールが大きくなる速度
	const float INITIAL_DESTSCALE = 1.5f;	// 初期の目標スケール
	const float INITIAL_HEIGHT_BASE = 70.0f;	// 初期の基準高さ
	const float RANGE_FLOAT = 50.0f;	// 浮き沈みする範囲
	const float SPEED_ROTATE = 0.01f;	// 回転速度
	const float SPEED_MOVE = 0.2f;	// 追従速度
	const float SPEED_FLOAT = 0.03f;	// 浮き沈みする速度
}

//=====================================================
// コンストラクタ
//=====================================================
CItemWeapon::CItemWeapon(int nPriority) : CGimmick(nPriority)
{
	m_type = CWeapon::TYPE_MAGNUM;
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// デストラクタ
//=====================================================
CItemWeapon::~CItemWeapon()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CItemWeapon::Init(void)
{
	// 継承クラスの初期化
	CGimmick::Init();

	// 読み込み
	Load();

	// スケール初期設定
	SetScale(0.0f);

	// 横向きにする
	D3DXVECTOR3 rot = GetRot();

	rot.x = D3DX_PI * 0.5f;

	SetRot(rot);

	m_info.fScaleDest = INITIAL_DESTSCALE;

	return S_OK;
}

//=====================================================
// 読み込み処理
//=====================================================
void CItemWeapon::Load(void)
{
	char* apPath[CWeapon::TYPE_MAX] =
	{
		"data\\MODEL\\weapon\\magnum.x",
		"data\\MODEL\\weapon\\mac10.x",
		"data\\MODEL\\weapon\\shotgun.x",
		"data\\MODEL\\weapon\\railgun.x",
		"data\\MODEL\\weapon\\minigun_000.x",
		"data\\MODEL\\weapon\\launcher.x",
	};

	// モデルの読込
	int nIdx = CModel::Load(apPath[m_type]);
	SetIdxModel(nIdx);
	BindModel(nIdx);
}

//=====================================================
// 終了処理
//=====================================================
void CItemWeapon::Uninit(void)
{
	// 継承クラスの終了
	CGimmick::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CItemWeapon::Update(void)
{
	// 継承クラスの更新
	CGimmick::Update();

	// スケールの管理
	ManageScale();

	// 回す処理
	ManageTransform();
}

//=====================================================
// スケールの管理
//=====================================================
void CItemWeapon::ManageScale(void)
{
	float fScale = GetScale();

	fScale += (m_info.fScaleDest - fScale) * SPEED_SCALING;

	SetScale(fScale);
}

//=====================================================
// トランスフォームの管理
//=====================================================
void CItemWeapon::ManageTransform(void)
{
	// 回転
	D3DXVECTOR3 rot = GetRot();

	rot.y += SPEED_ROTATE;

	universal::LimitRot(&rot.y);

	SetRot(rot);

	// 目標位置に移動
	D3DXVECTOR3 pos = GetPosition();
	pos.y = 0.0f;
	D3DXVECTOR3 posDest = m_info.posDest + pos;

	pos += (posDest - pos) * SPEED_MOVE;

	SetPosition(pos);

	// 浮き沈みさせる
	m_info.fTimer += SPEED_FLOAT;

	universal::LimitRot(&m_info.fTimer);

	float fDiff = sinf(m_info.fTimer) * RANGE_FLOAT;

	m_info.posDest.y = INITIAL_HEIGHT_BASE + fDiff;
}

//=====================================================
// アイテム入手時の処理
//=====================================================
void CItemWeapon::Interact(CObject *pObj)
{
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pObj == nullptr || pPlayerManager == nullptr)
	{
		return;
	}

	// プレイヤー取得
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		CPlayer *pPlayer = pPlayerManager->GetPlayer(i);

		if (pPlayer != nullptr)
		{
			if ((CObject*)pPlayer == pObj)
			{// プレイヤー検出
				bool bGet = pPlayer->InputInteract();

				if (bGet)
				{
					// 効果の付与
					ApplyEffect(pPlayer);

					Uninit();
				}
			}
		}
	}
}

//=====================================================
// 効果を適用する処理
//=====================================================
void CItemWeapon::ApplyEffect(CPlayer* pPlayer)
{
	if (pPlayer == nullptr)
	{
		return;
	}

	pPlayer->SetWeapon(m_type);
}

//=====================================================
// 描画処理
//=====================================================
void CItemWeapon::Draw(void)
{
	// 継承クラスの描画
	CGimmick::Draw();

	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc == nullptr)
	{
		return;
	}

	pDebugProc->Print("\nアイテムの目標位置[%f,%f,%f]", m_info.posDest.x, m_info.posDest.y, m_info.posDest.z);
}

//=====================================================
// 生成処理
//=====================================================
CItemWeapon *CItemWeapon::Create(CWeapon::TYPE type)
{
	if (type >= CWeapon::TYPE_MAX || type < 0)
	{
		assert(("想定外の武器を出そうとしてます",false));
	}

	CItemWeapon *pItemWeapon = nullptr;

	if (pItemWeapon == nullptr)
	{
		pItemWeapon = new CItemWeapon;

		if (pItemWeapon != nullptr)
		{
			pItemWeapon->m_type = type;

			// 初期化
			pItemWeapon->Init();
		}
	}

	return pItemWeapon;
}