#ifndef __SIM_H__
#define __SIM_H__

#include "platform.h"
#include "calc.h"
#include "object.h"

// sim.cpp
void InitScene( void );
void UpdateScene( void );
void TermScene( void );

// draw.cpp
void PreDraw( void );
void PostDraw( void );
void DrawScene( void );
//void Lighting( void );
//void HeadLight( void );
/*
��ObjDataT�̒�`�́Aobject.h�Ɉڍs���܂���
*/

//////// MREAL
#define N_TARGETS 15
#define N_MARKERS 2048

//-------- simulation data
typedef struct {
	int time;

	float clip_near;
	float clip_far;
	float air_color[4];
	float sky_color[4];
    //////// ���[�U��`�̃V�[���ɂ��Ẵf�[�^�������ɂ܂Ƃ߂�

	ObjDataT cube; ///////���L���[�u
	ObjDataT sphere; /////������

	ObjDataT player; /////���v���C���i�̑������j������킷�I�u�W�F�N�g

	ObjDataT head;//��
	ObjDataT body;
	ObjDataT handL;//��
	ObjDataT handR;//��
	ObjDataT footL;
	ObjDataT footR;

	ObjDataT *active_camera; //�J�����̃|�C���^�ϐ�

	ObjDataT target[N_TARGET]; //////// MREAL
	
	TargetT TargetList[N_TARGET];
	MarkerT MarkerList[N_MARKER];

	////////
} SimDataT;

#endif //__SIM_H__
