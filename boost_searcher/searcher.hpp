#ifndef __SEARCHER_HPP__
#define __SEARCHER_HPP__
#include "index.hpp"
#include "util.hpp"

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
      
      for(std::string s:words)
      {
        boost::to_lower(s); // 建立索引的时候是忽略大小写的,我们搜索的时候也需要

      }
      // 3 合并排序  -- 按照相关性进行降序排序
      // 4 构建json串

    }

  private:
    ns_index::Index *index; // 提供系统经行查找索引
  };
}
#endif
