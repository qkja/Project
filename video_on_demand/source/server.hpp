#ifndef __SERVER_HPP__
#define __SERVER_HPP__
#include "data.hpp"
#include "../cpp-httplib/httplib.h"
namespace aod
{
#define WWWROOT "../http/www"
#define VIDEO_ROOT "/video/"
#define IMAGE_ROOT "/image/"
  TableVideo *tb_video = nullptr;
  class Server
  {
  public:
    Server(uint16_t port)
        : _port(port)
    {
    }

  public:
    static void Insert(const httplib::Request &rep, httplib::Response &rsp);
    static void Updata(const httplib::Request &rep, httplib::Response &rsp);
    static void Delete(const httplib::Request &rep, httplib::Response &rsp);
    static void SelectOne(const httplib::Request &rep, httplib::Response &rsp);
    static void SelectAll(const httplib::Request &rep, httplib::Response &rsp);

  private:
    uint16_t _port;
    httplib::Server _svr;
  };
}
#endif
