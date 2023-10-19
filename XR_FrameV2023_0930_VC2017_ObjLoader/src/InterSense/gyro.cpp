#include "isense.h"
#include "Gyro.h"

static ISD_TRACKER_HANDLE     g_ISDhandle;		//!< �f�o�C�X�̃n���h��
static ISD_TRACKER_INFO_TYPE  g_ISDtracker;	//!< �g���b�J�[�̊e����(�o�[�W�����AFPS��)
static ISD_TRACKER_DATA_TYPE  g_ISDdata;		//!< �g���b�J�[���瓾������f�[�^(3���̌X��)
static ISD_STATION_INFO_TYPE  g_ISDstation;

static bool active = false;

void InitGyro(void)
{
	/*g_shareIC3Data.open(true);*/
	g_ISDhandle = ISD_OpenTracker(NULL, 0, FALSE, TRUE);

    ISD_GetStationConfig( g_ISDhandle, &g_ISDstation, 1, TRUE );
	g_ISDstation.Compass = 1; //�n���C�ɂ��␳��L����
	ISD_SetStationConfig( g_ISDhandle, &g_ISDstation, 1, TRUE );

	active = true;

	return;
}

void UpdateGyro( float rot[3] )
{
	if( !active ) return;

	ISD_GetData(g_ISDhandle, &g_ISDdata);
	ISD_GetCommInfo(g_ISDhandle, &g_ISDtracker);

	rot[0] =   - g_ISDdata.Station[0].Orientation[2];	//roll
	rot[1] =   g_ISDdata.Station[0].Orientation[1];		//pitch
	rot[2] =   - g_ISDdata.Station[0].Orientation[0];	//yaw

	return;
}

void ResetGyro( void )
{
	if( active ) ISD_ResetHeading( g_ISDhandle, (WORD)g_ISDstation.ID );
}

void TermGyro( void )
{
	if( active ) ISD_CloseTracker( g_ISDhandle );
	active = false;
}
