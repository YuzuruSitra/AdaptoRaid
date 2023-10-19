#include "platform.h"

#include "common.h"
#include "sim.h"

extern SimDataT simdata;
extern WindowDataT window;

/*---------------------------------------------------------------- Viewing
 * Viewing:
 *--------*/
void Viewing( void )
{
	//��σJ�����̏ꍇ
    //gluLookAt( 0.0, 1.0, 5.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0 );

	applyObjInverse( &simdata.head );
	/*
	glRotatef( - simdata.head.roll, 0.0, 0.0, 1.0 ); //roll�̋t�ϊ�
	glRotatef( - simdata.head.pitch, 1.0, 0.0, 0.0 ); //pitch�̋t�ϊ�
	glRotatef( - simdata.head.yaw, 0.0, 1.0, 0.0 ); //yaw�̋t�ϊ�
	glTranslatef( - simdata.head.x, - simdata.head.y, - simdata.head.z );
	*/
	//applyObjInverse( &simdata.player );
	/*	
	glRotatef( - simdata.active_camera->roll, 0.0, 0.0, 1.0 );
	glRotatef( - simdata.active_camera->pitch, 1.0, 0.0, 0.0 );
	glRotatef( - simdata.active_camera->yaw, 0.0, 1.0, 0.0 );
	//������₷���悤�ɉ��s���Ă��܂����A���s�Ȃ��ł��\���܂���B
	glTranslatef( 	- simdata.active_camera->x,
			- simdata.active_camera->y, 
			- simdata.active_camera->z );
	*/
	//----------------------------------------------------
	//�q�σJ�����i�Œ�J�����j�Ńv���C���𒍎�����ꍇ�͂�����
	//gluLookAt( 0.0, 1.0, 3.0, simdata.player.x, simdata.player.y, simdata.player.z, 0.0, 1.0, 0.0 );
}
/*---------------------------------------------------------------- Projection
 * Projection:
 *--------*/
void Projection( void )
{
	//---- begin projection transformation
    gluPerspective( 45.0, window.aspect, simdata.clip_near, simdata.clip_far );
}
