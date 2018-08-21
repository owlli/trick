#include "./include/proto.h"
#include "./include/server.h"
#include "./include/surprise.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;

  pid = fork();
  if (pid == 0) {
    setsid();
    FILE *fp;
    fp = fopen(LOG, "w");
    fprintf(fp, "sdfasfdaf\n");
    fflush(NULL);
    server_recv(fp);
  }

  /*  pid = fork();
    if (pid == 0) {
      setsid();
      // printf("start surprise\n");
      surprise();
      exit(0);
    }*/
  sleep(2);
  // printf("success\n");
  // sleep(200);
  return 0;
}
