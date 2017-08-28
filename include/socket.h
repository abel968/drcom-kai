#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>

#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>



int InitSocketClient(int* pPort, char* ip);
int ReleaseSocketClient();

void SendTo(unsigned char* data, size_t len, unsigned char* server, int port);
void RecvFrom(unsigned char* buffer, size_t* plen, char** ppaddr, int* precvport, int port);
#endif