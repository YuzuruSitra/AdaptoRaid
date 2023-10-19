#ifndef __TCPFUNC_H__
#define __TCPFUNC_H__

#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define PORTNUM 10001

typedef struct{
	WSADATA WSAData;//winsock������
	SOCKET sock;//�\�P�b�g

	sockaddr_in addr;//�A�h���X�Ƃ�

	//�T�[�o�p�f�[�^
	sockaddr_in client;
	SOCKET newSock;

	//����
	void *data_recv;//��M�p�\���̎w��
	void *data_send;//���M�p�\���̎w��

	int datasize_recv;//��M�p�\���̂̃f�[�^�T�C�Y
	int datasize_send;//���M�p�\���̂̃f�[�^�T�C�Y

	bool v_flag;

	bool server;

}TCPDataT;

//�����ݒ�
int initTCPServ(TCPDataT *tcpdata);//�T�[�o�[��������
int ConnectTCPServ(TCPDataT *tcpdata);//�T�[�o�[���ڑ��҂�
int initTCPClient(TCPDataT *tcpdata, char *hostname);//�N���C�A���g��������
int ConnectTCPClient(TCPDataT *tcpdata);//�N���C�A���g���ڑ��҂�
//�ʐM
int TCPSend(TCPDataT *tcpdata);//�f�[�^���M
int TCPRecv(TCPDataT *tcpdata);//�f�[�^��M


//�I������ 
void termTCP(SOCKET *sock);

#endif //__TCPFUNC_H__
