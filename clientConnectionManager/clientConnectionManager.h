
#ifndef CLIENT_CONN_MAN_H
#define CLIENT_CONN_MAN_H

#include <stdio.h>
#include <winsock2.h>
#include "../partidaUsuario.h"
#define SERVER_IP "127.0.0.1"


class clientConnectionManager
{
private:
    
    WSADATA wsaData;
    
    struct sockaddr_in server;
    
public:
    PartidaUsuario* partidaUsuario;
    char sendBuff[512], recvBuff[512];
    SOCKET s;
    clientConnectionManager(/* args */);
    ~clientConnectionManager();

    int initializeConnection();
    int initializeSocket(int puertoJugador);
    int connectToServer();
    int sendData(int type, char* data);
    int closeSocket();
};





#endif