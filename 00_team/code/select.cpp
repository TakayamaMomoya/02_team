//*****************************************************
//
// 人数選択処理[select.cpp]
// Author:小笠原彪
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "select.h"
#include "object.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "inputjoypad.h"
#include "manager.h"
#include "debugproc.h"
#include "motion.h"
#include "model.h"
#include "fade.h"
#include "texture.h"
#include "camera.h"
#include "renderer.h"
#include "sound.h"
#include "object2D.h"
#include "objectX.h"
#include "billboard.h"
#include "object3D.h"
#include "playerManager.h"
#include "player.h"
#include "sound.h"
#include "debrisSpawner.h"
#include "debris.h"
#include "lift.h"
#include "container.h"
#include "weaponManager.h"
#include "edit.h"
#include "animEffect3D.h"
#include "number3D.h"
#include <stdio.h>

#include "number3D.h"
#include "UIManager.h"

//*****************************************************
// マクロ定義
//*****************************************************
namespace
{
	const D3DXVECTOR3 UI_POS({ -150.0f, 30.0f, -470.0f });	// UIの位置
	const D3DXVECTOR3 UI_SPACE({ 140.0f, 0.0f, 0.0f });	// UI間の間隔
	const D3DXVECTOR2 SIZE_FONT(20.0f, 5.0f);	//UIの大きさ(参加：A)
	const float BLINKING_SPEED(0.02f);	//UI点滅の速さ(参加：A)

	const D3DXVECTOR3 LEAF_POS({ -150.0f, 20.0f, -430.0f });	// ポテトの葉の位置

	const D3DXVECTOR3 SPOWN_POS({ LEAF_POS.x, -80.0f, LEAF_POS.z });	//プレイヤー出現の高さ(旅出すためマイナス値)

	const float ADULTWALL_POS_Z(-470.0f);
	const float GRAVITY(5.0f);	//重力

	const D3DXVECTOR3 CONTAINER_POS({ -150.0, 0.0, -100.0f });	// コンテナの位置
	const D3DXVECTOR3 CONTAINER_SPACE({ 400.0, 0.0, -150.0f });	// コンテナ間の広さ
	const float RESPAWN_TIME(10.0f);	// コンテナ復活の時間

	const float RIFT_IN(100.0f);	// リフトの範囲
	const float LIFT_UP(2.0f);	// リフト上昇速度

	const float GO_GAME_POSy(250.0f);	// 遷移する高さ

	const float POW_JUMP = 25.0f;	// エントリー時のジャンプ力
};

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CNumber3D *CSelect::m_apNumber[2] = {};

//=====================================================
// コンストラクタ
//=====================================================
CSelect::CSelect()
{
	ZeroMemory(&m_apPlayerData[0], sizeof(m_apPlayerData));
	ZeroMemory(&m_aContainerData[0], sizeof(m_aContainerData));
	ZeroMemory(&m_apNumber[0], sizeof(m_apNumber));
	ZeroMemory(&m_aJoinUiData[0], sizeof(m_aJoinUiData));
	m_pStartUI = nullptr;
	m_pLift = nullptr;
	m_bRiftCamera = false;
	m_bOk = false;
	m_selectState = SELECT_STATE::STATE_BEFORE;
}

//=====================================================
// デストラクタ
//=====================================================
CSelect::~CSelect()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CSelect::Init(void)
{
	// カメラ情報の取得
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera != nullptr)
	{
		pCamera->SetSelect();
	}

	MenuInit();
	StartInit();
	ContainerInit();

	// UIマネージャーの追加
	CUIManager::Create();

	// プレイヤーマネージャーの生成
	CPlayerManager::Create();

	// エディットの生成
	//CEdit::Create();

	// ブロックの読み込み
	CBlock::Load("data\\MAP\\select_map00.bin");

	// 床の生成
	CObject3D* pObject = CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	if (pObject != nullptr)
	{
		int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\BG\\wood001.jpg");
		pObject->SetIdxTexture(nIdx);
		pObject->SetTex(D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(0.0f, 0.0f));
	}

	// ポテトの寝床の生成
	CObjectX* pObjectX = CObjectX::Create({ 58.0f, 0.5f, -430.5f });
	if (pObjectX != nullptr)
	{
		pObjectX->BindModel(CModel::Load("data\\MODEL\\select\\potato_bed.x"));
	}

	PotatoLeafInit();

	// 参加人数の表示
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apNumber[nCnt] = CNumber3D::Create(1, 0);

		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->SetPosition({ 15.0f + (nCnt * 30), 20.0f, 140.0f });
			m_apNumber[nCnt]->SetSizeAll(10.0f, 20.0f);
		}
	}

	CBillboard* pBill = CBillboard::Create({ m_apNumber[0]->GetPosition().x + 15.0f, m_apNumber[0]->GetPosition().y, m_apNumber[0]->GetPosition().z }, 10.0f, 20.0f);
	if (pBill != nullptr)
	{
		int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\slash.png");
		pBill->SetIdxTexture(nIdx);
	}

	// 開始位置
	m_pLift = CLift::Create(D3DXVECTOR3(30.0f, 0.5f, 100.0f));
	
	// サウンドインスタンスの取得
	CSound* pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(pSound->LABEL_BGM_SELECT);
	}

	// ３Dアニメーション管理の生成
	CAnimEffect3D::Create();

	// コンテナのリスポーン時間を設定
	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		m_aContainerData[nCnt].fReSpawnTimer = RESPAWN_TIME;
	}

	return S_OK;
}

//=====================================================
// メニューの初期化処理
//=====================================================
void CSelect::MenuInit(void)
{
	char* apPath[NUM_PLAYER] =
	{
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
		"data\\TEXTURE\\UI\\join.png",
	};

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		// 文字の生成
		m_aJoinUiData[nCnt].pUi2D = CBillboard::Create
		(
			{ // 位置
				UI_POS.x + (nCnt * UI_SPACE.x),
				UI_POS.y,
				UI_POS.z
			},
			// サイズ
			SIZE_FONT.x, SIZE_FONT.y
		);

		if (m_aJoinUiData[nCnt].pUi2D != nullptr)
		{
			m_aJoinUiData[nCnt].pUi2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_aJoinUiData[nCnt].pUi2D->SetIdxTexture(CTexture::GetInstance()->Regist(apPath[nCnt]));
		}

		m_aJoinUiData[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aJoinUiData[nCnt].state = FADE_OUT;
	}
}

//=====================================================
// スタートの初期化処理
//=====================================================
void CSelect::StartInit(void)
{
	m_pStartUI = CObject2D::Create(6);

	if (m_pStartUI != nullptr)
	{
		m_pStartUI->SetPosition(D3DXVECTOR3(1100.0f, 650.0f, 0.0f));
		m_pStartUI->SetSize(150.0f, 50.0f);
		m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\start_game.png");
		m_pStartUI->SetIdxTexture(nIdx);

		m_pStartUI->SetVtx();
	}
}

//=====================================================
// ポテトの葉の初期化処理
//=====================================================
void CSelect::PotatoLeafInit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		// 文字の生成
		m_apPlayerData[nCnt].pLeaf = CObjectX::Create
		(
			{ // 位置
				LEAF_POS.x + (nCnt * UI_SPACE.x),
				0.0f,
				LEAF_POS.z
			}
		);

		if (m_apPlayerData[nCnt].pLeaf != nullptr)
		{
			int nIdx = CModel::Load("data\\MODEL\\select\\potatoLeaf.x");
			m_apPlayerData[nCnt].pLeaf->BindModel(nIdx);
		}
	}
}

//=====================================================
// コンテナの初期化処理
//=====================================================
void CSelect::ContainerInit(void)
{
	// 武器マネージャの生成
	CWeaponManager::Create();

	int nCnt1 = 0;
	int nCnt2 = 0;

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		// コンテナの生成
		m_aContainerData[nCnt].pContainer = CContainer::Create();

		// 位置設定
		if (nCnt % 2 == 0)
		{
			m_aContainerData[nCnt].pContainer->SetPosition(D3DXVECTOR3
			(
				CONTAINER_POS.x,
				0.0f, 
				CONTAINER_POS.z + (nCnt1 * CONTAINER_SPACE.z))
			);

			nCnt1++;
		}
		else
		{
			m_aContainerData[nCnt].pContainer->SetPosition(D3DXVECTOR3
			(
				CONTAINER_POS.x + CONTAINER_SPACE.x,
				0.0f + +CONTAINER_SPACE.y,
				CONTAINER_POS.z + (nCnt2 * CONTAINER_SPACE.z))
			);

			nCnt2++;
		}
	}
}

//=====================================================
// 終了処理
//=====================================================
void CSelect::Uninit(void)
{
	// ブロックの破棄
	CBlock::DeleteAll();

	// オブジェクト全破棄
	CObject::ReleaseAll();
}

//=====================================================
// 更新処理
//=====================================================
void CSelect::Update(void)
{
	// 情報取得
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CInputMouse* pMouse = CInputMouse::GetInstance();
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();

	int nJoinPlayer = 0;

	// シーンの更新
	CScene::Update();

	//CFade* pFade = CFade::GetInstance();

	if (m_selectState == SELECT_STATE::STATE_BEFORE)
	{
		if (pKeyboard != nullptr && pMouse != nullptr)
		{
			if (CLift::GetIsIn() == true)
			{// 参加中の全員が範囲内に入ったという判定を貰ったら

				if (pKeyboard->GetTrigger(DIK_RETURN) ||
					pMouse->GetTrigger(CInputMouse::BUTTON_LMB) ||
					pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_START, 0))
				{// フェード
					m_selectState = STATE_GO;
					m_bOk = true;
				}

				// StartUIを見えるように
				if (m_pStartUI != nullptr)
				{
					m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					m_pStartUI->SetVtx();
				}
			}
			else
			{
				// StartのUIを見えないように
				if (m_pStartUI != nullptr)
				{
					m_pStartUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
					m_pStartUI->SetVtx();
				}
			}
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_apNumber[nCnt] != nullptr)
			{
				m_apNumber[nCnt]->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
			}
		}

		Rift();
	}

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		if (m_aJoinUiData[nCntPlayer].pUi2D != nullptr && m_selectState == SELECT_STATE::STATE_BEFORE)
		{
			// 色の変更
			MenuColorChange(nCntPlayer);
			// 参加入力
			EntryInput(nCntPlayer);
		}

		if (m_abEntry[nCntPlayer] == true)
		{
			// プレイヤー参上の処理
			PlayerShowUp(nCntPlayer);

			// 行動制限
			MoveLimit(nCntPlayer);

			nJoinPlayer++;
		}
	}

	// 参加人数の設定
	CLift::SetjoinPlayer(nJoinPlayer);

	// リフト内人数のUI
	LiftInNumberUi(nJoinPlayer);
	
	// コンテナの再設置
	ReSetContainer();

#ifdef _DEBUG
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		// 操作
		pCamera->Control();
	}

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CDebrisSpawner::Create(D3DXVECTOR3(0.0f, 10.0f, -400.0f), CDebrisSpawner::TYPE::TYPE_SOIL, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	CDebugProc::GetInstance()->Print("\n参加人数[%d]\n", nJoinPlayer);
#endif
}

//=====================================================
// 再設定
//=====================================================
void CSelect::ReSetContainer(void)
{
	int nCnt1 = 0;
	int nCnt2 = 0;

	for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		if (m_aContainerData[nCnt].pContainer != nullptr)
		{
			if (m_aContainerData[nCnt].pContainer->GetState() == CContainer::STATE_END)
			{
				m_aContainerData[nCnt].pContainer = nullptr;
				m_aContainerData[nCnt].fReSpawnTimer = RESPAWN_TIME;
			}
		}

		if (m_aContainerData[nCnt].pContainer == nullptr)
		{
			// 経過時間取得
			float fTick = CManager::GetTick();

			m_aContainerData[nCnt].fReSpawnTimer -= fTick;

			if (m_aContainerData[nCnt].fReSpawnTimer > 0)
			{
				continue;
			}
			
			// コンテナの生成
			m_aContainerData[nCnt].pContainer = CContainer::Create();

			if (m_aContainerData[nCnt].pContainer == nullptr)
			{
				continue;
			}

			// 位置設定
			if (nCnt % 2 == 0)
			{
				m_aContainerData[nCnt].pContainer->SetPosition(D3DXVECTOR3
				(
					CONTAINER_POS.x,
					0.0f,
					CONTAINER_POS.z + (nCnt1 * CONTAINER_SPACE.z))
				);

				nCnt1++;
			}
			else
			{
				m_aContainerData[nCnt].pContainer->SetPosition(D3DXVECTOR3
				(
					CONTAINER_POS.x + CONTAINER_SPACE.x,
					0.0f + +CONTAINER_SPACE.y,
					CONTAINER_POS.z + (nCnt2 * CONTAINER_SPACE.z))
				);

				nCnt2++;
			}
		}
	}
}

//=====================================================
// UI点滅
//=====================================================
void CSelect::MenuColorChange(int nPlayer)
{
	if (m_aJoinUiData[nPlayer].state == FADE_IN)
	{//フェードイン状態
		m_aJoinUiData[nPlayer].col.a -= BLINKING_SPEED;			//ポリゴンを透明にしていく

		if (m_aJoinUiData[nPlayer].col.a <= 0.0f)
		{
			m_aJoinUiData[nPlayer].col.a = 0.0f;

			m_aJoinUiData[nPlayer].state = FADE_OUT;
		}
	}
	else if (m_aJoinUiData[nPlayer].state == FADE_OUT)
	{//フェードアウト状態
		m_aJoinUiData[nPlayer].col.a += BLINKING_SPEED;			//ポリゴンを不透明にしていく

		if (m_aJoinUiData[nPlayer].col.a >= 1.0f)
		{
			m_aJoinUiData[nPlayer].col.a = 1.0f;

			m_aJoinUiData[nPlayer].state = FADE_IN;
		}
	}

	// 色の設定
	m_aJoinUiData[nPlayer].pUi2D->SetColor(m_aJoinUiData[nPlayer].col);
}

//=====================================================
// 参加入力
//=====================================================
void CSelect::EntryInput(int nPlayer)
{
	CInputJoypad* pJoypad = CInputJoypad::GetInstance();
	CInputKeyboard* pKeyboard = CInputKeyboard::GetInstance();
	CPlayerManager *pPlayerManager = CPlayerManager::GetInstance();

	if (pJoypad->GetTrigger(CInputJoypad::PADBUTTONS_A, nPlayer))
	{
		if (m_abEntry[nPlayer] == true || m_apPlayerData[nPlayer].pPlayer != nullptr || pPlayerManager == nullptr)
		{
			return;
		}

		// サウンドインスタンスの取得
		CSound* pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(pSound->LABEL_SE_APPEARE);
		}

		// 参加状態へ
		m_abEntry[nPlayer] = true;
		m_apPlayerData[nPlayer].state = PLAYER_ENTRY;

		// プレイヤーを生成
		m_apPlayerData[nPlayer].pPlayer = pPlayerManager->BindPlayer(nPlayer);

		// 位置をUIの場所へ
		m_apPlayerData[nPlayer].pPlayer->SetPosition(D3DXVECTOR3(
			SPOWN_POS.x + (nPlayer * UI_SPACE.x),
			SPOWN_POS.y,
			SPOWN_POS.z));

		// ジャンプさせる
		D3DXVECTOR3 move = { 0.0f,POW_JUMP,0.0f };
		m_apPlayerData[nPlayer].pPlayer->SetMove(move);

		CDebrisSpawner::Create(D3DXVECTOR3(
			m_aJoinUiData[nPlayer].pUi2D->GetPosition().x,
			50.0f,
			m_aJoinUiData[nPlayer].pUi2D->GetPosition().z), CDebrisSpawner::TYPE::TYPE_SOIL, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// UI削除
		ObjDelete(nPlayer);
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_F4))
	{
		if (m_abEntry[nPlayer] == true || m_apPlayerData[nPlayer].pPlayer != nullptr || pPlayerManager == nullptr)
		{
			return;
		}

		// サウンドインスタンスの取得
		CSound* pSound = CSound::GetInstance();

		if (pSound != nullptr)
		{
			pSound->Play(pSound->LABEL_SE_APPEARE);
		}

		// 参加状態へ
		m_abEntry[nPlayer] = true;
		m_apPlayerData[nPlayer].state = PLAYER_ENTRY;

		// プレイヤーを生成
		m_apPlayerData[nPlayer].pPlayer = pPlayerManager->BindPlayer(nPlayer);

		// 位置をUIの場所へ
		m_apPlayerData[nPlayer].pPlayer->SetPosition(D3DXVECTOR3(
			SPOWN_POS.x + (nPlayer * UI_SPACE.x),
			SPOWN_POS.y,
			SPOWN_POS.z));

		// ジャンプさせる
		D3DXVECTOR3 move = { 0.0f,POW_JUMP,0.0f };
		m_apPlayerData[nPlayer].pPlayer->SetMove(move);

		CDebrisSpawner::Create(D3DXVECTOR3(
			m_aJoinUiData[nPlayer].pUi2D->GetPosition().x,
			50.0f,
			m_aJoinUiData[nPlayer].pUi2D->GetPosition().z), CDebrisSpawner::TYPE::TYPE_SOIL, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// UI削除
		ObjDelete(nPlayer);
	}
#endif
}

//=====================================================
// 透明な壁
//=====================================================
void CSelect::MoveLimit(int nPlayer)
{
	if (m_apPlayerData[nPlayer].pPlayer == nullptr)
	{
		return;
	}

	// 情報の取得
	D3DXVECTOR3 pos = m_apPlayerData[nPlayer].pPlayer->GetPosition();
	D3DXVECTOR3 move = m_apPlayerData[nPlayer].pPlayer->GetMove();
	CCamera* pCamera = CManager::GetCamera();

	// 大人の壁判定
	if (m_selectState == STATE_BEFORE)
	{
		if (pos.z < ADULTWALL_POS_Z)
		{
			pos.z = ADULTWALL_POS_Z;
		}
	}
	else
	{
		if (pos.z < 20.0f)
		{
			pos.z = 20.0f;
		}
	}

	//情報の反映
	//m_apPlayerData[nPlayer].pPlayer->SetPosition(pos);
	//m_apPlayerData[nPlayer].pPlayer->SetMove(move);
}

//=====================================================
// プレイヤーの登場
//=====================================================
void CSelect::PlayerShowUp(int nPlayer)
{
	if (m_apPlayerData[nPlayer].pPlayer == nullptr)
	{
		return;
	}

	if (m_apPlayerData[nPlayer].state != PLAYER_ENTRY)
	{
		return;
	}

	// 情報の取得
	D3DXVECTOR3 pos = m_apPlayerData[nPlayer].pPlayer->GetPosition();
	D3DXVECTOR3 move = m_apPlayerData[nPlayer].pPlayer->GetMove();

	if (pos.y >= 100.0f)
	{
		m_apPlayerData[nPlayer].state = PLAYER_FREE;
	}
}

//=====================================================
// リフト
//=====================================================
void CSelect::Rift(void)
{
	if (m_bOk == true)
	{
		CCamera* pCamera = CManager::GetCamera();

		D3DXVECTOR3 rift = m_pLift->GetPosition();
		rift.y += LIFT_UP;
		m_pLift->SetPosition(rift);

		if (m_bRiftCamera == false)
		{
			pCamera->SetLift();
			m_bRiftCamera = true;
		}
		else
		{
			pCamera->SetUpLift();
		}

		for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
		{
			if (m_abEntry[nCnt] == true)
			{
				D3DXVECTOR3 pos = m_apPlayerData[nCnt].pPlayer->GetPosition();
				D3DXVECTOR3 move = m_apPlayerData[nCnt].pPlayer->GetMove();

				pos = m_apPlayerData[nCnt].pPlayer->GetPosition();
				pos.y += LIFT_UP;
				m_apPlayerData[nCnt].pPlayer->SetPosition(pos);
			}
		}

		CFade* pFade = CFade::GetInstance();

		if (rift.y > GO_GAME_POSy)
		{
			if (pFade != nullptr && m_abEntry[0] != false)
			{
				pFade->SetFade(CScene::MODE_GAME);
			}
		}
	}
}

//=====================================================
// リフト内に入った人数のUI
//=====================================================
void CSelect::LiftInNumberUi(int nPlayer)
{
	//for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apNumber[0] != nullptr)
		{
			m_apNumber[0]->SetValue(CLift::GetInPlayer(), 1);
		}

		if (m_apNumber[1] != nullptr)
		{
			m_apNumber[1]->SetValue(nPlayer, 1);
		}
	}
}

//=====================================================
// オブジェクトえお消す処理
//=====================================================
void CSelect::ObjDelete(int nPlayer)
{
	if (m_aJoinUiData[nPlayer].pUi2D != nullptr)
	{
		m_aJoinUiData[nPlayer].pUi2D->Uninit();
		m_aJoinUiData[nPlayer].pUi2D = nullptr;
	}
	if (m_apPlayerData[nPlayer].pLeaf != nullptr)
	{
		m_apPlayerData[nPlayer].pLeaf->Uninit();
		m_apPlayerData[nPlayer].pLeaf = nullptr;
	}
}

//=====================================================
// 描画処理
//=====================================================
void CSelect::Draw(void)
{

}