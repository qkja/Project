/**
* User: Qkj
* Description: 
* Date: 2023-01-28
* Time: 15:27
*/

#include "cpp-httplib/httplib.h"
#include "searcher.hpp"

const std::string root_path = "./wwwroot";

int main()
{
  ns_srearchre::Searcher searcher;

  httplib::Server svr;
  svr.set_base_dir(root_path.c_str()); // 设置web根目录

  svr.listen("0.0.0.0", 8081);
  return 0;
}
