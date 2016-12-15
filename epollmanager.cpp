#include "epollmanager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

EpollManager& TCPManager::getInstance()
{
	static TCPManager instance;
	return instance;
}
int EpollManager::connectToServer(int& socketfd,const std::string ip, const unsigned int port)
{
	CRAWLER_INFO_LOG("connecting to server [ip:%s, port:%d]", ip.c_str(), port);
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd < 0)
	{
		CRAWLER_DEBUG_LOG("create socket failed.");
		return ERROR;
	}

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr);
	servaddr.sin_port = htons(port);

	int ret = connect(socketfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(0 != ret)
	{
		CRAWLER_DEBUG_LOG("Connect to server [ip:%s, port:%d] failed.", ip.c_str(), port);
		return ERROR;
	}

	//设置套接字为非阻塞
	int flags = fcntl(socketfd, F_GETFL, 0);
	if(-1 == flags)
	{
		CRAWLER_DEBUG_LOG("Get socket flags failed.");
		return ERROR;
	}
	ret = fcntl(socketfd, F_SETFL, flags | O_NONBLOCK);
	if(-1 == flags)
	{
		CRAWLER_DEBUG_LOG("Set socket flags failed.");
		return ERROR;
	}
	
	return SUCCESS;
}

int EpollManager::createEpoll(int& epfd)
{
	epfd = epoll_create(MAX_EPOLL_SIZE);
	return SUCCESS;
}

int EpollManager::registerEvent(int epfd, OPRATION opration, int fd, int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epfd, opration, fd, &ev);

	return SUCCESS;
}

void EpollManager::doEpoll(int epollfd)
{
  struct epoll_event events[MAX_EVENTS_SIZE];
  int ready_num;
  while(true)
  {
    ready_num = epoll_wait(epollfd, epoll_event, MAX_EVENTS_SIZE, -1);
    handleEvents(epollfd, events, ready_num);
  }
}

int EpollManager::handleEvents(int epollfd, struct epoll_event* events, int num)
{
   return SUCCESS;
}

int EpollManager::closeEpoll(int epfd)
{
    close(epfd);

    return SUCCESS;
}

int EpollManager::writen(int fd, char*  vptr, int n)
{
	int nleft;
	int nwriten;
	char *ptr = vptr;
	nleft = n;
	while(nleft > 0)
	{
		if((nwriten = write(fd, ptr, nleft)) <= 0)
		{
			if(nwriten < 0 && errno == EINTR)
			{
				nwriten = 0;
			}
			else
			{
				return ERROR;
			}
			
		}
		nleft -= nwriten;
		ptr += nwriten;
	}
	return n;
}

int EpollManager::readn(int fd, char *vptr, int n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = vptr;
	nleft = n;
	while(nleft > 0)
	{
		if((nread = read(fd, ptr, nleft)) < 0)
		{
			if(errno == EINTR)
			{
				nread = 0;
			}
			else
			{
				return ERROR;
			}
		}
		else if(nread == 0)
		{
			break;
		}
		nleft -= nread;
		ptr += nread;
	}
	return (n-nleft);
}
