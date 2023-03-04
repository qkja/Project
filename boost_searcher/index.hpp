#ifndef __INDEX_HPP__
#define __INDEX_HPP__
// 建立 索引
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

#include <mutex>

#include "util.hpp"

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

  private:
    Index() {}
    Index(const Index &) = delete;
    Index &operator=(const Index &) = delete;
    static Index *instance;
    static std::mutex mtx;

  public:
    ~Index()
    {
    }
    static Index *GetInstance()
    {
      if (nullptr == instance)
      {
        mtx.lock();
        if (instance == nullptr)
        {
          instance = new Index;
        }
        mtx.unlock();
      }
      return instance;
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
    /// @param src_path 去标签后目录文件目录
    /// @return
    bool BuildIndex(const std::string &src_path)
    {
      std::ifstream in(src_path, std::ios::in | std::ios::binary);

      if (in.is_open() == false)
      {
        std::cerr << "文件目录 " << src_path << "无效" << std::endl;
        return false;
      }

      int count = 0;
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
        count++;
        if (count % 50 == 0)
        {
          // 后期加上一个进度条
          std::cout << "当前已经处理了 索引文档 " << count << std::endl;
        }
      }

      return true;
    }

  private:
    /// @brief 根据字符串建立正派索引  也就是根据文旦id找到 文档内容
    /// @param line 一个字符串,该字符串保留一个html文档的所有内容
    /// @return
    DocInfo *BuildForwardIndex(const std::string &line)
    {
      // title\3content\3url\n

      std::vector<std::string> results;
      const std::string sep = "\3";
      ns_util::StringUtil::Split(line, &results, sep);

      if (results.size() != 3)
        return nullptr;

      DocInfo doc;
      doc.title = results[0];
      doc.content = results[1];
      doc.url = results[2];
      doc.doc_id = forward_index.size(); // 注意这里是 正派拉链

      forward_index.push_back(std::move(doc));
      return &(forward_index[forward_index.size() - 1]);
    }

    // 为了词频统计
    struct word_cnt
    {
      int title_cnt;
      int content_cnt;
      word_cnt() : title_cnt(0), content_cnt(0) {}
    };

    /// @brief 根据一个文档内容的结构体建立倒排索引,需要经行分词  --
    /// @param doc  这个是一个结构体
    /// @return
    bool BuildInvertedIndex(const DocInfo &doc)
    {

      // 用来暂存 词频
      std::unordered_map<std::string, word_cnt> word_map;
      // 1.对标题 分词
      std::vector<std::string> title_words;
      ns_util::JiebaUtil::CutString(doc.title, &title_words);

      // 不区分大小写
      // 那么用户也不因该区分大小写
      for (std::string s : title_words)
      {
        boost::to_lower(s);
        word_map[s].title_cnt++; // 解释一下
      }
      // for (std::string &s : title_words)
      //{
      //   // 这里有点bug
      //   word_map[s].title_cnt++; // 解释一下
      // }

      // 对文档内容分词
      std::vector<std::string> content_words;
      ns_util::JiebaUtil::CutString(doc.content, &content_words);
      // for (auto &s : content_words)
      //{
      //   word_map[s].content_cnt++;
      // }

      for (auto s : content_words)
      {
        boost::to_lower(s);
        word_map[s].content_cnt++;
      }
      // 3 构建倒排拉链
      for (auto &word_pair : word_map)
      {
        InvertedElem item;
        item.doc_id = doc.doc_id; // 这里解释了上面我们为何添加了id
        item.word = word_pair.first;
        item.weight = _build_relevance(word_pair.second);

        // 加入倒排拉链中
        InvertedList &inverted_list = inverted_index[word_pair.first];
        inverted_list.push_back(std::move(item));
      }

      return true;
    }

  private:
    /// @brief 构建权重
    /// @param word
    /// @return
    int _build_relevance(const struct word_cnt &word)
    {
#define X 10
#define Y 1
      return X * word.title_cnt + Y * word.content_cnt;
    }

  private:
    // 正排索引 -- 根据vector下标可以更加高效作为id找到内容
    std::vector<struct DocInfo>
        forward_index;
    // 倒排索引 一个关键字 可能在很多的文档中出现,一定是一个关键字和一组InvertedElem对应
    std::unordered_map<std::string, InvertedList> inverted_index;
  };

  Index *Index::instance = nullptr;
  std::mutex Index::mtx;
}

#endif
