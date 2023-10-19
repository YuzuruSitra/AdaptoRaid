#ifndef PLATFORM_H
#define PLATFORM_H
//��platform.h�̂݁A���ނƂ���
//�u�C���N���[�h�K�[�h�\�L�v�̗�Ƃ��Ďc���Ă����܂�
//����ȊO�̃w�b�_�[�t�@�C���ł�
//#pragma once
//���g�����Ƃɂ��܂�
//-------- common
#define _USE_MATH_DEFINES

//-------- Microsoft Windows OS
#if defined _WIN64 || defined _WIN32

#if 1
#pragma comment(lib, "libjpeg.lib")
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "libpng16.lib")
#else
#pragma comment(lib, "vs2010\libjpeg.lib")
#pragma comment(lib, "vs2010\zlib.lib")
#pragma comment(lib, "vs2010\libpng16.lib")
#endif

//---- ignore annoying warnings
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#pragma warning(disable : 4334)
#define PLATFORM_WINDOWS
//----
#include <stdlib.h>
#include <stdio.h>
//#include <WinSock.h>
#include <WinSock2.h>
#include <windows.h>
#include <math.h>
#include "gl/glut.h"
#include "GL/glext.h"
//#define GL_GLEXT_PROTOTYPES
#include "config.h"
static inline void msleep( int msec ){ Sleep( msec ); }
#else 
//-------- Mac OS
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#define __OSX_AVAILABLE_STARTING(...)
#define __OSX_AVAILABLE_BUT_DEPRECATED_MSG(...)
//#include <stdlib.h>
//#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <GLUT/glut.h>
#define PLATFORM_MACOS
static inline void msleep( int msec ){ usleep( msec ); }
static inline void Sleep( int msec ){ msleep( msec ); }
#endif

#include "myShape.h"
//-------------------------
#endif
