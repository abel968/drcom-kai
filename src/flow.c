#include "flow.h"

void login(
  __OUT__ unsigned char* tail,
  __OUT__ unsigned char* salt,
  __IN__  char* host_ip,
  __IN__  char* hostname,
  __IN__  char* dns,
  __IN__  char* username,
  __IN__  char* password,
  __IN__  char* server
)
{
  int len;
  int i = 0;
  while (1)
  {
    challenge(salt, server, GetTime() + GetRandInt(0x0f, 0xff));
    unsigned char* data = Pack_str2(&len, salt, host_ip, hostname, dns, username, password, mac);
    SendTo(data, len, server, 61440);
    unsigned char buffer[1024];
    RecvFrom(buffer, &len, &addr, &port);
    if (strcmp(addr, server) == 0 && port == 61440)
    {
      if (buffer[0] == 0x04)
      {
        printf("Loged in.\n");
        break;
      }
      else
      {
        printf("Login failed.\n");
        sleep(3);
      }
    }
    else if (i >= 5)
    {
      printf("exception occured.\n");
      exit(1);
    }
    else
    {
      i++;
    }
  }
  memcpy(tail, buffer + 23, 16);
  return;
}

void challenge(
  __OUT__ unsigned char* salt, // [4]
  __IN__  char* server,
  __IN__  int ran
)
{
  unsigned char* data;
  unsigned char buffer[1024];
  char* addr[20];
  int port = 0;
  size_t len;
  while (1)
  {
    data = Pack_str1(&len, ran);
    SendTo(data, len, server, 61440);
    RecvFrom(buffer, &len, &addr, &port);
    if (strcmp(addr, server) == 0 && port == 61440)
      break;
    else
      continue;
  }
  if (buffer[0] != 0x02)
  {
    printf("Challenge error.\n");
    return;
  }
  memcpy(salt, buffer + 4, 4);
}

void empty_socket_buffer()
{
  unsigned char buffer[1024];
  char* addr[20];
  while (1)
  {
    RecvFrom(buffer, &len, &addr, &port);
  }
}