#include "./include/client_daemon.h"
#include "./include/get_time.h"
#include "./include/proto.h"
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int rec_server_ip(FILE *fp) {
  int sd;
  struct sockaddr_in laddr, raddr;
  socklen_t raddr_len;
  struct server_ip sp;
  char timestr[BUFSIZE];

  sd = socket(AF_INET, SOCK_DGRAM, 0 /*IPPROTO_UDP*/);
  if (sd < 0) {
    fprintf(fp, "%s socket():%s\n", get_time(timestr), strerror(errno));
    return -1;
  }

  laddr.sin_family = AF_INET;
  laddr.sin_port = htons(atoi(CLIENTPORT));
  inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
  if (bind(sd, (void *)&laddr, sizeof(laddr)) < 0) {
    fprintf(fp, "%s bind():%s\n", get_time(timestr), strerror(errno));
    return -1;
  }
  while (1) {
    fprintf(fp, "%s start recvfrom\n", get_time(timestr));
    if (recvfrom(sd, &sp, sizeof(sp), 0, (void *)&raddr, &raddr_len) < 0) {
      fprintf(fp, "%s recvfrom:%s\n", get_time(timestr), strerror(errno));
      continue;
    }
    fprintf(fp, "%s recvfrom success\n", get_time(timestr));
    fprintf(fp, "%s server_ip is %s\n", get_time(timestr), sp.s_p);
    fflush(NULL);
    //    inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
    //    printf("------MESSAGE FROM:%s:%d-------\n", ipstr,
    //    ntohs(raddr.sin_port));
  }

  close(sd);

  exit(0);

  return 0;
}

int main() {
  //  printf("start client_daemon\n");
  pid_t pid;
  //创建客户端守护进程来获得服务器端ip
  fflush(NULL);
  pid = fork();
  if (pid == 0) {
    //    printf("entry client_daemon children process\n");
    setsid();
    FILE *fp;
    fp = fopen(SAVE_SIP, "a");
    rec_server_ip(fp);
    exit(0);
  }
  sleep(1);
  return 0;
}
