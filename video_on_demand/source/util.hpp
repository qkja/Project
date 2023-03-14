#ifndef __UTIL_HPP__
#define __UTIL_HPP__
// 这是一个工具集

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include <memory>

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
      if (Exists() == true)
        return true;

      mkdir(_name.c_str(), 0777);
      return true;
    }

    /// @brief 向文件中写入数据
    /// @param body
    /// @return
    bool SetContent(const std::string &body)
    {
      std::ofstream ofs;
      ofs.open(_name, std::ios::binary); // 二进制方式打开
      if (ofs.is_open() == false)
      {
        std::cerr << "打开文件 " << _name << "失败" << std::endl;
        return false;
      }

      ofs.write(body.c_str(), body.size());

      if (ofs.good() == false)
      {
        std::cerr << "保存文件失败" << std::endl;
        ofs.close();
        return false;
      }

      ofs.close();
      return true;
    }

    /// @brief 获取文件数据到body中
    /// @param body
    /// @return
    bool GetContent(std::string *body)
    {
      std::ifstream ifs;
      ifs.open(_name, std::ios::binary); // 二进制方式打开
      if (ifs.is_open() == false)
      {
        std::cerr << "打开文件 " << _name << "失败" << std::endl;
        return false;
      }

      // 开始读取文件的数据
      std::size_t flen = Size();
      body->resize(flen);
      ifs.read(&((*body)[0]), flen); // 禁止使用 c_str() 这是constfr
      if (ifs.good() == false)
      {
        std::cerr << "读取文件失败" << std::endl;
        ifs.close();
        return false;
      }
      ifs.close();
      return true;
    }

    /// @brief 获取文件大小
    /// @return
    std::size_t Size()
    {
      if (Exists() == false)
        return 0;
      // 获取文件的属性信息

      struct stat st; // 保存文件属性信息的
      int ret = stat(_name.c_str(), &st);
      if (ret != 0)
      {
        return 0;
      }
      // 这里成功了
      // long int 就是一个 长整型
      return st.st_size;
    }

    /// @brief 判断文件是否存在
    /// @return
    bool Exists()
    {
      // F_OK 检测是否存在,存在返回0,不存在返回-1,并且错误码被设置
      int ret = access(_name.c_str(), F_OK);
      if (ret != 0)
      {
        std::cout << "文件不存在" << std::endl;
        return false;
      }
      return true;
    }

  private:
    std::string _name; // 文件路径名称
  };

  /// @brief 回去看看序列化和反序列化的一些接口
  class JsonUtil
  {
  public:
    /// @brief 序列化
    /// @param val
    /// @param body
    /// @return
    static bool Serialize(const Json::Value &val, std::string *body)
    {
      Json::StreamWriterBuilder swb;
      std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());

      std::stringstream ss;
      int ret = sw->write(val, &ss);
      if (ret != 0)
      {
        std::cerr << "序列化失败" << std::endl;
        return false;
      }
      *body = ss.str();
      return true;
    }

    /// @brief 反序列化
    /// @param val
    /// @param body
    /// @return
    static bool UnSerialize(const std::string &body, Json::Value *val)
    {
      Json::CharReaderBuilder crb;
      std::unique_ptr<Json::CharReader> cr(crb.newCharReader());
      std::string err;
      bool ret = cr->parse(body.c_str(), body.c_str() + body.size(), val, &err);
      if (ret == false)
      {
        std::cerr << "反序列化失败" << std::endl;
        return false;
      }
      return true;
    }
  };

}

#endif