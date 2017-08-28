#include "socket.h"

int socket_fd = -1;
struct sockaddr_in addr;

int InitSocketClient(int* pPort, char* ip)
{
  sturct timeval timeout = {4, 0};
  
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd == -1)
  {
    printf("Create socket error.\n");
    return 1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(*pPort);
  addr.sin_addr.s_addr = inet_addr(ip);
  bzero(&(addr.sin_zero), 8);

  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));
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

void SendTo(unsigned char* data, size_t len, unsigned char* server, int port)
{
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(server);
  bzero(&(addr.sin_zero), 8);

  sendto(socket_fd, data, len, 0, (struct sockaddr*)&addr, sizeof(addr));
}

void RecvFrom(unsigned char* buffer, size_t* plen, char** ppaddr, int* precvport, int port)
{
  int recvlen = recvfrom(sock_fd, buffer, sizof(buffer), 0, &addr, &addr_len);
  *ppaddr = inet_ntoa(addr.sin_addr);
  *precvport = addr.sin_port;
}