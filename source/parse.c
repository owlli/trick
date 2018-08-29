#include "../include/parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// bug:不能使用连续的--

int parse_sh_cmd(struct c_data *c_data_p, const char *string) {
  /*printf("c_data_p->unkown_data.sh_cmd_st.cmd is %s\n",
  c_data_p->unkown_data.sh_cmd_st.cmd);
  printf("c_data_p->unkown_data.sh_cmd_st.opt is %s\n",
  c_data_p->unkown_data.sh_cmd_st.opt);
  printf("c_data_p->unkown_data.sh_cmd_st.arg is %s\n",
  c_data_p->unkown_data.sh_cmd_st.arg);*/
  CMD s = {'\0'};
  int i = 0, n = 0, t = 0;
  int cmd_n = 0, opt_n = 0, arg_n = 0;
  strncpy(s, string, CMDSIZE);
  while (s[i]) {
    if (n == 0) {
      // if ((s[i] < 'Z' && s[i] > 'A') || (s[i] < 'z' && s[i] > 'a')) {
      if (s[i] != ' ') {
        if ((++cmd_n) > (SIZE - 1)) {
          memset(c_data_p->unkown_data.sh_cmd_st.cmd, '\0', cmd_n - 1);
          return CMD_TOOLANG;
        }
        memcpy(&(c_data_p->unkown_data.sh_cmd_st.cmd[i]), &s[i], 1);
        t = 1;
        printf("s[%d] is %c\n", i, s[i]);
        printf("c_data_p->unkown_data.sh_cmd_st.cmd is %s\n",
               c_data_p->unkown_data.sh_cmd_st.cmd);
        i++;
      } else if (s[i] == ' ' && t == 1) {
        n = 1;
        i++;
        printf("cmd over\n");
        // memcpy(&(c_data_p->unkown_data.sh_cmd_st.cmd[i]), "\0", 1);
      }
    } else if (n == 1) {
      if (s[i] == '-') {
        printf("c_data_p->unkown_data.sh_cmd_st.opt is %s\n",
               c_data_p->unkown_data.sh_cmd_st.opt);
        memcpy(&(c_data_p->unkown_data.sh_cmd_st.opt[opt_n]), &s[i], 1);
        printf("s[%d] is %c\n", i, s[i]);
        printf("c_data_p->unkown_data.sh_cmd_st.opt is %s\n",
               c_data_p->unkown_data.sh_cmd_st.opt);
        opt_n++;
        t = 2;
        i++;
      } else if (t == 2) {
        // if ((s[i] < 'Z' && s[i] > 'A') || (s[i] < 'z' && s[i] > 'a')) {
        if (s[i] != ' ') {
          if ((opt_n) > (SIZE - 2)) {
            memset(c_data_p->unkown_data.sh_cmd_st.opt, '\0', opt_n);
            return OPT_TOOLANG;
          }
          printf("opt_n is %d\n", opt_n);
          memcpy(&(c_data_p->unkown_data.sh_cmd_st.opt[opt_n]), &s[i], 1);
          printf("s[%d] is %c\n", i, s[i]);
          printf("c_data_p->unkown_data.sh_cmd_st.opt is %s\n",
                 c_data_p->unkown_data.sh_cmd_st.opt);
          opt_n++;
          i++;
        } else if (s[i] == ' ') {
          // n = 2;
          t = 1;
          i++;
        }
      } else if (s[i] != ' ') {
        if ((arg_n) > (SIZE - 2)) {
          memset(c_data_p->unkown_data.sh_cmd_st.arg, '\0', arg_n);
          return ARG_TOOLANG;
        }
        if ((arg_n) < 0)
          return ARG_ERR;
        memcpy(&(c_data_p->unkown_data.sh_cmd_st.arg[arg_n]), &s[i], 1);
        printf("s[%d] is %c\n", i, s[i]);
        printf("c_data_p->unkown_data.sh_cmd_st.arg is %s\n",
               c_data_p->unkown_data.sh_cmd_st.arg);
        i++;
        arg_n++;
      } else if (s[i] == ' ') {
        i++;
        if (arg_n > 0)
          arg_n = -1;
      }
    }
  }
  if (!(c_data_p->unkown_data.sh_cmd_st.cmd))
    return CMD_NULL;
  return 0;
}
