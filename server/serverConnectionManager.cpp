#include "serverConnectionManager.h"



serverConnectionManager::serverConnectionManager()
{
	
}

serverConnectionManager::~serverConnectionManager()
{
}

int serverConnectionManager::initializeServer()
{
    printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
    printf("Initialised.");
    return 0;
}
int serverConnectionManager::initializeSocket()
{
    if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
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
int serverConnectionManager::bindToSocket()
{   
    if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Bind done.\n");
    return 0;
}
int serverConnectionManager::listenToConnections()
{
    if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
    return 0;
}
int serverConnectionManager::acceptIncomingConnections()
{
    printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));
	int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
            printf("Receiving match name: \n");
			printf("NAME RECEIVED:\n \t %s \n", recvBuff);
        
        }
    return 0;

}
int serverConnectionManager::sendData(char* data)
{

}
int serverConnectionManager::closeSocket()
{
    closesocket(conn_socket);
    return 0;
}
int serverConnectionManager::receiveData()
{
    do
    {
    int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
            printf("Receiving message... \n");
			printf("DATA RECEIVED:\n \t %s \n", recvBuff);
        
        }
        
    } while (1);
    return 0;
}

int main(int argc, char const *argv[])
{
    serverConnectionManager SCM = serverConnectionManager();
    SCM.initializeServer();
    SCM.initializeSocket();
    SCM.bindToSocket();
    SCM.listenToConnections();
    SCM.acceptIncomingConnections();
    SCM.receiveData();
    SCM.closeSocket();
    return 0;
}




