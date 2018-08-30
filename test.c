#include <stdio.h>
#include <string.h>
void get_ssh_file(char *lname) {
  if (!strcmp(lname, "root")) {
    sprintf(lname, "/root/.ssh/id_rsa.pub");
  }
  int i = (int)strlen(lname);
  char p[20];
  strncpy(p, lname, i + 1);
  // printf("sizeof(lname)=%d\n", (int)sizeof(lname));
  sprintf(lname, "/home/%s/.ssh/id_rsa.pub", p);
}
int main() {
  char p[40] = "lizhiheng";
  //	sprintf(p,"haha");
  //	strncpy(p,"haha",3);
  get_ssh_file(p);

  printf("p=%s\n", p);
}
