#ifndef _CRAWLER_
#define _CRAWLER_

#include "base.h"
#include <string>

/*
 * 客户端
 */
class Client
{
public:
  Client(){}
  ~Crawler(){}

  int run();

  /*
   * 连接指定服务器
   */
  int connect(int& socketfd,const std::string url, const unsigned int port);

  /*
   * 向服务器发送请求
   */
  int sendRequest(int socketfd, string request);

  /*
   * 接受服务器返回的消息
   */
  int recvResponse(int socketfd, string response);
};

#endif
