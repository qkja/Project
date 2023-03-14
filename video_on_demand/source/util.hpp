#ifndef __UTIL_HPP__
#define __UTIL_HPP__
// 这是一个工具集

#include <iostream>
#include <string>
#include <fstream>

namespace aod
{
  class FileUtil
  {
  public:
    FileUtil(const std::string &name)
        : _name(name)
    {
    }

  public:
    /// @brief 针对目录是创建目录
    /// @return
    bool CreateDirectory()
    {
    }

    /// @brief 向文件中写入数据
    /// @param body
    /// @return
    bool SetContent(const std::string &body)
    {
    }

    /// @brief 获取文件数据到body中
    /// @param body
    /// @return
    bool GetContent(std::string *body)
    {
    }

    /// @brief 获取文件大小
    /// @return
    std::size_t Size()
    {
    }

  private:
    std::string _name; // 文件路径名称
  };
}

#endif