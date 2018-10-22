#include "socket_udp_client.h"

int socket_fd = -1;
struct sockaddr_in addr;

int InitSocketClient()
{
  struct timeval timeout = {4, 0};
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd == -1)
  {
    printf("[InitSocketClient]sockfd_fd == -1\n");
    return 1;
  }
  setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));
  return 0;
}

int ReleaseSocketClient()
{
  if (socket_fd != -1)
  {
    close(socket_fd);
  }
  return 0;
}

void SendTo(unsigned char* data, size_t len, char* ip_server, int port)
{
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip_server);
  bzero(&(addr.sin_zero), 8);

  int info = sendto(socket_fd, data, len, 0, (struct sockaddr*)&addr, sizeof(addr));
}

void RecvFrom(unsigned char* buffer, int* plen, char** ppaddr, int* pport)
{
  int addr_len;
  *plen = recvfrom(socket_fd, buffer, *plen, 0/*MSG_DONTWAIT*/, (struct sockaddr*)&addr, (socklen_t*)&addr_len);
  *ppaddr = inet_ntoa(addr.sin_addr);
  *pport = ntohs(addr.sin_port);
}