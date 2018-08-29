#include "./include/proto.h"
#include "./include/search_client.h"
#include "./include/server.h"
#include "./include/surprise.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;

  //  getchar();
  //  printf("server_main success\n");
  fflush(NULL);

  pid = fork();
  if (pid == 0) {
    //    printf("fork1 success\n");
    setsid();
    FILE *fp;
    fp = fopen(LOG, "a");
    fflush(NULL);
    server_recv(fp);
  }

  pid = fork();
  if (pid == 0) {
    //    printf("fork2 success\n");
    setsid();
    // printf("start surprise\n");
    surprise();
    exit(0);
  }

  pid = fork();
  if (pid == 0) {
    //    printf("fork3 success\n");
    setsid();
    send_myip();
    exit(0);
  }
  sleep(1);
  // printf("success\n");
  // sleep(200);
  return 0;
}
