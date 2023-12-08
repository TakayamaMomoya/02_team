//*****************************************************
//
// �c�e��UI�̏���[UIMagazine.h]
// Author:���R����
//
//*****************************************************

#ifndef _UI_MAGAZINE_H_
#define _UI_MAGAZINE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************

class CUI;
class CNumber;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CUIMagazine : public CObject
{
public:

	CUIMagazine(int nPriority = 7);	// �R���X�g���N�^
	~CUIMagazine();	// �f�X�g���N�^

	static CUIMagazine* Create(int nIdx);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float width, float height);
	void SetCol(D3DXCOLOR col);
	void SetNumMagazine(void);

	D3DXCOLOR GetCol(void) { return m_info.col; }

private:

	struct Sinfo
	{
		int nIdxPlayer;		// �Q�Ƃ���v���C���[�̔ԍ�

		D3DXVECTOR3 pos;		// �ʒu
		float fWidth;			// ����
		float fHeight;			// �c��
		float fWidthSub;		// ���Z���鉡��
		float fHeightSub;		// ���Z����c��
		D3DXCOLOR col;			// �F

		int nIdxTexture;					// �e�N�X�`���ԍ�
		static LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���ւ̃|�C���^
	};

	CNumber* m_pNumDig;	// ���e���i�����j�̃|�C���^
	Sinfo m_info;		// ���g�̏��
};

#endif
