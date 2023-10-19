#pragma once

#include <stdio.h>
#define _WINSOCKAPI_
#include <windows.h>

#define  _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

#include <GL/gl.h>
#include <GL/glu.h>

#include "resource.h"

void setLight();
void dispCone( GLUquadric* Cylinder, GLdouble radius, GLdouble height, 
	GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f );
BOOL InitApp( HINSTANCE hInstance, LPSTR className );
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND InitInstance ( HINSTANCE hInstance, LPSTR className ,int nCmdShow );
void initOpenGL( HWND hWnd );
void setLight();
BOOL setPixelFormat( HDC hdc );
void dispFunc ();
void finalizeOpenGL( HWND hWnd );
void keyPress( HWND hWnd, WPARAM wParam );
BOOL initMrPlatform( void );
void releaseMrPlatform( void );
void dispCylinder ( GLUquadric* Cylinder, GLdouble radius, GLdouble height, 
	GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f );
