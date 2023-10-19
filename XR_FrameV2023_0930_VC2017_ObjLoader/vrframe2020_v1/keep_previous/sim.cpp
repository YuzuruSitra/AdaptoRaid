#include "platform.h"

#include "common.h" //WindowDataT, MouseDataT, KeyDataT
#include "calc.h"
#include "sim.h"
#include "config.h"

#include "ezTrack.h"

#include "GyroFiles/gyro.h"

#include "mymodel.h" //��

SimDataT simdata; //SimDataT�^�\���̂̃f�[�^��錾
extern MouseDataT mouse;
extern KeyDataT keydata; //���C����
extern int time;
///////////////////////////////////////////////////////
//�g���b�J�[�f�o�C�X��L���ɂ���t���O
//bool use_tracker = false; //�L���ɂ���Ƃ�true

ezTracker *tracker; //���L�������o�R�Ńg���b�J�[�̏��𓾂�I�u�W�F�N�g
//�g���b�J�[����󂯎�����f�[�^�ւ̃|�C���^
ezTrackDataT *trackBase; //��}�[�J
ezTrackDataT *trackHead;
ezTrackDataT *trackBody;
ezTrackDataT *trackHandR;
ezTrackDataT *trackHandL;
ezTrackDataT *trackFootR;
ezTrackDataT *trackFootL;
//�}�[�J�������Ȃ��ꍇ�Ȃǂ̃_�~�[�f�[�^
ezTrackDataT localBase = { 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
ezTrackDataT localHead = { 0, 0.0, 1.5, 0.0, 0.0, 0.0, 0.0 };
ezTrackDataT localBody = { 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
ezTrackDataT localHandR = { 0, 0.25, 1.25, -2.0, 0.0, 0.0, 0.0 };//��-2.0
ezTrackDataT localHandL = { 0,-0.25, 1.25, -2.0, 0.0, 0.0, 0.0 };//��-2.0
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
	setObjPos( &simdata.cube, 1.0, 0.0, -3.0 );
	setObjRot( &simdata.cube, 0.0, 45.0, 30.0 );
    setObjColor( &simdata.cube, 0.0, 0.0, 0.0 );
	simdata.cube.visible = true;
	simdata.cube.state = 0; //////////////��
    simdata.cube.radius = 0.5;

	simdata.cube.xsize = 2.0;
	simdata.cube.ysize = 4.0;
	simdata.cube.zsize = 0.2;

	setObjPos( &simdata.sphere, -1.0, 0.0, -5.0 );
	setObjRot( &simdata.sphere, 0.0, 0.0, 0.0 );
	setObjColor( &simdata.sphere, 1.0, 0.5, 0.0 );
	simdata.sphere.visible = true;
	simdata.sphere.state = 0;
	simdata.sphere.radius = 0.5; //����04

	simdata.handR.radius = 0.25; //��04
	simdata.handL.radius = 0.25; //��04
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

	tracker = new ezTracker( use_tracker ); //VICON�g���Ƃ���true
	tracker->open( "VICON", false ); //���ʖ�, W�t���O(false:R/O)

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

	CreateMyModels(); //��

	if( use_gyro ) InitGyro();

	return;
}
/*-------------------------------------------------------------- UpdateScene
 * UpdateScene:
 *--------*/
void UpdateScene( void )
{
	//////// �f�[�^�X�V ////////
	if( use_tracker ){
		//�g���b�J�[����̃f�[�^���Q�b�g
		tracker->read(); //���L����������f�[�^��ǂݏo��
		trackHead = tracker->getTrackData( "CAP" ); //VICON�}�[�J�̖��O
		trackBody = tracker->getTrackData( "Chest" );
		trackHandR = tracker->getTrackData("TREE_A" );
		trackHandL = tracker->getTrackData(  "TREE_B" );
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
		simdata.handR.z -= 0.5;
		simdata.handL.z -= 0.5;
	}
	else{
		//��01���R�����g��
		/*
		copyTrackToObj( trackHandL, &simdata.handL );
		copyTrackToObj( trackHandR, &simdata.handR );
		*/
		//��02���}�E�X�ŉE��handR�𓮂���
		//���x�����{��ʒu����
		simdata.handR.x = mouse.x * 2.0 + 0.25; // mouse.x: -1.0�i���[�j�`1.0�i�E�[�j
		simdata.handR.y = -mouse.y * 2.0 + 1.2; // mouse.y; -1.0�i��[�j�`1.0�i���[�j
		//simdata.handR.z = -2.0;//���R�����g��
		//��
		
		//��03�����łɍ���handL���������`�E��Ə㉺���E���t�ɂ����肷��
		//���x�����{��ʒu����
		simdata.handL.x = - mouse.x * 2.0 - 0.25; // mouse.x: -1.0�i���[�j�`1.0�i�E�[�j
		simdata.handL.y = mouse.y * 2.0 + 1.2; // mouse.y; -1.0�i��[�j�`1.0�i���[�j
		//simdata.handL.z = -2.0;//���R�����g��
		//��
		
		////���ǉ�
		if (keydata.arrowUp) {
			simdata.handL.z -= 0.01;
		}
		if (keydata.arrowDown) {
			simdata.handL.z += 0.01;
		}
		//////////��
	}

	if( use_gyro ){
		float rot[3];
		UpdateGyro( rot );
		simdata.head.roll = rot[0];
		simdata.head.pitch = rot[1];
		simdata.head.yaw = rot[2];
	}

	/*
	//----------------------------------------------- �}�E�X�ňړ�����
	simdata.player.turn = - 0.5 * mouse.xRel;
	simdata.player.move = - 0.2 * mouse.yRel;
	MoveObject( &simdata.player ); 
	*/

	//���萔�Ƃ��ĕϐ����g�������Ƃ��ɂ́uconst�v������
	const float yon = 1.5, yoff = 1.0;

	//���O�̒l��ێ��������Ƃ��ɂ́ustatic�v������
	static float xo, zo;

	//������̓���ňړ����鑀��
	switch (simdata.handL.state) {
	case 0: //����ړ����[�h
		if (simdata.handL.y > yon) {
			simdata.handL.state = 1;
			xo = simdata.handL.x;
			zo = simdata.handL.z;
			setObjColor(&simdata.handL, 1.0, 1.0, 0.0);
		}
		break;
	case 1: //���ړ����[�h
		if (simdata.handL.y < yoff) {
			simdata.handL.state = 0;
			setObjColor(&simdata.handL, 1.0, 0.0, 0.0);
		}
		//�ړ��̏���
		simdata.player.turn = - 0.5 * (simdata.handL.x - xo);
		simdata.player.move = - 0.2 * (simdata.handL.z - zo);
		MoveObject(&simdata.player);
		break;
	}

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

    return;
}
