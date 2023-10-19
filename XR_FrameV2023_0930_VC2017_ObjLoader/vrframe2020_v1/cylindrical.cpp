/******************************************************************************
 * glsample_frame.cpp 
 * Level 3 - base framework */

#include "platform.h"

#include "common.h"
#include "sim.h"

#include "calc.h"

extern WindowDataT window;
extern SimDataT simdata;

void HeadLight();
void Lighting();

/*------------------------------------------------------------------- display
 * View_Cylindical:�V�����h���J���X�N���[���p�̉摜���� 
 */
void cylindricalView( float dx )
{
	int i;
	float glnear = simdata.clip_near; //�j�A�v���[������
    float glfar = simdata.clip_far;   ////�t�@�[�v���[������
    const float view_angle_h = 125.0; //�X�N���[������p�i�V�X�e���ŗL�j
    const int n_views = 5; //�X�N���[���������i�����,��������ƍ����ג��Ӂj

	ObjDataT player_world;

	copyObj(&simdata.player, &player_world);
	moveLocalToWorld(&player_world);

    float da = view_angle_h / n_views;

    float vangle = - 0.5 * ( view_angle_h - da );

    int width = window.width / n_views;
    int height = window.height;

    int xo[n_views];

    for( i=0; i< n_views; i++ ) xo[i]    = width * i;

    float left, right, bottom, top;

    right  =   glnear * tanf( da / 2.0 * 3.14 / 180.0 );
    left   = - right;
    top    =   right * height / width;
    bottom = - top;

    //���o�b�t�@�N���A
    //glViewport( 0, 0, g_width, g_height );
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( left, right, bottom, top, glnear, glfar );
	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();

    for( i = 0; i < n_views; i++ ){

        glViewport( xo[i], 0, width, height );

		glPushAttrib( GL_ALL_ATTRIB_BITS );
		glPushMatrix();

        //glEnable( GL_DEPTH_TEST );

    	glLoadIdentity();
        glRotatef( vangle + da * i, 0.0, 1.0, 0.0 );
		glTranslatef( dx, 0.0, 0.0 );

/*
        //���J�����I�t�Z�b�g
		gluLookAt(
			0.0, 1.6, 0.0,
			0.0, 1.6, -6.0,
			0.0, 1.0, 0.0 );
*/
		//���w�b�h�ɂ��r���[�C���O�ϊ�
/*
	    glRotatef( - simdata.head.roll, 0.0, 0.0, 1.0 ); //roll�̋t�ϊ�
	    glRotatef( - simdata.head.pitch, 1.0, 0.0, 0.0 ); //pitch�̋t�ϊ�
	    glRotatef( - simdata.head.yaw, 0.0, 1.0, 0.0 ); //yaw�̋t�ϊ�
*/
	    //glTranslatef( - simdata.head.x, - simdata.head.y, - simdata.head.z );
	    glTranslatef( - OBJ_X(&simdata.head), 
	    - OBJ_Y(&simdata.head), 
	    - OBJ_Z(&simdata.head) );
		/*
		glRotatef( - simdata.body.roll,  0.0, 0.0, 1.0 );
		glRotatef( - simdata.body.pitch, 1.0, 0.0, 0.0 );
		glRotatef( - simdata.body.yaw,   0.0, 1.0, 0.0 );
		glTranslatef( - simdata.body.x, - simdata.body.y, - simdata.body.z );
		*/
		/*
		glRotatef( - player_world.roll,  0.0, 0.0, 1.0 );
		glRotatef( - player_world.pitch, 1.0, 0.0, 0.0 );
		glRotatef( - player_world.yaw,   0.0, 1.0, 0.0 );
		glTranslatef( - player_world.x, - player_world.y, - player_world.z );
		*/

		applyObjInverse( &player_world ); //////////

		HeadLight();
		Lighting();

        DrawScene();
        //glDisable(GL_DEPTH_TEST);

		glPopMatrix();
		glPopAttrib();
    }
}
/******************************************************************************
 * end of source code */
