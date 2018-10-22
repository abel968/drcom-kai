#ifndef PACKAGE_H
#define PACKAGE_H

#include <string.h>
#include "utils.h"
#include "md5.h"



unsigned char* Pack_str1(int* plen, int ran);

unsigned char* Pack_str2(int* plen, unsigned char* salt, char* host_ip, char* hostname, char* dns, char* username, char* password, unsigned char* mac);

unsigned char* Pack_str3(int* plen, unsigned char* salt, unsigned char* tail, unsigned char* password);

unsigned char* Pack_str4(int* plen, char* host_ip, unsigned int num, unsigned int* pran, unsigned char* tail, unsigned int type, unsigned int first);
#endif