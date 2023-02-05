#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include <string>
#include <fstream>
#include <iostream>

namespace ns_util
{
  class FileUtil
  {
    public:
      static bool ReadFile(const std::string& file_name, std::string* out)
      {
        std::ifstream in(file_name, std::ios::in);
        if(in.is_open() == false)
        {
          std::cerr << "打开文件 " << file_name  <<" 失败" <<std::endl;
          return false;
        }

        std::string line;
        while(std::getline(in, line)) 
        {
          *out += line;
        }
        in.close();
        return true;
      }
  };
}
#endif
