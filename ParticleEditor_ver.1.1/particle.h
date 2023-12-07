//*****************************************************
//
// �p�[�e�B�N������[particle.h]
// Author:���R����
//
//*****************************************************

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �N���X��`
//*****************************************************
class CParticle : public CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// ���ł��Ȃ�
		TYPE_EXPLOSION,	// ����
		TYPE_SAND,	// ���ڂ���
		TYPE_MAX
	}TYPE;

	CParticle(int nPriority = 3);	// �R���X�g���N�^
	~CParticle();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};
	static CParticle *Create(D3DXVECTOR3 pos, TYPE type);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return D3DXVECTOR3(); }	// �擾����
	float GetWidth(void) { return 0.0f; }	// �T�C�Y�擾
	float GetHeight(void) { return 0.0f; }	// �T�C�Y�擾
	static void Input(void);	// ���͏���
	static void Load(void);

private:
	static void Save(void);

	D3DXVECTOR3 m_pos;	// �ʒu
	int m_nLifeParticle;	// ����

	static char *m_pTexPath;	// �e�N�X�`���p�X
	static D3DXVECTOR3 m_rot;	// ����
	static int m_nLife;	// ����
	static int m_nLifeEffect;	// �G�t�F�N�g�̎���
	static float m_fRadiusEffect;	// �G�t�F�N�g�̔��a
	static int m_nNumEffect;	// �G�t�F�N�g�̐�
	static float m_fRangeSpeed;	// �X�s�[�h�̕�
	static float m_fRangeRadius;	// �T�C�Y�̕�
	static float m_fSpeed;	// �G�t�F�N�g�̊�X�s�[�h
	static D3DXCOLOR m_col;	// �F
	static int m_bAdd;	// ���Z���������邩�ǂ���
	static int m_nCurrentCol;	// �F�̑I��v�f
	static bool m_bLoop;	// ���[�v���邩�ǂ���
	static int m_nRate;	// ���Z�{��
	static float m_fGravity;	// �d��
	static float m_fDecrease;	// ���a������
	static int m_bRot;	// �����𔽉f���邩�ǂ���
	static float m_fRangeRot;	// �����̃����_���͈�
	static int m_nNumAll;	// ����
	static bool m_bTurn;	// ���]���邩�ǂ���
};

#endif