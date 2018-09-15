#include "../include/search_client.h"
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

//获取客户端ip
int get_client_ip(char *buffer) {
  char sh[BUFSIZE];
  char *p = "nmap %s >/dev/null;cat /proc/net/arp|grep -i %s|awk '{print $1}'";
  snprintf(sh, BUFSIZE, p, IP_NETMASK, CMAC);
  // printf("%s\n", sh);
  FILE *fp = popen(sh, "r");
  // printf("fp success\n");
  int n = fread(buffer, 1, BUFSIZE, fp);
  // printf("buffer is %s\n", buffer);
  // printf("n=%d\n", n);
  pclose(fp);
  if (!n) {
    return -1;
  }

  return 0;
}

static void alrm_sa(int s, siginfo_t *infop, void *unused) {
  //  if (infop->si_code != SI_KERNEL)
  //    return;
  return;
}

//每隔20分钟扫描整个内网,如果发现客户端,向客户端发送本机ip
int send_myip() {
  struct server_ip sp;
  struct sockaddr_in raddr;
  int sd;
  //设置定时器,20分钟后产生信号,循环时间为20分钟
  struct itimerval itv;
  itv.it_interval.tv_sec = 1200;
  itv.it_interval.tv_usec = 0;
  itv.it_value.tv_sec = 10;
  itv.it_value.tv_usec = 0;
  if (setitimer(ITIMER_REAL, &itv, NULL) < 0) {
    perror("setitimer()");
    exit(1);
  }
  //设置信号处理函数
  struct sigaction sa, oldsa;
  sa.sa_sigaction = alrm_sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;
  sigaction(SIGALRM, &sa, &oldsa);
  // printf("start pause\n");
  do {
    pause();
    if (get_client_ip(sp.s_p) < 0)
      continue;
    // printf("start create socket\n");
    // printf("sp.s_p is %s\n", sp.s_p);
    sd = socket(AF_INET, SOCK_DGRAM, 0 /*IPPROTO_UDP*/);
    if (sd < 0) {
      continue;
    }
    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(CLIENTPORT));
    inet_pton(AF_INET, sp.s_p, &raddr.sin_addr);
    // inet_pton(AF_INET, "192.168.99.129", &raddr.sin_addr);

    if (sendto(sd, &sp, sizeof(sp), 0, (void *)&raddr, sizeof(raddr)) < 0) {
      close(sd);
      continue;
      // perror("sendto()");
      // return -1;
    }
    // printf("sendto success\n");
    close(sd);

  } while (1);
}
