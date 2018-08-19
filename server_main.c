#include "./include/proto.h"
#include "./include/server.h"
#include "./include/surprise.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    setsid();
    FILE *fp;
    fp = fopen(LOG, "a");

    server_recv(fp);
  }

  pid = fork();
  fflush(NULL);
  if (pid == 0) {
    setsid();
    printf("start surprise\n");
    surprise();
    printf("end surprise\n");
  }

  printf("success\n");
  sleep(200);
  return 0;
}
