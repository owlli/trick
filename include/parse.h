#ifndef PARSE_H__
#define PARSE_H__
#include "../include/proto.h"

//对c选项的参数进行分析,创建成一个描述命令的结构体
int parse_sh_cmd(struct c_data *c_data_p, const char *string);



#endif
