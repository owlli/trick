#include "../include/client.h"
#include "../include/proto.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int client_send(struct sh_cmd sh_cmd_st, const char *ip) {
  int sd;
  struct sockaddr_in raddr;
  char ip_v[IPSTRSIZE] = {"\0"};
  // CMD cmd_s;

  strncpy(ip_v, ip, IPSTRSIZE);
  // memcpy(cmd_s, cmd, BUFSIZE);
  int sh_cmd_len;
  struct sh_cmd sh_cmd_val = sh_cmd_st;

  sh_cmd_len = sizeof(struct sh_cmd);
  /*    sh_cmd_val.num = 1;
      memcpy(&sh_cmd_val.cmd, "cmd", sizeof("cmd"));
      memcpy(&sh_cmd_val.opt, "opt", sizeof("opt"));
      memcpy(&sh_cmd_val.arg, "arg", sizeof("arg"));*/

  //创建socket ,使用tcp协议
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if (sd < 0) {
    perror("socket()");
    exit(1);
  }

  //构建服务器地址信息
  raddr.sin_family = AF_INET;
  raddr.sin_port = htons(atoi(SERVERPORT));
  inet_pton(AF_INET, ip_v, &raddr.sin_addr);

  //连接到服务器
  if (connect(sd, (void *)&raddr, sizeof(raddr)) < 0) {
    perror("connect()");
    exit(1);
  }

  //发送数据
  if (send(sd, &sh_cmd_val, sh_cmd_len, 0) < 0) {
    perror("send()");
    exit(1);
  }

  return 0;
}
