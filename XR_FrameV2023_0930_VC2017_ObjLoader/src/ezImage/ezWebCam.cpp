#include <stdlib.h>
#include "ezWebCam.h"

#include "ewclib/ewclib.h"
//�ȈՃJ�������̓��C�u����EWCLIB�̃C���N���[�h
//http://insubaru.g1.xrea.com/ewclib/index.html

void ezWebCam_GetFormat( char *devicename )
{
	//int EWC_GetFormat(char *devicename, ewc_format *fmt, int *nmax);
	int nmax = 256;
	ewc_format f[256];
	int n_cams;

	n_cams = EWC_GetFormat( devicename, f, &nmax);
	printf( ">>> %s\n", devicename );
	//�t�H�[�}�b�g�ꗗ�̕\��
    for(int i=0; i<nmax; i++){
        printf("%d: %dx%d(%d) %I64d %f[fps] %s\n",
               i, f[i].width, f[i].height, f[i].bit, 
			   f[i].AvgTimePerFrame, f[i].fps, f[i].subtype_t);
    }
}

//=============================================================================
// EWCLIB�����b�s���O��ewclib.h���B�؂�����
//-----------------------------------------------------------------------------
int ezWebCam_Open( int cam, int wx, int wy, double fps, int device, int mstype )
{
	GUID guidmstype;
	int status;
	if( mstype == -1 ) guidmstype = MEDIASUBTYPE_RGB24; //32
	else guidmstype = EWC_TYPE;

	status = EWC_Open( cam, wx, wy, fps, device, guidmstype );
	if( status != 0 )
	{
	    char s[160];
		EWC_GetLastMessage(s,sizeof(s));
		printf("%s\n",s);
		printf("[ezWebCam] EWC_Open Error %d\n", status);
	}
	EWC_PropertyPage( cam ); // �J�����v���p�e�B���J��
	printf("[ezWebCam] BufferSize: %d\n", EWC_GetBufferSize( cam ));
	//printf("[ezwebCam] CameraNum: %d\n",  EWC_GetCamera());
	printf("[ezwebCam] DeviceName: %s\n", EWC_GetDeviceName( cam ));
	// �K�v�ȃo�b�t�@�T�C�Y�̎擾

	return status;
}
//�J�������w��o�[�W����
int ezWebCam_OpenName( int cam, char *devicename, int wx, int wy, double fps, int mstype)
{
	GUID guidmstype;
	int status;
	printf("OpenbyCameraName\nSetting Name: %s\n", devicename);
	if( mstype == -1 ) guidmstype = MEDIASUBTYPE_RGB24; //32
	else guidmstype  = EWC_TYPE;
	status = EWC_Open( cam, wx, wy, fps, devicename, guidmstype );
	if( status != 0 ) {
		printf("[ezWebCam] EWC_Open Error 0\n");
	}
	EWC_PropertyPage( cam ); // �J�����v���p�e�B���J��
	printf("[ezWebCam] BufferSize: %d\n", EWC_GetBufferSize( cam ));
	printf("[ezwebCam] GetDeviceName: %s\n", EWC_GetDeviceName( cam ));
	return status;
}
//-----------------------------------------------------------------------------
int ezWebCam_Close( int cam )
{
	return EWC_Close( cam );
}
//-----------------------------------------------------------------------------
void ezWebCam_GetImage( int cam, unsigned char *buffer )
{
	EWC_GetImage( cam, (void *)buffer );
	return;
}
//---------------------------------------------------------------
unsigned char *ezWebCam_image( int cam )
{
	unsigned char *buf;
	EWC_GetBuffer( cam, (void **)(&buf) );
	return buf;
}
//-------------------------------------------------------------
void ezWebCam_setBuffer( int camID, unsigned char *buffer )
{
	EWC_SetBuffer( camID, (void *)buffer );
}
//-------------------------------------------------------------
unsigned char *ezWebCam_getBuffer( int camID )
{
	unsigned char *p;
	EWC_GetBuffer( camID, (void **)&p );
	return p;
}
//-------------------------------------------------------------
bool ezWebCam_isCaptured( int camID )
{
	return (bool)EWC_IsCaptured( camID );
}

