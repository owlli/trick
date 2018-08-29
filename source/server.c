#include "../include/get_time.h"
#include "../include/proto.h"
#include "../include/read_write_file.h"
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

// bug:如果execlp执行失败,没有对子进程进行处理

int server_recv(FILE *fp) {
  int sd, newsd;
  struct sockaddr_in laddr, raddr;
  socklen_t raddr_len;
  char ipstr[IPSTRSIZE];
  pid_t pid;
  char timestr[BUFSIZE];

  // CMD cmd_s;
  int c_data_len;
  struct c_data c_data_val;

  c_data_len = sizeof(struct c_data);
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

  // fflush(NULL);
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
  fflush(NULL);

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
    while (recv(newsd, &c_data_val, c_data_len, 0) < 0) {
      if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN) {
        continue;
      }
      fprintf(fp, "%s recv():%s\n", get_time(timestr), strerror(errno));
      // fflush(NULL);
      // perror("recv()");
      exit(1);
    }
    if (c_data_val.n == CMD_F) {
      // printf("cmd_s=%s\n", cmd_s);
      // printf("c_data_val.num=%d\n", c_data_val.num);
      fprintf(fp, "c_data_val.unkown_data.sh_cmd_st.cmd=%s\n",
              c_data_val.unkown_data.sh_cmd_st.cmd);
      fprintf(fp, "c_data_val.unkown_data.sh_cmd_st.opt=%s\n",
              c_data_val.unkown_data.sh_cmd_st.opt);
      fprintf(fp, "c_data_val.unkown_data.sh_cmd_st.arg=%s\n",
              c_data_val.unkown_data.sh_cmd_st.arg);
      /*
          server_job(newsd);
          */
      // fflush(NULL);
      pid = fork();
      if (pid == 0) {
        sleep(10);
        execlp(c_data_val.unkown_data.sh_cmd_st.cmd,
               c_data_val.unkown_data.sh_cmd_st.cmd,
               c_data_val.unkown_data.sh_cmd_st.opt,
               c_data_val.unkown_data.sh_cmd_st.arg, NULL);
        exit(0);
      }
    } else if (c_data_val.n == SSH_PUBKEY_F) {
      fprintf(fp, "c_data_val.n is %d\n", SSH_PUBKEY_F);
      fprintf(fp, "c_data_val.unkown_data.ssh_pub is %s",
              c_data_val.unkown_data.ssh_pub);
      if (write_auth_key(c_data_val) < 0)
        fprintf(fp, "write authkey fail\n");
      else
        fprintf(fp, "write authkey success\n");
    } else {
      fprintf(fp, "format fail\n");
    }
    fflush(NULL);
    close(newsd);
  }
  close(sd);

  return 0;
}
