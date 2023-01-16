/**
* User: Qkj
* Description: 这是一个去标签的程序,把input中所有的标签去掉放在rawzh中
* Date: 2023-01-16
* Time: 21:36
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

// 下面是路径
const std::string src_path = "data/input";
const std::string output = "data/raw_html/raw.txt";

typedef struct DocInfo
{
  std::string title;   // 文档标题
  std::string content; // 文档内容
  std::string url;     // 该文档在官网的url
} DocInfo_t;

bool EnumFile(const std::string& src_path, std::vector<std::string>* p_files_list)
{
  (void)src_path;
  (void)p_files_list;
  return false;
}

bool ParseHtml(const std::vector<std::string> files_list, std::vector<DocInfo_t> *result)
{

}

bool SaveHtml(const std::vector<DocInfo_t>& result, const std::string& output)
{

}

int main()
{
  std::vector<std::string> files_list;
  // 1. 保存所有文件名 到 files_list 中
  if(!EnumFile(src_path, &files_list))
  {
    std::cerr<<"enum file name errno"<<std::endl;
    exit(1); // 退出码可以自己定
  }

  // 2. 去标签
  std::vector<DocInfo_t> result;
  if(!ParseHtml(files_list, &result))
  {
    std::cerr<<"parse html errno"<<std::endl;
    exit(2); // 退出码可以自己定
  }

  // 3. 把所有文件内容 写入到 output中 ,按照\3作为分割符
  if(!SaveHtml(result, output))
  {
    std::cerr<<"save html errno"<<std::endl;
    exit(3); // 退出码可以自己定
  }

  return 0;
}
