#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <fstream>
#include "util.hpp"
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

  private:
    Index(){};
    ~Index(){};
    Index(const Index& index) = delete;
    Index& operator=(const Index&) = delete;
 // public:
 //   Index(){};
 //   ~Index(){};

  public:
    // 倒排拉链
    typedef std::vector<InvertedElem> InvertedList;
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
    // 建立正派索引
    DocInfo *BuildForwardIndex(const std::string &line)
    {
      // 解析line  字符串切分
      // xxxx/3yyyyyy/3zzzzzzzz/3
      std::vector<std::string> results;
      std::string sep;
      sep.push_back('\3');
      ns_util::StringUtil::CutString(line, &results, sep);
      if (results.size() != 3)
      {
        return nullptr;
      }

      // 填充 DocInfo doc;

      DocInfo doc;
      doc.title = results[0];
      doc.content = results[1];
      doc.url = results[2];
      doc.doc_id = forward_index.size(); // 注意这里
      
      // push
      forward_index.push_back(std::move(doc));
      return &forward_index.back();
    } 

    // 建立倒排索引
    bool BuildInvertedIndex(const DocInfo &doc)
    {
      struct word_cnt {
        int title_cnt = 0;
        int content_cnt = 0;
      };

      std::unordered_map<std::string, word_cnt> word_map;

      // 这里是标头
      std::vector<std::string> title_words;
      ns_util::JiebaUtil::CutString(doc.title, &title_words);

      for(auto s:title_words)
      {
        // 转成小写
        boost::to_lower(s);
        word_map[s].title_cnt++;
      }

      // 这里是内容
      std::vector<std::string> content_words;
      ns_util::JiebaUtil::CutString(doc.title, &content_words);
      for(auto s:content_words)
      {
        boost::to_lower(s);
        word_map[s].content_cnt++;
      }


      // 构建拉链
      for(auto& word_pair:word_map)
      {
        InvertedElem item;
        item.doc_id = doc.doc_id;
        item.word = word_pair.first;
#define X 10
#define Y 1
        item.weight = X*word_pair.second.title_cnt + Y*word_pair.second.content_cnt;


        // 插入倒排索引
        inverted_index[item.word].push_back(std::move(item));
        // 根据权重进行排序
      }


      return true;
    }

  private:
    // 正派索引 -- 通过id找内容  用数字的下标来做文档的id
    std::vector<DocInfo> forward_index;
    // 倒排索引 -- 关键字 找道文档id ,id可能有多个
    std::unordered_map<std::string, InvertedList> inverted_index;
  public:
    static Index* instance;
    static std::mutex mtx;
  public:
    static Index* GetInstance()
    {
      if(nullptr == instance)
      {
        mtx.lock();
        if(nullptr == instance)
        {
          instance = new Index();
        }
        mtx.unlock();
      }

      return instance;
    }
  };


  Index* Index::instance = nullptr;
}
