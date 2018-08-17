#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

//文件源
#define SFILE "/etc/example"
//输出文件
#define DFILE "/home/lzh/SURPRISED"
#define LINESIZE 1024

static void alrm_sa(int s, siginfo_t *infop, void *unused) {
  if (infop->si_code != SI_KERNEL)
    return;
  return;
}

int main() {
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    //将子进程变为守护进程
    setsid();
    //设置定时器,5秒后产生信号,循环时间为5秒
    struct itimerval itv;
    itv.it_interval.tv_sec = 5;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 5;
    itv.it_value.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &itv, NULL) < 0) {
      perror("setitimer()");
      exit(1);
    }
    //
    struct sigaction sa, oldsa;
    sa.sa_sigaction = alrm_sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGALRM, &sa, &oldsa);
    do {
      pause();
      unsigned long ln = LINESIZE;
      FILE *df, *sf;
      sf = fopen(SFILE, "r");
      if (sf < 0)
        continue;
      df = fopen(DFILE, "w+");
      if (df < 0)
        continue;
      int n;
      char *l;
      srand(time(NULL));
      int x;
      n = rand() % 5;
      //	printf("n = %d\n",n);

      do {
        x = getline(&l, &ln, sf);
        n--;
      } while (n > 0);

      //		printf("l = %s\n",l);
      fwrite(l, 1, x, df);

      fclose(sf);
      fclose(df);
    } while (1);
    //	printf("end \n");

    sigaction(SIGALRM, &oldsa, NULL);
    exit(0);
  }
}
