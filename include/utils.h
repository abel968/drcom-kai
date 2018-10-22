#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

time_t GetTime();

void InitRandom();

int GetRandInt(int low, int high);

void ipstr2byte(char* ipaddr, unsigned char* ipbyte);

unsigned char ror(unsigned char* md5, char* password);

void checksum(unsigned char* ret, unsigned char* str, size_t len);

int StartWith(unsigned char* src, unsigned char* pattern, size_t len);

void HexLog(unsigned char* src, int len);

#endif