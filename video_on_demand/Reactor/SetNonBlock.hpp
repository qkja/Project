#pragma once
#include <unistd.h>
#include <fcntl.h>

namespace Util
{
  // 设置 非阻塞fd
  bool SetNonBlock(int sock)
  {

    int flag = fcntl(sock, F_GETFL); // 获取 原本的 文件描述符的属性

    if (flag == -1)
      return false;

    int n = fcntl(sock, F_SETFL, flag | O_NONBLOCK); // 覆盖式设置
    if (n == -1)
      return false;
    return true;
  }
}