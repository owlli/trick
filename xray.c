#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>



#define SFILE		"/etc/example"
#define DFILE		"/home/lzh/SURPRISED"
#define LINESIZE	1024

static void alrm_sa(int s,siginfo_t *infop,void *unused)
{
	if(infop->si_code != SI_KERNEL)
		return ;

	unsigned long ln = LINESIZE;
	FILE *df,*sf;
	sf = fopen(SFILE,"r");
	df = fopen(DFILE,"w+");
	int i,n;
	char *l;
	srand(time(NULL));
	int x;

	n = rand() % 5;
//	printf("n = %d\n",n);

	for(i = 0;i < n;i++)
	{
		x = getline(&l,&ln,sf);
//		printf("ln = %ld\n",ln);
//		printf("x = %d\n",x);
//		printf("l = %s\n",l);

		//memset(l,0,LINESIZE);
	}
//	printf("finish for\n");
	x = getline(&l,&ln,sf);

//		printf("l = %s\n",l);
	fwrite(l,1,x,df);

	fclose(sf);
	fclose(df);

}


int main()
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		do
		{
		setsid();
		struct itimerval itv;
		itv.it_interval.tv_sec = 5;
		itv.it_interval.tv_usec = 0;
		itv.it_value.tv_sec = 5;
		itv.it_value.tv_usec = 0;
		if(setitimer(ITIMER_REAL,&itv,NULL) < 0)
		{
			perror("setitimer()");
			exit(1);
		}

		struct sigaction sa,oldsa;
		sa.sa_sigaction = alrm_sa;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGALRM,&sa,&oldsa);
		pause();
		}while(1);
//	printf("end \n");

	exit(0);
	}

}
