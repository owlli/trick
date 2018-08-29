#ifndef READ_WRITE_H__
#define READ_WRITE_H__

#include "proto.h"

//获得客户端ssh公钥
int get_ssh_pub_key(struct c_data *c_data_p);

//写入服务器端ssh的auth文件
int write_auth_key(struct c_data c_data_st);
#endif
