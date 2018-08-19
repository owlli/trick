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

typedef char CMD[CMDSIZE];

//文件源
#define SFILE "/etc/tkexample"

//输出文件
#define DFILE "/home/lzh/SURPRISED"

#endif
