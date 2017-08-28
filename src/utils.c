#include "utils.h"

time_t GetTime()
{
  time_t h;
  time(&h);
  return h;
}

void InitRandom()
{
  srand((int)time(0));
}

int GetRandInt(int low, int high)
{
  return low + (int)(rand() * (double)(high - low) / (RAND_MAX + 1.0f));
}

void ipstr2byte(char* ipaddr, unsigned char* ipbyte)
{
  size_t len = strlen(ipaddr);
  char buffer[4];
  memset(buffer, 0, 4);
  int n = 0;
  int c = 0;
  for (size_t i = 0; i < len; i++)
  {
    if (ipaddr[i] != '.')
    {
      buffer[n++] = ipaddr[i];
    }
    else
    {
      ipbyte[c++] = (unsigned char)atoi(buffer);
      memset(buffer, 0, 4);
      n = 0;
    }
  }
  ipbyte[c] = (unsigned char)atoi(buffer);
}

unsigned char ror(unsigned char* md5, char* password)
{
  unsigned int x;
  unsigned char ret = 0;
  for (size_t i = 0; i < strlen(password); i++)
  {
    x = md5[i] ^ password[i];
    ret += (unsigned char)(((x << 3) & 0xff) + (x >> 5));
  }
  return ret;
}

void checksum(unsigned char* ret, unsigned char* str, size_t len)
{
  unsigned long long t = 1234;
  unsigned int x = 0;
  for (size_t i = 0; i < len; i += 4)
  {
    x = str[i] | str[i + 1] << 8 | str[i + 2] << 16 | str[i + 3] << 24;
    t ^= x;
    t = (1968 * t) & 0xffffffff;
  }
  *ret++ = (unsigned char)(t & 0xff);
  *ret++ = (unsigned char)((t >> 8) & 0xff);
  *ret++ = (unsigned char)((t >> 16) & 0xff);
  *ret++ = (unsigned char)((t >> 24) & 0xff);
}