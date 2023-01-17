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
#include <cassert>
#include <boost/filesystem.hpp>

// 下面是路径
const std::string src_path = "data/input";
const std::string output = "data/raw_html/raw.txt";

typedef struct DocInfo
{
  std::string title;   // 文档标题
  std::string content; // 文档内容
  std::string url;     // 该文档在官网的url
} DocInfo_t;

// 保存src_path路径下所有文件名 到 files_list 中
bool EnumFile(const std::string& src_path, std::vector<std::string>* files_list)
{
  namespace fs = boost::filesystem;

  // 构建一个对象
  fs::path root_path(src_path);
  // 判断 路径是不是存在
  if(!fs::exists(root_path))
  {
    std::cerr<< "文件路径不存在" << std::endl;
    return false;
  }

  // 定义一个空的迭代器
  fs::recursive_directory_iterator end;
  for(fs::recursive_directory_iterator iter(root_path); iter != end; iter++)
  {
    // 此时我们遍历所有的文件
    // 筛选出常规文件
    if(!fs::is_regular_file(*iter)) 
    {
      continue; 
    }
    // 检测带路径的文件名
    if(!(iter->path().extension() == ".html"))
    {
      continue; 
    }
    // std::cout << iter->path().string() <<std::endl;
    // 当前的路径一定是一个以.html的普通文件
    files_list->push_back(iter->path().string());
  }

  return true;
}

// 2. 去标签,把 files_list 中所有的文件内容保存到一个结构体中,
// 把结构体放在 result中
bool ParseHtml(const std::vector<std::string> files_list, std::vector<DocInfo_t> *result)
{
  assert(result);
  for(const std::string& file : files_list)
  {
    // 1. 读取文件
    
    // 2. 提取文件 tile 
    // 3. 提取content
    // 4. 提取 特定的文件路径,构建  url 
  }
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
