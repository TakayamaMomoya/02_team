//*****************************************************
//
// �����_���[�̏���[renderer.h]
// Author:���R����
//
//*****************************************************

#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CRenderer
{
public:
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindow);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��
	void DrawFPS(void);	//FPS�\������
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// �f�o�C�X�̎擾

private:
	LPDIRECT3D9 m_pD3D;	// �I�u�W�F�N�g�̐���
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// �f�o�C�X
};

#endif