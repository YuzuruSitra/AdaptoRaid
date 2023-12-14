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
WaitProcess waitProcess[STOCK_WAITPROCESS];
QLearning qLearning;

//#include "SerialIO.h"
//HANDLE comm;
int comm;

inline float ObjX(ObjDataT *obj) { return OBJ_X(obj); }
inline float ObjY(ObjDataT *obj) { return OBJ_Y(obj); }
inline float ObjZ(ObjDataT *obj) { return OBJ_Z(obj); }
inline float ObjRoll(ObjDataT *obj) { return OBJ_ROLL(obj); }
inline float ObjPitch(ObjDataT *obj) { return OBJ_PITCH(obj); }
inline float ObjYaw(ObjDataT *obj) { return OBJ_YAW(obj); }

SimDataT simdata; //SimDataT�^�\���̂̃f�[�^��錾
extern MouseDataT mouse;
extern KeyDataT keydata; //���C����

#define MY_TCP_FLAG 0
ezDepth *kinect = new ezDepth();
TCPDataT tcpdata;
///////////////////////////////////////////////////////
//�g���b�J�[�f�o�C�X��L���ɂ���t���O
//bool use_tracker = false; //�L���ɂ���Ƃ�true

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
////////////////////////////////////////////////////////


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

#if MY_TCP_FLAG
	//////
	//�ȉ�TCP�ʐM�̐ݒ�
	//initTCPClient(&tcpdata,"172.28.139.203");//��M�p�\���̃f�[�^�̏������B�A�h���X�͑����̂���

	initTCPClient(&tcpdata, "127.0.0.1");//�ʐM�p�\���̃f�[�^�̏������B�A�h���X�͑����̂���
	ConnectTCPClient(&tcpdata);//�T�[�o�[�ɐڑ����ɂ����B

	//�����[�g�f���֘A201870730�ǉ�
	//colortex->Open(KINECT_WIDTH, KINECT_HEIGHT, GL_BGRA_EXT);
	//depthtex->Open(KINECT_WIDTH, KINECT_HEIGHT, GL_DEPTH_COMPONENT);
	//depthtex->Open( KINECT_WIDTH, KINECT_HEIGHT, GL_LUMINANCE); /////////////////////

	tcpdata.data_recv = (void *)(&simdata.downdata);//��M�p�\���̂̐ݒ�
	tcpdata.data_send = (void *)(&simdata.updata);//���M�p�\���̂̐ݒ�

	tcpdata.datasize_recv = sizeof(DownDataT);//��M�p�\���̂̃f�[�^�T�C�Y�擾
	tcpdata.datasize_send = sizeof(UpDataT);//���M�p�\���̂̃f�[�^�T�C�Y�擾

	kinect->open(KINECT_WIDTH, KINECT_HEIGHT, 42.5, simdata.clip_near, simdata.clip_far);
	kinect->attach(simdata.downdata.color, simdata.downdata.depth);

	tcpdata.v_flag = true;//���M�����b�Z�[�W���o�����ǂ����̃t���O(true:�o��false:�o���Ȃ�)
#endif
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


	const float SET_POS_Z = -10.0;

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

		//printf("enemies[%i]�� X���W:%f Y���W:%f\n", i, setPosX, setPosY);

		simdata.enemies[i].move = 0.0;
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

#ifndef MREALMODE
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

#else

	///////////��
	int i;

#endif
	if (use_gyro) InitGyro();

	//simdata.camR = new ezCamera();
	//simdata.camR->open( 0, 640, 480, 30.0, GL_BGRA_EXT, "Microsoft LifeCam Rear"  );
	//simdata.camR->open( 0, 640, 480, 30.0, GL_BGRA_EXT, "ELECOM 5MP Webcam" ); //�������W�������J����
	//simdata.camR->open( 0, 640, 480, 30.0, GL_BGRA_EXT, "IPEVO V4K" );

	//simdata.camL = new ezCamera();
	//simdata.camL->open( 1, 640, 480, 30.0, GL_BGRA_EXT, "ELECOM 5MP Webcam"  ); //�������W�������J����
	//simdata.camL->open( 1, 640, 480, 30.0, GL_BGRA_EXT, "IPEVO V4K" );

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

	//// InitScene�ɒǉ�����////////////////////////
	/*
	comm = ComInit("COM3");
	//getchar(); ////////�폜���Ă悢
	if (comm == INVALID_HANDLE_VALUE) exit(-1);
	*/
#ifdef ARDUINO	
	comm = 3;
	OpenCOMDevice(comm, 57600);
	/////////////////////////////////////////////////
#endif
	simdata.scale = 0;
	simdata.octabe = 5;

	ezMIDI::Open(true); //polyphonic
	simdata.midi = new ezMIDI(9);
	//simdata.midi = new ezMIDI(10, 27 );

	return;
}

void CopeSerialData2(unsigned char *buf, int len, vector_t *acc, euler_t *rot)
{
	float ax, ay, az;
	float gx, gy, gz;
	float roll, pitch, yaw;
	float temp;

	unsigned short data[10]; /////////

	int i = 0;
	if (buf[0] != 0xff) {//�擪��255�łȂ�������
		//�擪������Ă���̂ŁA�������f�[�^��ǂݔ�΂�

		while (buf[i] != 0xff) {//255�܂Ŕ�΂�
			i++;
			if (i > len) return;
		}
	}
	i++;
	unsigned char *p = &buf[i]; ////////

	//buf[i]����̐���bufbuf[0]�̌�ɑ������
	for (int j = 0; j < 10; j++) {
		data[j] = (*p << 8) | *p;
		p += 2;
	}

	const float ACCMAX = 20.0;
	const float GYROMAX = 500.0;
	const float K = 32767;

	acc->x = ((float)data[0] / K - 1.0)* ACCMAX;
	acc->y = ((float)data[1] / K - 1.0)*ACCMAX;
	acc->z = ((float)data[2] / K - 1.0)*ACCMAX;
	gx = ((float)data[3] / K - 1.0)*GYROMAX;
	gy = ((float)data[4] / K - 1.0)*GYROMAX;
	gz = ((float)data[5] / K - 1.0)*GYROMAX;
	rot->roll = ((float)data[6] / K - 1.0) * 180;
	rot->pitch = ((float)data[7] / K - 1.0) * 90;
	rot->yaw = ((float)data[8] / K - 1.0) * 180;

	temp = ((float)data[9] / K - 1.0) * 100;

	//Sleep(0); //// �폜���Ă悢
	/////////////////////////////////////////////////////////
}

int CopeSerialData3(unsigned char *buf, int len, vector_t *acc, euler_t *rot, euler_t *gyro)
{
	float ax, ay, az;
	float gx, gy, gz;
	float roll, pitch, yaw;
	float temp;
	int mpu;

	unsigned short data[10]; /////////

	int i = 0;
	if (buf[0] != 0xff) {//�擪��255�łȂ�������
		//�擪������Ă���̂ŁA�������f�[�^��ǂݔ�΂�

		while (buf[i] != 0xff) {//255�܂Ŕ�΂�
			i++;
			if (i > len) return 0; /////
		}
	}
	i++;
	mpu = buf[i]; ////////
	i++; ////////
	unsigned char *p = &buf[i];

	//buf[i]����̐���bufbuf[0]�̌�ɑ������
	for (int j = 0; j < 10; j++) {
		data[j] = (*p << 8) | *p;
		p += 2;
	}

	const float ACCMAX = 20.0;
	const float GYROMAX = 500.0;
	const float K = 32767;

	acc[mpu].x = ((float)data[0] / K - 1.0)* ACCMAX;
	acc[mpu].y = ((float)data[1] / K - 1.0)*ACCMAX;
	acc[mpu].z = ((float)data[2] / K - 1.0)*ACCMAX;
	gyro[mpu].roll = ((float)data[3] / K - 1.0)*GYROMAX;
	gyro[mpu].pitch = ((float)data[4] / K - 1.0)*GYROMAX;
	gyro[mpu].yaw = ((float)data[5] / K - 1.0)*GYROMAX;
	rot[mpu].roll = ((float)data[6] / K - 1.0) * 180;
	rot[mpu].pitch = ((float)data[7] / K - 1.0) * 90;
	rot[mpu].yaw = ((float)data[8] / K - 1.0) * 180;

	temp = ((float)data[9] / K - 1.0) * 100;

	//Sleep(0); //// �폜���Ă悢
	/////////////////////////////////////////////////////////

	i += 20; ////////
	return i;////////
}

void GetDataFromArduino(vector_t *acc, euler_t *rot, euler_t *gyro)
{
	unsigned char buf[2000];
	/////////////////////////////////////////////////
	static int count = 0;
	static int loop = 0;

	unsigned short len = 0;

	len = CollectUARTData(comm, (char *)buf);
	loop++;

	/*
	system("cls");

	for (int i = 0; i < len; i++) {
		printf(" %02x", buf[i]);
	}
	printf("\n");
	*/

	int head = 0;////////
	//if (len > 1)
	while (len - head > 1) ////////
	{
		////printf("count %d/%d\n", count++, loop);
		//CopeSerialData2(buf, len, acc, rot );
		int stat;
		stat = CopeSerialData3(&buf[head], len - head, acc, rot, gyro);
		if (stat < 1) break;
		else head += stat;
	}
	/*
	else {
		////printf("count %d/%d\t%d\n", count++, loop, len);
	}
	*/
	////printf("ACC: %8.3f %8.3f %8.3f\n",   acc->x, acc->y, acc->z);
	printf("ANGLE: %8.3f %8.3f %8.3f\n", rot->roll, rot->pitch, rot->yaw);

	//Sleep(0);
	return;
}

/*-------------------------------------------------------------- UpdateScene
 * UpdateScene:
 *--------*/

float deltaTime;
// �Q�[���̉���
const float LANGE_POS_X = 8;
// �C��̑ҋ@�N���X�I��������
int useWaitFortShoot = STOCK_WAITPROCESS;
// �G�ˌ�����̌o�ߎ���
float enemyShootInterval = 2.0f;
// �G�e�̑ҋ@�N���X�I��������
int useWaitEnemyShoot = STOCK_WAITPROCESS;
// ��Փx�����̑ҋ@�N���X������
int useCalcDifficulty = STOCK_WAITPROCESS;

void UpdateScene(void)
{

	simdata.time = glutGet(GLUT_ELAPSED_TIME);

#if MY_TCP_FLAG
	//////// �f�[�^�X�V ////////	
	//�\�P�b�g�ʐM
	TCPRecv(&tcpdata);
	//�`����̍X�V

	/*
	colortex->Copy( simdata.downdata.color );
	colortex->Update();
	depthtex->Copy( (unsigned char *)simdata.downdata.depth);
	*/

	Sleep(0);
	//TCPSend(&tcpdata);
	printf("%08x\n", tcpdata.data_send);

#endif
#ifdef ARDUINO
	//////// �����x�Ɗp�����x���擾
	static vector_t acc[2];
	static euler_t rot[2], gyro[2];
	GetDataFromArduino(acc, rot, gyro);
	////////
#endif

	////simdata.movie->update(simdata.time); //

	//simdata.camR->update();
	//simdata.camL->update();
	if (usb_video) {
		simdata.extvideo->update();
	}

#ifdef MREALMODE
	for (int i = 0; i < N_TARGET; i++) {
		TargetToObjData(&simdata.TargetList[i], &simdata.target[i]);
	}
	TargetToObjData(&simdata.TargetList[0], &simdata.handR);
	TargetToObjData(&simdata.TargetList[1], &simdata.handL);
	TargetToObjData(&simdata.mrealCamera[0], &simdata.head);
	//copyObj( &simdata.target[0], &simdata.handR );
	//copyObj( &simdata.target[1], &simdata.handL );
#else
	//////// �f�[�^�X�V ////////
	if (use_tracker) {
		//�g���b�J�[����̃f�[�^���Q�b�g
		tracker->read(); //���L����������f�[�^��ǂݏo��
		if (use_vicon) {
			trackHead = tracker->getTrackData("CAP"); //VICON�}�[�J�̖��O
			trackHandR = tracker->getTrackData("TREE_A");
			trackHandL = tracker->getTrackData("TREE_B");
		}
		else {
			trackHead = tracker->getTrackData(0); //ARTOOLKIT�}�[�J�̔ԍ�
			trackHandR = tracker->getTrackData(1);
			trackHandL = tracker->getTrackData(2);
		}
		trackBody = tracker->getTrackData("Chest");
		trackBase = tracker->getTrackData("Candy");
		trackFootR = tracker->getTrackData("RightFoot");
		trackFootL = tracker->getTrackData("LeftFoot");

		copyTrackToObj(trackHead, &simdata.head);
		copyTrackToObj(trackBody, &simdata.body);
		copyTrackToObj(trackHandL, &simdata.handL);
		copyTrackToObj(trackHandR, &simdata.handR);
		copyTrackToObj(trackFootL, &simdata.footL);
		copyTrackToObj(trackFootR, &simdata.footR);
		//����F�\���̂̃|�C���^�������Ƃ���
		//&: �A�h���X�i���|�C���^�j��n�����Ƃ��w��
		simdata.handR.pos.z -= 0.5; //########
		simdata.handL.pos.z -= 0.5; //########
	}
	else {
		//��01���R�����g��

		//copyTrackToObj( trackHandL, &simdata.handL );
		//copyTrackToObj( trackHandR, &simdata.handR );

		/*

		//��02���}�E�X�ŉE��handR�𓮂���
		//���x�����{��ʒu���� ########
		simdata.handR.pos.x = mouse.x * 2.0 + 0.25; // mouse.x: -1.0�i���[�j�`1.0�i�E�[�j
		simdata.handR.pos.y = -mouse.y * 2.0 + 1.2; // mouse.y; -1.0�i��[�j�`1.0�i���[�j
		simdata.handR.rot.pitch = ( simdata.handR.pos.y - 1.2 ) * 100.0;
		simdata.handR.rot.yaw = ( simdata.handR.pos.x - 0.25 ) * ( - 100.0 );
		simdata.handR.rot.roll = simdata.handR.rot.yaw - 30.0;
		//Z���W��localHandR�ŏ����ݒ�̂܂�
		//��

		//��03�����łɍ���handL���������`�E��Ə㉺���E���t�ɂ����肷��
		//���x�����{��ʒu���� ########
		simdata.handL.pos.x = - mouse.x * 2.0 - 0.25; // mouse.x: -1.0�i���[�j�`1.0�i�E�[�j
		simdata.handL.pos.y = mouse.y * 2.0 + 1.2; // mouse.y; -1.0�i��[�j�`1.0�i���[�j
		simdata.handL.rot.pitch = ( simdata.handL.pos.y - 1.2 ) * 100.0;
		simdata.handL.rot.yaw = ( simdata.handL.pos.x + 0.25 ) * ( - 100.0 );
		simdata.handL.rot.roll = simdata.handL.rot.yaw + 30.0;
		//Z���W��localHandR�ŏ����ݒ�̂܂�
		//Z���W��localHandL�ŏ����ݒ�̂܂�
		//��


		////���ǉ�
		if (keydata.arrowUp) {
			simdata.handL.pos.z -= 0.01; //###### VECTOR Z
		}
		if (keydata.arrowDown) {
			simdata.handL.pos.z += 0.01; //###### VECTOR Z
		}
		//////////��
		*/
	}
	if (use_gyro) {
		float rot[3];
		UpdateGyro(rot);
		setObjRot(&simdata.head, rot); //////////VECTOR OBJ
	}
#endif
#ifdef ARDUINO
	////// ��̓������㏑��
	/*
	simdata.handR.pos.x = acc[0].x * 0.02 + 0.5;
	simdata.handR.pos.y = acc[0].y * 0.02 + 1.0;
	simdata.handR.pos.z = acc[0].z * 0.02 - 1.0;
	*/
	/**/
	simdata.handR.pos.x = acc[0].x * 0.1 + 0.5;
	simdata.handR.pos.y = acc[0].y * 0.1 + 1.0;
	simdata.handR.pos.z = acc[0].z * 0.1 - 1.0;
	/**/
	setObjRot(&simdata.handR, rot[0].roll, rot[0].pitch, rot[0].yaw);
	////
	/*
	simdata.handL.pos.x = acc[1].x * 0.02 - 0.5;
	simdata.handL.pos.y = acc[1].y * 0.02 + 1.0;
	simdata.handL.pos.z = acc[1].z * 0.02 - 1.0;
	*/
	/**/
	simdata.handL.pos.x = acc[1].x * 0.1 - 0.5;
	simdata.handL.pos.y = -acc[1].y * 0.1 + 1.0;
	simdata.handL.pos.z = acc[1].z * 0.1 - 1.0;
	/**/
	setObjRot(&simdata.handL, rot[1].roll, rot[1].pitch, rot[1].yaw);
#endif
	/*
	//----------------------------------------------- �}�E�X�ňړ�����
	simdata.player.turn = - 0.5 * mouse.xRel;
	simdata.player.move = - 0.2 * mouse.yRel;
	MoveObject( &simdata.player );
	*/

	//���萔�Ƃ��ĕϐ����g�������Ƃ��ɂ́uconst�v������
	const float yon = 1.25, yoff = 1.15;


	//���O�̒l��ێ��������Ƃ��ɂ́ustatic�v������
	static float xo, zo;


	// �t���[�����[�g�J�E���^�[���X�V
	frameRateCounter.Update();
	deltaTime = frameRateCounter.GetElapsedTime();


	/*
	//������̓���ňړ����鑀��
	switch (simdata.handL.state) {
	case 0: //����ړ����[�h
		if (ObjY(&simdata.handL) > yon) {  ////////VECTOR Y
			simdata.handL.state = 1;
			xo = ObjX(&simdata.handL); ////////VECTOR X
			zo = ObjZ(&simdata.handL); ////////VECTOR Z
			setObjColor(&simdata.handL, 1.0, 1.0, 0.0);
		}
		break;
	case 1: //���ړ����[�h
		if (ObjY(&simdata.handL) < yoff) { ////////VECTOR Y
			simdata.handL.state = 0;
			setObjColor(&simdata.handL, 1.0, 0.0, 0.0);
		}
		//�ړ��̏���
		simdata.player.turn = deltaTime * -10.0 * (ObjX(&simdata.handL) - xo); ////////VECTOR X
		simdata.player.move = deltaTime * -0.2 * (ObjZ(&simdata.handL) - zo); ////////VECTOR Z
		//simdata.player.turn = -0.5 * (ObjX(&simdata.handL) - xo); ////////VECTOR X
		//simdata.player.move = -0.2 * (ObjZ(&simdata.handL) - zo); ////////VECTOR Z
		MoveObject(&simdata.player);
		break;
	}
	*/


	//��ԑJ�ڂ̃`�F�b�N�A��ԑJ�ځA

	/*
	//��04
	bool ishit;
	switch (simdata.sphere.state) {
	case 0://���E�肩��O��A���E��ɐG��Ă��Ȃ����
		ishit = isHit(&simdata.sphere, &simdata.handR);
		if (ishit) {
			setObjColor(&simdata.sphere, 0.0, 1.0, 0.5);

			//��05
			simdata.sphere.state = 1;
			moveWorldToLocal( &simdata.sphere, &simdata.handR );

		}
		else {
			setObjColor(&simdata.sphere, 0.7, 0.7, 0.7);

		}
		break;
	case 1: //��06���E��ɔc������Ă�����
		ishit = isHit(&simdata.sphere, &simdata.handL);
		if (ishit) {
			setObjColor(&simdata.sphere, 1.0, 0.5, 0.0);
			moveLocalToWorld(&simdata.sphere);
			simdata.sphere.state = 2;//��07 0 -> 2
		}
		break;
	case 2://��08 �E��̔c������O�ꂽ���G���Ă�����
		ishit = isHit(&simdata.sphere, &simdata.handR);
		if (!ishit) {
			setObjColor(&simdata.sphere, 0.7, 0.7, 0.7);
			simdata.sphere.state = 0;
		}
		break;
	}

	if (isHitBox(&simdata.cube, &simdata.handR)) {
		setObjColor(&simdata.cube, 1.0, 0.0, 0.0);
		////simdata.movie->play(simdata.time);
	}
	else {
		setObjColor(&simdata.cube, 0.0, 1.0, 0.0);

	}
	*/

	// �t���[�Y���̖\���P�A
	if (deltaTime >= 0.1f) return;

	MovingFort();
	FortShooting();
	FortBulletMove();
	MovingEnemies();
	EnemyShooting();
	EnemyBulletMove();
	CalcDifficulty();
	OnCollision();
	StateRun();
	return;
}

// �C��(�v���C���[)�̈ړ�
void MovingFort(void)
{
	float speed = 4.0f;
	if (keydata.arrowLeft && simdata.fort.pos.x > -LANGE_POS_X) simdata.fort.pos.x -= speed * deltaTime;
	if (keydata.arrowRight && simdata.fort.pos.x < LANGE_POS_X) simdata.fort.pos.x += speed * deltaTime;
	simdata.buttonPresses++;
	return;
}

// �C�䂩��U��
void FortShooting(void)
{
	const float shootInterval = 0.25f;

	// �ҋ@����
	if (useWaitFortShoot == STOCK_WAITPROCESS) useWaitFortShoot = SelectWaitClass();
	bool waiting = !waitProcess[useWaitFortShoot].WaitForTime(shootInterval, deltaTime);
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
	useWaitFortShoot == STOCK_WAITPROCESS;
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
		//if (!simdata.enemies[i].visible) continue;
		// ����delay
		if (simdata.enemies[i].enemyMoveTime >= 0)
		{
			simdata.enemies[i].enemyMoveTime -= deltaTime;
			continue;
		}

		float speed = 1.0f;
		float downPadding = 0.5f;

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
				simdata.enemies[i].pos.y -= downPadding;
			}
		}

		if (!simdata.enemies[i].enemyGoRight) speed *= -1;

		float setPosX = simdata.enemies[i].pos.x + speed * deltaTime;
		setObjPos(&simdata.enemies[i], setPosX, simdata.enemies[i].pos.y, simdata.enemies[i].pos.z);
	}
	return;
}

// �G�̍U��
void EnemyShooting(void)
{
	// �ҋ@����
	if (useWaitEnemyShoot == STOCK_WAITPROCESS) useWaitEnemyShoot = SelectWaitClass();
	bool waiting = !waitProcess[useWaitEnemyShoot].WaitForTime(enemyShootInterval, deltaTime);
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
		enemyShootInterval = uniformRandom(0.2f, 1.2f);
		// �ҋ@�N���X�I���̏�����
		useWaitEnemyShoot = STOCK_WAITPROCESS;
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


int useFortWaitClass = STOCK_WAITPROCESS;
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
		// ��e���
	case 1:
		useFortWaitClass = SelectWaitClass();
		if (useFortWaitClass != STOCK_WAITPROCESS) simdata.fort.state = 2;
		break;
	case 2:
		setObjColor(&simdata.fort, 0.8, 0.2, 0.2);
		setObjColor(&simdata.fortTop, 0.8, 0.2, 0.2);
		if (waitProcess[useFortWaitClass].WaitForTime(0.75f, deltaTime))
		{
			simdata.fort.state = 0;
			useFortWaitClass = STOCK_WAITPROCESS;
		}
		break;
	}
	return;
}

// ��Փx�̑J��
void CalcDifficulty(void)
{
	// �ҋ@����
	if (useCalcDifficulty == STOCK_WAITPROCESS) useCalcDifficulty = SelectWaitClass();
	bool waiting = !waitProcess[useCalcDifficulty].WaitForTime(3.0f, deltaTime);
	if (waiting) return;
	// ��Փx��������
	double hitRate;
	if (simdata.currentAllBullet == 0) hitRate = 0;
	else hitRate = simdata.currentHitBullet / simdata.currentAllBullet;
	// �v���C���[�̏�肳���v�Z���AQ�l���X�V
	qLearning.updateScores(hitRate, simdata.buttonPresses, simdata.destroyEnemies);
	double playerSkill = qLearning.calculateSkill();
	printf("Player Skill : %lf\n", playerSkill);
	// �l�̃��Z�b�g
	simdata.currentHitBullet = 0;
	simdata.currentAllBullet = 0;
	simdata.destroyEnemies = 0;

	// �ҋ@�N���X�I���̏�����
	useCalcDifficulty = STOCK_WAITPROCESS;
	return;
}

// ��̋󂢂Ă�WaitProcess�N���X��I��
int SelectWaitClass()
{
	for (int i = 0; i < STOCK_WAITPROCESS; i++)
	{
		if (waitProcess[i].InWaitProcess) continue;
		return i;
	}
	return STOCK_WAITPROCESS;
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