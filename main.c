#include <stdio.h>
#include "./include/surprise.h"
#include <stdlib.h>

int main()
{
	printf("start\n");
	FILE *fp;
	char *l=NULL;
	long ln=1024;
	fp=fopen("/etc/tkexample","r");
	printf("open success\n");
	getline(&l,&ln,fp);
	printf("l=%s\n",l);


	printf("end\n");
}
