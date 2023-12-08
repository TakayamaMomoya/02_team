//*****************************************************
//
// UI�}�l�[�W���[[UIManager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "inputkeyboard.h"
#include "UIManager.h"
#include "game.h"

#include "texture.h"

#include "UI.h"
#include "life.h"
#include "UIMagazine.h"

#include "player.h"
#include "playerManager.h"
#include "weapon.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define TIME_PENALTY	(15)	// �^�C���y�i���e�B

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
	const D3DXVECTOR3 FRAME_POS[NUM_PLAYER] =
	{// ��̈ʒu
		D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.225f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.225f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 0.775f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.775f, 0.0f),
	};

	const D3DXVECTOR3 FACE_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3(0.0f, -95.0f, 0.0f),
		D3DXVECTOR3(0.0f, -95.0f, 0.0f),
		D3DXVECTOR3(0.0f,  90.0f, 0.0f),
		D3DXVECTOR3(0.0f,  90.0f, 0.0f),
	};
	const float FACE_SIZE = 65.0f;
	const float FACE_WIDTH = 0.5f * FACE_SIZE ;
	const float FACE_HEIGHT = 0.6f * FACE_SIZE;
	const D3DXCOLOR FACE_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const char* FACE_FILE_NAME[NUM_PLAYER] =
	{// �t�@�C����
		"data\\TEXTURE\\UI\\player01.png",
		"data\\TEXTURE\\UI\\player02.png",
		"data\\TEXTURE\\UI\\player03.png",
		"data\\TEXTURE\\UI\\player04.png",
	};

	const D3DXVECTOR3 WEAPON_NULL_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3(0.0f, -20.0f, 0.0f),
		D3DXVECTOR3(0.0f, -20.0f, 0.0f),
		D3DXVECTOR3(0.0f,  20.0f, 0.0f),
		D3DXVECTOR3(0.0f,  20.0f, 0.0f),
	};
	const float WEAPON_NULL_SIZE = 30.0f;
	const float WEAPON_NULL_WIDTH = 1.0f * WEAPON_NULL_SIZE;
	const float WEAPON_NULL_HEIGHT = 0.5f * WEAPON_NULL_SIZE;
	const D3DXCOLOR WEAPON_NULL_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const char* WEAPON_NULL_FILE_NAME = "data\\TEXTURE\\UI\\weapon_null.png";

	const D3DXVECTOR3 WEAPON_POS_PLUS[CWeapon::TYPE_MAX][NUM_PLAYER] =
	{// �������Z���̈ʒu
		
		D3DXVECTOR3(-10.0f, -20.0f, 0.0f),
		D3DXVECTOR3( 10.0f, -20.0f, 0.0f),
		D3DXVECTOR3(-10.0f,  20.0f, 0.0f),
		D3DXVECTOR3( 10.0f,  20.0f, 0.0f),
		
		D3DXVECTOR3(-10.0f, -20.0f, 0.0f),
		D3DXVECTOR3( 10.0f, -20.0f, 0.0f),
		D3DXVECTOR3(-10.0f,  20.0f, 0.0f),
		D3DXVECTOR3( 10.0f,  20.0f, 0.0f),

		D3DXVECTOR3(0.0f, -20.0f, 0.0f),
		D3DXVECTOR3(0.0f, -20.0f, 0.0f),
		D3DXVECTOR3(0.0f,  20.0f, 0.0f),
		D3DXVECTOR3(0.0f,  20.0f, 0.0f),
		
		D3DXVECTOR3(0.0f, -20.0f, 0.0f),
		D3DXVECTOR3(0.0f, -20.0f, 0.0f),
		D3DXVECTOR3(0.0f, 20.0f, 0.0f),
		D3DXVECTOR3(0.0f, 20.0f, 0.0f),
	};
	const float WEAPON_SIZE[CWeapon::TYPE_MAX] =
	{// �������Z���̈ʒu
		40.0f,
		50.0f,
		50.0f,
		35.0f,
	};
	const float WEAPON_WIDTH[CWeapon::TYPE_MAX] =
	{// �������Z���̈ʒu
		1.0f * WEAPON_SIZE[CWeapon::TYPE_MAGNUM],
		0.6f * WEAPON_SIZE[CWeapon::TYPE_MACHINEGUN],
		1.0f * WEAPON_SIZE[CWeapon::TYPE_SHOTGUN],
		1.4f * WEAPON_SIZE[CWeapon::TYPE_RAILGUN],
	};
	const float WEAPON_HEIGHT[CWeapon::TYPE_MAX] =
	{// �������Z���̈ʒu
		0.5f * WEAPON_SIZE[CWeapon::TYPE_MAGNUM],
		0.7f * WEAPON_SIZE[CWeapon::TYPE_MACHINEGUN],
		0.2f * WEAPON_SIZE[CWeapon::TYPE_SHOTGUN],
		0.4f * WEAPON_SIZE[CWeapon::TYPE_RAILGUN],
	};
	const D3DXCOLOR WEAPON_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const char* WEAPON_FILE_NAME[CWeapon::TYPE_MAX] =
	{// �t�@�C����
		"data\\TEXTURE\\UI\\weapon_magnum.png",
		"data\\TEXTURE\\UI\\weapon_mac10.png",
		"data\\TEXTURE\\UI\\weapon_shotgun.png",
		"data\\TEXTURE\\UI\\weapon_railgun.png",
	};

	const D3DXVECTOR3 LIFE_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3( 30.0f, -40.0f, 0.0f),
		D3DXVECTOR3(-30.0f, -40.0f, 0.0f),
		D3DXVECTOR3( 30.0f,  80.0f, 0.0f),
		D3DXVECTOR3(-30.0f,  80.0f, 0.0f),
	};
	const D3DXVECTOR3 LIFE_FRAME_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3( 30.0f, -60.0f, 0.0f),
		D3DXVECTOR3(-30.0f, -60.0f, 0.0f),
		D3DXVECTOR3( 30.0f,  60.0f, 0.0f),
		D3DXVECTOR3(-30.0f,  60.0f, 0.0f),
	};
	const float LIFE_SIZE = 30.0f;
	const float LIFE_WIDTH = 0.8f * LIFE_SIZE;
	const float LIFE_HEIGHT = 0.7f * LIFE_SIZE;
	const D3DXCOLOR LIFE_COLOR = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR LIFE_FRAME_COLOR = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	const char* LIFE_FILE_NAME = "data\\TEXTURE\\UI\\life000.png";

	const D3DXVECTOR3 MAGAZINE_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3(-15.0f,  60.0f, 0.0f),
		D3DXVECTOR3( -5.0f,  60.0f, 0.0f),
		D3DXVECTOR3(-15.0f, -60.0f, 0.0f),
		D3DXVECTOR3( -5.0f, -60.0f, 0.0f),
	};
	const D3DXVECTOR3 MAGAZINE_FRAME_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3(-15.0f,  60.0f, 0.0f),
		D3DXVECTOR3( -5.0f,  60.0f, 0.0f),
		D3DXVECTOR3(-15.0f, -60.0f, 0.0f),
		D3DXVECTOR3( -5.0f, -60.0f, 0.0f),
	};
	const D3DXVECTOR3 MAGAZINE_NUM_POS_PLUS[NUM_PLAYER] =
	{// �������Z���̈ʒu
		D3DXVECTOR3(-30.0f,	60.0f, 0.0f),
		D3DXVECTOR3(-20.0f,	60.0f, 0.0f),
		D3DXVECTOR3(-30.0f,-60.0f, 0.0f),
		D3DXVECTOR3(-20.0f,-60.0f, 0.0f),
	};
	const float MAGAZINE_SIZE = 60.0f;
	const float MAGAZINE_WIDTH = MAGAZINE_SIZE * 0.6f;
	const float MAGAZINE_HEIGHT = MAGAZINE_SIZE * 0.8f;
	const float MAGAZINE_NUM_SIZE = 12.5f;
	const float MAGAZINE_NUM_WIDTH = MAGAZINE_NUM_SIZE * 1.0f;
	const float MAGAZINE_NUM_HEIGHT = MAGAZINE_NUM_SIZE * 1.0f;
	const D3DXCOLOR MAGAZINE_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const D3DXCOLOR MAGAZINE_FRAME_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
	const D3DXCOLOR MAGAZINE_NUM_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const char* MAGAZINE_FILE_NAME = "data\\TEXTURE\\UI\\magazin.png";
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CUIManager *CUIManager::m_pUIManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CUIManager::CUIManager()
{
	m_bDisp = false;
	ZeroMemory(&m_aInfo[0], sizeof(m_aInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CUIManager::~CUIManager()
{

}

//=====================================================
// ��������
//=====================================================
CUIManager *CUIManager::Create(void)
{
	if (m_pUIManager == nullptr)
	{// �C���X�^���X����
		m_pUIManager = new CUIManager;

		// ����������
		m_pUIManager->Init();
	}

	return m_pUIManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CUIManager::Init(void)
{
	m_bDisp = true;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CUIManager::Uninit(void)
{
	m_pUIManager = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CUIManager::Update(void)
{
	// ����UI�̍X�V
	UpdateUIWeapon();

	// �F�؂�ւ�����
	UpdateUIColor();

	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetTrigger(DIK_1))
		{
			m_bDisp = m_bDisp ? false : true;
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CUIManager::Draw(void)
{
#ifdef _DEBUG

#endif
}

//=====================================================
// �v���C���[UI�̐�������
//=====================================================
void CUIManager::SetPlayer(int nIdx)
{
	m_aInfo[nIdx].fUIColorAlpha = 1.0f;

	CreateFace(nIdx);
	CreateWeapon(nIdx);
	CreateLife(nIdx);
	CreateUIMagazine(nIdx);
}

//=====================================================
// ��UI�̐�������
//=====================================================
void CUIManager::CreateFace(int nIdx)
{
	// ��UI�̐�������
	CUI* pUiFace = CUI::Create();

	if (pUiFace != nullptr &&
		m_aInfo[nIdx].pUiFace == nullptr)
	{
		// ��UI�̃|�C���^����
		m_aInfo[nIdx].pUiFace = pUiFace;

		// ��UI�̐ݒ�
		m_aInfo[nIdx].pUiFace->SetPosition(FRAME_POS[nIdx] + FACE_POS_PLUS[nIdx]);
		m_aInfo[nIdx].pUiFace->SetSize(FACE_WIDTH, FACE_HEIGHT);
		m_aInfo[nIdx].pUiFace->SetCol(FACE_COLOR);

		CTexture* pTexture = CTexture::GetInstance();

		if (pTexture != nullptr)
		{
			int nTexIdx = pTexture->Regist(FACE_FILE_NAME[nIdx]);
			m_aInfo[nIdx].pUiFace->SetIdxTexture(nTexIdx);
			m_aInfo[nIdx].pUiFace->SetVtx();
		}
	}
}
//=====================================================
// ����UI�̐�������
//=====================================================
void CUIManager::CreateWeapon(int nIdx)
{
	// ����UI�̐�������
	CUI* pUiWeapon = CUI::Create();

	if (pUiWeapon != nullptr &&
		m_aInfo[nIdx].pUiWeapon == nullptr)
	{
		// NULL����UI�̃|�C���^����
		m_aInfo[nIdx].pUiWeapon = pUiWeapon;
		m_aInfo[nIdx].bIsWeaponNull = true;

		// NULL����UI�̐ݒ�
		m_aInfo[nIdx].pUiWeapon->SetPosition(FRAME_POS[nIdx] + WEAPON_NULL_POS_PLUS[nIdx]);
		m_aInfo[nIdx].pUiWeapon->SetSize(WEAPON_NULL_WIDTH, WEAPON_NULL_HEIGHT);
		m_aInfo[nIdx].pUiWeapon->SetCol(WEAPON_NULL_COLOR);

		CTexture* pTexture = CTexture::GetInstance();

		if (pTexture != nullptr)
		{
			int nTexIdx = pTexture->Regist(WEAPON_NULL_FILE_NAME);
			m_aInfo[nIdx].pUiWeapon->SetIdxTexture(nTexIdx);
			m_aInfo[nIdx].pUiWeapon->SetVtx();
		}
	}
}

//=====================================================
// ���C�t�̐�������
//=====================================================
void CUIManager::CreateLife(int nIdx)
{
	// ���C�t�̐�������
	CLife* pLife = CLife::Create(nIdx);

	if (pLife != nullptr &&
		m_aInfo[nIdx].pLife == nullptr)
	{
		// ���C�t�̃|�C���^����
		m_aInfo[nIdx].pLife = pLife;

		// ���C�t�̐ݒ�
		m_aInfo[nIdx].pLife->SetPosition(
			FRAME_POS[nIdx] + LIFE_POS_PLUS[nIdx],
			FRAME_POS[nIdx] + LIFE_FRAME_POS_PLUS[nIdx]);
		m_aInfo[nIdx].pLife->SetSize(LIFE_WIDTH, LIFE_HEIGHT);
		m_aInfo[nIdx].pLife->SetCol(LIFE_COLOR,LIFE_FRAME_COLOR);
		m_aInfo[nIdx].pLife->SetTexture(LIFE_FILE_NAME);
	}
}

//=====================================================
// ���e���̐�������
//=====================================================
void CUIManager::CreateUIMagazine(int nIdx)
{
	// ���e��UI�̐�������
	CUIMagazine* pUIMagazine = CUIMagazine::Create(nIdx);

	if (pUIMagazine != nullptr &&
		m_aInfo[nIdx].pUIMagazine == nullptr)
	{
		// ���C�t�̃|�C���^����
		m_aInfo[nIdx].pUIMagazine = pUIMagazine;

		// ���C�t�̐ݒ�
		m_aInfo[nIdx].pUIMagazine->SetPosition(
			FRAME_POS[nIdx] + MAGAZINE_POS_PLUS[nIdx],
			FRAME_POS[nIdx] + MAGAZINE_FRAME_POS_PLUS[nIdx], 
			FRAME_POS[nIdx] + MAGAZINE_NUM_POS_PLUS[nIdx]);

		m_aInfo[nIdx].pUIMagazine->SetSize(
			MAGAZINE_WIDTH, MAGAZINE_HEIGHT,
			MAGAZINE_NUM_WIDTH, MAGAZINE_NUM_HEIGHT);

		m_aInfo[nIdx].pUIMagazine->SetCol(MAGAZINE_COLOR, MAGAZINE_FRAME_COLOR, MAGAZINE_NUM_COLOR);
		m_aInfo[nIdx].pUIMagazine->SetTexture(MAGAZINE_FILE_NAME);
	}
}

//=====================================================
// ����UI�̐؂�ւ�����
//=====================================================
void CUIManager::UpdateUIWeapon(void)
{
	CPlayerManager* pPlayerManager = CPlayerManager::GetInstance();

	if (pPlayerManager != nullptr)
	{
		for (int nIdx = 0; nIdx < NUM_PLAYER; nIdx++)
		{
			// �v���C���[�̎擾
			CPlayer* pPlayer = pPlayerManager->GetPlayer(nIdx);

			if (m_aInfo[nIdx].pUiWeapon != nullptr)
			{
				CWeapon* pWeapon = nullptr;

				if (pPlayer != nullptr)
				{
					pWeapon = pPlayer->GetWeapon();
				}

				if (pWeapon != nullptr ||
					m_aInfo[nIdx].bIsWeaponNull == true && pWeapon != nullptr)
				{
					if (m_aInfo[nIdx].bIsWeaponNull == true ||
						m_aInfo[nIdx].weaponType != pWeapon->GetType())
					{
						m_aInfo[nIdx].weaponType = pWeapon->GetType();
						m_aInfo[nIdx].bIsWeaponNull = false;

						m_aInfo[nIdx].pUiWeapon->SetPosition(FRAME_POS[nIdx] + WEAPON_POS_PLUS[m_aInfo[nIdx].weaponType][nIdx]);
						m_aInfo[nIdx].pUiWeapon->SetSize(WEAPON_WIDTH[m_aInfo[nIdx].weaponType], WEAPON_HEIGHT[m_aInfo[nIdx].weaponType]);
						m_aInfo[nIdx].pUiWeapon->SetCol(WEAPON_COLOR);

						CTexture* pTexture = CTexture::GetInstance();

						if (pTexture != nullptr)
						{
							int nTexIdx = pTexture->Regist(WEAPON_FILE_NAME[m_aInfo[nIdx].weaponType]);
							m_aInfo[nIdx].pUiWeapon->SetIdxTexture(nTexIdx);
							m_aInfo[nIdx].pUiWeapon->SetVtx();
						}
					}
				}
				else
				{
					m_aInfo[nIdx].bIsWeaponNull = true;

					m_aInfo[nIdx].pUiWeapon->SetPosition(FRAME_POS[nIdx] + WEAPON_NULL_POS_PLUS[nIdx]);
					m_aInfo[nIdx].pUiWeapon->SetSize(WEAPON_NULL_WIDTH, WEAPON_NULL_HEIGHT);
					m_aInfo[nIdx].pUiWeapon->SetCol(WEAPON_NULL_COLOR);

					CTexture* pTexture = CTexture::GetInstance();

					if (pTexture != nullptr)
					{
						int nTexIdx = pTexture->Regist(WEAPON_NULL_FILE_NAME);
						m_aInfo[nIdx].pUiWeapon->SetIdxTexture(nTexIdx);
						m_aInfo[nIdx].pUiWeapon->SetVtx();
					}
				}
			}
		}
	}
}

//=====================================================
// UI�̐F�ύX����
//=====================================================
void CUIManager::UpdateUIColor(void)
{
	for (int nIdx = 0; nIdx < NUM_PLAYER; nIdx++)
	{
		if (m_aInfo[nIdx].fUIColorAlpha >= 1.0f)
		{
			m_aInfo[nIdx].fUIColorAlpha -= 0.01f;

			if (m_aInfo[nIdx].pUiFace != NULL)
			{
				D3DXCOLOR col = m_aInfo[nIdx].pUiFace->GetCol();
				col.a = m_aInfo[nIdx].fUIColorAlpha;
				m_aInfo[nIdx].pUiFace->SetCol(col);
			}
			if (m_aInfo[nIdx].pUiWeapon != NULL)
			{
				D3DXCOLOR col = m_aInfo[nIdx].pUiWeapon->GetCol();
				col.a = m_aInfo[nIdx].fUIColorAlpha;
				m_aInfo[nIdx].pUiWeapon->SetCol(col);
			}
			if (m_aInfo[nIdx].pLife != NULL)
			{
				D3DXCOLOR colLife = m_aInfo[nIdx].pLife->GetColLife();
				D3DXCOLOR colLifeFrame = m_aInfo[nIdx].pLife->GetColLifeFrame();
				colLife.a = m_aInfo[nIdx].fUIColorAlpha;
				colLifeFrame.a = m_aInfo[nIdx].fUIColorAlpha;
				m_aInfo[nIdx].pLife->SetCol(colLife, colLifeFrame);
			}
			if (m_aInfo[nIdx].pUIMagazine != NULL)
			{
				D3DXCOLOR colMagazine = m_aInfo[nIdx].pUIMagazine->GetColMagazine();
				D3DXCOLOR colMagazineFrame = m_aInfo[nIdx].pUIMagazine->GetColMagazineFrame();
				D3DXCOLOR colNum = m_aInfo[nIdx].pUIMagazine->GetColNum();

				colMagazine.a = m_aInfo[nIdx].fUIColorAlpha;
				colMagazineFrame.a = m_aInfo[nIdx].fUIColorAlpha;
				colNum.a = m_aInfo[nIdx].fUIColorAlpha;

				m_aInfo[nIdx].pUIMagazine->SetCol(colMagazine, colMagazineFrame, colNum);
			}
		}
	}
}