#pragma once
  #include <sys/epoll.h>
#include "log.hpp"
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

class Epoller
{
private:
  /* data */
public:
  static const int gsize = 128;
  static int CreaterEpoller()
  {
    int epfd = epoll_create(gsize);
    if (epfd < 0)
    {
      logMessage(FATAL, "%d %s", errno, strerror(errno));
      exit(4);
    }
    return epfd;
  }
  static bool DelEvent(int epfd, int sock)
  {
    int n = epoll_ctl(epfd, EPOLL_CTL_DEL, sock, nullptr);
    if (n == 0)
      return false;
    return true;
  }

  static bool ModEvent(int epfd, int sock, std::uint32_t event)
  {
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = sock;

    int n = epoll_ctl(epfd, EPOLL_CTL_MOD, sock, &ev);
    if (n == 0)
      return false;
    return true;
  }
  static bool AddEvent(int epfd, int sock, std::uint32_t event)
  {
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = sock;

    int n = epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev);
    if (n == 0)
      return false;
    return true;
  }

  // 获取已经就绪的时间
  static int LoopOnce(int epfd, struct epoll_event revs[], int num)
  {
    int timeout = -1; // 阻塞时等待

    // n 就是就绪的队列
    int n = epoll_wait(epfd, revs, num, timeout);
    if (n == -1)
    {
      logMessage(FATAL, "%d %s", errno, strerror(errno));
    }
    return n;
  }
};
