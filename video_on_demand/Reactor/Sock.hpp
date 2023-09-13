#pragma once
#include <sys/types.h> /*
       See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>

class Sock
{
public:
  static int Socket()
  {
    int listenSock = socket(PF_INET, SOCK_STREAM, 0);
    if (listenSock < 0)
    {
      exit(1);
    }
    int opt = 1;
    setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    return listenSock;
  }
  
  static void Bind(int sock, std::uint16_t port)
  {
    struct sockaddr_in local; // 用户栈
    memset(&local, 0, sizeof local);
    local.sin_family = PF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (const struct sockaddr *)&local, sizeof local) < 0)
    {
      exit(2);
    }
  }
  static void Listen(int sock)
  {
    if (listen(sock, 20 /*后面再说*/) < 0)
    {
      exit(3);
    }
  }
  static int Accept(int socket, std::string *clientip, std::uint16_t *clientport)
  {
    struct sockaddr_in peer;
    socklen_t len = sizeof(peer);
    // 4. 获取连接, accept 的返回值是一个新的socket fd ？？
    // 4.1 listenSock_: 监听 && 获取新的链接-> sock
    // 4.2 serviceSock: 给用户提供新的socket服务
    int serviceSock = accept(socket, (struct sockaddr *)&peer, &len);
    if (serviceSock < 0)
    {
      return serviceSock;
    }
    if (clientip)
      *clientip = inet_ntoa(peer.sin_addr);
    if (clientport)
      *clientport = ntohs(peer.sin_port);
    return serviceSock;
  }
};
