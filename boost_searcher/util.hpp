#ifndef __UTIL_HPP__
#define __UTIL_HPP__
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include "cppjieba/Jieba.hpp"

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
      std::ifstream in(file_path, std::ios::in);
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

  /// @brief 字符串切分
  class StringUtil
  {
  public:
    static void CutString(const std::string &target, std::vector<std::string> *out, const std::string sep)
    {
      assert(out);
      // 我们这里使用现成的切分函数
      boost::split(*out, target, boost::is_any_of(sep),
                   boost::token_compress_on);
    }
  };
  // 这是 我们词库的位置
  const char *const DICT_PATH = "./dict/jieba.dict.utf8";
  const char *const HMM_PATH = "./dict/hmm_model.utf8";
  const char *const USER_DICT_PATH = "./dict/user.dict.utf8";
  const char *const IDF_PATH = "./dict/idf.utf8";
  const char *const STOP_WORD_PATH = "./dict/stop_words.utf8";

  /// @brief 这是一个jieba分词
  class JiebaUtil
  {
  public:
    /// @brief 这里是分词
    /// @param src
    /// @param out
    static void CutString(const std::string &src, std::vector<std::string> *out)
    {
      jieba.CutForSearch(src, *out);
    }

  private:
    static cppjieba::Jieba jieba;
  };
  cppjieba::Jieba JiebaUtil::jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);

}
#endif
