//*****************************************************
//
// �r�[���̏���[beam.h]
// Author:���R����
//
//*****************************************************

#ifndef _BEAM_H_
#define _BEAM_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CAnim3D;

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CBeam : public CObject
{
public:
	CBeam(int nPriority = 3);	// �R���X�g���N�^
	~CBeam();	// �f�X�g���N�^

	static CBeam *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetMtx(D3DXMATRIX mtx) { m_info.mtxWorld = mtx; }
	void SetAnimSize(float fWidth, float fLength) { m_info.fWidthAnim = fWidth; m_info.fLengthAnim = fLength; }

private:
	struct SInfo
	{
		CAnim3D *pAnim;	// �A�j���[�V�����G�t�F�N�g
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
		float fWidthAnim;	// �A�j���[�V�����̕�
		float fLengthAnim;	// �A�j���[�V�����̒���
	};

	void SetAnimVtx(void);

	SInfo m_info;
};

#endif
