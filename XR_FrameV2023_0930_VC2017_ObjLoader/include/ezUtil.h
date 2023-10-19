#ifndef __EZ_UTIL_H__
#define __EZ_UTIL_H__
/*===========================================================================*/
/* OpenGL Misc Utility Functions
 *
 * This code is provided for non-profit and personal learning use
 * without any guarantee for results of the use.
 * Any comercial reuse of this material is prohibited.
 * Under the condition, this code can be redistributed as is.
 * Copyright (C) 2014 Toshikazu Ohshima, All Rights Reserved.
 */
/*
#if defined _WIN64 || defined _WIN32
#include <windows.h>
#endif

#include <gl/GL.h>
*/


/* draws stroke fonts using GLUT.
 * x, y: position on XY-plane in 3d-world coordinates
 * string: text string to be drawn
 * glut_stroke_font:
 * GLUT_STROKE_ROMAN
 * GLUT_STROKE_MONO_ROMAN
 */
//----------------------------------------------------------------------- ezUtil
/*--------*/
void ezUtil_drawGrid( int n, float range );
/* draws grid on XY-plane.
 * n: number of grid lines for X and Y axis
 * range: grid is drawn in area [-range, range]
 */
/*--------*/
void ezUtil_drawAxes( float l );
/* draws XYZ axes with RED, GREEN and BLUE for each axis.
 * l: length of axis to be drawn
 */
void ezUtil_drawCircle( float r, int n, bool fill );
void ezUtil_drawScale( float r, int n, int axis, float offset, int mode );
/*--------*/
void ezUtil_makeStars( int n, float range );
/* makes stars as OpenGL display list.
 * n: number of stars
 * range: stars are drawn in area [-range, range]
 */
/*--------*/
void ezUtil_drawStars();
/* draws stars made with makeStars
 */
/*--------*/
void ezUtil_transform( float x, float y, float z,
                       float roll, float pitch, float yaw );
/* makes transform matrix - Rz(roll)Rx(pitch)Ry(yaw)T(x,y,z)
 */
/*--------*/
void ezUtil_inverse( float x, float y, float z,
                     float roll, float pitch, float yaw );
/* makes transform matrix - T(-x,-y,-z)Ry(-yaw)Rx(-pitch)Rz(-roll)
 */
/*--------*/
void ezUtil_transform( float *pos, float *rot );
/* makes transform matrix - Rz(roll)Rx(pitch)Ry(yaw)T(x,y,z)
 */
/*--------*/
void ezUtil_inverse( float *pos, float *rot );
/* makes transform matrix - T(-x,-y,-z)Ry(-yaw)Rx(-pitch)Rz(-roll)
 */
/*--------*/
void ezUtil_postMultInv( float *base_pos, float *base_rot,
	float *target_pos, float *target_rot,
	float *out_pos, float *out_rot );
/* makes multiply inverse matrix and matrix - Mb-1*Mt
 */
//////// MREAL orientation version
void ezUtil_postMultInv2( float *base_pos, float *base_rot,
	float *target_pos, float *target_rot,
	float *out_pos, float *out_rot );

/*--------*/
void ezUtil_Mult( float *base_pos, float *base_rot,
	float *target_pos, float *target_rot,
	float *out_pos, float *out_rot );
//////// MREAL orientation version
void ezUtil_Mult2( float *base_pos, float *base_ori,
	float *target_pos, float *target_rot,
	float *out_pos, float *out_rot );

/*--------*/
void ezUtil_getRot( const float matrix[],
                           float *roll, float *pitch, float *yaw );
void ezUtil_getRot( const float matrix[], float *rot );
/* extracts rotation, (*roll,*pitch,*yaw), from matrix
 */
/*--------*/
void ezUtil_getPos( const float matrix[], float *x, float *y, float *z );
void ezUtil_getPos( const float matrix[], float *pos );
/* extracts position, (*x,*y,*z), from matrix
 */

//#include "ezTexture.h"

//==============================================================================
#endif
