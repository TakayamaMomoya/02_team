//*****************************************************
//
// �����L�����N�^�[�̏���[characterDiv.h]
// Author:���R����
//
//*****************************************************

#ifndef _CHARACTER_DIV_H_
#define _CHARACTER_DIV_H_

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"

//*****************************************************
// �O���錾
//*****************************************************
class CMotion;

//*****************************************************
// �萔��`
//*****************************************************

//*****************************************************
// �N���X�̒�`
//*****************************************************
class CCharacterDiv : public CObject
{
public:

	CCharacterDiv(int nPriority = 4);	// �R���X�g���N�^
	~CCharacterDiv();					// �f�X�g���N�^

	static CCharacterDiv* Create(char* pPathUpper,char* pPathLower);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos) { m_info.pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_info.pos; }
	void SetPositionOld(D3DXVECTOR3 pos) { m_info.posOld = pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_info.posOld; }
	void SetMove(D3DXVECTOR3 move) { m_info.move = move; }
	D3DXVECTOR3 GetMove(void) { return m_info.move; }
	void SetRot(D3DXVECTOR3 rot) { m_info.rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_info.rot; }
	CMotion* GetBody(int nNum) { return m_info.apBody[nNum]; }
	void Load(char* pPathUpper, char* pPathLower);
	void SetMotion(int nNum,int nMotion);
	int GetMotion(int nNum);

private:

	enum Parts
	{
		PARTS_UPPER = 0,	// �㔼�g
		PARTS_LOWER,		// �����g
		PARTS_MAX
	};

	struct SInfo
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 posOld;	// �O��̈ʒu
		D3DXVECTOR3 move;	// �ړ���
		D3DXVECTOR3 rot;	// ����
		CMotion* apBody[PARTS_MAX];	// ��
		char* apPath[PARTS_MAX];	// �̂̃p�X
	};

	SInfo m_info;	// ���g�̏��
};

#endif