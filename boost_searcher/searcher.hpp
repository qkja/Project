#pragma once 
#include "index.hpp"
namespace ns_srearchre
{
  class Searcher
  {
    public:
      Searcher(){};
      ~Searcher(){};
    public:
      void InitSearcher(const std::string& input)
      {
        // 1.获取对象
        // 2. 建立索引
      }

      void Search(const std::string& query, std::string* json_string)
      {
        // 1. [分词] 对query 进行分词
        // 2. [触发] 
      }
    private:
      ns_index::Index* index;
  };
}

