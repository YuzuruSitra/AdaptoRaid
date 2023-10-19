#ifndef __EZ_TEXTURE_H__
#define __EZ_TEXTURE_H__
/*===========================================================================*/
/* OpenGL Texture Utility Functions
 *
 * This code is provided for non-profit and personal learning use
 * without any guarantee for results of the use.
 * Any comercial reuse of this material is prohibited.
 * Under the condition, this code can be redistributed as is.
 * Copyright (C) 2014 Toshikazu Ohshima, All Rights Reserved.
 */
#include "..\platform.h"
/*
//-------------------------------------------------------- object management
ezTextureT *ezTexture_new();
void ezTexture_delete( ezTextureT *tex );
*/
void ezTex_bind( GLuint texid );
void ezTex_unbind( void );

GLubyte *ezTex_load( int width, int height, GLuint pixformat, GLubyte *image, const char *file = NULL );
GLuint ezTex_create( int width, int height, GLuint pixformat, GLubyte *image = NULL );
void ezTex_subimage( int width, int height, GLuint pixformat, GLubyte *image, GLuint texid );

//GLubyte *ezTex_alloc( int width, int height, GLuint pixformat );

GLuint ezTex_makeMesh( void );
void ezTex_drawMesh( GLuint texID, GLuint meshID );

/*---------------------------------------------------------------------------*/
void ezTexEnv_Modulate( void ); //GL_MODULATE
void ezTexEnv_Replace( void );  //GL_REPLACE
void ezTexEnv_Copy( void );     //GL_COPY
void ezTexEnv_Decal( void );    //GL_DECAL
void ezTexEnv_Blend( void );    //GL_BLEND
/*===========================================================================*/
#endif //__EZ_TEXTURE_H__
