//*****************************************************
//
// 分割キャラクターの処理[character.h]
// Author:酒井南勝
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "characterDiv.h"
#include "motionDiv.h"

#include "universal.h"

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
CCharacterDiv* CCharacterDiv::Create(char* pPathLower, char* pPathUpper)
{
	CCharacterDiv* pCharacter = nullptr;

	pCharacter = new CCharacterDiv;

	if (pCharacter != nullptr)
	{
		pCharacter->m_info.apPath[PARTS_LOWER] = pPathLower;
		pCharacter->m_info.apPath[PARTS_UPPER] = pPathUpper;
		pCharacter->Init();
	}

	return pCharacter;
}

//=====================================================
// 読込処理
//=====================================================
void CCharacterDiv::Load(char* pPathLower, char* pPathUpper)
{
	if (m_info.pBody == nullptr && pPathLower != nullptr && pPathUpper != nullptr)
	{
		m_info.pBody = CMotionDiv::Create(pPathLower, pPathUpper);

		if (m_info.pBody != nullptr)
		{
			D3DXVECTOR3 pos = GetPosition();
			D3DXVECTOR3 rot = GetRot();

			m_info.pBody->SetPosition(pos);
			m_info.pBody->SetRot(rot);
			m_info.pBody->MultiplyMtx();
		}
	}
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CCharacterDiv::Init(void)
{
	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CCharacterDiv::Uninit(void)
{
	if (m_info.pBody != nullptr)
	{
		m_info.pBody->Uninit();
		m_info.pBody = nullptr;
	}

	// 自身の破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CCharacterDiv::Update(void)
{
	if (m_info.pBody != nullptr)
	{// 体の追従
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 rot = GetRot();

		m_info.pBody->SetPosition(pos);
		m_info.pBody->SetRot(rot);
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
	if (m_info.pBody != nullptr)
	{
		m_info.pBody->SetMotion(nNum,nMotion);
	}
}

//=====================================================
// モーション取得
//=====================================================
int CCharacterDiv::GetMotion(int nNum)
{
	int nMotion = 0;

	if (m_info.pBody != nullptr)
	{
		nMotion = m_info.pBody->GetMotion(nNum);
	}

	return nMotion;
}