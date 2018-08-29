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

//服务器端日志
#define LOG         "/tmp/trick"
//客户端保存服务器端ip文件
#define SAVE_SIP    "/tmp/sip"

//描述命令的结构体
struct sh_cmd
{
  //int num;
  char cmd[SIZE];
  char opt[SIZE];
  char arg[SIZE];
}__attribute__((packed));

//网络传输文件的结构体
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
//服务器端用户名
#define RNAME "lzh"

//客户端mac地址
#define CMAC "20:76:93:2c:55:80"
//客户端所属网段
#define IP_NETMASK "192.168.99.0/24"
//客户端监听端口
#define CLIENTPORT "8623"
//描述服务器ip的结构体
struct server_ip
{
  char s_p[BUFSIZE];
}__attribute__((packed));

#endif
