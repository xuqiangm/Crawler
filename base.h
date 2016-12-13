#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
 
#define SUCCESS 0
#define ERROR 1

#define MAX_LINE_LENGTH 100
#define EPOLL_SIZE 100
#define MAX_EVENTS_SIZE 20
#define MAX_HTML_SIZE 524288

#define CRAWLER_DEBUG_LOG(M, ...) fprintf(stderr, "[ERROR] (%s:%d)" M "\n", __FILE__, __LINE__, ##__VA_ARGS__ )
#define CRAWLER_INFO_LOG(M, ...) fprintf(stderr, "[INFO ] (%s:%d)" M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif
