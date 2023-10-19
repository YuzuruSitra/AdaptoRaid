//#include "ez/platform.h"
#include <stdio.h>

#include "ezWebCam.h"

#include "ewclib/ewclib.h"
//�ȈՃJ�������̓��C�u����EWCLIB�̃C���N���[�h

//=============================================================================
// EWCLIB�����b�s���O��ewclib.h���B�؂�����
//-----------------------------------------------------------------------------
int ezWebCam_Open( int cam, int wx, int wy, double fps, int device, int mstype )
{
	GUID guidmstype;
	int status;
	if( mstype == -1 ) guidmstype = MEDIASUBTYPE_RGB24; 
	else guidmstype = EWC_TYPE;
	status = EWC_Open( cam, wx, wy, fps, device, guidmstype );
	if( status != 0 ){
		printf("[ezWebCam] EWC_Open Error 0\n");
	}
	EWC_PropertyPage( cam ); // �J�����v���p�e�B���J��
	printf("[ezWebCam] BufferSize: %d\n", EWC_GetBufferSize( cam )); 
	// �K�v�ȃo�b�t�@�T�C�Y�̎擾

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
	EWC_GetImage( cam, buffer );
	return;
}

