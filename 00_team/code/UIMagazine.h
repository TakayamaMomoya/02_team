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

	void SetPosition(D3DXVECTOR3 posDig, D3DXVECTOR3 posMaxDig);
	void SetSize(float width, float height);
	void SetCol(D3DXCOLOR col);

private:

	struct Sinfo
	{
		int nIdxPlayer;		// �Q�Ƃ���v���C���[�̔ԍ�
		int nIdxTexture;					// �e�N�X�`���ԍ�
		static LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���ւ̃|�C���^
	};

	CNumber* m_pNumDig;			// ���e���i�����j�̃|�C���^
	CNumber* m_pNumMaxDig;		// �ő呕�e���i�����j�̃|�C���^
	Sinfo m_info;	// ���g�̏��
};

#endif
