#ifndef _TCPMANAGER_
#define _TCPMANAGER_

#include "base.h"

#include <sys/epoll.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>
#include <string>

/*
 * ��epoll������еĲ���
 */
enum OPRATION {
  ADD = EPOLL_CTL_ADD,
  MOD = EPOLL_CTL_MOD,
  DEL = EPOLL_CTL_DEL
};

/*
 * Class: Epoll������
 * Description: ��Epoll��صĲ������й���
 */
class EpollManager {
public:
  static EpollManager& getInstance();

  /*
   *Description:    ����epoll���
   *Input:          epfd  epoll�����ֵ���������
   *Return:         �Ƿ񴴽��ɹ�
   */
  int createEpoll(int& epfd);

  /*
   *Description:    epoll�¼�ע��
   *Input:          epfd  epoll�����ֵ���������
   *                opration ��epoll������еĲ���
   *                fd  ��Ҫ������fd
   *                state ���fd��״̬���ڸ�fd��״̬��Ϊ�ñ���ָ����ֵʱ���ᴥ���¼�����
   *Return:         �Ƿ�ע��ɹ�
   */
  int registerEvent(int epfd, OPRATION opration, int fd, int state);

  /*
   *Description:    ִ��Epoll���
   *Input:          epfd  epoll�����ֵ���������
   */
  void doEpoll(int epfd);

  /*
   *Description:    ����ʱ��
   *Input:          epfd  epoll�����ֵ���������
   *                events ��Ҫ������¼��б�
   *                num ��Ҫ������¼��б�Ĵ�С
   *Return:         �Ƿ���ɹ�
   */
  int handleEvents(int epfd, struct epoll_event* events, int num);

  /*
   *Description:    �ر�epoll���
   *Input:          epfd  epoll�����ֵ���������
   *Return:         �Ƿ�رճɹ�
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
