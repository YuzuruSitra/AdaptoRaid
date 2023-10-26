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

#include <FrameRateCounter.h>

// �O���[�o���ϐ��Ƃ��Đ錾
FrameRateCounter frameRateCounter;
//#include "SerialIO.h"
//HANDLE comm;
int comm;

inline float ObjX( ObjDataT *obj ){ return OBJ_X(obj);}
inline float ObjY( ObjDataT *obj ){ return OBJ_Y(obj);}
inline float ObjZ( ObjDataT *obj ){ return OBJ_Z(obj);}
inline float ObjRoll( ObjDataT *obj ){ return OBJ_ROLL(obj);}
inline float ObjPitch( ObjDataT *obj ){ return OBJ_PITCH(obj);}
inline float ObjYaw( ObjDataT *obj ){ return OBJ_YAW(obj);}

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
ezTrackDataT localHead = { 0, 0.0, 1.5, 0.0, 0.0, 0.0, 0.0 };
ezTrackDataT localBody = { 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
ezTrackDataT localHandR = { 0, 0.25, 1.25, -0.5, 0.0, 0.0, 0.0 };
ezTrackDataT localHandL = { 0,-0.25, 1.25, -0.5, 0.0, 0.0, 0.0 };
ezTrackDataT localFootR = { 0, 0.25, 0.0, -0.5, 0.0, 0.0, 0.0 };
ezTrackDataT localFootL = { 0,-0.25, 0.0, -0.5, 0.0, 0.0, 0.0 };
////////////////////////////////////////////////////////


/*--------------------
 * copyTrackToObj
 */
static void copyTrackToObj( ezTrackDataT *src, ObjDataT *dst )
{
	float pos[3], rot[3];
	if( src == NULL ) return;
	ezTrack_getPos( src, pos );
	setObjPos( dst, pos );
	ezTrack_getRot( src, rot );
	setObjRot( dst, rot );
}


/*---------------------------------------------------------------- InitScene
 * InitScene:
 *--------*/
void InitScene( void )
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
	setObjPos( &simdata.cube, 0.0, 1.0, -1.0 );
	setObjRot( &simdata.cube, 0.0, 0.0, 0.0 );
    setObjColor( &simdata.cube, 0.5, 0.3, 0.2 );
	simdata.cube.visible = true;
	simdata.cube.state = 0; //////////////��
    simdata.cube.radius = 0.2;

	simdata.cube.xsize = 0.6;
	simdata.cube.ysize = 0.05;
	simdata.cube.zsize = 0.25;

	setObjPos( &simdata.sphere, 0.0, 1.2, -1.0 );
	setObjRot( &simdata.sphere, 0.0, 0.0, 0.0 );
	setObjColor( &simdata.sphere, 1.0, 0.5, 0.0 );
	simdata.sphere.visible = true;
	simdata.sphere.state = 0;
	simdata.sphere.radius = 0.125; //����04

	simdata.handR.radius = 0.125; //��04
	simdata.handL.radius = 0.125; //��04
	simdata.handR.state = 0;
	simdata.handL.state = 0;
	
	setObjPos( &simdata.player, 0.0, 0.0, 0.0 );
	setObjRot( &simdata.player, 0.0, 0.0, 0.0 );
	setObjColor( &simdata.player, 0.0, 0.5, 1.0 );
	simdata.player.visible = true;
	simdata.player.state = 0;
	simdata.player.turn = 0.0;
	simdata.player.move = 0.0;
	simdata.player.radius = 0.5;
	
	//�E��i���[�J�����W�j���v���C���̎q���W�n�Ƃ���
	setObjLocal( &simdata.handR, &simdata.player ); //��

	//����������l
	setObjLocal( &simdata.handL, &simdata.player ); //��

	//�����v���C���[�̎q���W�n�ɂ���
	setObjLocal(&simdata.head, &simdata.player );

	simdata.active_camera = &simdata.player;
	//simdata.active_camera = NULL;
	//�v���C���I�u�W�F�N�g�̃A�h���X���J�����̃|�C���^�ɕR�t����

	setObjColor( &simdata.handR, 0.0, 1.0, 0.0 ); //�E��O���[��
	setObjColor( &simdata.handL, 1.0, 0.0, 0.0 ); //���背�b�h

#ifndef MREALMODE
	tracker = new ezTracker( use_tracker ); //VICON�g���Ƃ���true
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
	copyTrackToObj( trackHead, &simdata.head );
    copyTrackToObj( trackBody, &simdata.body );
	copyTrackToObj( trackHandL, &simdata.handL );
	copyTrackToObj( trackHandR, &simdata.handR );
	copyTrackToObj( trackFootL, &simdata.footL );
	copyTrackToObj( trackFootR, &simdata.footR );

#else

	///////////��
	int i; 

#endif
	if( use_gyro ) InitGyro();

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
	setObjColor(&simdata.movie_screen, 0.8, 0.8, 0.8 );
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
	OpenCOMDevice( comm,57600 );
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
	rot[mpu].roll =  ((float)data[6] / K - 1.0) * 180;
	rot[mpu].pitch = ((float)data[7] / K - 1.0) * 90;
	rot[mpu].yaw =   ((float)data[8] / K - 1.0) * 180;

	temp = ((float)data[9] / K - 1.0) * 100;

	//Sleep(0); //// �폜���Ă悢
	/////////////////////////////////////////////////////////

	i += 20; ////////
	return i;////////
}

void GetDataFromArduino( vector_t *acc, euler_t *rot, euler_t *gyro ) 
{
	unsigned char buf[2000];
	/////////////////////////////////////////////////
	static int count = 0;
	static int loop = 0;

	unsigned short len = 0;

	len = CollectUARTData( comm, (char *)buf);
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
		stat = CopeSerialData3(&buf[head], len - head, acc, rot, gyro );
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
void UpdateScene( void )
{
	simdata.time = glutGet( GLUT_ELAPSED_TIME );

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
	GetDataFromArduino( acc, rot, gyro);
	////////
#endif

	////simdata.movie->update(simdata.time); //

	//simdata.camR->update();
	//simdata.camL->update();
	if (usb_video) {
		simdata.extvideo->update();
	}

#ifdef MREALMODE
	for( int i = 0; i< N_TARGET; i++ ){
		TargetToObjData( &simdata.TargetList[i], &simdata.target[i] ); 
	}
	TargetToObjData( &simdata.TargetList[0], &simdata.handR ); 
	TargetToObjData( &simdata.TargetList[1], &simdata.handL ); 
	TargetToObjData( &simdata.mrealCamera[0], &simdata.head );
	//copyObj( &simdata.target[0], &simdata.handR );
	//copyObj( &simdata.target[1], &simdata.handL );
#else
	//////// �f�[�^�X�V ////////
	if( use_tracker ){
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
		trackBase = tracker->getTrackData( "Candy" );
		trackFootR = tracker->getTrackData( "RightFoot" );
		trackFootL = tracker->getTrackData( "LeftFoot" );
		
		copyTrackToObj( trackHead, &simdata.head );
		copyTrackToObj( trackBody, &simdata.body );
		copyTrackToObj( trackHandL, &simdata.handL );
		copyTrackToObj( trackHandR, &simdata.handR );
		copyTrackToObj( trackFootL, &simdata.footL );
		copyTrackToObj( trackFootR, &simdata.footR );
		//����F�\���̂̃|�C���^�������Ƃ���
		//&: �A�h���X�i���|�C���^�j��n�����Ƃ��w��
		simdata.handR.pos.z -= 0.5; //########
		simdata.handL.pos.z -= 0.5; //########
	}
	else{
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
	if( use_gyro ){
		float rot[3];
		UpdateGyro( rot );
		setObjRot( &simdata.head, rot ); //////////VECTOR OBJ
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
	setObjRot(&simdata.handR, rot[0].roll, rot[0].pitch, rot[0].yaw );
	////
	/*
	simdata.handL.pos.x = acc[1].x * 0.02 - 0.5;
	simdata.handL.pos.y = acc[1].y * 0.02 + 1.0;
	simdata.handL.pos.z = acc[1].z * 0.02 - 1.0;
	*/
	/**/
	simdata.handL.pos.x = acc[1].x * 0.1 - 0.5;
	simdata.handL.pos.y = - acc[1].y * 0.1 + 1.0;
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
	float deltaTime = frameRateCounter.GetElapsedTime();


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

    return;
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