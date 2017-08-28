#ifndef FLOW_H
#define FLOW_H
#define __IN__
#define __OUT__

#include "utils.h"
#include "package.h"
#include "socket.h"

void login(
  __OUT__ unsigned char* tail,
  __OUT__ unsigned char* salt,
  __IN__  char* host_ip,
  __IN__  char* hostname,
  __IN__  char* dns,
  __IN__  char* username,
  __IN__  char* password,
  __IN__  char* server
);

void challenge(
  __OUT__ unsigned char* salt, // [4]
  __IN__  char* server,
  __IN__  int ran
);

void empty_socket_buffer();

#endif