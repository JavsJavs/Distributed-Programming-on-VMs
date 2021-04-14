#ifndef  _UTILSH
#define  _UTILSH

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>


int initServer(int port);
int initClient(char* host, int port);
int waitForConnections(int sock_fd);
void sendMSG(int socket, const void* data, int dataLen);
void recvMSG(int socket, void** data, int* dataLen);
void closeConnection(int socket_fd);

#endif
