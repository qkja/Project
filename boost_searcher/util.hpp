#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace ns_util
{
  class FileUtil
  {
  public:
    static bool ReadFile(const std::string &file_path, std::string *out)
    {
      std::ifstream in(file_path, std::ios::in);
      if (!in.is_open()) // 这里我可能有一点问题
      {
        std::cout << "打开文件 " << file_path << " 失败" << std::endl;
        return false;
      }

      std::string line;
      while (std::getline(in, line)) // 此时我们operator bool
      {
        *out += line;
      }

      in.close();
      return true;
    }
  };

  // 字符串切分函数
  class StringUtil
  {
  public:
    static void CutString(const std::string &target, std::vector<std::string> *out, std::string &sep)
    {
      // 这里简绍一个新的东西 boost 库中有一个函数
      boost::split(*out, target, boost::is_any_of(sep), boost::token_compress_on);
    }
  };

}
