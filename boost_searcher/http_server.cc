/**
* User: Qkj
* Description: 
* Date: 2023-03-04
* Time: 10:30
*/
#include "cpp-httplib/httplib.h"

const std::string root_path = "./wwwroot";

int main()
{

  httplib::Server svr;
  svr.set_base_dir(root_path.c_str()); // 设置跟目录
  svr.Get("/hi",[](const httplib::Request& req, httplib::Response& rsp) {
      rsp.set_content("hello word!", "text/plain; charset=utf-8");
      });
  svr.listen("0.0.0.0",8081);
  return 0;
}
