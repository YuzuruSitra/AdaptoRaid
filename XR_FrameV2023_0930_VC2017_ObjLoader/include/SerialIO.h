#ifndef _SerialIO_h_
#define _SerialIO_h_

HANDLE ComInit(char* comport);
void ComEnd(HANDLE hComm);
int ReadData(HANDLE hComm, char* buff, unsigned int nread, unsigned int max_size);
bool WriteData(HANDLE hComm, char* buff, unsigned int data_size);
bool SendAnalogData(HANDLE hComm, int ch, int value);

#endif