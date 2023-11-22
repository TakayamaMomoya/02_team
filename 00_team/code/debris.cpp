//*****************************************************
//
// パーティクル処理[particle.cpp]
// Author:��山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "debris.h"
#include "debrisSpawner.h"
#include <stdio.h>

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CDebris::PARTICLE_INFO* CDebris::m_apDebris[CDebris::TYPE_MAX + 1] = {};

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CDebris::CDebris(int nPriority) : CObject(nPriority)
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_type = TYPE_NONE;
	m_pPosOwner = nullptr;
	m_nPriorityDebris = 0;
	m_nLife = 0;

	SetType(TYPE_PARTICLE);
}

//=====================================================
//	デストラクタ
//=====================================================
CDebris::~CDebris()
{

}

//=====================================================
//	初期化処理
//=====================================================
HRESULT CDebris::Init(void)
{
	return S_OK;
}

//=====================================================
//	終了処理
//=====================================================
void CDebris::Uninit(void)
{
	Release();
}

//=====================================================
//	破棄処理
//=====================================================
void CDebris::Unload(void)
{
	for (int nCntDebris = 0; nCntDebris < TYPE_MAX; nCntDebris++)
	{
		if (m_apDebris[nCntDebris] != nullptr)
		{
			delete m_apDebris[nCntDebris];
			m_apDebris[nCntDebris] = nullptr;
		}
	}
}

//=====================================================
//	更新処理
//=====================================================
void CDebris::Update(void)
{
	// 変数宣言
	float fRot, fRot2;
	float fMove = 0.0f;
	float fRadius = 0.0f;
	int nLife = 0;
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };
	CObjectX* pEffect3D = nullptr;

	for (int nCntEffect = 0; nCntEffect < m_apDebris[m_type]->nNumDebris; nCntEffect++)
	{
		if (m_apDebris[m_type]->nRot)
		{// 向きの反映
			if (m_apDebris[m_type]->fRangeRot > 0.1f)
			{
				fRot = m_rot.x + (float)(rand() % (int)(m_apDebris[m_type]->fRangeRot * 100.0f) - m_apDebris[m_type]->fRangeRot * 50.0f) / 100.0f;
				fRot2 = m_rot.y + (float)(rand() % (int)(m_apDebris[m_type]->fRangeRot * 100.0f) - m_apDebris[m_type]->fRangeRot * 50.0f) / 100.0f * 2;
			}
			else
			{
				fRot = m_rot.x + (rand() % (int)(0.1f * 100.0f) - 0.1f * 50.0f) / 100.0f;
				fRot2 = m_rot.y + (rand() % (int)(0.1f * 100.0f) - 0.1f * 50.0f) / 100.0f * 2;
			}
		}
		else
		{// 全方位
			fRot = rand() % 628 - 314 / 100.0f;
			fRot2 = rand() % 628 - 314 / 100.0f;
		}

		if (m_apDebris[m_type]->fSpeed > 0.1f)
		{
			fMove = (float)(rand() % (int)(m_apDebris[m_type]->fSpeed * 10)) * 0.1f + m_apDebris[m_type]->fSpeed * 0.5f;
		}
		if (m_apDebris[m_type]->nLifeDebris != 0)
		{
			nLife = rand() % m_apDebris[m_type]->nLifeDebris + m_apDebris[m_type]->nLifeDebris / 2;
		}

		move.x = sinf(fRot) * sinf(fRot2) * fMove;
		move.y = cosf(fRot) * fMove;
		move.z = sinf(fRot) * cosf(fRot2) * fMove;

			// エフェクト生成
		pEffect3D = CDebrisSpawner::Create(m_pos, nLife, move, m_apDebris[m_type]->fGravity);
	}

	m_nLife--;

	if (m_nLife < 0)
	{
		// 自身の破棄
		Uninit();
	}
}

//=====================================================
//	位置設定処理
//=====================================================
void CDebris::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
//	生成処理
//=====================================================
CDebris* CDebris::Create(D3DXVECTOR3 pos, TYPE type, D3DXVECTOR3 rot, D3DXVECTOR3* pPosOwner, int nPriority)
{
	CDebris* pParticle = nullptr;

	if (pParticle == nullptr)
	{// インスタンス生成
		pParticle = new CDebris;

		pParticle->m_type = type;

		pParticle->m_pos = pos;

		pParticle->m_rot = rot;

		pParticle->m_nLife = m_apDebris[type]->nLife;

		pParticle->m_pPosOwner = pPosOwner;

		pParticle->m_nPriorityDebris = nPriority;
	}

	return pParticle;
}

//=====================================================
//	読込処理
//=====================================================
void CDebris::Load(void)
{
	// 変数宣言
	char cTemp[256];
	int nCntDebris = 1;
	PARTICLE_INFO* pInfo = nullptr;

	// ファイルから読み込む
	FILE* pFile = fopen("data\\TEXT\\debris.txt", "r");

	if (pFile != nullptr)
	{// ファイルが開けた場合
		while (true)
		{
			// 文字読み込み
			(void)fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "DEBRISSET") == 0)
			{// 読込開始
				if (m_apDebris[nCntDebris] == nullptr)
				{
					// インスタンス生成
					m_apDebris[nCntDebris] = new PARTICLE_INFO;
				}

				pInfo = m_apDebris[nCntDebris];

				while (true)
				{
					// 文字読み込み
					(void)fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "END_DEBRISSET") == 0)
					{// パーティクル情報終了条件
						break;
					}

					if (strcmp(cTemp, "NUM_DEBRIS") == 0)
					{// エフェクト数取得
						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%d", &pInfo->nNumDebris);
					}

					if (strcmp(cTemp, "LIFE_DEBRIS") == 0)
					{// エフェクト寿命取得
						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%d", &pInfo->nLifeDebris);
					}

					if (strcmp(cTemp, "SPEED_DEBRIS") == 0)
					{// エフェクト速度取得
						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%f", &pInfo->fSpeed);
					}

					if (strcmp(cTemp, "GRAVITY") == 0)
					{// 重力取得
						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%f", &pInfo->fGravity);
					}

					if (strcmp(cTemp, "RANGEROT") == 0)
					{// 向きのランダム幅取得
						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%f", &pInfo->fRangeRot);
					}

					if (strcmp(cTemp, "IS_ROT") == 0)
					{// 加算合成かどうか取得
						(void)fscanf(pFile, "%s", &cTemp[0]);

						(void)fscanf(pFile, "%d", &pInfo->nRot);
					}
				}

				// パーティクル数加算
				nCntDebris++;
			}

			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// 終了条件
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		assert(("パーティクル情報読み込みに失敗", false));
	}
}