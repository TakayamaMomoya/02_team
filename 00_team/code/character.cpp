//*****************************************************
//
// キャラクターの処理[character.h]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "character.h"
#include "motion.h"

//*****************************************************
// マクロ定義
//*****************************************************
#define BODY_PATH	"data\\MOTION\\rayleigh.txt"	// 体のパス

//=====================================================
// 優先順位を決めるコンストラクタ
//=====================================================
CCharacter::CCharacter(int nPriority)
{
	ZeroMemory(&m_info, sizeof(CCharacter::SInfo));
}

//=====================================================
// デストラクタ
//=====================================================
CCharacter::~CCharacter()
{

}

//=====================================================
// 生成処理
//=====================================================
CCharacter *CCharacter::Create(char *pPath)
{
	CCharacter *pCharacter = nullptr;

	pCharacter = new CCharacter;

	if (pCharacter != nullptr)
	{
		pCharacter->m_info.pPath = pPath;
		pCharacter->Init();
	}

	return pCharacter;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CCharacter::Init(void)
{
	// 体の生成
	if (m_info.pBody == nullptr && m_info.pPath != nullptr)
	{
		m_info.pBody = CMotion::Create(m_info.pPath);
	}

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CCharacter::Uninit(void)
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
void CCharacter::Update(void)
{
	// 前回の位置を保存
	m_info.posOld = m_info.pos;

	if (m_info.pBody != nullptr)
	{// 体の追従
		D3DXVECTOR3 pos = GetPosition();

		m_info.pBody->SetPosition(pos);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CCharacter::Draw(void)
{

}