#ifndef PROTO_H__
#define PROTO_H__

#define SERVERPORT  "4572"
#define FMT_STAMP   "%ld\r\n"

#define IPSTRSIZE   20
#define BUFSIZE     1024
#define CMDSIZE     BUFSIZE
#define SIZE        10

#define CMD_TOOLANG -1
#define OPT_TOOLANG -2
#define ARG_TOOLANG -3
#define CMD_NULL    -4
#define ARG_ERR     -5

#define LOG          "/tmp/trick"


//描述命令的结构体
struct sh_cmd
{
  //int num;
  char cmd[SIZE];
  char opt[SIZE];
  char arg[SIZE];
}__attribute__((packed));

//网络传输的结构体
struct c_data{
  int n;
  union unkown_data_u
  {
    struct sh_cmd sh_cmd_st;
    char ssh_pub[BUFSIZE];
  } unkown_data;
}__attribute__((packed));

#define CMD_F         1
#define SSH_PUBKEY_F  2

typedef char CMD[CMDSIZE];

//文件源
#define SFILE "/etc/tkexample"

//输出文件
#define DFILE "/home/lzh/SURPRISED"

//本地用户名
#define LNAME "lzh"
#define RNAME "lzh"

#endif
