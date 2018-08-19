#include "../include/get_time.h"
#include "../include/proto.h"
#include "../include/server.h"
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int server_recv(FILE *fp) {
  int sd, newsd;
  struct sockaddr_in laddr, raddr;
  socklen_t raddr_len;
  char ipstr[IPSTRSIZE];
  pid_t pid;
  char timestr[BUFSIZE];

  // CMD cmd_s;
  int sh_cmd_len;
  struct sh_cmd sh_cmd_val;

  sh_cmd_len = sizeof(struct sh_cmd);
  //创建socket,使用tcp协议
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if (sd < 0) {
    // perror("socket()");
    fprintf(fp, "%s socket():%s\n", get_time(timestr), strerror(errno));
    exit(1);
  }

  //设置socket选项,进程退出时立即关闭此socket
  int val = 1;
  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
    fprintf(fp, "%s setsockopt():%s\n", get_time(timestr), strerror(errno));
    // perror("setsockopt()");
    exit(1);
  }

  //构建本地地址信息
  laddr.sin_family = AF_INET;
  laddr.sin_port = htons(atoi(SERVERPORT));
  inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

  //绑定,套接字与需要进行通信的地址建立联系
  if (bind(sd, (void *)&laddr, sizeof(laddr)) < 0) {
    fprintf(fp, "%s bind():%s\n", get_time(timestr), strerror(errno));
    // perror("bind()");
    exit(1);
  }

  //监听此socket
  if (listen(sd, 100) < 0) {
    fprintf(fp, "%s listen():%s\n", get_time(timestr), strerror(errno));
    // perror("listen()");
    exit(1);
  }

  //此处加打印监听成功的日志
  fprintf(fp, "%s listen success!\n", get_time(timestr));

  raddr_len = sizeof(raddr);

  while (1) {
    //阻塞等待客户端连接,newsd为用来通信的socket
    newsd = accept(sd, (void *)&raddr, &raddr_len);
    if (newsd < 0) {
      if (errno == EAGAIN || errno == EINTR)
        continue;
      fprintf(fp, "%s accept():%s\n", get_time(timestr), strerror(errno));
      // perror("accept()");
      exit(1);
    }

    //打印客户端地址和端口
    inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
    // printf("Client:%s:%d\n", ipstr, ntohs(raddr.sin_port));
    fprintf(fp, "%s accept success! Client:%s:%d\n", get_time(timestr), ipstr,
            ntohs(raddr.sin_port));
    //阻塞接受数据
    while (recv(newsd, &sh_cmd_val, sh_cmd_len, 0) < 0) {
      if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN) {
        continue;
      }
      fprintf(fp, "%s recv():%s\n", get_time(timestr), strerror(errno));
      // perror("recv()");
      exit(1);
    }

    // printf("cmd_s=%s\n", cmd_s);
    // printf("sh_cmd_val.num=%d\n", sh_cmd_val.num);
    fprintf(fp, "sh_cmd_val.cmd=%s\n", sh_cmd_val.cmd);
    fprintf(fp, "sh_cmd_val.opt=%s\n", sh_cmd_val.opt);
    fprintf(fp, "sh_cmd_val.arg=%s\n", sh_cmd_val.arg);
    /*
        server_job(newsd);
        */
    fflush(NULL);
    pid = fork();
    if (pid == 0) {
      sleep(10);
      execlp(sh_cmd_val.cmd, sh_cmd_val.cmd, sh_cmd_val.opt, sh_cmd_val.arg,
             NULL);
    }

    wait(NULL);
    close(newsd);
  }
  close(sd);

  return 0;
}
