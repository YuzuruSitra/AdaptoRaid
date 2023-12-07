#ifndef __SIM_H__
#define __SIM_H__

#include "platform.h"
#include "calc.h"
//#include "object.h"
#include "image.h"
#include "ezMovie.h"
#include "ezMIDI.h"
#include "tcpData.h"

// sim.cpp
void InitScene( void );
void UpdateScene( void );
void TermScene( void );
void MovingFort(void);
void FortBulletMove(void);
void FortShooting(void);
void MovingEnemies(void);
void EnemyShooting(void);
void EnemyBulletMove(void);
void OnCollision(void);
void StateRun(void);
void CalcDifficulty(void);
int SelectWaitClass(void);

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
#define N_TARGET 15
#define N_MARKER 2048

//////// �N����
#define N_ENEMIES 24
#define N_ENEMY_BULLETS 5

//////// �v���C���[�̒e
#define FORT_BULLETS 5

// �V�[���h
#define SHIELDS 12
//////// WaitProcess�N���X�̍݌�
#define STOCK_WAITPROCESS 10

//-------- simulation data
typedef struct {

	ezCamera *camL; //�E�ڃJ����
	ezCamera *camR; //���ڃJ����

	ezCamera *extvideo; //�O���r�f�I�f�o�C�X

	int time;

	float clip_near;
	float clip_far;
	float air_color[4];
	float sky_color[4];

	// ������
	int currentHitBullet;
	int currentAllBullet;
	// �G�̎c��
	int remainingEnemies;

    //////// ���[�U��`�̃V�[���ɂ��Ẵf�[�^�������ɂ܂Ƃ߂�

	ObjDataT cube; ///////���L���[�u
	ObjDataT sphere; /////������

	ObjDataT player; /////���v���C���i�̑������j������킷�I�u�W�F�N�g

	ObjDataT enemies[N_ENEMIES];
	ObjDataT enemyBullets[N_ENEMY_BULLETS];
	ObjDataT fort; //�C��(�v���C���[)
	ObjDataT fortTop; //�C���[
	ObjDataT fortBullets[FORT_BULLETS];
	ObjDataT shields[SHIELDS]; // �V�[���h

	ObjDataT head;//��
	ObjDataT body;
	ObjDataT handL;//��
	ObjDataT handR;//��
	ObjDataT footL;
	ObjDataT footR;

	ObjDataT *active_camera; //�J�����̃|�C���^�ϐ�

	ObjDataT target[N_TARGET]; //////// MREAL

	int n_cam;
	TargetT mrealCamera[8];

	TargetT TargetList[N_TARGET];
	MarkerT MarkerList[N_MARKER];

	DownDataT downdata;
	UpDataT updata;

	unsigned char *colorimage;
	unsigned short *depthimage;

	////////

	ObjDataT movie_screen;
	ezMovie *movie;

	ezMIDI *midi;
	int scale;
	int octabe;

	////////
} SimDataT;

#endif //__SIM_H__
