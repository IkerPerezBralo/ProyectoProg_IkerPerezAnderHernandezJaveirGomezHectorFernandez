#ifndef SERVER_CONN_MAN_H
#define SERVER_CONN_MAN_H
#include<stdio.h>
#include<winsock2.h>
#include"..\partida.h"
#pragma comment(lib,"ws2_32.lib")
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT_1 6000
#define SERVER_PORT_2 6001
#define SERVER_INFOPORT 6002
class serverConnectionManager
{
private:
    Partida* partida;
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
    int initializeSocket(int puerto);
    int bindToSocket();
    int listenToConnections();
    int acceptIncomingConnections();
    int sendData(char* data);
    int closeSocket();
    int receiveData();
    
};






#endif