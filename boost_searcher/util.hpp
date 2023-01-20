#pragma once
#include <iostream>
#include <string>
#include <fstream>

namespace ns_util
{
  class FileUtil
  {
    public:
      static bool ReadFile(const std::string& file_path, std::string* out)
      {
        std::ifstream in(file_path, std::ios::in);
        if(!in.is_open())// 这里我可能有一点问题
        {
          std::cout << "打开文件 " << file_path << " 失败" << std::endl;
          return false;
        }

        std::string line;
        while(std::getline(in, line)) // 此时我们operator bool 
        {
          *out += line;
        }

        in.close();
        return true;
      }
  };
}
