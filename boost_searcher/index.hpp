#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

namespace ns_index
{
  struct DocInfo
  {
    std::string title;
    std::string content;
    std::string url;
    uint64_t doc_id; // 文档的id ,暂时不做理解
  };

  struct InvertedElem
  {
    uint64_t doc_id;
    std::string word; // 关键字
    int weight;       // 权重
  };

  class Index
  {
  public:
    // 倒排拉链
    typedef std::vector<InvertedElem> InvertedList;

  public:
    Index(){};
    ~Index(){};

  public:
    // 根据 id 找到文档内容
    DocInfo *GetForwardIndex(uint64_t id)
    {
      if (id < 0 || id >= forward_index.size())
      {
        std::cerr << "id越界了" << std::endl;
        return nullptr;
      }

      return &(forward_index[id]);
    }

    // 根据关键子找到倒排拉链
    InvertedList *GetInvertedList(const std::string &key)
    {
      auto it = inverted_index.find(key);
      if (it == inverted_index.end())
      {
        std::cerr << key << "没有倒排拉链" << std::endl;
        return nullptr;
      }
      return &(it->second);
    }

    // 根据去标签之后的文档正派和倒排索引
    bool BuildIndex(const std::string &input)
    {

      std::ifstream in(input, std::ios::in | std::ios::binary);
      if (!in.is_open())
      {
        std::cerr << "你给的路径是不正确的" << std::endl;
        return false;
      }
      std::string line;
      while (std::getline(in, line))
      {
        // 这里添加到正牌索引中
        DocInfo *doc = BuildForwardIndex(line);
        if (doc == nullptr)
        {
          std::cerr << "建立正牌索引失败 " << line << std::endl;
          continue;
        }

        // 建立倒排索引
        BuildInvertedIndex(*doc);
      }
      return true;
    }

  private:
    DocInfo *BuildForwardIndex(const std::string &line)
    {
      return nullptr;
    }
    void BuildInvertedIndex(const DocInfo &doc)
    {
    }

  private:
    // 正派索引 -- 通过id找内容  用数字的下标来做文档的id
    std::vector<DocInfo> forward_index;
    // 倒排索引 -- 关键字 找道文档id ,id可能有多个
    std::unordered_map<std::string, InvertedList> inverted_index;
  };
}
