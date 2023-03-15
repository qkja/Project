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
      std::string root = WWWROOT;

      std::string video_root_path = root + VIDEO_ROOT;
      std::string image_root_path = root + IMAGE_ROOT;
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
    static void Insert(const httplib::Request &req, httplib::Response &rsp);
    static void Update(const httplib::Request &req, httplib::Response &rsp);
    static void Delete(const httplib::Request &req, httplib::Response &rsp)
    {
      // 需要进行捕捉
      // 这个是捕捉的数据 /numbers/123
      // matches[0] = "/numbers/123"  matches[1] = "123"
      std::string s = req.matches[1];
      int video_id = atoi(s.c_str()); // 捕捉id

      // 去数据库里面查找是否存在
      Json::Value video;
      if (false == tb_video->SelectOne(video_id, &video))
      {
        rsp.status = 500;
        rsp.body = R"({"result":false, "reason":"视频不存在"})";
        rsp.set_header("Content-Type", "application/json");
      }
      std::string root = WWWROOT;
      std::string video_path = root + video["video"].asString();
      std::string image_path = root + video["image"].asString();
      // 删除文件
      remove(video_path.c_str());
      remove(image_path.c_str());

      // 删除数据库
      if (false == tb_video->Delete(video_id))
      {
        rsp.status = 500;
        rsp.body = R"({"result":false, "reason":"删除数据库信息失败"})";
        rsp.set_header("Content-Type", "application/json");
      }
    }
    static void SelectOne(const httplib::Request &req, httplib::Response &rsp);
    static void SelectAll(const httplib::Request &req, httplib::Response &rsp);

  private:
    uint16_t _port;
    httplib::Server _svr;
  };
  // 这里尝试的不一样的
  void Server::Insert(const httplib::Request &req, httplib::Response &rsp)
  {
    if (req.has_file("name") == false ||
        req.has_file("info") == false ||
        req.has_file("video") == false ||
        req.has_file("image") == false)
    {
      rsp.status = 400;
      rsp.body = R"({"result":false, "reason":"上传数据错误"})";
      rsp.set_header("Content-Type", "application/json");
      return;
    }
    httplib::MultipartFormData name = req.get_file_value("name");   // 视频名称
    httplib::MultipartFormData info = req.get_file_value("info");   // 视频简介
    httplib::MultipartFormData video = req.get_file_value("video"); // 视频文件
    httplib::MultipartFormData image = req.get_file_value("image"); // 视频图片
    // struct MultipartFormData
    // {
    //  name,
    //  content_type,
    //  filename,
    //  content
    // };
    std::string video_name = name.content; // 这里解释一下content为何是这个,不是文件名称
    std::string video_info = info.content;

    // ../http/www/video/变形金刚ss.mp4
    std::string root = WWWROOT;
    std::string video_path = root + VIDEO_ROOT + name + video.filename;
    //../http/www/image/变形金刚1.jpg
    std::string image_path = root + IMAGE_ROOT + name + image.filename;

    if (false == FileUtil(video_path).SetContent(video.content))
    {
      // std::cerr << "文件存储失败" << std::endl;
      rsp.status = 500;
      rsp.body = R"({"result":false, "reason":"视频存储失败"})";
      rsp.set_header("Content-Type", "application/json");
      return;
    }
    if (false == FileUtil(image_path).SetContent(image.content))
    {

      // std::cerr << "文件存储失败" << std::endl;
      rsp.status = 500;
      rsp.body = R"({"result":false, "reason":"图片文件存储失败"})";
      rsp.set_header("Content-Type", "application/json");
      return;
    }

    Json::Value video_json;
    video_json["name"] = video_name;

    video_json["info"] = video_info;

    video_json["video"] = VIDEO_ROOT + name + video.filename;
    video_json["image"] = IMAGE_ROOT + name + image.filename;

    // 数据库插入
    if (false == tb_video->Insert(video_json))
    {

      // std::cerr << "文件存储失败" << std::endl;
      rsp.status = 500;
      rsp.body = R"({"result":false, "reason":"数据库存储失败"})";
      rsp.set_header("Content-Type", "application/json");
      return;
    }
  }
}
#endif
