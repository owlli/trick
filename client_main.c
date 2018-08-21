#include "./include/client.h"
#include "./include/parse.h"
#include "./include/proto.h"
#include "./include/read_write_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//如果要将本地ssh公钥传送至服务器,必须要在本地通过rsa加密算法生成公钥

/*struct sh_cmd ct_sh_cmd(const char *string) {
  char *s = (char *)string;
  struct sh_cmd sh_cmd_st;

  return sh_cmd_st;
}*/

// struct sh_cmd sh_cmd_st;
struct c_data c_data_st;

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
      if (!optarg) {
        printf("format err,format look like \"cmd -opt arg\"\n");
        return -1;
      }
      strncpy(ip_v, optarg, IPSTRSIZE);
      break;
    //获得shell命令
    case 'c':
      if (!optarg) {
        printf("format err,format look like \"cmd -opt arg\"\n");
        return -1;
      }
      c_data_st.n = CMD_F;
      strncpy(cmd_s, optarg, CMDSIZE);
      break;
    //调用ssh
    case 's':
      c_data_st.n = SSH_PUBKEY_F;
      if (get_ssh_pub_key(&c_data_st) < 0) {
        printf("open ssh public key fail\n");
        return -1;
      }
      break;
    //异常选项处理
    case '?':
      break;
    }
  }
  if (c_data_st.n == CMD_F) {
    printf("cmd_s=%s\n", cmd_s);
    printf("ip_v=%s\n", ip_v);

    i = parse_sh_cmd(&c_data_st, cmd_s);
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
  }
  if (c_data_st.n == SSH_PUBKEY_F) {
    printf("ssh_pub_key=%s\n", c_data_st.unkown_data.ssh_pub);
  }
  // client_send(sh_cmd_st, ip_v);
  client_send(c_data_st, ip_v);

  //需要添加服务器端是否执行成功的功能

  return 0;
}
