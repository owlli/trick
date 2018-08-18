#ifndef PROTO_H__
#define PROTO_H__

#define SERVERPORT "4572"
#define FMT_STAMP "%ld\r\n"

#define IPSTRSIZE 1024
#define BUFSIZE 1024
#define SIZE 10


struct sh_cmd
{
  int num;
  char cmd[SIZE];
  char opt[SIZE];
  char arg[SIZE];
}__attribute__((packed));

#endif
