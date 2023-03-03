#ifndef __INDEX_HPP__
#define __INDEX_HPP__
// 建立 索引
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <fstream>

namespace ns_index
{
  struct DocInfo
  {
    std::string title;   // 文档标题
    std::string content; // 文档内容
    std::string url;     // 官网url

    uint64_t doc_id; // 文旦的id 暂时不做理解
  };

  /// @brief 作为倒排索引的辅助
  struct InvertedElem
  {
    uint64_t doc_id;  // 文旦id
    std::string word; // 关键字
    int weight;       // 权重
  };

  // 倒排拉链  -- 根据用一个关键字 来拿到一组的InvertedElem
  typedef std::vector<struct InvertedElem> InvertedList;

  class Index
  {

  public:
    Index()
    {
    }
    ~Index()
    {
    }

    /// @brief 根据doc_id来获取正派索引 ,也就是文旦内容
    /// @param doc_id  文旦id
    /// @return 返回文档结构体的地址
    struct DocInfo *GetForwardIndex(const uint64_t doc_id)
    {
      if (doc_id < 0 || doc_id >= forward_index.size())
      {
        std::cerr << "索引id " << doc_id << " 越界了" << std::endl;
        return nullptr;
      }

      return &(forward_index[doc_id]);
    }

    /// @brief 根据关键字 获取倒排拉链
    /// @param word 关键
    /// @return
    InvertedList *GetInvertedList(const std::string &word)
    {
      auto it = inverted_index.find(word);
      if (it == inverted_index.end())
      {
        std::cerr << "关键字 " << word << " 不存在" << std::endl;
        return nullptr;
      }

      return &(it->second);
    }

    /// @brief 根据目录 文件 构建 正派和倒排索引,这里是最重的一步
    /// @param src_path 目录文件
    /// @return
    bool BuildIndex(const std::string &src_path)
    {
      std::ifstream in(src_path, std::ios::in | std::ios::binary);

      if (in.is_open() == false)
      {
        std::cerr << "文件目录 " << src_path << "无效" << std::endl;
        return false;
      }
      std::string line;
      while (std::getline(in, line))
      {
        // 此时我们已经提取到每一个html内容了
        // 建立正派索引
        DocInfo *doc = BuildForwardIndex(line);
        if (doc == nullptr)
        {
          std::cerr << "建立一个正派索引失败" << line << std::endl;
          continue;
        }
        // 建立 倒排索引
        BuildInvertedIndex(*doc);
      }

      return true;
    }

  private:
    /// @brief 根据字符串建立正派索引
    /// @param line 一个字符串,该字符串保留一个html文档的所有内容
    /// @return
    DocInfo *BuildForwardIndex(const std::string &line)
    {
      return nullptr;
    }

    /// @brief 根据一个文档内容的结构体建立倒排索引,需要经行分词
    /// @param doc  这个是一个结构体
    /// @return
    bool BuildInvertedIndex(const DocInfo &doc)
    {
      return false;
    }

  private:
    // 正排索引 -- 根据vector下标可以更加高效作为id找到内容
    std::vector<struct DocInfo>
        forward_index;
    // 倒排索引 一个关键字 可能在很多的文档中出现,一定是一个关键字和一组InvertedElem对应
    std::unordered_map<std::string, InvertedList> inverted_index;
  };
}

#endif
