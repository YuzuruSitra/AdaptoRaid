#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define BAUD_RATE		9600
#define BYTE_SIZE		8
//#define PARITY			EVENPARITY
#define PARITY			NOPARITY
#define STOP_BIT		TRUE
#define F_PARITY		ONESTOPBIT

//HANDLE hComm;									// シリアルポートとの通信ハンドル
//------------------------------------------------------------------------------------------------
HANDLE ComInit(char* comport)
{
	HANDLE hComm;
	// シリアルポートを開ける
	hComm = CreateFile(
		comport,					/* シリアルポートの文字列 */
		GENERIC_READ | GENERIC_WRITE,	/* アクセスモード：読み書き */
		0,								/* 共有モード：他からはアクセス不可 */
		NULL,							/* セキュリティ属性：ハンドル継承せず */
		OPEN_EXISTING,					/* 作成フラグ： */
		FILE_ATTRIBUTE_NORMAL,			/* 属性： */
		NULL							/* テンプレートのハンドル： */
	);
	printf("COMPORT = %s\n", comport);
	if (hComm == INVALID_HANDLE_VALUE) {
		printf("シリアルポートを開くことが出来ませんでした。\n");
		return hComm;
	}
	printf("シリアルポートを開きました。\n");

	// 通信属性を設定する
	DCB dcb;
	GetCommState(hComm, &dcb); /* DCB を取得 */
	dcb.BaudRate = BAUD_RATE;
	dcb.ByteSize = BYTE_SIZE;
	dcb.Parity = PARITY;
	dcb.fParity = STOP_BIT;
	dcb.StopBits = F_PARITY;
	SetCommState(hComm, &dcb); /* DCB を設定 */

	return hComm;
}
//---------------------------------------------------------------------------------------------
void ComEnd(HANDLE hComm)
{
	// ハンドルを閉じる
	CloseHandle(hComm);
}
//----------------------------------------------------------------------------------------------
bool WriteData(HANDLE hComm, char* buff, unsigned int data_size)
{
	DWORD dwWritten; /* ポートへ書き込んだバイト数 */
	WriteFile(hComm, buff, data_size, &dwWritten, NULL);

	if (dwWritten != data_size) {
		printf("データの送信に失敗しました。\n");
		return false;
	}
	return true;
}
//----------------------------------------------------------------------------------------------
int ReadData(HANDLE hComm, char* buff, unsigned int nread, unsigned int max_size)
{
	DWORD dwErrors;  /* エラー情報 */
	COMSTAT ComStat; /* デバイスの状態 */
	DWORD dwCount;   /* 受信データのバイト数 */
	DWORD dwRead;    /* ポートから読み出したバイト数 */

	ClearCommError(hComm, &dwErrors, &ComStat);
	dwCount = ComStat.cbInQue;
	if (dwCount > max_size) { //受信データのバイト数が最大数よりも大きい場合
		//printf("バッファサイズが足りません。\n");
		//return -1;
	}
	int status;
	status = ReadFile(hComm, buff, nread, &dwRead, NULL);

	//if (dwCount != dwRead) { //受信データのバイト数とポートから読み出したバイト数が一致しない場合
	if (nread != dwRead) {
		printf("データの受け取りに失敗しました。\n");
		return -1;
	}
	return dwRead; //正常に行けばポートから読み出したバイト数を返す
}

bool SendAnalogData(HANDLE hComm, int ch, int value)
{
	char data[2];
	data[0] = ch;
	data[1] = value;
	return WriteData(hComm, data, 2);
}
