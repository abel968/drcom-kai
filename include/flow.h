#ifndef FLOW_H
#define FLOW_H
#define __IN__
#define __OUT__

#include "utils.h"
#include "package.h"
#include "socket_udp_client.h"

int login(
  __OUT__ unsigned char* tail,
  __OUT__ unsigned char* salt,
  __IN__  char* host_ip,
  __IN__  char* host_name,
  __IN__  char* dns,
  __IN__  char* username,
  __IN__  char* password,
  __IN__  char* server_ip,
  __IN__  unsigned char* mac
);

int challenge(
  __OUT__ unsigned char* salt, // [4]
  __IN__  char* server_ip,
  __IN__  int ran
);

void empty_socket_buffer();

int keep_alive1(
  __IN__  unsigned char* salt,
  __IN__  unsigned char* package_tail,
  __IN__  char* password,
  __IN__  char* server_ip
);

int keep_alive2(
  __IN__  unsigned char* salt,
  __IN__  unsigned char* package_tail,
  __IN__ char* password,
  __IN__ char* server_ip,
  __IN__ char* host_ip
);

#endif