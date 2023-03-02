#ifndef __INDEX_HPP__
#define __INDEX_HPP__
// 建立 索引
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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
        std::cerr << "索引id " << doc_id << " 越界了" <<std::endl;
        return nullptr;
      }
      
      return &(forward_index[doc_id]);
    }

    /// @brief 根据关键字 获取倒排拉链
    /// @param word 关键
    /// @return
    InvertedList *GetInvertedList(const std::string &word)
    {
      return nullptr;
    }

    /// @brief 根据目录 文件 构建 正派和倒排索引,这里是最重的一步
    /// @param src_path 目录文件
    /// @return
    bool BuildIndex(const std::string &src_path)
    {

      return true;
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
