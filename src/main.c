#include <stdio.h>


#include "socket.h"
#include "utils.h"

extern int socket_fd;
extern struct sockaddr_in addr;

int main()
{
  InitRandom();
  int port = 61440;
  char* ip = "127.0.0.1";
  unsigned char message[100];
  printf("Drcom-kai ver0.1\n");
  // InitSocketClient(&port, ip);
  // while (1)
  // {
  //   scanf("%s", message);
  //   printf("input = %s\n", message);
  //   sendto(socket_fd, message, sizeof(message), 0, (struct sockaddr*)&addr, sizeof(addr));
  //   if (strcmp(message,"stop") == 0)
  //   {
  //     printf("client will stop.\n");
  //     break;
  //   }
  // }
  // ReleaseSocketClient();
  //memcpy(message, ip, 5);
  //ipstr2byte("59.72.109.147", message);
  unsigned char* p = message;
  //p += 100;
  //int cc = (int)(p - message);
  unsigned char str[] = {0x01, 0x02, 0x03, 0x04};
  int x = str[0] |
          str[1] << 8 |
          str[2] << 16 |
          str[3] << 24;
  *p++ = (unsigned char)(x & 0xff);
  *p++ = (unsigned char)((x >> 8) & 0xff);
  *p++ = (unsigned char)((x >> 16) & 0xff);
  *p++ = (unsigned char)((x >> 24) & 0xff);
  return 0;
}