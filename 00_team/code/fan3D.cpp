//*****************************************************
//
// 2D~Μ[Fan3D.h]
// Author:ϋόRη
//
//*****************************************************

//*****************************************************
// CN[h
//*****************************************************
#include "fan3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "universal.h"
#include "debugproc.h"

//*****************************************************
// θθ`
//*****************************************************
namespace
{
	const float INITIAL_RADIUS = 50.0f;	// ϊΜΌa
	const char* TEX_PATH = "data\\TEXTURE\\UI\\gauge.png";	// eNX`ΜpX
}

//=====================================================
// DζΚπίιRXgN^
//=====================================================
CFan3D::CFan3D(int nPriority) : CObject(nPriority)
{
	// ΟΜNA
	m_pVtxBuff = nullptr;
	m_bBillboard = false;
	m_pos = { 0,0,0 };
	m_rot = { 0.0f,0.0f,0.0f };
	m_fRadius = 0.0f;
	m_nNumVtx = 0;
	m_fAngleMax = 1.0f;
	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_nIdxTexture = -1;
}

//=====================================================
// fXgN^
//=====================================================
CFan3D::~CFan3D()
{

}

//=====================================================
// Ά¬
//=====================================================
CFan3D *CFan3D::Create(int nPriority, int nNumVtx)
{
	CFan3D *pFan3D = nullptr;

	// CX^XΆ¬
	pFan3D = new CFan3D(nPriority);

	if (pFan3D != nullptr)
	{
		pFan3D->m_nNumVtx = nNumVtx;

		// ϊ»
		pFan3D->Init();
	}

	return pFan3D;
}

//=====================================================
// ϊ»
//=====================================================
HRESULT CFan3D::Init(void)
{
	// foCXΜζΎ
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	if (pDevice != nullptr)
	{
		if (m_pVtxBuff == nullptr)
		{
			// Έ_obt@ΜΆ¬
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nNumVtx + 2),
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&m_pVtxBuff,
				nullptr);
		}
	}

	// eNX`Ηέέ
	int nIdx = CTexture::GetInstance()->Regist(TEX_PATH);
	SetIdxTexture(nIdx);

	m_fRadius = INITIAL_RADIUS;

	// Fϊ»
	SetCol(m_col);

	// Έ_έθ
	SetVtx();

	EnableLighting(false);

	return S_OK;
}

//=====================================================
// IΉ
//=====================================================
void CFan3D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// ©ͺ©gΜjό
	Release();
}

//=====================================================
// XV
//=====================================================
void CFan3D::Update(void)
{
	SetVtx();
}

//=====================================================
// Έ_Κuέθ
//=====================================================
void CFan3D::SetVtx(void)
{
	// Έ_ξρΜ|C^
	VERTEX_3D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// Έ_obt@πbN΅AΈ_ξρΦΜ|C^πζΎ
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// SΜΈ_Μέθ
		pVtx[0].pos = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
		pVtx[0].tex = D3DXVECTOR2{ 0.5f,0.5f };

		for (int i = 1;i < m_nNumVtx + 2;i++)
		{// ~όΜΈ_Μέθ
			float fAngle = (6.28f * m_fAngleMax) * ((float)(i - 1) / (float)m_nNumVtx);

			universal::LimitRot(&fAngle);

			pVtx[i].pos =
			{
				sinf(fAngle) * m_fRadius,
				cosf(fAngle) * m_fRadius,
				0.0f,
			};

			D3DXVECTOR2 tex =
			{
				0.5f + sinf(fAngle) * 0.5f,
				0.5f - cosf(fAngle) * 0.5f,
			};

			pVtx[i].tex = tex;
		}

		// Έ_obt@ΜAbN
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// `ζ
//=====================================================
void CFan3D::Draw(void)
{
	// foCXΜζΎ
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	if (pDevice != nullptr)
	{

		//[h}gbNXϊ»
		D3DXMatrixIdentity(&m_mtxWorld);

		if (m_bBillboard)
		{// r{[h`ζ
			DrawBillboard();
		}
		else
		{// ΚνΜ`ζ
			DrawNormal();
		}

		//[h}gbNXέθ
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//Έ_obt@πf[^Xg[Ιέθ
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//Έ_tH[}bgΜέθ
		pDevice->SetFVF(FVF_VERTEX_3D);

		// eNX`έθ
		LPDIRECT3DTEXTURE9 pTexture = CTexture::GetInstance()->GetAddress(m_nIdxTexture);
		pDevice->SetTexture(0, pTexture);

		// JOΜOFF
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// `ζ
		pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, m_nNumVtx);

		// JOΜON
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_FORCE_DWORD);
	}
}

//=====================================================
// Κν`ζ
//=====================================================
void CFan3D::DrawNormal(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	//ό«π½f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//Κuπ½f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//=====================================================
// r{[h`ζ
//=====================================================
void CFan3D::DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();
	D3DXMATRIX mtxView, mtxTrans;

	//r[}gbNXζΎ
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//|SπJΙό―ι
	D3DXMatrixInverse(&m_mtxWorld, nullptr, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// Κuπ½f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//=====================================================
// έθ
//=====================================================
void CFan3D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=====================================================
// Fέθ
//=====================================================
void CFan3D::SetCol(D3DXCOLOR col)
{
	m_col = col;

	// Έ_ξρΜ|C^
	VERTEX_3D *pVtx;

	if (m_pVtxBuff != nullptr)
	{
		// Έ_obt@πbN΅AΈ_ξρΦΜ|C^πζΎ
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < m_nNumVtx + 2; nCnt++)
		{
			pVtx[nCnt].col = (D3DCOLOR)m_col;

			pVtx[nCnt].nor = D3DXVECTOR3{ 0.0f, 0.0f, -1.0f };
		}

		// Έ_obt@ΜAbN
		m_pVtxBuff->Unlock();
	}
}