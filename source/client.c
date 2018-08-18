#include "../include/proto.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int sd;
  struct sockaddr_in raddr;

  int sh_cmd_len;
  struct sh_cmd sh_cmd_val;

  //判断参数个数是否满足
  if (argc < 2) {
    fprintf(stderr, "Usage...\n");
    exit(1);
  }

  sh_cmd_len = sizeof(struct sh_cmd);
  sh_cmd_val.num = 1;
  memcpy(&sh_cmd_val.cmd, "cmd", sizeof("cmd"));
  memcpy(&sh_cmd_val.opt, "opt", sizeof("opt"));
  memcpy(&sh_cmd_val.arg, "arg", sizeof("arg"));

  //创建socket ,使用tcp协议
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if (sd < 0) {
    perror("socket()");
    exit(1);
  }

  //构建服务器地址信息
  raddr.sin_family = AF_INET;
  raddr.sin_port = htons(atoi(SERVERPORT));
  inet_pton(AF_INET, argv[1], &raddr.sin_addr);

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
