#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

// 这是一个工具集
namespace ns_util
{
  /// @brief  这是为了解析文件
  class FileUtil
  {
  public:
    /// @brief 读取文件内容到 out中
    /// @param file_path
    /// @param out
    /// @return
    static bool ReadFile(const std::string &file_path, std::string *out)
    {
      assert(out);
      std::ifstream in(file_path.c_str(), std::ios::in);
      if (in.is_open() == false)
      {
        std::cerr << file_path << " 打开失败" << std::endl;
        return false;
      }

      std::string line;
      // 注意 getline 不会 读取 \n
      while (std::getline(in, line)) 
      {
       *out += line;
      }
      
      in.close();
      return true;
    }
  };

}
#endif