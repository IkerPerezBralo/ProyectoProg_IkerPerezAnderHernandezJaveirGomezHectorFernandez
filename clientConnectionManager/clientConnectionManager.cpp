#include "clientConnectionManager.h"
#include <string.h>

#include <iostream>
using namespace std;
#ifndef USUARIO_H_

#endif

clientConnectionManager::clientConnectionManager()
{

}
clientConnectionManager::~clientConnectionManager()
{
    
}


 int  clientConnectionManager::initializeConnection()
    {
        
        printf("\nInitialising Winsock...\n");
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            printf("Failed. Error Code : %d", WSAGetLastError());
            return -1;
        }

        printf("Initialised.\n");
        return 0;
    }

int clientConnectionManager::initializeSocket()
{
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
    return 0;

}
int clientConnectionManager::connectToServer()
{
    if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));
    
    return 0;
}
int clientConnectionManager::sendData(int type, char* data)
{
    sprintf(sendBuff, "%d-%s", type, data);
    send(s, sendBuff, sizeof(sendBuff), 0);
    cout<<sendBuff<<endl; 
   
    return 0;
}
int clientConnectionManager::closeSocket()
{
    closesocket(s);
	WSACleanup();
}