#include "../include/proto.h"
#include "../include/surprise.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static void alrm_sa(int s, siginfo_t *infop, void *unused) {
  if (infop->si_code != SI_KERNEL)
    return;
  return;
}

void surprise() {
  // printf("enter surprise\n");

  //设置定时器,10秒后产生信号,循环时间为600秒
  struct itimerval itv;
  itv.it_interval.tv_sec = 10;
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
    unsigned long ln = BUFSIZE;
    FILE *df, *sf;
    sf = fopen(SFILE, "r");
    if (sf < 0)
      continue;
    // printf("open %s success\n", SFILE);
    df = fopen(DFILE, "w+");
    if (df < 0)
      continue;
    // printf("open %s success\n", DFILE);
    int n;
    char *l = NULL;
    srand(time(NULL));
    int x;
    n = rand() % 5;
    // printf("n = %d\n", n);

    do {
      x = getline(&l, &ln, sf);
      // printf("l = %s\n", l);
      n--;
    } while (n > 0);

    // printf("l = %s\n", l);
    fwrite(l, x, 1, df);
    // printf("write success\n");
    fclose(sf);
    fclose(df);
  } while (1);
  //	printf("end \n");

  sigaction(SIGALRM, &oldsa, NULL);
  exit(0);
}
