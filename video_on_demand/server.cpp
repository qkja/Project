/**
* User: Qkj
* Description: 
* Date: 2023-03-08
* Time: 10:45
*/
#include <string>
#include "cpp-httplib/httplib.h"
using namespace httplib;
void HelloBit(const Request& rep, Response & rsp)
{
  rsp.body = "hello bit";
  rsp.status = 200; //这个是可以忽略的
}

void Numbers(const Request& rep, Response & rsp)
{

  std::string num = rep.matches[1];

  rsp.set_content(num, "text/plain");
  rsp.status = 200;
}
int main()
{


  Server server;
  // 设置静态根目录 另外一个用法 
  server.set_mount_point("/", "./www");

  // 条件请求
  server.Get("/hi", HelloBit);

  server.Get("/numbers/(\\d+)", Numbers);

  return 0;
}
