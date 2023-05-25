#ifndef SERVER_CONN_MAN_H
#define SERVER_CONN_MAN_H
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
class serverConnectionManager
{
private:
    WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];
public:

   

    serverConnectionManager();
    ~serverConnectionManager();
    int initializeServer();
    int initializeSocket();
    int bindToSocket();
    int listenToConnections();
    int acceptIncomingConnections();
    int sendData(char* data);
    int closeSocket();
    int receiveData();
};






#endif