/**
 * User: Qkj
 * Description:
 * Date: 2023-03-08
 * Time: 10:45
 */

#include <string>
#include <iostream>
#include "../cpp-httplib/httplib.h"
using namespace httplib;
void HelloBit(const Request &rep, Response &rsp)
{
  rsp.body = "hello bit";
  rsp.status = 200;
}

void Numbers(const Request &rep, Response &rsp)
{

  // 这个是捕捉的数据 /numbers/123 -> matches[0] = "/numbers/123"  matches[1] = "123"
  std::string num = rep.matches[1];
  rsp.set_content(num, "text/plain"); // 设置正文
  rsp.status = 200;
}

void Multipart(const Request &rep, Response &rsp)
{
  // 文件上传的的
  if (rep.has_file("file1") == false)
  {
    rsp.status = 400;
    return;
  }
  MultipartFormData file = rep.get_file_value("file1");
  std::cout << file.filename << std::endl; // 区域文件名称
  std::cout << file.content << std::endl;  // 区域文件内容
  rsp.status = 200;
}

int main()
{

  Server server;
  // 设置静态根目录 另外一个用法
  server.set_mount_point("/", "./www");

  // 条件请求
  server.Get("/hi", HelloBit);

  // 正则表达式 ,在正则表达式中
  // \d 表示数字,
  // + 表示一次或者多次
  // ()--表示捕捉数据s
  server.Get("/numbers/(\\d+)", Numbers);

  server.Post("/multipart", Multipart);

  server.listen("0.0.0.0", 8081);

  return 0;
}
