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
void InitialSetting(void);
void InitScene(void);
void UpdateScene(void);
void TermScene(void);
void MovingFort(void);
void FortBulletMove(void);
void FortShooting(void);
void MovingEnemies(void);
void EnemyShooting(void);
void EnemyBulletMove(void);
void OnCollision(void);
void StateRun(void);
void CalcPlayerSkill(void);
void CalcDifficulty(double playerSkill);
void RestartGame(void);

// draw.cpp
void PreDraw(void);
void PostDraw(void);
void DrawScene(void);


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
#define N_ENEMY_BULLETS 5
#define N_ENEMY_POINT 100

//////// プレイヤーの弾
#define FORT_BULLETS 5

// シールド
#define SHIELDS 12

// プレイヤースキル計算の待機時間
#define CALC_SKILL_WAIT_TIME 5

//-------- simulation data
typedef struct {

	ezCamera *camL; //右目カメラ
	ezCamera *camR; //左目カメラ

	ezCamera *extvideo; //外部ビデオデバイス

	int time;
	int score;
	int gameRound;

	float enemyMoveSpeed;
	float enemyShootInterval;

	double CurrentHitRate;
	double CurrentPushRate;
	double CurrentKillRate;
	double PlayerSkill;

	float clip_near;
	float clip_far;
	float air_color[4];
	float sky_color[4];

	// 命中率
	int currentHitBullet;
	int currentAllBullet;
	// 倒した敵数
	int destroyEnemies;
	// ボタンの押した回数
	int buttonPresses;


	//////// ユーザ定義のシーンについてのデータをここにまとめる

	ObjDataT cube; ///////◆キューブ
	ObjDataT sphere; /////◆球体

	ObjDataT player; /////◆プレイヤ（の足元★）をあらわすオブジェクト

	ObjDataT enemies[N_ENEMIES];
	ObjDataT enemyBullets[N_ENEMY_BULLETS];
	ObjDataT fort; //砲台(プレイヤー)
	ObjDataT fortTop; //砲台先端
	ObjDataT fortBullets[FORT_BULLETS];
	ObjDataT shields[SHIELDS]; // シールド

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