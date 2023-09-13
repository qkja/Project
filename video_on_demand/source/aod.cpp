/**
 * User: Qkj
 * Description:测试工具类
 * Date: 2023-03-14
 * Time: 20:30
 */
#include "util.hpp"
#include "data.hpp"
#include "../Reactor/server.hpp"
void ServerTest()
{

#define WWWROOT "wwwroot"
#define VIDEO_ROOT "/video/"
#define IMAGE_ROOT "/image/"

  aod::FileUtil(WWWROOT).CreateDirectory();
  std::string root = WWWROOT;

  std::string video_root_path = root + VIDEO_ROOT;
  std::string image_root_path = root + IMAGE_ROOT;
  // 这是文件存放的目录
  aod::FileUtil(video_root_path).CreateDirectory();
  aod::FileUtil(image_root_path).CreateDirectory();
  // 2. 设置静态文件根目录

  Server *_sver = new Server(8080);
  _sver->SetMountPoint(WWWROOT); // 设置跟目录

  // 启动服务器
  _sver->Listen();
}
int main()
{

  ServerTest();
  return 0;
}
