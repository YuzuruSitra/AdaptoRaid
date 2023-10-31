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

// draw.cpp
void PreDraw( void );
void PostDraw( void );
void DrawScene( void );
void MovingEnemies( void );
//void Lighting( void );
//void HeadLight( void );
/*
★ObjDataTの定義は、object.hに移行しました
*/

//////// MREAL
#define N_TARGET 15
#define N_MARKER 2048

//////// 侵略者
#define N_ENEMIES 24

//-------- simulation data
typedef struct {

	ezCamera *camL; //右目カメラ
	ezCamera *camR; //左目カメラ

	ezCamera *extvideo; //外部ビデオデバイス

	int time;

	float clip_near;
	float clip_far;
	float air_color[4];
	float sky_color[4];
    //////// ユーザ定義のシーンについてのデータをここにまとめる

	ObjDataT cube; ///////◆キューブ
	ObjDataT sphere; /////◆球体

	ObjDataT player; /////◆プレイヤ（の足元★）をあらわすオブジェクト

	ObjDataT enemies[N_ENEMIES];


	ObjDataT head;//★
	ObjDataT body;
	ObjDataT handL;//★
	ObjDataT handR;//★
	ObjDataT footL;
	ObjDataT footR;

	ObjDataT *active_camera; //カメラのポインタ変数

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
