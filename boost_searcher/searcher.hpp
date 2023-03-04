#ifndef __SEARCHER_HPP__
#define __SEARCHER_HPP__
#include "index.hpp"
#include "util.hpp"
#include <algorithm>
#include <jsoncpp/json/json.h>

namespace ns_searcher
{
  class Searcher
  {
  public:
    Searcher() {}
    ~Searcher() {}
    /// @brief
    /// @param input  去标签后的 文件目录
    void InitSearcher(const std::string &input)
    {
      // 获取创建index对象
      index = ns_index::Index::GetInstance();
      std::cout << "获取单例成功" << std::endl;
      // 根据index对象建立索引
      index->BuildIndex(input);

      std::cout << "建立正派倒排索引成功" << std::endl;
    }

    /// @brief
    /// @param query 搜索关键字
    /// @param json_string 返回给浏览器的数据,也就是搜索结果
    void Search(const std::string &query, std::string *json_string)
    {
      // 1 分词  先来分词后面在进行查找
      std::vector<std::string> words;
      ns_util::JiebaUtil::CutString(query, &words);

      // 2 根据分词结果依次触发  搜索

      ns_index::InvertedList inverted_list_all; // 保存所有的倒排拉链里面的内容

      for (std::string s : words)
      {
        boost::to_lower(s); // 建立索引的时候是忽略大小写的,我们搜索的时候也需要
        // 先查倒排
        ns_index::InvertedList *inverted_list = index->GetInvertedList(s);
        if (nullptr == inverted_list)
        {
          continue;
        }
        // 此时找到了 保存所有的 拉链里面的值
        // 不完美 一个词可能和多个文档相关 一个文档
        inverted_list_all.insert(inverted_list_all.end(),
                                 inverted_list->begin(), inverted_list->end());
      }

      // 3 合并排序  -- 按照相关性进行降序排序
      std::sort(inverted_list_all.begin(), inverted_list_all.end(),
                [](const ns_index::InvertedElem &e1, const ns_index::InvertedElem &e2)
                {
                  return e1.weight > e2.weight;
                });
      // 4 构建json串 使用序列化和反序列化
      Json::Value root;
      for (auto &item : inverted_list_all)
      {
        // 此时拿到正派
        ns_index::DocInfo *doc = index->GetForwardIndex(item.doc_id);
        if (nullptr == doc)
        {
          continue;
        }

        // 获取了 文档内容
        Json::Value elem;
        elem["title"] = doc->title;
        elem["desc"] = make_summary(doc->content, item.word); // 我们需要根据关键字来提取摘要
        elem["url"] = doc->url;

        //fordebug
        elem["id"] = (int)item.doc_id;
        elem["weight"] = item.weight; // 会自动转成string
        root.append(elem); // 这里是有序的
      }

      Json::StyledWriter writer; // 这里我们暂时用这个格式
      *json_string = writer.write(root);
    }

  private:
    // 获取摘要
    std::string make_summary(const std::string &content, const std::string &word)
    {
      //这里有点问题  content 是文档内容,不区分大小写  word 确是 小的的
      // 这里获取摘要有点问题,关键字不一定会出现在内容中, 注意是非常小的概率
      //std::size_t pos = content.find(words);
      //if (pos == std::string::npos)
      //  return "Node";

      auto item = std::search(content.begin(), content.end(), word.begin(), word.end(),
          [](int x, int y){
          return std::tolower(x) == std::tolower(y);
          });
      if(item == content.end())
        return "Node";

      // 找到了 计算 跌打器到begin的距离
      std::size_t pos = std::distance(content.begin(), item);
      const std::size_t prev_step = 50;
      const std::size_t next_step = 100;
      // 先前找 50个 向后找 50个
      std::size_t begin = 0;
      // 注意szie_t是一个无符号数,这里我们-1 绝对有问题
      if (pos > prev_step)
      {
        begin = pos - prev_step;
      }
      std::size_t end = pos + next_step;
      if (end > content.size())
      {
        end = content.size();
      }

      if (end > begin)
        return content.substr(begin, end - begin);
      else
        return "Node";
    }
    ns_index::Index *index; // 提供系统经行查找索引
  };
}
#endif
