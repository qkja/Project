#ifndef __UTIL_HPP__
#define __UTIL_HPP__
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
    /// @brief 读物文件内容到 out中
    /// @param file_path 
    /// @param out 
    /// @return 
    static bool ReadFile(const std::string &file_path, std::string *out)
    {
      assert(out);
      return true;
    }


  };

}
#endif