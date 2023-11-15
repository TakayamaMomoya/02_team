//*****************************************************
//
// 武器マネージャー[weaponManager.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "weaponManager.h"
#include "Weapon.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define PARAM_PATH	"data\\TEXT\\weapon.txt"	// パラメーターのパス

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CWeaponManager *CWeaponManager::m_pWeaponManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CWeaponManager::CWeaponManager()
{

}

//=====================================================
// デストラクタ
//=====================================================
CWeaponManager::~CWeaponManager()
{

}

//=====================================================
// 生成処理
//=====================================================
CWeaponManager *CWeaponManager::Create(void)
{
	if (m_pWeaponManager == nullptr)
	{// インスタンス生成
		m_pWeaponManager = new CWeaponManager;

		// 初期化処理
		m_pWeaponManager->Init();
	}

	return m_pWeaponManager;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CWeaponManager::Init(void)
{
	// パラメーター読み込み
	LoadParam();

	return S_OK;
}

//=====================================================
// パラメーター読み込み処理
//=====================================================
void CWeaponManager::LoadParam(void)
{
	// 変数宣言
	char cTemp[256];
	int nCntParam = 0;

	// ファイルから読み込む
	FILE* pFile = fopen(PARAM_PATH, "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "MAGNUMSET") == 0)
			{// パラメーター読込開始
				while (true)
				{
					// 文字読み込み
					(void)fscanf(pFile, "%s", &cTemp[0]);

					// 基底パラメーター読み込み
					LoadBaseInfo(pFile, &cTemp[0], CWeapon::TYPE_MAGNUM);

					if (strcmp(cTemp, "END_MAGNUMSET") == 0)
					{// パラメーター読込終了
						break;
					}
				}
			}

			if (strcmp(cTemp, "MACHINEGUNSET") == 0)
			{// パラメーター読込開始
				while (true)
				{
					// 文字読み込み
					(void)fscanf(pFile, "%s", &cTemp[0]);

					// 基底パラメーター読み込み
					LoadBaseInfo(pFile, &cTemp[0], CWeapon::TYPE_MACHINEGUN);

					if (strcmp(cTemp, "END_MACHINEGUNSET") == 0)
					{// パラメーター読込終了
						break;
					}
				}
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// 読み込みの終了
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		assert(("武器情報読み込みに失敗", false));
	}
}

//=====================================================
// パラメーター読込
//=====================================================
void CWeaponManager::LoadBaseInfo(FILE* pFile, char* pTemp, int nCntParam)
{
	if (strcmp(pTemp, "BULLET") == 0)
	{// 弾数
		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%d", &m_aInfo[nCntParam].nMaxBullet);
	}

	if (strcmp(pTemp, "RAPID") == 0)
	{// 連射力
		(void)fscanf(pFile, "%s", pTemp);

		(void)fscanf(pFile, "%d", &m_aInfo[nCntParam].nRapid);
	}
}

//=====================================================
// 終了処理
//=====================================================
void CWeaponManager::Uninit(void)
{
	m_pWeaponManager = nullptr;

	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CWeaponManager::Update(void)
{

}

//=====================================================
// 描画処理
//=====================================================
void CWeaponManager::Draw(void)
{

}