#ifndef __EZ_FONT_H__
#define __EZ_FONT_H__
//##############################################################################
/* ezFont.h
 *
 * SAMPLE CODE FOR INTERACTIVE CG PROGRAMMING COURSES
 * AT COLLEGE OF IMAGE ARTS AND SCIENCES, RITSUMEIKAN UNIVERSITY
 * COPYRIGHT(C)2008 TOSHIKAZU OHSHIMA, ALL RIGHTS RESERVED
 */
//##############################################################################

#include <GL/glut.h>

//----------------------------------------------------------------------- ezFont
/* ezFont_* : GRAPHIC TEXT UTILITY FUNCTIONS
 */
/*--------*/
GLuint ezFont_makeBitmap( void );
/* makes display-list for OpenGL bitmap fonts.
 */
/*--------*/
void ezFont_drawBitmap( float x, float y, char *string );
/* draws bitmap fonts made with makeBitmap.
 * x, y: raster position in window coordinates
 * string: text string to be drawn
 */
/*--------*/
void ezFont_drawGlutBitmap( float x, float y, char *string,
                            void *glut_bitmap_font );
/* draws bitmap fonts using GLUT.
 * x, y: raster position in window coordinates
 * string: text string to be drawn
 * glut_bitmap_font:
 * GLUT_BITMAP_8_BY_13: Fixed-8x13
 * GLUT_BITMAP_9_BY_15: Fixed-9x15
 * GLUT_BITMAP_TIMES_ROMAN_10: Times-Roman-10
 * GLUT_BITMAP_TIMES_ROMAN_24: Times-Roman-24
 * GLUT_BITMAP_HELVETICA_10: Helvetica-10
 * GLUT_BITMAP_HELVETICA_12: Helvetica-12
 * GLUT_BITMAP_HELVETICA_18: Helvetica-18
 */
/*--------*/
void ezFont_drawGlutStroke( float x, float y, float z,
                            char *string,
                            float xs = 1.0, float ys = 1.0,
                            void *glut_stroke_font = GLUT_STROKE_MONO_ROMAN
);
/* draws stroke fonts using GLUT.
 * x, y: position on XY-plane in 3d-world coordinates
 * string: text string to be drawn
 * font:
 * GLUT_STROKE_ROMAN
 * GLUT_STROKE_MONO_ROMAN
 */
//==============================================================================
#endif
