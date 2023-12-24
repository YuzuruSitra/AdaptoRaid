#include "platform.h"

#include "common.h" //WindowDataT, MouseDataT, KeyDataT
#include "calc.h"
#include "sim.h"
#include "config.h"

#include "ezTrack.h"

#include "gyro.h"

#include "mymodel.h" //��
#include <stdio.h>
#include "Com.h"

#include "depth.h"
#include "tcpFunc.h"

#include "FrameRateCounter.h"
#include "WaitProcess.h"
#include "Qlearning.h"

// �ǉ��N���X���C���X�^���X��
FrameRateCounter frameRateCounter;
WaitProcess waitProcess;
QLearning qLearning;

//#include "SerialIO.h"
//HANDLE comm;
int comm;

SimDataT simdata; //SimDataT�^�\���̂̃f�[�^��錾
extern MouseDataT mouse;
extern KeyDataT keydata; //���C����

#define MY_TCP_FLAG 0
///////////////////////////////////////////////////////
//�g���b�J�[�f�o�C�X��L���ɂ���t���O


ezTracker *tracker = nullptr; //���L�������o�R�Ńg���b�J�[�̏��𓾂�I�u�W�F�N�g
//�g���b�J�[����󂯎�����f�[�^�ւ̃|�C���^
ezTrackDataT *trackBase = nullptr; //��}�[�J
ezTrackDataT *trackHead = nullptr;
ezTrackDataT *trackBody = nullptr;
ezTrackDataT *trackHandR = nullptr;
ezTrackDataT *trackHandL = nullptr;
ezTrackDataT *trackFootR = nullptr;
ezTrackDataT *trackFootL = nullptr;
//�}�[�J�������Ȃ��ꍇ�Ȃǂ̃_�~�[�f�[�^{id,x,y,z,roll,pitch,yaw}
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
	////// �V�[���f�[�^�̏�����
	simdata.clip_far = 200.0; //���t�@�[�N���b�v�v���[��
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

	///���ǉ������I�u�W�F�N�g�̏�����
	setObjPos(&simdata.cube, 0.0, 1.0, -1.0);
	setObjRot(&simdata.cube, 0.0, 0.0, 0.0);
	setObjColor(&simdata.cube, 0.5, 0.3, 0.2);
	simdata.cube.visible = true;
	simdata.cube.state = 0; //////////////��
	simdata.cube.radius = 0.2;

	simdata.cube.xsize = 0.6;
	simdata.cube.ysize = 0.05;
	simdata.cube.zsize = 0.25;

	setObjPos(&simdata.sphere, 0.0, 1.2, -1.0);
	setObjRot(&simdata.sphere, 0.0, 0.0, 0.0);
	setObjColor(&simdata.sphere, 1.0, 0.5, 0.0);
	simdata.sphere.visible = true;
	simdata.sphere.state = 0;
	simdata.sphere.radius = 0.125; //����04

	simdata.handR.radius = 0.125; //��04
	simdata.handL.radius = 0.125; //��04
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

	//�E��i���[�J�����W�j���v���C���̎q���W�n�Ƃ���
	setObjLocal(&simdata.handR, &simdata.player); //��

	//����������l
	setObjLocal(&simdata.handL, &simdata.player); //��

	//�����v���C���[�̎q���W�n�ɂ���
	setObjLocal(&simdata.head, &simdata.player);

	simdata.active_camera = &simdata.player;
	//simdata.active_camera = NULL;
	//�v���C���I�u�W�F�N�g�̃A�h���X���J�����̃|�C���^�ɕR�t����

	setObjColor(&simdata.handR, 0.0, 1.0, 0.0); //�E��O���[��
	setObjColor(&simdata.handL, 1.0, 0.0, 0.0); //���背�b�h

	// �ݒ����
	tracker = new ezTracker(use_tracker); //VICON�g���Ƃ���true
	if (use_vicon) {
		tracker->open("VICON", false); //���ʖ�, W�t���O(false:R/O)
	}
	else {
		tracker->open("ARTOOLKIT", false); //���ʖ�, W�t���O(false:R/O)
	}
	trackHead = &localHead;
	trackBody = &localBody;
	trackHandR = &localHandR;
	trackHandL = &localHandL;
	trackBase = &localBase;
	trackFootL = &localFootL;
	trackFootR = &localFootR;

	//���C����UpdataScene����R�s�[
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
	CreateMyModels(); //��

	simdata.movie = new ezMovie("../images/test_images/result", 145, 6);
	setObjPos(&simdata.movie_screen, 0.0, 1.0, -1.0);
	setObjRot(&simdata.movie_screen, 0.0, 0.0, 0.0);
	setObjColor(&simdata.movie_screen, 0.8, 0.8, 0.8);
	setObjSize(&simdata.movie_screen, 0.4, 0.3, 0.1);
	simdata.cube.visible = true;
	simdata.cube.state = 0; //////////////��
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
	// �C��
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

	// �C��̒e
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

	// �G
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
		// �����蔻��
		simdata.enemies[i].radius = 0.5;
		simdata.enemies[i].state = 0;
		simdata.enemies[i].visible = true;

		// �ړ��p�ϐ��̏�����
		simdata.enemies[i].enemyMoveTime = countY * delayValue;
		simdata.enemies[i].enemyGoRight = true;
		simdata.enemies[i].enemyLastReachPoint = 0;// ��:0 �E:1
		simdata.enemies[i].enemyLine = countY;
		simdata.enemies[i].enemyRow = i % enemyMaxRow;
	}

	// �G�̒e
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

	// �V�[���h
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
		// �����蔻��
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
// �Q�[���̉���
const float LANGE_POS_X = 8;
// �C��̑ҋ@�N���X�I��������
int useWaitFortShoot = waitProcess.WAIT_ERROR_VALUE;
// �G�ˌ�����̌o�ߎ���
float enemyShootInterval = 2.0f;
// �G�e�̑ҋ@�N���X�I��������
int useWaitEnemyShoot = waitProcess.WAIT_ERROR_VALUE;
// ��Փx�����̑ҋ@�N���X������
int useWaitCalcDifficulty = waitProcess.WAIT_ERROR_VALUE;
int useFortWaitClass = waitProcess.WAIT_ERROR_VALUE;
int useResetWaitClass = waitProcess.WAIT_ERROR_VALUE;
int currentPressButton = -1;

void UpdateScene(void)
{

	simdata.time = glutGet(GLUT_ELAPSED_TIME);

	// �t���[�����[�g�J�E���^�[���X�V
	frameRateCounter.Update();
	deltaTime = frameRateCounter.GetElapsedTime();

	// �t���[�Y���̖\���P�A
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


// �C��(�v���C���[)�̈ړ�
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

// �C�䂩��U��
void FortShooting(void)
{
	const float shootInterval = 0.1f;

	// �ҋ@����
	if (useWaitFortShoot == waitProcess.WAIT_ERROR_VALUE) useWaitFortShoot = waitProcess.SelectID();
	bool waiting = !waitProcess.WaitForTime(useWaitFortShoot, shootInterval, deltaTime);
	if (waiting) return;
	// �v���C���[�̓���
	if (!keydata.spaceKey) return;
	simdata.buttonPresses++;
	// ��ғ��̒e������
	int target = FORT_BULLETS;
	for (int i = 0; i < FORT_BULLETS; i++)
	{
		if (simdata.fortBullets[i].visible) continue;
		target = i;
		break;
	}
	// �����Ɏ��s�����ꍇ�͏������I������
	if (target == FORT_BULLETS) return;
	simdata.fortBullets[target].visible = true;
	float setPosY = simdata.fort.pos.y + 1.0f;
	setObjPos(&simdata.fortBullets[target], simdata.fort.pos.x, setPosY, simdata.fort.pos.z);
	simdata.currentAllBullet += 1;
	keydata.spaceKey = false;

	// �ҋ@�N���X�I���̏�����
	useWaitFortShoot == waitProcess.WAIT_ERROR_VALUE;
	return;
}

// �C�e�̐���
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

// �G�̈ړ�
void MovingEnemies(void)
{
	for (int i = 0; i < N_ENEMIES; i++)
	{
		// ����delay
		if (simdata.enemies[i].enemyMoveTime >= 0)
		{
			simdata.enemies[i].enemyMoveTime -= deltaTime;
			continue;
		}

		const float DOWN_PADDING = 0.5f;

		// ���E�ړ��̐؂�ւ�����
		if ((simdata.enemies[i].pos.x > LANGE_POS_X && simdata.enemies[i].enemyLastReachPoint == 0) || (simdata.enemies[i].pos.x < -LANGE_POS_X && simdata.enemies[i].enemyLastReachPoint == 1))
		{
			setObjPos(&simdata.enemies[i], (simdata.enemies[i].enemyLastReachPoint == 0) ? LANGE_POS_X : -LANGE_POS_X, simdata.enemies[i].pos.y, simdata.enemies[i].pos.z);
			int line = simdata.enemies[i].enemyLine;
			// �����s�̓G�ɉe����^����
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

// �G�̍U��
void EnemyShooting(void)
{
	// �ҋ@����
	if (useWaitEnemyShoot == waitProcess.WAIT_ERROR_VALUE) useWaitEnemyShoot = waitProcess.SelectID();
	bool waiting = !waitProcess.WaitForTime(useWaitEnemyShoot, simdata.enemyShootInterval, deltaTime);
	if (waiting) return;

	// ��ʂɂ��钆����ˌ�����G��I��
	int atackEnemy = diceRandom(0, enemyMaxRow - 1);

	for (int i = 0; i < N_ENEMIES; i++)
	{
		if (simdata.enemies[i].enemyRow != atackEnemy || !simdata.enemies[i].visible) continue;
		// ��ғ��̒e������
		int target = N_ENEMY_BULLETS;
		for (int i = 0; i < N_ENEMY_BULLETS; i++)
		{
			if (simdata.enemyBullets[i].visible) continue;
			target = i;
			break;
		}
		// �����Ɏ��s�����ꍇ�͏������I������
		if (target == N_ENEMY_BULLETS) return;
		simdata.enemyBullets[target].visible = true;
		float setPosY = simdata.enemies[i].pos.y - 1.0f;
		setObjPos(&simdata.enemyBullets[target], simdata.enemies[i].pos.x, setPosY, simdata.enemies[i].pos.z);
		// �ҋ@�N���X�I���̏�����
		useWaitEnemyShoot = waitProcess.WAIT_ERROR_VALUE;
		break;
	}
	return;
}

// �G�e�̐���
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

// �����蔻��
void OnCollision(void)
{
	// �C�e�̃q�b�g����
	bool fortBulletHit = false;
	for (int i = 0; i < FORT_BULLETS; i++)
	{
		if (!simdata.fortBullets[i].visible) continue;

		// �G�̃q�b�g����
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

		// �V�[���h�̃q�b�g����
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

	// �G�e�̃q�b�g����
	for (int i = 0; i < N_ENEMY_BULLETS; i++)
	{
		if (!simdata.enemyBullets[i].visible) continue;

		// �V�[���h�̃q�b�g����
		bool shieldsHit = false;
		for (int j = 0; j < SHIELDS; j++)
		{
			if (!simdata.shields[j].visible) continue;
			shieldsHit = isHit(&simdata.shields[j], &simdata.enemyBullets[i]);
			if (!shieldsHit) continue;
			simdata.shields[j].visible = false;
			simdata.enemyBullets[i].visible = false;
		}

		// �C��̃q�b�g����
		bool enemyBulletHit = isHit(&simdata.fort, &simdata.enemyBullets[i]) || isHit(&simdata.fortTop, &simdata.enemyBullets[i]);
		if (simdata.fort.state == 0 && enemyBulletHit)
		{
			simdata.enemyBullets[i].visible = false;
			simdata.fort.state = 1;
		}
	}
}

// ��Ԗ��̏���
void StateRun(void)
{
	// �C��̃q�b�g����
	switch (simdata.fort.state)
	{
		// �W�����
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

// ��Փx�̑J��
void CalcPlayerSkill(void)
{
	// �ҋ@����
	if (useWaitCalcDifficulty == waitProcess.WAIT_ERROR_VALUE) useWaitCalcDifficulty = waitProcess.SelectID();
	bool waiting = !waitProcess.WaitForTime(useWaitCalcDifficulty, CALC_SKILL_WAIT_TIME, deltaTime);
	if (waiting) return;

	// ��Փx��������
	double hitRate;
	if (simdata.currentAllBullet == 0 || simdata.currentHitBullet == 0) hitRate = 0;
	else hitRate = (double)simdata.currentHitBullet / (double)simdata.currentAllBullet;
	// �v���C���[�̏�肳���v�Z���AQ�l���X�V
	qLearning.updateScores(hitRate, simdata.buttonPresses, simdata.destroyEnemies);
	simdata.PlayerSkill = qLearning.calculateSkill();
	CalcDifficulty(simdata.PlayerSkill);
	// �e�l�̎擾
	simdata.CurrentHitRate = qLearning.CalcHitRate;
	simdata.CurrentPushRate = qLearning.CalcPushRate;
	simdata.CurrentKillRate = qLearning.CalcKillRate;
	// �v�Z�l�̃��Z�b�g
	simdata.currentHitBullet = 0;
	simdata.currentAllBullet = 0;
	simdata.destroyEnemies = 0;
	simdata.buttonPresses = 0;

	// �ҋ@�N���X�I���̏�����
	useWaitCalcDifficulty = waitProcess.WAIT_ERROR_VALUE;
	return;
}

// ��Փx�̕ύX����
void CalcDifficulty(double playerSkill)
{
	double normalizedSkill = playerSkill / 100.0;
	// �G�̈ړ����x���w��͈͂ŎZ�o
	const double ENEMY_MOVE_SPEED_MIN = 0.1;
	const double ENEMY_MOVE_SPEED_MAX = 2.0;
	simdata.enemyMoveSpeed = ENEMY_MOVE_SPEED_MIN + normalizedSkill * (ENEMY_MOVE_SPEED_MAX - ENEMY_MOVE_SPEED_MIN);
	// �G�̔��C�C���^�[�o�����w��͈͂ŎZ�o
	const double ENEMY_SHOOT_INTERVAL_MIN = 0.1;
	const double ENEMY_SHOOT_INTERVAL_MAX = 1.5;
	simdata.enemyShootInterval = ENEMY_SHOOT_INTERVAL_MAX - normalizedSkill * (ENEMY_SHOOT_INTERVAL_MAX - ENEMY_SHOOT_INTERVAL_MIN);
}

// ���X�^�[�g
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
	//// �I������
	printf("GOING TO EXIT..\n");
	if (use_gyro) TermGyro();
	//Sleep( 5000 );
	printf("BYE\n");

	return;
}