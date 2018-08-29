#ifndef SEARCH_CLIENT__
#define SEARCH_CLIENT__


#include "proto.h"

//每隔20分钟扫描整个内网,如果发现客户端,向客户端发送本机ip
int send_myip();


#endif
