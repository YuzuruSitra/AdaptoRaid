#include "platform.h"

#include "common.h" //WindowDataT, MouseDataT, KeyDataT
#include "calc.h"
#include "sim.h"
#include "config.h"

#include "ezTrack.h"

#include "gyro.h"

#include "mymodel.h" //★
#include <stdio.h>
#include "Com.h"

#include "depth.h"
#include "tcpFunc.h"

#include "FrameRateCounter.h"
#include "WaitProcess.h"
#include "Qlearning.h"

// 追加クラスをインスタンス化
FrameRateCounter frameRateCounter;
WaitProcess waitProcess;
QLearning qLearning;

//#include "SerialIO.h"
//HANDLE comm;
int comm;

SimDataT simdata; //SimDataT型構造体のデータを宣言
extern MouseDataT mouse;
extern KeyDataT keydata; //★修正★

#define MY_TCP_FLAG 0
///////////////////////////////////////////////////////
//トラッカーデバイスを有効にするフラグ


ezTracker *tracker = nullptr; //共有メモリ経由でトラッカーの情報を得るオブジェクト
//トラッカーから受け取ったデータへのポインタ
ezTrackDataT *trackBase = nullptr; //基準マーカ
ezTrackDataT *trackHead = nullptr;
ezTrackDataT *trackBody = nullptr;
ezTrackDataT *trackHandR = nullptr;
ezTrackDataT *trackHandL = nullptr;
ezTrackDataT *trackFootR = nullptr;
ezTrackDataT *trackFootL = nullptr;
//マーカが見えない場合などのダミーデータ{id,x,y,z,roll,pitch,yaw}
ezTrackDataT localBase = { 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
//ezTrackDataT localHead = { 0, 0.0, 1.5, 0.0, 0.0, 0.0, 0.0 };
ezTrackDataT localHead = { 0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0 };
ezTrackDataT localBody = { 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
ezTrackDataT localHandR = { 0, 0.25, 1.25, -0.5, 0.0, 0.0, 0.0 };
ezTrackDataT localHandL = { 0,-0.25, 1.25, -0.5, 0.0, 0.0, 0.0 };
ezTrackDataT localFootR = { 0, 0.25, 0.0, -0.5, 0.0, 0.0, 0.0 };
ezTrackDataT localFootL = { 0,-0.25, 0.0, -0.5, 0.0, 0.0, 0.0 };

/*--------------------
 * copyTrackToObj
 */
static void copyTrackToObj(ezTrackDataT *src, ObjDataT *dst)
{
	float pos[3], rot[3];
	if (src == NULL) return;
	ezTrack_getPos(src, pos);
	setObjPos(dst, pos);
	ezTrack_getRot(src, rot);
	setObjRot(dst, rot);
}


/*---------------------------------------------------------------- InitScene
 * InitScene:
 *--------*/

const int enemyMaxRow = 6;

void InitScene(void)
{
	////// シーンデータの初期化
	simdata.clip_far = 200.0; //◆ファークリッププレーン
	simdata.clip_near = 0.1;
	simdata.air_color[0] = 1.0;
	simdata.air_color[1] = 1.0;
	simdata.air_color[2] = 1.0;
	simdata.air_color[3] = 0.5; // fog density factor
	simdata.sky_color[0] = 0.2;
	simdata.sky_color[1] = 0.3;
	simdata.sky_color[2] = 0.4;
	simdata.sky_color[3] = 0.5; // sky color factor
	//////

	///▼追加したオブジェクトの初期化
	setObjPos(&simdata.cube, 0.0, 1.0, -1.0);
	setObjRot(&simdata.cube, 0.0, 0.0, 0.0);
	setObjColor(&simdata.cube, 0.5, 0.3, 0.2);
	simdata.cube.visible = true;
	simdata.cube.state = 0; //////////////◆
	simdata.cube.radius = 0.2;

	simdata.cube.xsize = 0.6;
	simdata.cube.ysize = 0.05;
	simdata.cube.zsize = 0.25;

	setObjPos(&simdata.sphere, 0.0, 1.2, -1.0);
	setObjRot(&simdata.sphere, 0.0, 0.0, 0.0);
	setObjColor(&simdata.sphere, 1.0, 0.5, 0.0);
	simdata.sphere.visible = true;
	simdata.sphere.state = 0;
	simdata.sphere.radius = 0.125; //★◆04

	simdata.handR.radius = 0.125; //◆04
	simdata.handL.radius = 0.125; //◆04
	simdata.handR.state = 0;
	simdata.handL.state = 0;

	setObjPos(&simdata.player, 0.0, 0.0, 0.0);
	setObjRot(&simdata.player, 0.0, 0.0, 0.0);
	setObjColor(&simdata.player, 0.0, 0.5, 1.0);
	simdata.player.visible = true;
	simdata.player.state = 0;
	simdata.player.turn = 0.0;
	simdata.player.move = 0.0;
	simdata.player.radius = 0.5;

	InitialSetting();

	simdata.PlayerSkill = 50;
	simdata.score = 0;
	simdata.gameRound = 0;
	simdata.CurrentHitRate = 0;
	simdata.CurrentPushRate = 0;
	simdata.CurrentKillRate = 0;
	simdata.enemyMoveSpeed = 1.0f;
	simdata.enemyShootInterval = 1.0f;

	//右手（ローカル座標）をプレイヤの子座標系とする
	setObjLocal(&simdata.handR, &simdata.player); //★

	//★左手も同様
	setObjLocal(&simdata.handL, &simdata.player); //★

	//頭をプレイヤーの子座標系にする
	setObjLocal(&simdata.head, &simdata.player);

	simdata.active_camera = &simdata.player;
	//simdata.active_camera = NULL;
	//プレイヤオブジェクトのアドレスをカメラのポインタに紐付ける

	setObjColor(&simdata.handR, 0.0, 1.0, 0.0); //右手グリーン
	setObjColor(&simdata.handL, 1.0, 0.0, 0.0); //左手レッド

	// 設定周り
	tracker = new ezTracker(use_tracker); //VICON使うときはtrue
	if (use_vicon) {
		tracker->open("VICON", false); //識別名, Wフラグ(false:R/O)
	}
	else {
		tracker->open("ARTOOLKIT", false); //識別名, Wフラグ(false:R/O)
	}
	trackHead = &localHead;
	trackBody = &localBody;
	trackHandR = &localHandR;
	trackHandL = &localHandL;
	trackBase = &localBase;
	trackFootL = &localFootL;
	trackFootR = &localFootR;

	//★修正★UpdataSceneからコピー
	copyTrackToObj(trackHead, &simdata.head);
	copyTrackToObj(trackBody, &simdata.body);
	copyTrackToObj(trackHandL, &simdata.handL);
	copyTrackToObj(trackHandR, &simdata.handR);
	copyTrackToObj(trackFootL, &simdata.footL);
	copyTrackToObj(trackFootR, &simdata.footR);
	if (use_gyro) InitGyro();

	if (usb_video) {
		simdata.extvideo = new ezCamera();
		simdata.extvideo->open(0, 640, 480, 30.0, GL_BGRA_EXT, "ELECOM 5MP Webcam");
	}
	CreateMyModels(); //★

	simdata.movie = new ezMovie("../images/test_images/result", 145, 6);
	setObjPos(&simdata.movie_screen, 0.0, 1.0, -1.0);
	setObjRot(&simdata.movie_screen, 0.0, 0.0, 0.0);
	setObjColor(&simdata.movie_screen, 0.8, 0.8, 0.8);
	setObjSize(&simdata.movie_screen, 0.4, 0.3, 0.1);
	simdata.cube.visible = true;
	simdata.cube.state = 0; //////////////◆
	simdata.cube.radius = 0.2;


	simdata.scale = 0;
	simdata.octabe = 5;

	ezMIDI::Open(true); //polyphonic
	simdata.midi = new ezMIDI(9);
	//simdata.midi = new ezMIDI(10, 27 );

	return;
}

void InitialSetting()
{
	const float SET_POS_Z = -10.0;

	moveLocalToWorld(&simdata.fortTop);
	// 砲台
	setObjPos(&simdata.fort, 0.0, 0.0, SET_POS_Z);
	setObjRot(&simdata.fort, 0.0, 0.0, 0.0);
	setObjColor(&simdata.fort, 0.0, 0.8, 0.8);
	simdata.fort.visible = true;
	simdata.fort.state = 0;
	simdata.fort.radius = 1.0;
	simdata.fort.xsize = 2.0;
	simdata.fort.ysize = 0.3;
	simdata.fort.zsize = 1.0;

	setObjPos(&simdata.fortTop, 0.0, 0.25, SET_POS_Z);
	setObjRot(&simdata.fortTop, 0.0, 0.0, 0.0);
	setObjColor(&simdata.fortTop, 0.0, 0.8, 0.8);
	simdata.fortTop.visible = true;
	simdata.fortTop.state = 0;
	simdata.fortTop.radius = 1.0;
	simdata.fortTop.xsize = 0.6;
	simdata.fortTop.ysize = 0.5;
	simdata.fortTop.zsize = 1.0;
	moveWorldToLocal(&simdata.fortTop, &simdata.fort);

	// 砲台の弾
	for (int i = 0; i < FORT_BULLETS; i++)
	{
		setObjPos(&simdata.fortBullets[i], 0.0, -1.0, SET_POS_Z);
		setObjRot(&simdata.fortBullets[i], 0.0, 0.0, 0.0);
		setObjColor(&simdata.fortBullets[i], 0.0, 0.8, 0.8);
		simdata.fortBullets[i].visible = false;
		simdata.fortBullets[i].state = 0;
		simdata.fortBullets[i].radius = 0.2;

		simdata.fortBullets[i].xsize = 0.25;
		simdata.fortBullets[i].ysize = 0.5;
		simdata.fortBullets[i].zsize = 0.25;
	}

	// 敵
	const float CREVICE_X = 1.5;
	const float CREVICE_Y = 1.25;
	const float THRESHOLD_Y_POINT = 6;
	const float THRESHOLD_X_POINT = enemyMaxRow / 2 * CREVICE_X - CREVICE_X / 2;
	const float delayValue = 0.2f;
	for (int i = 0; i < N_ENEMIES; i++)
	{
		int countY = i / enemyMaxRow;
		float setPosX = (i * CREVICE_X) - (countY * enemyMaxRow * CREVICE_X) - THRESHOLD_X_POINT;
		float setPosY = countY * CREVICE_Y + THRESHOLD_Y_POINT;

		setObjPos(&simdata.enemies[i], setPosX, setPosY, SET_POS_Z);
		setObjRot(&simdata.enemies[i], 0.0, 0.0, 0.0);
		simdata.enemies[i].xsize = 0.75;
		simdata.enemies[i].ysize = 0.75;
		simdata.enemies[i].zsize = 0.75;

		simdata.enemies[i].move = 1.0;
		simdata.enemies[i].turn = 0.0;

		setObjColor(&simdata.enemies[i], 0.0, 1.0, 0.0);
		// 当たり判定
		simdata.enemies[i].radius = 0.5;
		simdata.enemies[i].state = 0;
		simdata.enemies[i].visible = true;

		// 移動用変数の初期化
		simdata.enemies[i].enemyMoveTime = countY * delayValue;
		simdata.enemies[i].enemyGoRight = true;
		simdata.enemies[i].enemyLastReachPoint = 0;// 左:0 右:1
		simdata.enemies[i].enemyLine = countY;
		simdata.enemies[i].enemyRow = i % enemyMaxRow;
	}

	// 敵の弾
	for (int i = 0; i < N_ENEMY_BULLETS; i++)
	{
		setObjPos(&simdata.enemyBullets[i], 0.0, -1.0, SET_POS_Z);
		setObjRot(&simdata.enemyBullets[i], 0.0, 0.0, 0.0);
		setObjColor(&simdata.enemyBullets[i], 0.0, 1.0, 0.0);
		simdata.enemyBullets[i].visible = false;
		simdata.enemyBullets[i].state = 0;
		simdata.enemyBullets[i].radius = 0.2;

		simdata.enemyBullets[i].xsize = 0.25;
		simdata.enemyBullets[i].ysize = 0.5;
		simdata.enemyBullets[i].zsize = 0.25;
	}

	// シールド
	const float PADDING = 0.75f;
	const float SPACE = 2.0f;
	const int SEPALATE_COUNT = 3;
	const int FACTOR = SHIELDS / SEPALATE_COUNT;
	const float ADJAST_X = (PADDING * SHIELDS + SPACE * FACTOR) / 2 + PADDING / 2;
	float setPosX = -ADJAST_X;
	for (int i = 0; i < SHIELDS; i++)
	{
		int tmp = i % FACTOR;
		setPosX += PADDING;
		if (tmp == 0) setPosX += SPACE;

		setObjPos(&simdata.shields[i], setPosX, 2.0f, SET_POS_Z);
		setObjRot(&simdata.shields[i], 0.0, 0.0, 0.0);
		simdata.shields[i].xsize = 0.5;
		simdata.shields[i].ysize = 0.5;
		simdata.shields[i].zsize = 0.5;

		setObjColor(&simdata.shields[i], 0.9, 0.3, 0.0);
		// 当たり判定
		simdata.shields[i].radius = 0.5;
		simdata.shields[i].state = 0;
		simdata.shields[i].visible = true;
	}

	simdata.currentHitBullet = 0;
	simdata.currentAllBullet = 0;
	simdata.destroyEnemies = 0;
	simdata.buttonPresses = 0;
}

/*-------------------------------------------------------------- UpdateScene
 * UpdateScene:
 *--------*/

float deltaTime;
// ゲームの横幅
const float LANGE_POS_X = 8;
// 砲台の待機クラス選択初期化
int useWaitFortShoot = waitProcess.WAIT_ERROR_VALUE;
// 敵射撃からの経過時間
float enemyShootInterval = 2.0f;
// 敵弾の待機クラス選択初期化
int useWaitEnemyShoot = waitProcess.WAIT_ERROR_VALUE;
// 難易度調整の待機クラス初期化
int useWaitCalcDifficulty = waitProcess.WAIT_ERROR_VALUE;
int useFortWaitClass = waitProcess.WAIT_ERROR_VALUE;
int useResetWaitClass = waitProcess.WAIT_ERROR_VALUE;
int currentPressButton = -1;

void UpdateScene(void)
{

	simdata.time = glutGet(GLUT_ELAPSED_TIME);

	// フレームレートカウンターを更新
	frameRateCounter.Update();
	deltaTime = frameRateCounter.GetElapsedTime();

	// フリーズ時の暴走ケア
	if (deltaTime >= 0.001f) return;

	MovingFort();
	FortShooting();
	FortBulletMove();
	MovingEnemies();
	EnemyShooting();
	EnemyBulletMove();
	CalcPlayerSkill();
	OnCollision();
	StateRun();
	RestartGame();

	return;
}


// 砲台(プレイヤー)の移動
void MovingFort(void)
{
	float speed = 4.0f;
	int pushButoon = -1;
	if (keydata.arrowLeft && simdata.fort.pos.x > -LANGE_POS_X)
	{
		simdata.fort.pos.x -= speed * deltaTime;
		pushButoon = 0;
	}
	if (keydata.arrowRight && simdata.fort.pos.x < LANGE_POS_X)
	{
		simdata.fort.pos.x += speed * deltaTime;
		pushButoon = 1;
	}
	if (pushButoon != currentPressButton) simdata.buttonPresses++;
	currentPressButton = pushButoon;

	return;
}

// 砲台から攻撃
void FortShooting(void)
{
	const float shootInterval = 0.1f;

	// 待機処理
	if (useWaitFortShoot == waitProcess.WAIT_ERROR_VALUE) useWaitFortShoot = waitProcess.SelectID();
	bool waiting = !waitProcess.WaitForTime(useWaitFortShoot, shootInterval, deltaTime);
	if (waiting) return;
	// プレイヤーの入力
	if (!keydata.spaceKey) return;
	simdata.buttonPresses++;
	// 非稼働の弾を検索
	int target = FORT_BULLETS;
	for (int i = 0; i < FORT_BULLETS; i++)
	{
		if (simdata.fortBullets[i].visible) continue;
		target = i;
		break;
	}
	// 検索に失敗した場合は処理を終了する
	if (target == FORT_BULLETS) return;
	simdata.fortBullets[target].visible = true;
	float setPosY = simdata.fort.pos.y + 1.0f;
	setObjPos(&simdata.fortBullets[target], simdata.fort.pos.x, setPosY, simdata.fort.pos.z);
	simdata.currentAllBullet += 1;
	keydata.spaceKey = false;

	// 待機クラス選択の初期化
	useWaitFortShoot == waitProcess.WAIT_ERROR_VALUE;
	return;
}

// 砲弾の制御
void FortBulletMove(void)
{
	const float SPEED = 10.0f;
	for (int i = 0; i < FORT_BULLETS; i++)
	{
		if (!simdata.fortBullets[i].visible) continue;
		simdata.fortBullets[i].pos.y += SPEED * deltaTime;
		if (simdata.fortBullets[i].pos.y >= 10) simdata.fortBullets[i].visible = false;
	}
}

// 敵の移動
void MovingEnemies(void)
{
	for (int i = 0; i < N_ENEMIES; i++)
	{
		// 初動delay
		if (simdata.enemies[i].enemyMoveTime >= 0)
		{
			simdata.enemies[i].enemyMoveTime -= deltaTime;
			continue;
		}

		const float DOWN_PADDING = 0.5f;

		// 左右移動の切り替え制御
		if ((simdata.enemies[i].pos.x > LANGE_POS_X && simdata.enemies[i].enemyLastReachPoint == 0) || (simdata.enemies[i].pos.x < -LANGE_POS_X && simdata.enemies[i].enemyLastReachPoint == 1))
		{
			setObjPos(&simdata.enemies[i], (simdata.enemies[i].enemyLastReachPoint == 0) ? LANGE_POS_X : -LANGE_POS_X, simdata.enemies[i].pos.y, simdata.enemies[i].pos.z);
			int line = simdata.enemies[i].enemyLine;
			// 同じ行の敵に影響を与える
			for (int i = 0; i < N_ENEMIES; i++)
			{
				if (simdata.enemies[i].enemyLine != line) continue;
				simdata.enemies[i].enemyGoRight = !simdata.enemies[i].enemyGoRight;
				simdata.enemies[i].enemyLastReachPoint = (simdata.enemies[i].enemyLastReachPoint == 0) ? 1 : 0;
				simdata.enemies[i].pos.y -= DOWN_PADDING;
			}
		}

		if (!simdata.enemies[i].enemyGoRight) simdata.enemies[i].move = simdata.enemyMoveSpeed * -1;
		else simdata.enemies[i].move = simdata.enemyMoveSpeed;
		float setPosX = simdata.enemies[i].pos.x + simdata.enemies[i].move * deltaTime;
		setObjPos(&simdata.enemies[i], setPosX, simdata.enemies[i].pos.y, simdata.enemies[i].pos.z);
	}
	return;
}

// 敵の攻撃
void EnemyShooting(void)
{
	// 待機処理
	if (useWaitEnemyShoot == waitProcess.WAIT_ERROR_VALUE) useWaitEnemyShoot = waitProcess.SelectID();
	bool waiting = !waitProcess.WaitForTime(useWaitEnemyShoot, simdata.enemyShootInterval, deltaTime);
	if (waiting) return;

	// 底面にいる中から射撃する敵を選定
	int atackEnemy = diceRandom(0, enemyMaxRow - 1);

	for (int i = 0; i < N_ENEMIES; i++)
	{
		if (simdata.enemies[i].enemyRow != atackEnemy || !simdata.enemies[i].visible) continue;
		// 非稼働の弾を検索
		int target = N_ENEMY_BULLETS;
		for (int i = 0; i < N_ENEMY_BULLETS; i++)
		{
			if (simdata.enemyBullets[i].visible) continue;
			target = i;
			break;
		}
		// 検索に失敗した場合は処理を終了する
		if (target == N_ENEMY_BULLETS) return;
		simdata.enemyBullets[target].visible = true;
		float setPosY = simdata.enemies[i].pos.y - 1.0f;
		setObjPos(&simdata.enemyBullets[target], simdata.enemies[i].pos.x, setPosY, simdata.enemies[i].pos.z);
		// 待機クラス選択の初期化
		useWaitEnemyShoot = waitProcess.WAIT_ERROR_VALUE;
		break;
	}
	return;
}

// 敵弾の制御
void EnemyBulletMove(void)
{
	const float SPEED = 8.0f;
	for (int i = 0; i < N_ENEMY_BULLETS; i++)
	{
		if (!simdata.enemyBullets[i].visible) continue;
		simdata.enemyBullets[i].pos.y -= SPEED * deltaTime;
		if (simdata.enemyBullets[i].pos.y <= -1) simdata.enemyBullets[i].visible = false;
	}
}

// 当たり判定
void OnCollision(void)
{
	// 砲弾のヒット判定
	bool fortBulletHit = false;
	for (int i = 0; i < FORT_BULLETS; i++)
	{
		if (!simdata.fortBullets[i].visible) continue;

		// 敵のヒット判定
		for (int j = 0; j < N_ENEMIES; j++)
		{
			if (!simdata.enemies[j].visible) continue;
			fortBulletHit = isHit(&simdata.fortBullets[i], &simdata.enemies[j]);
			if (!fortBulletHit) continue;
			simdata.fortBullets[i].visible = false;
			simdata.enemies[j].visible = false;
			simdata.currentHitBullet += 1;
			simdata.score += N_ENEMY_POINT;
			simdata.destroyEnemies++;
		}

		// シールドのヒット判定
		bool shieldsHit = false;
		for (int j = 0; j < SHIELDS; j++)
		{
			if (!simdata.shields[j].visible) continue;
			shieldsHit = isHit(&simdata.shields[j], &simdata.fortBullets[i]);
			if (!shieldsHit) continue;
			simdata.shields[j].visible = false;
			simdata.fortBullets[i].visible = false;
		}
	}

	// 敵弾のヒット判定
	for (int i = 0; i < N_ENEMY_BULLETS; i++)
	{
		if (!simdata.enemyBullets[i].visible) continue;

		// シールドのヒット判定
		bool shieldsHit = false;
		for (int j = 0; j < SHIELDS; j++)
		{
			if (!simdata.shields[j].visible) continue;
			shieldsHit = isHit(&simdata.shields[j], &simdata.enemyBullets[i]);
			if (!shieldsHit) continue;
			simdata.shields[j].visible = false;
			simdata.enemyBullets[i].visible = false;
		}

		// 砲台のヒット判定
		bool enemyBulletHit = isHit(&simdata.fort, &simdata.enemyBullets[i]) || isHit(&simdata.fortTop, &simdata.enemyBullets[i]);
		if (simdata.fort.state == 0 && enemyBulletHit)
		{
			simdata.enemyBullets[i].visible = false;
			simdata.fort.state = 1;
		}
	}
}

// 状態毎の処理
void StateRun(void)
{
	// 砲台のヒット判定
	switch (simdata.fort.state)
	{
		// 標準状態
	case 0:
		setObjColor(&simdata.fort, 0.0, 0.8, 0.8);
		setObjColor(&simdata.fortTop, 0.0, 0.8, 0.8);
		break;
	case 1:
		if (useFortWaitClass == waitProcess.WAIT_ERROR_VALUE) useFortWaitClass = waitProcess.SelectID();
		setObjColor(&simdata.fort, 0.8, 0.2, 0.2);
		setObjColor(&simdata.fortTop, 0.8, 0.2, 0.2);
		if (waitProcess.WaitForTime(useFortWaitClass, 0.75f, deltaTime))
		{
			simdata.fort.state = 0;
			useFortWaitClass = waitProcess.WAIT_ERROR_VALUE;
		}
		break;
	}
	return;
}

// 難易度の遷移
void CalcPlayerSkill(void)
{
	// 待機処理
	if (useWaitCalcDifficulty == waitProcess.WAIT_ERROR_VALUE) useWaitCalcDifficulty = waitProcess.SelectID();
	bool waiting = !waitProcess.WaitForTime(useWaitCalcDifficulty, CALC_SKILL_WAIT_TIME, deltaTime);
	if (waiting) return;

	// 難易度調整処理
	double hitRate;
	if (simdata.currentAllBullet == 0 || simdata.currentHitBullet == 0) hitRate = 0;
	else hitRate = (double)simdata.currentHitBullet / (double)simdata.currentAllBullet;
	// プレイヤーの上手さを計算し、Q値を更新
	qLearning.updateScores(hitRate, simdata.buttonPresses, simdata.destroyEnemies);
	simdata.PlayerSkill = qLearning.calculateSkill();
	CalcDifficulty(simdata.PlayerSkill);
	// 各値の取得
	simdata.CurrentHitRate = qLearning.CalcHitRate;
	simdata.CurrentPushRate = qLearning.CalcPushRate;
	simdata.CurrentKillRate = qLearning.CalcKillRate;
	// 計算値のリセット
	simdata.currentHitBullet = 0;
	simdata.currentAllBullet = 0;
	simdata.destroyEnemies = 0;
	simdata.buttonPresses = 0;

	// 待機クラス選択の初期化
	useWaitCalcDifficulty = waitProcess.WAIT_ERROR_VALUE;
	return;
}

// 難易度の変更処理
void CalcDifficulty(double playerSkill)
{
	double normalizedSkill = playerSkill / 100.0;
	// 敵の移動速度を指定範囲で算出
	const double ENEMY_MOVE_SPEED_MIN = 0.1;
	const double ENEMY_MOVE_SPEED_MAX = 2.0;
	simdata.enemyMoveSpeed = ENEMY_MOVE_SPEED_MIN + normalizedSkill * (ENEMY_MOVE_SPEED_MAX - ENEMY_MOVE_SPEED_MIN);
	// 敵の発砲インターバルを指定範囲で算出
	const double ENEMY_SHOOT_INTERVAL_MIN = 0.1;
	const double ENEMY_SHOOT_INTERVAL_MAX = 1.5;
	simdata.enemyShootInterval = ENEMY_SHOOT_INTERVAL_MAX - normalizedSkill * (ENEMY_SHOOT_INTERVAL_MAX - ENEMY_SHOOT_INTERVAL_MIN);
}

// リスタート
void RestartGame()
{
	for (int i = 0; i < N_ENEMIES; i++) if (simdata.enemies[i].visible) return;
	if (useResetWaitClass == waitProcess.WAIT_ERROR_VALUE) useResetWaitClass = waitProcess.SelectID();
	bool waiting = !waitProcess.WaitForTime(useResetWaitClass, 3.0f, deltaTime);
	if (waiting) return;
	useResetWaitClass = waitProcess.WAIT_ERROR_VALUE;
	simdata.gameRound += 1;
	InitialSetting();
}

////////
void TermScene(void)
{
	//// 終了処理
	printf("GOING TO EXIT..\n");
	if (use_gyro) TermGyro();
	//Sleep( 5000 );
	printf("BYE\n");

	return;
}