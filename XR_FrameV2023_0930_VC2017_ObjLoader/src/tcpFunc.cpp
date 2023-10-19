#include "tcpFunc.h"
#include <stdio.h>
//�����ݒ�
/*------------------------------------------------------
initTCPServ
*/
//�T�[�o�[��������

int initTCPServ(TCPDataT *tcpdata)
{
	WORD VersionRequired;
	VersionRequired = MAKEWORD(2, 2);
	if(WSAStartup(VersionRequired, &tcpdata->WSAData) != 0)
	{
		printf("WSAStartup err\n");
		return -1;
	}

	tcpdata->sock = socket(AF_INET, SOCK_STREAM, 0);
	if(tcpdata->sock == INVALID_SOCKET)
	{
		printf("socket err\n");
		return -1;
	}

	tcpdata->server = true;

	memset(&tcpdata->addr, 0, sizeof(tcpdata->addr));
	tcpdata->addr.sin_family = AF_INET;
	tcpdata->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	tcpdata->addr.sin_port = htons(PORTNUM);
	bind(tcpdata->sock, (struct sockaddr *)&tcpdata->addr, sizeof(tcpdata->addr));

	return 0;
}
/*------------------------------------------------------
ConnectTCPServ
*/
//�T�[�o�[���ڑ��҂�
int ConnectTCPServ(TCPDataT *tcpdata)
{
	printf("�N���C�A���g�̐ڑ���҂��Ă��܂�\n");
	if(listen(tcpdata->sock, 5) != 0)
	{
		printf("listen err\n");
		return -1;
	}

	int len = sizeof(tcpdata->client);
	tcpdata->newSock = accept(tcpdata->sock, (struct sockaddr *)&tcpdata->client, &len);
	closesocket(tcpdata->sock);
	if(tcpdata->newSock == INVALID_SOCKET)
	{
		printf("new socket err\n");
		return -1;
	}
	printf("�N���C�A���g�Ƃ̐ڑ����������܂���\n");
	return 0;
}
/*------------------------------------------------------
initTCPClient
*/
//�N���C�A���g��������
int initTCPClient(TCPDataT *tcpdata, char *hostname)
{
	WORD VersionRequired;
	VersionRequired = MAKEWORD(2, 2);
	if(WSAStartup(VersionRequired, &tcpdata->WSAData) != 0)
	{
		printf("WSAStartup err\n");
		return -1;
	}

	tcpdata->sock = socket(AF_INET, SOCK_STREAM, 0);
	if(tcpdata->sock == INVALID_SOCKET)
	{
		printf("socket err\n");
		return -1;
	}

	tcpdata->server = false;

	memset(&tcpdata->addr, 0, sizeof(tcpdata->addr));
	tcpdata->addr.sin_family = AF_INET;
	tcpdata->addr.sin_addr.s_addr = inet_addr(hostname);
	tcpdata->addr.sin_port = htons(PORTNUM);
	return 0;
}
/*------------------------------------------------------
ConnectTCPClient
*/
//�N���C�A���g���ڑ��҂�
int ConnectTCPClient(TCPDataT *tcpdata)
{
	printf("�T�[�o�[�ɐڑ����܂�\n");
	int ret;
	for(int i = 0;i < 10;i++)
	{
		ret = connect(tcpdata->sock, (struct sockaddr *)&tcpdata->addr, sizeof(tcpdata->addr));
		if(ret == 0)
			break;
		printf("�ڑ��ł��܂���B�Đڑ����܂�\n");
		Sleep(2000);//2�b�҂�
	}
	if(ret != 0)
	{
		printf("connect err\n");
		closesocket(tcpdata->sock);
		WSACleanup();
		return -1;
	}
	printf("�T�[�o�[�ɐڑ��ł��܂���\n");
	return 0;
}
/*------------------------------------------------------
TCPSend
*/
//���M����

int TCPSend(TCPDataT *tcpdata)
{
	int ret = 0;
	int total = 0;

	if(tcpdata->v_flag)printf("���M�J�n\n");

	if( tcpdata->server ){
		do{
			ret = sendto(tcpdata->newSock, (char *)tcpdata->data_send, tcpdata->datasize_send, 0, 
				(struct sockaddr *)&tcpdata->addr, sizeof(tcpdata->addr));

			if( ret == SOCKET_ERROR )
			{
				perror( "TCPSend err" );
				return -1;
			}
			if(tcpdata->v_flag) printf("sent size = %d\n", ret );
			total += ret;
		}
		while( total < tcpdata->datasize_send );

	}
	else{

		do{
			ret = sendto( tcpdata->sock, (char *)tcpdata->data_send, tcpdata->datasize_send, 0, 
				(struct sockaddr *)&tcpdata->addr, sizeof(tcpdata->addr) );

			if( ret == SOCKET_ERROR )
			{
				perror( "TCPSend err" );
				return -1;
			}
			if(tcpdata->v_flag) printf("sent size = %d\n", ret );
			total += ret;
			if( total < tcpdata->datasize_send && tcpdata->v_flag)
				printf("SendLESS\n");
		}
		while( total < tcpdata->datasize_send );

	}

	return 0;
}

/*------------------------------------------------------
TCPRecv
*/
//��M����
int TCPRecv(TCPDataT *tcpdata)
{
	int n = sizeof(tcpdata->addr);
	int ret = 0;
	int total = 0;

	static int loop_count = 0;

	if( tcpdata->v_flag) printf( "LOOP COUNT: %d\n", loop_count ); 

	if(tcpdata->v_flag) printf("��M��҂��Ă��܂�\n");
	//
	if( tcpdata->server ){
		do{
			ret = recvfrom( tcpdata->newSock, (char*)tcpdata->data_recv,
				tcpdata->datasize_recv
				, 0, (struct sockaddr *)&tcpdata->addr, &n);

			if( ret == SOCKET_ERROR ){
				perror( "TCPRecv" );
				return -1;
			}
			if(tcpdata->v_flag) printf("recv size = %d\n", ret );
			total += ret;
			if( total < tcpdata->datasize_recv && tcpdata->v_flag)
				printf("RecvLESS\n");
		}
		while( total < tcpdata->datasize_recv );
	}
	else{
		do{
			ret = recvfrom(tcpdata->sock, &((char *)tcpdata->data_recv)[total], 
				tcpdata->datasize_recv-total, 0, (struct sockaddr *)&tcpdata->addr, &n);

			if( ret == SOCKET_ERROR ){
				perror( "TCPRecv" );
				return -1;
			}
			if(tcpdata->v_flag) printf("recv size = %d\n", ret );
			total += ret;
			if( total < tcpdata->datasize_recv && tcpdata->v_flag)
				printf("RecvLESS\n");
		}
		while( total < tcpdata->datasize_recv );
	}

	loop_count++;
	return 0;
}

void termTCP(SOCKET *sock)
{
	closesocket(*sock);
	WSACleanup();
	return;
}

