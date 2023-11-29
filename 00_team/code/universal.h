//*****************************************
//
// �ėp�����Z�b�g
// Author:���R����
//
//*****************************************
#ifndef _UNIVERSAL_H_
#define _UNIVERSAL_H_

#include "main.h"

//*****************************************
// �N���X�̒�`
//*****************************************
namespace universal
{
	void LimitRot(float *fRot);	//��]���䏈��
	void SetOffSet(D3DXMATRIX *pMtxWorldOffset, D3DXMATRIX mtxWorldOwner, D3DXVECTOR3 posOffset, D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f });	//�I�t�Z�b�g�ݒ菈��
	void FactingRot(float *pfRot, float fRotDest, float rotateFact);	//�����␳����
	bool DistCmp(D3DXVECTOR3 posOwn, D3DXVECTOR3 posTarget,float fLengthMax,float *fDiff);
	int RandRange(int nMax, int nMin);
	float CrossProduct(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
}

#endif