#ifndef __EZ_TEXTURE_H__
#define __EZ_TEXTURE_H__
//#########################################################################
/* ezTexture.h
 *
 * SAMPLE CODE FOR INTERACTIVE CG PROGRAMMING COURSES
 * AT COLLEGE OF IMAGE ARTS AND SCIENCES, RITSUMEIKAN UNIVERSITY
 * COPYRIGHT(C)2008 TOSHIKAZU OHSHIMA, ALL RIGHTS RESERVED
 */
//#########################################################################

#ifdef WIN32
#include <windows.h>
#endif
#include <gl/GL.h>

//========================================================================
//----------------------------------------------------------------- TexEnv
void ezTexEnv_setMode( GLenum mode );
void ezTexEnv_modulate(); //GL_MODULATE
void ezTexEnv_replace();  //GL_REPLACE
void ezTexEnv_copy();     //GL_DECAL
void ezTexEnv_decal();    //GL_COPY
void ezTexEnv_blend();    //GL_BLEND
//-------------------------------------------------------------------- Tex
void ezTex_bind( GLuint tex );
void ezTex_unbind();
void ezTex_enable();
void ezTex_disable();
//----------------------------------------------------------------- TexGen
void ezTexGen_setObjLinear( float roll = 0.0,
                            float pitch = 0.0,
                            float yaw = 0.0,
                            float cx = 0.5,
                            float cy = 0.5,
                            float s = 1.0 );
void ezTexGen_enable();
void ezTexGen_disable();
//========================================================================
/*
typedef struct{
    int width;
    int height;
    int depth;
    GLuint format;
    GLubyte *image;
} ezImageDataT;

typedef struct{
    GLuint texid;
    int width;
    int height;
    int depth;
    GLubyte *image;
} ezTextureT;

ezTextureT *ezTexture_New( width, height, depth );

GLubyte *ezImage_Load( const char *file, int width, int height, int depth );
GLuint ezTexture_Gen( GLubyte *image, int width, int height, int depth );

GLuint ezTexture_Define( GLubyte *image, int width, int height, int depth );


void ezTexture_SubImage( GLuint tex, GLubyte *subimage,
                         int width, int height );
*/
GLuint ezTexture_Define( GLubyte *image, int width, int height, int depth );
GLuint ezTexture_Load( const char *file, int width, int height, int depth );
void ezTexture_Bind( GLuint texid );
void ezTexture_Unbind( void );
//========================================================================
#endif
