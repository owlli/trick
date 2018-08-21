#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	fp=fopen("/tmp/trick","a");
	fprintf(fp,"sldjaljf\n");
	fclose(fp);
	return 0;
}
