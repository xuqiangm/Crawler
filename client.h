#ifndef _CRAWLER_
#define _CRAWLER_

#include "base.h"
#include <string>

/*
 * �ͻ���
 */
class Client
{
public:
  Client(){}
  ~Crawler(){}

  int run();

  /*
   * ����ָ��������
   */
  int connect(int& socketfd,const std::string url, const unsigned int port);

  /*
   * ���������������
   */
  int sendRequest(int socketfd, string request);

  /*
   * ���ܷ��������ص���Ϣ
   */
  int recvResponse(int socketfd, string response);
};

#endif
