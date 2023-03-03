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
      // 根据index对象建立索引
      index->BuildIndex(input);
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

      for(std::string s:words)
      {
        boost::to_lower(s); // 建立索引的时候是忽略大小写的,我们搜索的时候也需要
        // 先查倒排
        ns_index::InvertedList* inverted_list = index->GetInvertedList(s);
        if(nullptr == inverted_list)
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
          [](const ns_index::InvertedElem& e1, const ns_index::InvertedElem& e2) {
          return e1.weight > e2.weight;
          });
      // 4 构建json串 使用序列化和反序列化
      Json::Value root;
      for(auto& item: inverted_list_all)
      {
        // 此时拿到正派
       ns_index::DocInfo* doc =  index->GetForwardIndex(item.doc_id);
       if(nullptr == doc)
       {
         continue;
       }

       // 获取了 文档内容
       Json::Value elem;
       elem["title"] = doc->title;
       elem["desc"] = make_summary(doc->content);
       elem["url"] = doc->url;

       root.append(elem); // 这里是有序的
      }
      
      Json::StyledWriter writer; // 这里我们暂时用这个格式
      *json_string = writer.write(root);

    }

  private:
    std::string make_summary(const std::string& content)
    {
      return content;
    }
    ns_index::Index *index; // 提供系统经行查找索引
  };
}
#endif
