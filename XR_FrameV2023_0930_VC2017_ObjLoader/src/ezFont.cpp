//##############################################################################
/* ezUtil.cpp
 * 
 * SAMPLE CODE FOR INTERACTIVE CG PROGRAMMING COURSES
 * AT COLLEGE OF IMAGE ARTS AND SCIENCES, RITSUMEIKAN UNIVERSITY
 * COPYRIGHT(C)2008 TOSHIKAZU OHSHIMA, ALL RIGHTS RESERVED
 */
//##############################################################################

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "ezFont.h"
#include "font.h"

static GLuint _base;

//======================================================================= ezFont
//------------------------------------------------------------------- makeBitmap
/* makeBitmap: �t�H���g�I�u�W�F�N�g����������
 */
GLuint ezFont_makeBitmap( void )
{
    int i, n;

    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    _base = glGenLists(0x80);//�f�B�X�v���C���X�g�̈�� 128 �l��
    //�e�����̃r�b�g�}�b�v�f�[�^���e�f�B�X�v���C���X�g�Ɋ��蓖�Ă�
    n = 0;
    for( i = 0x20; i < 0x80; i++ ){
        glNewList( _base + i, GL_COMPILE );
        glBitmap( 8, 16, 0.0, 0.0, 9.0, 0.0, font[n++] );
        glEndList();
    }
    return _base;
}
//------------------------------------------------------------------- drawBitmap
/* drawBitmap: �r�b�g�}�b�v�t�H���g�ŕ������`�悷��
 */
void ezFont_drawBitmap( float x, float y, char *string )
{
    glPushAttrib( GL_LIST_BIT|GL_CURRENT_BIT );
    glRasterPos2f( x, y );//�`��ʒu�̐ݒ�
    //�����t�H���g�f�B�X�v���C���X�g�̊J�n�ʒu */
    glListBase( _base );
    //�f�B�X�v���C���X�g (������) ��`��
    glCallLists( strlen( string ), GL_UNSIGNED_BYTE, (unsigned char *)string );
    glPopAttrib();
    return;
}
//--------------------------------------------------------------- drawGlutBitmap
/* drawGlutBitmap: glut�r�b�g�}�b�v�t�H���g�ŕ������`�悷��
 */
void ezFont_drawGlutBitmap( float x, float y, char *string, void *font )
{
    glPushAttrib( GL_CURRENT_BIT );//���݂̃��X�^�[�|�W�V�����̕ۑ�
    glRasterPos2f( x, y );
    //�r�b�g�}�b�v������̕`��
    while( *string ){
        glutBitmapCharacter( font, *string++ );
    }
    glPopAttrib();//�ۑ��������X�^�[�|�W�V�����̃��[�h
    return;
}
//--------------------------------------------------------------- drawGlutStroke
/* drawGlutStroke
 */
void ezFont_drawGlutStroke( float x, float y, float z,
                            char *string,
                            float xscl, float yscl,
                            void *font )
{
    glPushMatrix();
    {
        glTranslatef( x, y, z );
        glScalef( xscl * 0.005, yscl * 0.005, 1.0 );
        //�X�g���[�N�t�H���g������̕`��
        while( *string ){
            glutStrokeCharacter( font, *string++ );
        }
    }
    glPopMatrix();
    return;
}
//==============================================================================
