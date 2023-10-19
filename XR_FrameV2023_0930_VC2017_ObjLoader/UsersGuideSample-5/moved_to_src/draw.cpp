#include "platform.h"

#include "ezUtil.h"
#include "sim.h"

#include "mymodel.h" //��

extern SimDataT simdata;

//-------- prototypes for user functions

void applyMaterialColor( float r, float g, float b );
void drawString(float x, float y, float z, float xscl, float yscl,
	const char *string);

/**/
/*---------------------------------------------------------------------------*/
void drawString(float x, float y, float z, float xscl, float yscl,
	const char *string)
{
	bool lighting = glIsEnabled(GL_LIGHTING);
	if (lighting) glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(xscl*0.001, yscl*0.001, 1.0);
	while (*string) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *string++);
	}
	glPopMatrix();
	if( lighting ) glEnable(GL_LIGHTING);
	return;
}
/*--------------------------------------------------------- setMaterialColor
 * applyMaterialColor:
 *--------*/
void applyMaterialColor( float r, float g, float b )
{
    float diffuse[4];
    float specular[] = { 0.8, 0.8, 0.8, 1.0 };

	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = 1.0;

    glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 32.0 );

    return;
}
/*----------------------------------------------------------- drawSolidCube
 * drawSolidCube:
 *--------*/
void drawSolidCube( void )
{
	glPushMatrix();
	{
		glTranslatef( 0.0, 0.0, 0.0 );   //�I�u�W�F�N�g��ʒu����
		glRotatef( 0.0, 0.0, 1.0, 0.0 ); //�I�u�W�F�N�g��p�������F���[�p
		glRotatef( 0.0, 1.0, 0.0, 0.0 ); //�I�u�W�F�N�g��p�������F�s�b�`�p
		glRotatef( 0.0, 0.0, 0.0, 1.0 ); //�I�u�W�F�N�g��p�������F���[���p
		glutSolidCube( 1.0 );
	}
	glPopMatrix();
    return;
}
/*--------------------------------------------------------- drawSolidSphere
 * drawSolidSphere:
 *--------*/
void drawSolidSphere( void )
{
	glPushMatrix();
	{
		glTranslatef( 0.0, 0.0, 0.0 );    //�I�u�W�F�N�g��ʒu����
		glRotatef( 0.0, 0.0, 1.0, 0.0 );  //�I�u�W�F�N�g��p�������F���[�p
		glRotatef( 90.0, 1.0, 0.0, 0.0 ); //�I�u�W�F�N�g��p�������F�s�b�`�p
		glRotatef( 0.0, 0.0, 0.0, 1.0 );  //�I�u�W�F�N�g��p�������F���[���p
		glutSolidSphere( 0.5, 18, 16 );   //���a�C�o�x�����������C�ܓx����������
	}
	glPopMatrix();
    return;
}
//----------------------------------------------- drawPlayer
void drawPlayer( void )
{
	glPushMatrix();
	{
		glTranslatef( 0.0, 0.0, 0.0 );    //�I�u�W�F�N�g��ʒu����
		glRotatef( 0.0, 0.0, 1.0, 0.0 );  //�I�u�W�F�N�g��p�������F���[�p
		glRotatef( 180.0, 1.0, 0.0, 0.0 ); //�I�u�W�F�N�g��p�������F�s�b�`�p
		glRotatef( 0.0, 0.0, 0.0, 1.0 );  //�I�u�W�F�N�g��p�������F���[���p
		glutSolidCone( 0.5, 1.0, 6, 4 );   //���a�C�o�x�����������C�ܓx����������
	}
	glPopMatrix();
}

void drawHandR( void )
{
	glPushMatrix();
	applyObjColor( &simdata.handR );
	applyObjTransform( &simdata.handR );
	//glutSolidSphere( 0.1, 8, 6 );
	drawHandRmodel();//mymodels.cpp�ō�����`��֐�
	glPopMatrix();
}
void drawHandL( void )
{
	glPushMatrix();
	applyObjColor( &simdata.handL );
	applyObjTransform( &simdata.handL );
	glutSolidSphere( 0.1, 8, 6 );
	//drawHandLmodel();
	glPopMatrix();
}
/*---------------------------------------------------------------- PreDraw
 * PreDraw:
 *--------*/
void PreDraw(void)
{
}
/*--------------------------------------------------------------- PostDraw
* PostDraw: 3D�̃V�[���ɏd�˂�2D�̏���\������֐�
*--------*/
void PostDraw(void)
{
	//������`�悷��R�[�h�ꎮ�Ȃ�
	//���C�e�B���O�Ȃ�
	//2D�̏����
	//2D�̓��e�ϊ���ݒ肷��i���s���e�j
	glMatrixMode(GL_PROJECTION);//���e�ϊ��}�g���N�X�ҏW���[�h
	glLoadIdentity();//������
	glOrtho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0); //��ʑS�̂�0.0�`1.0�͈̔͂ɐݒ�
	glMatrixMode(GL_MODELVIEW);//���f�����O�ϊ��}�g���N�X���[�h
	glLoadIdentity();//������

	//���D���ɕ`��
	char time_message[32];
	sprintf(time_message, "time = %d", simdata.time );
	glColor3f( 1.0, 1.0, 1.0 );
	drawString(0.1, 0.1, 0.0, 1.0, 1.0, time_message );

}
/**/
/*---------------------------------------------------------------- DrawScene
 * DrawScene:
 *--------*/
void DrawScene( void )
{
	for( int i = 0; i < N_TARGET; i++ ){

		if( !simdata.TargetList[i].detected ) continue;

		glPushMatrix();
		{
			glTranslatef( simdata.TargetList[i].pos.x,
				simdata.TargetList[i].pos.y,
				simdata.TargetList[i].pos.z );

			glRotatef( simdata.TargetList[i].ori.angle,
				simdata.TargetList[i].ori.x,
				simdata.TargetList[i].ori.y,
				simdata.TargetList[i].ori.z );
				
			switch( i ){/////�^�[�Q�b�g�p
			case 0://////////PageOne200-202//target:1
				applyMaterialColor(1.0, 0.0, 1.0);
				glutSolidCube(0.1);
				break;
			case 1://////////PageTwo203-205//target:2
				applyMaterialColor(0.0, 1.0, 0.0);
				glutSolidCube(0.1);

				break;
			case 2:
				applyMaterialColor(0.0, 0.0, 1.0);
				glutSolidCube(0.1);

				break;
			case 3:
				applyMaterialColor(1.0, 1.0, 1.0);
				glutSolidCube(0.1);

				break;
			case 4:
				
				break;
			case 5:
				
				break;
			case 6:
				break;
			case 7:
				
				break;
			case 8:
				
				break;
			case 9:

				break;
			case 10:

				break;
			case 11:

				break;
			case 12:

				break;
			case 13:

				break;
			case 14:

				break;
			default:
				break;

			}
		}
		glPopMatrix();
	}
}