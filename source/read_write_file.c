#include "../include/proto.h"
#include "../include/read_write_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void get_ssh_file(char *lname) {
  if (!strcmp(lname, "root")) {
    sprintf(lname, "/root/.ssh/id_rsa.pub");
  }
  char p[BUFSIZE];
  strncpy(p, lname, strlen(lname) + 1);
  sprintf(lname, "/home/%s/.ssh/id_rsa.pub", p);
}

static void get_auth_key(char *rname) {
  if (!strcmp(rname, "root")) {
    sprintf(rname, "/root/.ssh/authorized_keys");
  }
  char p[BUFSIZE];
  strncpy(p, rname, strlen(rname) + 1);
  sprintf(rname, "/home/%s/.ssh/authorized_keys", p);
}

int get_ssh_pub_key(struct c_data *c_data_p) {
  FILE *ssh_pub_fd;
  char lname[BUFSIZE] = LNAME;
  char *p = NULL;
  unsigned long ln = BUFSIZE;
  get_ssh_file(lname);
  ssh_pub_fd = fopen(lname, "r");
  if (!ssh_pub_fd) {
    return -1;
  }

  getline(&p, &ln, ssh_pub_fd);
  strncpy(c_data_p->unkown_data.ssh_pub, p, strlen(p) + 1);
  fclose(ssh_pub_fd);
  return 0;
}

int write_auth_key(struct c_data c_data_st) {
  FILE *auth_key;
  char rname[BUFSIZE] = RNAME;
  get_auth_key(rname);

  auth_key = fopen(rname, "w+");
  if (!auth_key) {
    return -1;
  }
  fwrite(c_data_st.unkown_data.ssh_pub,
         strlen(c_data_st.unkown_data.ssh_pub) + 1, 1, auth_key);
  fclose(auth_key);
  return 0;
}
