#include "client.h"
#include "base.h"
#include "tcpmanager.h"

#include <string>
#include <unistd.h>
#include <sys/socket.h>


int Client::run()
{
	int socketfd;
	if(ERROR == connect(socketfd, std::string("60.28.215.98"),80))
	{
		CRAWLER_DEBUG_LOG("Connect to server failed.");
		return ERROR;
	}

	if(ERROR == sendHomePageRequest(socketfd))
	{
		CRAWLER_DEBUG_LOG("Request home page failed.");
		return ERROR;
	}
	
	char htmlcontent[MAX_HTML_SIZE];
	recvResponse(socketfd, htmlcontent);

	return SUCCESS;
}

int Client::connect(int& socketfd,const std::string url, const unsigned int port)
{
	return TCPMN().connectToServer(socketfd, url, port);
}

int Client::sendHomePageRequest(int socketfd)
{
	int ret;
	std::string header("Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Encoding:gzip, deflate, sdch, br\r\nAccept-Language:zh-CN,zh;q=0.8,ja;q=0.6\r\nCache-Control:max-age=0\r\nConnection:keep-alive\r\nHost:www.zhihu.com\r\nUpgrade-Insecure-Requests:1\r\nUser-Agent:Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36\r\n");
	ret = TCPMN().writen(socketfd, (char*)header.c_str(), header.length());
	if(0 > ret)
	{
		CRAWLER_DEBUG_LOG("Send request for home page failed.");
		return ERROR;
	}

	return SUCCESS;
}

int Client::recvResponse(int socketfd, char* htmlcontent)
{
	int ret;
	ret = TCPMN().readn(socketfd, htmlcontent, MAX_HTML_SIZE);
	if(ret > 0)
	{
		CRAWLER_DEBUG_LOG("Receive response failed. ");
		return ERROR;
	}
	return SUCCESS;
}

