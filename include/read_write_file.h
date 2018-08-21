#ifndef READ_WRITE_H__
#define READ_WRITE_H__

#include "proto.h"

int get_ssh_pub_key(struct c_data *c_data_p);
int write_auth_key(struct c_data c_data_st);
#endif
