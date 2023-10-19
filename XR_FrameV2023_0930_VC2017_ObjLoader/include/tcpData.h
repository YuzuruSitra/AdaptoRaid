#ifndef __TCPDATA_H__
#define __TCPDATA_H__

//width * height * rgba


#define N_COLORSIZE 1228800

#define N_DEPTHSIZE 307200

#define KINECT_WIDTH 640
#define KINECT_HEIGHT 480

//-------- Send data
typedef struct {

	unsigned char color[ N_COLORSIZE ];
    unsigned short depth[ N_DEPTHSIZE ];

} DownDataT;

//-------- Recv data
typedef struct {

	float x,y,z;
	float roll, pitch,yaw;

} UpDataT;

#endif //__TCPDATA_H__