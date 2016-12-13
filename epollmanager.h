#ifndef _TCPMANAGER_
#define _TCPMANAGER_

#include "base.h"

#include <sys/epoll.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>
#include <string>

/*
 * 对epoll句柄进行的操作
 */
enum OPRATION {
  ADD = EPOLL_CTL_ADD,
  MOD = EPOLL_CTL_MOD,
  DEL = EPOLL_CTL_DEL
};

/*
 * Class: Epoll管理类
 * Description: 对Epoll相关的操作进行管理
 */
class EpollManager {
public:
  static EpollManager& getInstance();

  /*
   *Description:    创建epoll句柄
   *Input:          epfd  epoll句柄（值结果参数）
   *Return:         是否创建成功
   */
  int createEpoll(int& epfd);

  /*
   *Description:    epoll事件注册
   *Input:          epfd  epoll句柄（值结果参数）
   *                opration 对epoll句柄进行的操作
   *                fd  需要监听的fd
   *                state 监控fd的状态，在该fd的状态变为该变量指定的值时，会触发事件处理
   *Return:         是否注册成功
   */
  int registerEvent(int epfd, OPRATION opration, int fd, int state);

  /*
   *Description:    执行Epoll监控
   *Input:          epfd  epoll句柄（值结果参数）
   */
  void doEpoll(int epfd);

  /*
   *Description:    处理时间
   *Input:          epfd  epoll句柄（值结果参数）
   *                events 需要处理的事件列表
   *                num 需要处理的事件列表的大小
   *Return:         是否处理成功
   */
  int handleEvents(int epfd, struct epoll_event* events, int num);

  /*
   *Description:    关闭epoll句柄
   *Input:          epfd  epoll句柄（值结果参数）
   *Return:         是否关闭成功
   */
  int closeEpoll(int epfd);

  int writen(int fd, char* ptr, int n);
  int readn(int fd, char *buff, int n);

private:
  EpollManager() {
  }
  ~EpollManager() {
  }
};

#define EPOLLMN() EpollManager::getInstance()

#endif
