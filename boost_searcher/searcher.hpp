#pragma once
#include "index.hpp"
#include "util.hpp"
#include <jsoncpp/json/json.h>

namespace ns_srearchre
{
  class Searcher
  {
  public:
    Searcher(){};
    ~Searcher(){};

  public:
    void InitSearcher(const std::string &input)
    {
      // 1.获取对象
      index = ns_index::Index::GetInstance(); // 饱含模式
      std::cout << "获取index 单例 成功..." << std::endl;
      // 2. 建立索引
      bool ret = index->BuildIndex(input);
      if (ret)
        std::cout << "建立正派和倒排索引成功..." << std::endl;
    }

    void Search(const std::string &query, std::string *json_string)
    {
      // 1. [分词] 对query 进行分词
      std::vector<std::string> words;
      ns_util::JiebaUtil::CutString(query, &words);
      // for (auto word : words)
      // {
      //   std::cout << "------------- " << word << std::endl;
      // }
      // 2. [触发]
      ns_index::InvertedList inverted_list_all;

      for (auto word : words)
      {
        ns_index::InvertedList *inverted_list = index->GetInvertedList(word);

        if (inverted_list == nullptr)
        {
          continue;
        }
        // 找到倒排拉链
        // 有一个不完美的地方,我们可以通过一个map来这样做漏掉重复放热
        // 注意.漏掉的时候把权重拿出来  或者使用布隆锅炉器
        inverted_list_all.insert(inverted_list_all.end(), inverted_list->begin(), inverted_list->end());
      }

      // 3.合并排序
      std::sort(inverted_list_all.begin(), inverted_list_all.end(),
                [](const ns_index::InvertedElem &e1, const ns_index::InvertedElem &e2)
                {
                  return e1.weight > e2.weight; // 降序
                });
      // 4. 构建
      Json::Value root;
      for (auto &item : inverted_list_all)
      {
        ns_index::DocInfo *doc = index->GetForwardIndex(item.doc_id);
        if (doc == nullptr)
        {
          continue; // 理论上失败是不可能的
        }
        // 找到id 序列化和反序列化
        Json::Value elem;
        elem["title"] = doc->title;
        // elem["desc"] = doc->content; // 我们想要的是一部分,这个需要特殊处理
        elem["desc"] = GetDesc(doc->content, item.word); // 我们想要的是一部分,这个需要特殊处理
        elem["url"] = doc->url;

        root.append(elem);
      }

      Json::StyledWriter writer;
      *json_string = writer.write(root);
    }

  private:
    std::string GetDesc(const std::string &content, const std::string &word)
    {

      const std::size_t prev_step = 50;
      const std::size_t next_step = 100;
      std::size_t pos = content.find(word);
      // std::cout << "1111111111111111" << std::endl;
      if (pos == std::string::npos)
      {
        return "None";
      }
      // std::cout << "2222222222222222222222" << std::endl;

      std::size_t start = 0;
      std::size_t end = content.size() - 1;
      if (pos - start > prev_step)
      {
        start = pos - prev_step;
      }
      if (next_step + pos < end)
      {
        end = pos + next_step;
      }
      // std::cout << "1111111111111111" << std::endl;
      //  std::cout << "1111111111111111" << std::endl;

      if (start >= end)
      {
        // std::cout << start << std::endl;
        // std::cout << end << std::endl;

        // std::cout << "3333333333333333333333333" << std::endl;

        return "None";
      }
      // std::cout << "1111111111111111" << std::endl;

      return content.substr(start, end - start + 1);
    }

  private:
    ns_index::Index *index;
  };
}
