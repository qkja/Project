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

    // 初始化
    bool RunModule()
    {
      tb_video = new TableVideo();
      // 1. 初始化操作
      // 创建根目录 www
      FileUtil(WWWROOT).CreateDirectory();
      std::string video_root_path = std::string(WWWROOT).append(VIDEO_ROOT);
      std::string image_root_path = std::string(WWWROOT).(IMAGE_ROOT);
      // 这是文件存放的目录
      FileUtil(video_root_path).CreateDirectory();
      FileUtil(image_root_path).CreateDirectory();
      // 2. 设置静态文件根目录
      _svr.set_mount_point("/", WWWROOT);
      // 3. 添加请求
      _svr.Post("/video", Insert);
      _svr.Delete("/video/(\\d+)", Delete);
      _svr.Put("/video/(\\d+)", Update);
      _svr.Get("/video/(\\d+)", SelectOne);
      _svr.Get("/video", SelectAll);

      // 启动服务器
      _svr.listen("0.0.0.0", _port);
      return true;
    }

  public:
    static void Insert(const httplib::Request &rep, httplib::Response &rsp);
    static void Update(const httplib::Request &rep, httplib::Response &rsp);
    static void Delete(const httplib::Request &rep, httplib::Response &rsp);
    static void SelectOne(const httplib::Request &rep, httplib::Response &rsp);
    static void SelectAll(const httplib::Request &rep, httplib::Response &rsp);

  private:
    uint16_t _port;
    httplib::Server _svr;
  };
}
#endif
