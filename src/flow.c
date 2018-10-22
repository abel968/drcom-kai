#include "flow.h"

char* g_paddress = NULL;
int g_port = 0;
int g_len = 0;
unsigned char g_buffer[1024];

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
)
{
  // -----init-----
  int i = 0;
  unsigned char* data;
  while (1)
  {
    if (challenge(salt, server_ip, GetTime() + GetRandInt(0x0f, 0xff)))
    {
      printf("[login] Challenge success.\n");
    }
    //HexLog(salt, 4);
    data = Pack_str2(&g_len, salt, host_ip, host_name, dns, username, password, mac);
    //HexLog(data, g_len);
    printf("[login] Sending : %s:(%d)\n", server_ip, g_len);
    SendTo(data, g_len, server_ip, 61440);
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    if (strcmp(g_paddress, server_ip) == 0 && g_port == 61440)
    {
      if (g_buffer[0] == 0x04)
      {
        printf("[login] login success.\n");
        break;
      }
      else
      {
        printf("[login] login failed, try again.\n");
        sleep(3);
      }
    }
    else if (i >= 5)
    {
      printf("[login] Try 5 times but not right.\n");
      return 0;
    }
    else
    {
      printf("[login] Try again.\n");
      i++;
    }
  }
  memcpy(tail, g_buffer + 23, 16);
  return 1;
}

int challenge(
  __OUT__ unsigned char* salt, // [4]
  __IN__  char* server_ip,
  __IN__  int ran
)
{
  // -----init-----
  unsigned char* data;
  // -----send challenge-----
  while (1)
  {
    data = Pack_str1(&g_len, ran);
    printf("[challenge] Sending : %s:(%d)\n", server_ip, g_len);
    SendTo(data, g_len, server_ip, 61440);
    g_len = 1024;
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    printf("[challenge] Get result from %s:%d(%d)\n", g_paddress, g_port, g_len);
    if (strcmp(g_paddress, server_ip) == 0 && g_port == 61440)
    {
      printf("[challenge] Result is recieved from right address.\n");
      break;
    }
    else
    {
      printf("[challenge] Result is recieved from wrong address, try again.\n");
      sleep(3);
      continue;
    }
  }
  // -----check challenge result-----
  if (g_buffer[0] != 0x02)
  {
    printf("[challenge] data[0] != 0x02\n");
    return 0;
  }
  printf("[challenge] Checked green.\n");
  memcpy(salt, g_buffer + 4, 4);
  return 1;
}

void empty_socket_buffer()
{
  while (1)
  {
    g_len = 1024;
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    if (g_len == -1)
    {
      printf("[empty_socket_buffer] buffer empty.\n");
      break;
    }
  }
}

int keep_alive1(
  __IN__  unsigned char* salt,
  __IN__  unsigned char* package_tail,
  __IN__  char* password,
  __IN__  char* server_ip
)
{
  unsigned char* data = Pack_str3(&g_len, salt, package_tail, (unsigned char*)password);
  printf("[keep_alive1] Sending : %s:(%d)\n", server_ip, g_len);
  SendTo(data, g_len, server_ip, 61440);
  while (1)
  {
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    if (g_buffer[0] == 0x07)
    {
      printf("[keep_alive1] buffer[0] == 0x07.\n");
      break;
    }
  }
  return 1;
}

int keep_alive2(
  __IN__  unsigned char* salt,
  __IN__  unsigned char* package_tail,
  __IN__ char* password,
  __IN__ char* server_ip,
  __IN__ char* host_ip
)
{
  unsigned char tail[4] = {0x00, 0x00, 0x00, 0x00};
  int ran = GetRandInt(0, 0xffff);
  ran += GetRandInt(1, 10);
  unsigned char svr_num = 0;
  int check = 0;
  unsigned char* data = Pack_str4(&g_len, host_ip, svr_num, (unsigned int*)&ran, tail, 1, 1);
  printf("[keep_alive2] Recv 1.\n");
  while (1)
  {
    printf("[keep_alive2] Sending : %s:(%d)\n", server_ip, g_len);
    SendTo(data, g_len, server_ip, 61440);
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    unsigned char pattern[] = {0x07, 0x00, 0x28, 0x00};
    if (StartWith(g_buffer, pattern, 4))
    {
      printf("[keep_alive2] start with 1 ok.\n");
      break;
    }
    pattern[1] = svr_num;
    if (StartWith(g_buffer, pattern, 4))
    {
      printf("[keep_alive2] start with 2 ok.\n");
      break;
    }
    if (g_buffer[0] == 0x07 && g_buffer[2] == 0x10)
    {
      printf("[keep_alive2] try other pack.\n");
      svr_num++;
      data = Pack_str4(&g_len, host_ip, svr_num,  (unsigned int*)&ran,tail, 1, 0);
    }
    else
    {
      printf("[keep_alive2] Unexcepted.\n");
    }
  }

  printf("[keep_alive2] Recv 2.\n");
  ran += GetRandInt(1, 10);
  data = Pack_str4(&g_len, host_ip, svr_num,  (unsigned int*)&ran,tail, 1, 0);
  printf("[keep_alive2] Sending : %s:(%d)\n", server_ip, g_len);
  SendTo(data, g_len, server_ip, 61440);
  while (1)
  {
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    if (g_buffer[0] == 0x07)
    {
      printf("[keep_alive2] buffer[0] == 0x07\n");
      svr_num++;
      break;
    }
    else
    {
      printf("[keep_alive2] Unexcepted.\n");
    }
  }
  memcpy(tail, g_buffer + 16, 4);

  printf("[keep_alive2] Recv 3.\n");
  ran += GetRandInt(1, 10);
  data = Pack_str4(&g_len, host_ip, svr_num,  (unsigned int*)&ran,tail, 3, 0);
  printf("[keep_alive2] Sending : %s:(%d)\n", server_ip, g_len);
  SendTo(data, g_len, server_ip, 61440);
  while (1)
  {
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    if (g_buffer[0] == 0x07)
    {
      printf("[keep_alive2] buffer[0] == 0x07\n");
      svr_num++;
      break;
    }
    else
    {
      printf("[keep_alive2] Unexcepted.\n");
    }
  }
  memcpy(tail, g_buffer + 16, 4);

  unsigned char i = svr_num;
  while (1)
  {
    ran += GetRandInt(1, 10);
    data = Pack_str4(&g_len, host_ip, i,  (unsigned int*)&ran,tail, 1, 0);
    printf("[keep_alive2] Sending : %s:(%d)\n", server_ip, g_len);
    SendTo(data, g_len, server_ip, 61440);
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    memcpy(tail, g_buffer + 16, 4);

    ran += GetRandInt(1, 10);
    data = Pack_str4(&g_len, host_ip, i + 1,  (unsigned int*)&ran,tail, 3, 0);
    printf("[keep_alive2] Sending : %s:(%d)\n", server_ip, g_len);
    SendTo(data, g_len, server_ip, 61440);
    RecvFrom(g_buffer, &g_len, &g_paddress, &g_port);
    memcpy(tail, g_buffer + 16, 4);

    i = (i + 2) % 0xff;
    sleep(20);
    keep_alive1(salt, package_tail, password, server_ip);
  }
}