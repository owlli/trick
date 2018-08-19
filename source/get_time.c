#include "../include/get_time.h"

char *get_time(char *timestr) {
  time_t stamp;
  struct tm *tm;

  //得出当前时间
  stamp = time(NULL);
  tm = localtime(&stamp);
  strftime(timestr, BUFSIZE, "%Y-%m-%d %H:%M:%S", tm);
  return timestr;
}
