#include "./include/client.h"
#include "./include/parse.h"
#include "./include/proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*struct sh_cmd ct_sh_cmd(const char *string) {
  char *s = (char *)string;
  struct sh_cmd sh_cmd_st;

  return sh_cmd_st;
}*/

struct sh_cmd sh_cmd_st;

int main(int argc, char *argv[]) {
  int ch, i;
  char ip_v[IPSTRSIZE] = {'\0'};
  CMD cmd_s = {'\0'};

  while (1) {
    ch = getopt(argc, argv, "r:c:s");
    if (ch < 0)
      break;

    switch (ch) {
    //获得服务器ip
    case 'r':
      strncpy(ip_v, optarg, IPSTRSIZE);
      break;
    //获得shell命令
    case 'c':
      strncpy(cmd_s, optarg, CMDSIZE);
      break;
    //调用ssh
    case 's':
      break;
    //异常选项处理
    case '?':
      break;
    }
  }
  printf("cmd_s=%s\n", cmd_s);
  printf("ip_v=%s\n", ip_v);

  i = parse_sh_cmd(&sh_cmd_st, cmd_s);
  if (i < 0) {
    if (i == CMD_TOOLANG)
      printf("cmd too lang\n");
    if (i == OPT_TOOLANG)
      printf("opt too lang\n");
    if (i == ARG_TOOLANG)
      printf("arg too lang\n");
    if (i == CMD_NULL)
      printf("cmd is null\n");
    if (i == ARG_ERR)
      printf("format err,format look like \"cmd -opt arg\"\n");
    return -1;
  }

  client_send(sh_cmd_st, ip_v);

  //需要添加服务器端是否执行成功的功能

  return 0;
}
