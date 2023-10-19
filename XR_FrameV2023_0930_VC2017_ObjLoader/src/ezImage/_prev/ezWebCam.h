#include <stdlib.h>

//-------- VIDEO INPUT FUNCTIONS --------
int ezWebCam_Open(int cam, int wx, int wy, double fps = 30.0, int device=-1, int mstype=-1);
void ezWebCam_GetImage( int cam, unsigned char *buffer );
int ezWebCam_Close(int cam);
