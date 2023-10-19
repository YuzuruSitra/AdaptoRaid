#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define BAUD_RATE		9600
#define BYTE_SIZE		8
//#define PARITY			EVENPARITY
#define PARITY			NOPARITY
#define STOP_BIT		TRUE
#define F_PARITY		ONESTOPBIT

//HANDLE hComm;									// �V���A���|�[�g�Ƃ̒ʐM�n���h��
//------------------------------------------------------------------------------------------------
HANDLE ComInit(char* comport)
{
	HANDLE hComm;
	// �V���A���|�[�g���J����
	hComm = CreateFile(
		comport,					/* �V���A���|�[�g�̕����� */
		GENERIC_READ | GENERIC_WRITE,	/* �A�N�Z�X���[�h�F�ǂݏ��� */
		0,								/* ���L���[�h�F������̓A�N�Z�X�s�� */
		NULL,							/* �Z�L�����e�B�����F�n���h���p������ */
		OPEN_EXISTING,					/* �쐬�t���O�F */
		FILE_ATTRIBUTE_NORMAL,			/* �����F */
		NULL							/* �e���v���[�g�̃n���h���F */
	);
	printf("COMPORT = %s\n", comport);
	if (hComm == INVALID_HANDLE_VALUE) {
		printf("�V���A���|�[�g���J�����Ƃ��o���܂���ł����B\n");
		return hComm;
	}
	printf("�V���A���|�[�g���J���܂����B\n");

	// �ʐM������ݒ肷��
	DCB dcb;
	GetCommState(hComm, &dcb); /* DCB ���擾 */
	dcb.BaudRate = BAUD_RATE;
	dcb.ByteSize = BYTE_SIZE;
	dcb.Parity = PARITY;
	dcb.fParity = STOP_BIT;
	dcb.StopBits = F_PARITY;
	SetCommState(hComm, &dcb); /* DCB ��ݒ� */

	return hComm;
}
//---------------------------------------------------------------------------------------------
void ComEnd(HANDLE hComm)
{
	// �n���h�������
	CloseHandle(hComm);
}
//----------------------------------------------------------------------------------------------
bool WriteData(HANDLE hComm, char* buff, unsigned int data_size)
{
	DWORD dwWritten; /* �|�[�g�֏������񂾃o�C�g�� */
	WriteFile(hComm, buff, data_size, &dwWritten, NULL);

	if (dwWritten != data_size) {
		printf("�f�[�^�̑��M�Ɏ��s���܂����B\n");
		return false;
	}
	return true;
}
//----------------------------------------------------------------------------------------------
int ReadData(HANDLE hComm, char* buff, unsigned int nread, unsigned int max_size)
{
	DWORD dwErrors;  /* �G���[��� */
	COMSTAT ComStat; /* �f�o�C�X�̏�� */
	DWORD dwCount;   /* ��M�f�[�^�̃o�C�g�� */
	DWORD dwRead;    /* �|�[�g����ǂݏo�����o�C�g�� */

	ClearCommError(hComm, &dwErrors, &ComStat);
	dwCount = ComStat.cbInQue;
	if (dwCount > max_size) { //��M�f�[�^�̃o�C�g�����ő吔�����傫���ꍇ
		//printf("�o�b�t�@�T�C�Y������܂���B\n");
		//return -1;
	}
	int status;
	status = ReadFile(hComm, buff, nread, &dwRead, NULL);

	//if (dwCount != dwRead) { //��M�f�[�^�̃o�C�g���ƃ|�[�g����ǂݏo�����o�C�g������v���Ȃ��ꍇ
	if (nread != dwRead) {
		printf("�f�[�^�̎󂯎��Ɏ��s���܂����B\n");
		return -1;
	}
	return dwRead; //����ɍs���΃|�[�g����ǂݏo�����o�C�g����Ԃ�
}

bool SendAnalogData(HANDLE hComm, int ch, int value)
{
	char data[2];
	data[0] = ch;
	data[1] = value;
	return WriteData(hComm, data, 2);
}
