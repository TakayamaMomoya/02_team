//*****************************************************
//
// 分割キャラクターの処理[character.h]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "characterDiv.h"
#include "motion.h"

//*****************************************************
// マクロ定義
//*****************************************************

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CCharacterDiv::CCharacterDiv(int nPriority)
{
	ZeroMemory(&m_info, sizeof(CCharacterDiv::SInfo));
}

//=====================================================
// デストラクタ
//=====================================================
CCharacterDiv::~CCharacterDiv()
{

}

//=====================================================
// 生成処理
//=====================================================
CCharacterDiv* CCharacterDiv::Create(char* pPathUpper, char* pPathLower)
{
	CCharacterDiv* pCharacter = nullptr;

	pCharacter = new CCharacterDiv;

	if (pCharacter != nullptr)
	{
		pCharacter->m_info.apPath[PARTS_UPPER] = pPathUpper;
		pCharacter->m_info.apPath[PARTS_LOWER] = pPathLower;
		pCharacter->Init();
	}

	return pCharacter;
}

//=====================================================
// 読込処理
//=====================================================
void CCharacterDiv::Load(char* pPathUpper, char* pPathLower)
{
	if (m_info.apBody[PARTS_UPPER] == nullptr && pPathUpper != nullptr &&
		m_info.apBody[PARTS_LOWER] == nullptr && pPathLower != nullptr)
	{
		m_info.apBody[PARTS_UPPER] = CMotion::Create(pPathUpper);

		if (m_info.apBody[PARTS_UPPER] != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 rot = GetRot();

			m_info.apBody[PARTS_UPPER]->SetPosition(pos);
			m_info.apBody[PARTS_UPPER]->SetRot(rot);

			m_info.apBody[PARTS_UPPER]->MultiplyMtx();
		}

		m_info.apBody[PARTS_LOWER] = CMotion::Create(pPathLower);

		if (m_info.apBody[PARTS_LOWER] != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 rot = GetRot();

			m_info.apBody[PARTS_LOWER]->SetPosition(pos);
			m_info.apBody[PARTS_LOWER]->SetRot(rot);

			m_info.apBody[PARTS_LOWER]->MultiplyMtx();
		}
	}
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CCharacterDiv::Init(void)
{
	// 体の読込
	Load(m_info.apPath[PARTS_UPPER], m_info.apPath[PARTS_LOWER]);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CCharacterDiv::Uninit(void)
{
	if (m_info.apBody[PARTS_UPPER] != nullptr)
	{
		m_info.apBody[PARTS_UPPER]->Uninit();
		m_info.apBody[PARTS_UPPER] = nullptr;
	}

	if (m_info.apBody[PARTS_LOWER] != nullptr)
	{
		m_info.apBody[PARTS_LOWER]->Uninit();
		m_info.apBody[PARTS_LOWER] = nullptr;
	}

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CCharacterDiv::Update(void)
{
	if (m_info.apBody[PARTS_UPPER] != nullptr &&
		m_info.apBody[PARTS_LOWER] != nullptr)
	{// 体の追従
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRot();

		m_info.apBody[PARTS_UPPER]->SetPosition(pos);
		m_info.apBody[PARTS_UPPER]->SetRot(rot);

		m_info.apBody[PARTS_LOWER]->SetPosition(pos);
		m_info.apBody[PARTS_LOWER]->SetRot(rot);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CCharacterDiv::Draw(void)
{

}

//=====================================================
// モーション設定
//=====================================================
void CCharacterDiv::SetMotion(int nNum, int nMotion)
{
	if (m_info.apBody[nNum] != nullptr)
	{
		m_info.apBody[nNum]->SetMotion(nMotion);
	}
}

//=====================================================
// モーション取得
//=====================================================
int CCharacterDiv::GetMotion(int nNum)
{
	int nMotion = 0;

	if (m_info.apBody[nNum] != nullptr)
	{
		nMotion = m_info.apBody[nNum]->GetMotion();
	}

	return nMotion;
}