#ifndef __EZ_TRACK_H__
#define __EZ_TRACK_H__
/*===========================================================================*/
/* OpenGL TRACK Utility Functions
 *
 * This code is provided for non-profit and personal learning use
 * without any guarantee for results of the use.
 * Any commercial reuse of this material is prohibited.
 * Under the condition, this code can be redistributed as is.
 * Copyright (C) 2014 Toshikazu Ohshima, All Rights Reserved.
 */

#include "platform.h"

const int _n_tracks = 24;

typedef struct{
    int id;
    float x, y, z;
    float roll, pitch, yaw;
	char name[16];
} ezTrackDataT;

typedef struct{
	ezTrackDataT data[ _n_tracks ];
} ezTrackArrayT;

#ifdef PLATFORM_WINDOWS
#include "igSharedMemoryT.h"
#endif

class ezTracker{
  public:
	ezTracker( bool use = true );
	~ezTracker();
	void init();
	bool open( char *key, bool w );
	void read();
	void write();
	void close();
	void setPos( int i, float x, float y, float z );
	void setRot( int i, float roll, float pitch, float yaw );
	void setName( int i, const char *name );
	void setID( int i, int id );	
	ezTrackDataT *getTrackData( int i );
	ezTrackDataT *getTrackData( const char *name );
	ezTrackArrayT *getTrackArray();
	void setTrackData( int i, ezTrackDataT *trackdata );
  private:
	ezTrackArrayT trackarray;
	int n_tracks;
#ifdef PLATFORM_WINDOWS
	iglib::igSharedMemoryT<ezTrackArrayT> *trackshm;
#else
	void *trackshm;
#endif
	bool use;
};

void ezTrack_getPos( ezTrackDataT *track, float *pos );
void ezTrack_getRot( ezTrackDataT *track, float *rot );

void ezTrack_xformBase( ezTrackDataT *base, ezTrackDataT *target, float *pos, float *rot );

/*---------------------------------------------------------------------------*/

/*===========================================================================*/
#endif //__EZ_TRACK_H__
