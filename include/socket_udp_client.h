#ifndef SOCKET_UDP_CLIENT_H
#define SOCKET_UDP_CLIENT_H

#include <stdio.h>

#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

int InitSocketClient();
int ReleaseSocketClient();

void SendTo(unsigned char* data, size_t len, char* server, int port);
void RecvFrom(unsigned char* buffer, int* plen, char** ppaddr, int* pport);

#endif