#include "../include/proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// bug:不能使用连续的--

int parse_sh_cmd(struct sh_cmd *sh_cmd_p, const char *string) {
  printf("sh_cmd_p->cmd is %s\n", sh_cmd_p->cmd);
  printf("sh_cmd_p->opt is %s\n", sh_cmd_p->opt);
  printf("sh_cmd_p->arg is %s\n", sh_cmd_p->arg);
  CMD s = {'\0'};
  int i = 0, n = 0, t = 0;
  int cmd_n = 0, opt_n = 0, arg_n = 0;
  strncpy(s, string, CMDSIZE);
  while (s[i]) {
    if (n == 0) {
      // if ((s[i] < 'Z' && s[i] > 'A') || (s[i] < 'z' && s[i] > 'a')) {
      if (s[i] != ' ') {
        if ((++cmd_n) > (SIZE - 1)) {
          memset(sh_cmd_p->cmd, '\0', cmd_n - 1);
          return CMD_TOOLANG;
        }
        memcpy(&(sh_cmd_p->cmd[i]), &s[i], 1);
        t = 1;
        printf("s[%d] is %c\n", i, s[i]);
        printf("sh_cmd_p->cmd is %s\n", sh_cmd_p->cmd);
        i++;
      } else if (s[i] == ' ' && t == 1) {
        n = 1;
        i++;
        printf("cmd over\n");
        // memcpy(&(sh_cmd_p->cmd[i]), "\0", 1);
      }
    } else if (n == 1) {
      if (s[i] == '-') {
        printf("sh_cmd_p->opt is %s\n", sh_cmd_p->opt);
        memcpy(&(sh_cmd_p->opt[opt_n]), &s[i], 1);
        printf("s[%d] is %c\n", i, s[i]);
        printf("sh_cmd_p->opt is %s\n", sh_cmd_p->opt);
        opt_n++;
        t = 2;
        i++;
      } else if (t == 2) {
        // if ((s[i] < 'Z' && s[i] > 'A') || (s[i] < 'z' && s[i] > 'a')) {
        if (s[i] != ' ') {
          if ((opt_n) > (SIZE - 2)) {
            memset(sh_cmd_p->opt, '\0', opt_n);
            return OPT_TOOLANG;
          }
          printf("opt_n is %d\n", opt_n);
          memcpy(&(sh_cmd_p->opt[opt_n]), &s[i], 1);
          printf("s[%d] is %c\n", i, s[i]);
          printf("sh_cmd_p->opt is %s\n", sh_cmd_p->opt);
          opt_n++;
          i++;
        } else if (s[i] == ' ') {
          // n = 2;
          t = 1;
          i++;
        }
      } else if (s[i] != ' ') {
        if ((arg_n) > (SIZE - 2)) {
          memset(sh_cmd_p->arg, '\0', arg_n);
          return ARG_TOOLANG;
        }
        if ((arg_n) < 0)
          return ARG_ERR;
        memcpy(&(sh_cmd_p->arg[arg_n]), &s[i], 1);
        printf("s[%d] is %c\n", i, s[i]);
        printf("sh_cmd_p->arg is %s\n", sh_cmd_p->arg);
        i++;
        arg_n++;
      } else if (s[i] == ' ') {
        i++;
        if (arg_n > 0)
          arg_n = -1;
      }
    }
  }
  if (!(sh_cmd_p->cmd))
    return CMD_NULL;
  return 0;
}
