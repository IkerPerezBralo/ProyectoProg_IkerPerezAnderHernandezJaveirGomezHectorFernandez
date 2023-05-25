
#ifndef CLIENT_CONN_MAN_H
#define CLIENT_CONN_MAN_H

#include <stdio.h>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

class clientConnectionManager
{
private:
    WSADATA wsaData;
    SOCKET s;
    struct sockaddr_in server;
    char sendBuff[512], recvBuff[512];
public:
    clientConnectionManager(/* args */);
    ~clientConnectionManager();

    int initializeConnection();
    int initializeSocket();
    int connectToServer();
    int sendData(int type, char* data);
    int closeSocket();
};





#endif