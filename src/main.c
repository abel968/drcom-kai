#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "socket_udp_client.h"
#include "flow.h"
#include "utils.h"

extern int socket_fd;
extern struct sockaddr_in addr;

int main()
{
  int pid = 0;
  if (pid = fork())
  {
    exit(0);
  }
  else if (pid < 0)
  {
    exit(1);
  }
  setsid();
  if (pid = fork())
  {
    exit(0);
  }
  else if (pid < 0)
  {
    exit(1);
  }
  for (int i = 0; i < NOFILE; i++)
  {
    close(i);
  }
  chdir("/tmp");
  umask(0);
  // -----config-----
  char* server_ip = "10.100.61.3";
  char* username = "baiyz16";
  char* password = "SOSYUKIN333";
  char* host_ip = "49.140.185.83";
  //unsigned char mac[] = {0xf0, 0xb4, 0x29, 0xee, 0x19, 0xe5};
  unsigned char mac[] = {0xa0, 0x63, 0x91, 0x2d, 0xe9, 0x5a};
  char* host_name = "DESKTOP";
  char* host_os = "Windows 10";
  char* primary_dns = "10.10.10.10";
  // -----config-----
  // -----init-----
  InitRandom();
  InitSocketClient();
  printf("Drcom-kai ver0.1 started.\n");
  unsigned char package_tail[1];
  unsigned char salt[4];
  // -----init-----
  // -----run-----
  while (1)
  {
    if (!login(package_tail, salt, host_ip, host_name, primary_dns, username, password, server_ip, mac))
    {
      printf("[main] login failed, try again.\n");
      continue;
    }
    empty_socket_buffer();
    if (keep_alive1(salt, package_tail, password, server_ip))
    {
      printf("[keep_alive1] success.\n");
    }
    keep_alive2(salt, package_tail, password, server_ip, host_ip);
    break;
  }
  ReleaseSocketClient();
  return 0;
}