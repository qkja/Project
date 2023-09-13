#pragma once
// 基于 Reactor 模式, 编写一个 充分读取和写入的, EPOLL(ET) 的Server
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <unistd.h>
#include "Epoller.hpp"
#include "log.hpp"
#include "Sock.hpp"
#include "SetNonBlock.hpp"

class TcpServer;
class Connection;
using func_t = std::function<int(Connection *)>;
using callback_t = std::function<int(Connection *, std::string &)>;
using split_t = std::function<int(std::vector<std::string> *, std::string &)>;

// 这是一个链接里面的一个事务
class Connection
{

public:
  Connection(int sock, TcpServer *r) : sock_(sock), R(r)
  {
  }
  ~Connection()
  {
  }

public:
  void SetRecver(func_t recver)
  {
    recver_ = recver;
  }
  void SetSender(func_t sender)
  {
    sender_ = sender;
  }
  void SetExcepter(func_t excepter)
  {
    excepter_ = excepter;
  }

public:
  int sock_;             // 与客户端交流的套接字
  std::string inbuffer;  // 接受缓冲区
  std::string outbuffer; // 发送缓冲器
  func_t recver_;        // 读取回调
  func_t sender_;        // 发送回调
  func_t excepter_;      // 异常 回调
  TcpServer *R;
};

class TcpServer
{
public:
  TcpServer(std::uint16_t port, split_t sp, callback_t cb)
      : listensock_(-1),  epfd_(-1), port_(port), PackageSplit(sp), cb_(cb)
  {
    listensock_ = Sock::Socket();
    Sock::Bind(listensock_, port_);
    Sock::Listen(listensock_);
    logMessage(DEBUG, "创建监听套接字成功fd: %d", listensock_);
    // Util::SetNonBlock(listensock_);
    epfd_ = Epoller::CreaterEpoller();
    AddConnect(listensock_, EPOLLIN | EPOLLET,
               std::bind(&TcpServer::Accepter, this, std::placeholders::_1),
               nullptr,
               nullptr);
    revs = new struct epoll_event[revs_num];
  }

  int Accepter(Connection *conn)
  {
    // TODO
    while (true)
    {
      std::string clientip;
      std::uint16_t clientport;
      int sockFd = Sock::Accept(conn->sock_, &clientip, &clientport);
      if (sockFd < 0)
      {
        if (errno == EINTR) // 被信号终端了
        {
          continue;
        }
        else if (errno == EAGAIN || errno == EWOULDBLOCK) // 读取结束了
        {
          break;
        }
        else
        {
          logMessage(WARINING, "Accepter error");
          return -1;
        }
      }
      logMessage(DEBUG, "获取一个新链接 %d", sockFd);
      // 这里是对 与客户端进行对话的 套接字
      AddConnect(sockFd, EPOLLIN | EPOLLET,
                 std::bind(&TcpServer::TcpRecver, this, std::placeholders::_1),
                 std::bind(&TcpServer::TcpSender, this, std::placeholders::_1),
                 std::bind(&TcpServer::TcpExcept, this, std::placeholders::_1));
    }

    return 0;
  }

  void AddConnect(int sockfd, std::uint32_t event, func_t recver, func_t sender, func_t excepter)
  {
    if (event & EPOLLET) // 设置非阻塞
      Util::SetNonBlock(sockfd);
    Epoller::AddEvent(epfd_, sockfd, event);
    Connection *conn = new Connection(sockfd, this);
    // 对于普通成员 进行的方法绑定
    conn->SetRecver(recver);     // 设置读回调
    conn->SetSender(sender);     // 设置读回调
    conn->SetExcepter(excepter); // 设置读回调
    // conn->SetRecver(std::bind(&TcpServer::TcpRecver, this, std::placeholders::_1));   // 设置读回调
    // conn->SetSender(std::bind(&TcpServer::TcpSender, this, std::placeholders::_1));   // 设置读回调
    // conn->SetExcepter(std::bind(&TcpServer::TcpExcept, this, std::placeholders::_1)); // 设置读回调

    connections_.insert(std::make_pair(sockfd, conn));
    logMessage(DEBUG, "添加到connections_ 成功");
  }
  // 只是打开或者关闭

  void EnableReadWrite(int sock, bool readable, bool writerable)
  {
    std::uint32_t event = 0;
    event |= ((readable) ? EPOLLIN : 0);
    event |= ((writerable) ? EPOLLOUT : 0);
    Epoller::ModEvent(epfd_, sock, event);
  }
  // 读取数据
  int TcpRecver(Connection *conn)
  {
    while (true)
    {
      char buffer[1024] = {0};
      ssize_t s = recv(conn->sock_, buffer, sizeof(buffer) - 1, 0);

      if (s > 0)
      {
        // 由于 read 会读取换行,此时这里使用s-1之所以不用,这是应为我们的报文都是从 客户端发来的
        buffer[s] = 0;
        // std::cout << buffer << std::endl;

        // std::cout << buffer;
        // // logMessage(DEBUG, "buffer: %s", buffer);

        conn->inbuffer += buffer;
        // std::cout << __LINE__ << " s: " << s << " : " << conn->inbuffer.size()
        //           << " : " << conn->inbuffer << std::endl;
        // std::cout << "conn->inbuffer: " << conn->inbuffer << std::endl;
      }
      else if (s == 0)
      {
        conn->excepter_(conn); // 统一处理
        logMessage(DEBUG, "推出");
        return -1;
      }
      else
      {
        if (errno == EINTR) // 被信号终端了
        {
          continue;
        }
        else if (errno == EAGAIN || errno == EWOULDBLOCK) // 读取结束了
        {
          break;
        }
        else
        {
          // 这里是读错了
          conn->excepter_(conn);
          // 这里是为了 delete conn
          return -1;
        }
      }
    }
    // 报文分割
    std::vector<std::string> result;
    PackageSplit(&result, conn->inbuffer);
    for (auto &str : result)
    {
      // logMessage(DEBUG, "%s", str.c_str());
      cb_(conn, str); // 处理报文进行放到结果中
    }
    return 0;
  }
  // 写处理
  int TcpSender(Connection *conn)
  {
    while (true)
    {
      ssize_t n = send(conn->sock_, conn->outbuffer.c_str(), conn->outbuffer.size(), 0);
      if (n > 0)
      {
        // 去除缓冲区的数据
        conn->outbuffer.erase(0, n);
      }
      else
      {
        if (errno == EINTR) // 被信号终端了
        {
          continue;
        }
        else if (errno == EAGAIN || errno == EWOULDBLOCK) // 读取结束了,这里有可能对方缓冲区满了
        {
          break;
        }
        else
        {
          // 这里是读错了
          conn->excepter_(conn);
          logMessage(FATAL, "发送错误");
          break;
        }
      }
    }
    // if (conn->outbuffer.empty())
    //   EnableReadWrite(conn->sock_, true, false);

    return 0;
  }
  // 异常处理
  int TcpExcept(Connection *conn)
  {
    if (!IsExists(conn->sock_))
      return -1;
    // 移除,先移除,后关闭
    Epoller::DelEvent(epfd_, conn->sock_);
    logMessage(DEBUG, "移除成功");
    close(conn->sock_);
    logMessage(DEBUG, "关闭成功 %d", conn->sock_);

    delete connections_[conn->sock_];
    logMessage(DEBUG, "空间释放成功");
    connections_.erase(conn->sock_);
    logMessage(DEBUG, "hash释放成功");
    return 0;
  }
  ~TcpServer()
  {
    if (listensock_ != -1)
      close(listensock_);
    if (epfd_ != -1)
      close(epfd_);
    delete[] revs;
  }

public:
  bool IsExists(int sock)
  {
    auto iter = connections_.find(sock);
    if (iter == connections_.end())
      return false;
    return true;
  }
  // 事件派发
  void Dispatcher()
  {
    int n = Epoller::LoopOnce(epfd_, revs, revs_num);
    for (int i = 0; i < n; i++)
    {
      int sock = revs[i].data.fd;
      std::uint32_t event = revs[i].events;

      // 处理所有的异常
      if (event & EPOLLHUP)
        event |= (EPOLLIN | EPOLLOUT);
      if (event & EPOLLERR)
        event |= (EPOLLIN | EPOLLOUT);

      // 调用读回调
      if (event & EPOLLIN)
      {
        if (IsExists(sock) && connections_[sock]->recver_) // 先判断是否合法,函数对象如何判空
        {
          connections_[sock]->recver_(connections_[sock]); // 调用这个函数
        }
      }

      // 调用写回调
      if (event & EPOLLOUT)
      {
        if (IsExists(sock) && connections_[sock]->sender_) // 先判断是否合法,函数对象如何判空
        {
          connections_[sock]->sender_(connections_[sock]); // 调用这个函数
        }
      }
    }
  }

  void Run()
  {
    while (true)
    {
      Dispatcher();
    }
  }

private:
  static const int revs_num = 64;
  int listensock_;
  int epfd_;

  std::uint16_t port_;

  // 将epoll和上层进行结合
  std::unordered_map<int, Connection *> connections_;

  // 就绪事件列表
  struct epoll_event *revs;
  // 处理一个完整的报文
  split_t PackageSplit;
  // 处理分割报文的方法
  callback_t cb_; // 这里是处理报文的
};
