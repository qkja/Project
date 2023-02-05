/**
* User: Qkj
* Description: 进行去标签工作
* Date: 2023-02-05
* Time: 11:00
*/

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

#include "util.hpp"


// 这是源目录 放的是所有的 html文件
const std::string src_path = "./data/input"; 

// 保存所有去标签的html 文件
const std::string output = "./data/raw_html/raw.txt";

typedef struct DocInfo
{
  std::string title;
  std::string content;
  std::string url;
} DocInfo_t;

bool EnumFile(const std::string& src_path, std::vector<std::string>* file_list)
{
  //std::cout << "=====================" << std::endl;
  //std::cout <<src_path << std::endl;
  //std::cout << "=====================" << std::endl;
  namespace fs = boost::filesystem;
  
  fs::path root_path(src_path);  // 构建一个 path 对象  这里是局部优先,没有问题

  if(!fs::exists(root_path))
  {
    std::cerr << src_path << " 不存在" << std::endl;
    return false;
  }

  // 定义一个 空的迭代器 
  fs::recursive_directory_iterator end;
  for(fs::recursive_directory_iterator iter(root_path); iter != end; iter++)
  {
    // 注意这里是所有的文件 我们必须只要*html文件
    // 刷选常规文件
    if(!fs::is_regular_file(*iter))
    {
      continue;
    }

    // 拿到 *html 文件
    if((iter->path().extension() != ".html"))
    {
      continue;
    }

    //if((*file_list).size()%100 == 0)
    //{
    //  std::cout << "debug " << iter->path().string() <<std::endl;
    //}
    // 此时一定是 .html 文件
    file_list->push_back(iter->path().string());
  }
  //std::cout << file_list->size() << std::endl;
  return true;
}

static bool ParseTitle(const std::string& result, std::string* title)
{
  //搜索 title 关键字
  std::size_t begin = result.find("<title>");
  if(begin == std::string::npos)
  {
    return false;
  }
  std::size_t end = result.find("</title>");
  if(end == std::string::npos)
  {
    return false;
  }
  begin += std::string("<title>").size();

  if(begin>=end)
    return false;

  *title = result.substr(begin, end-begin);
  return true;
}


static bool ParseContent(const std::string& result, std::string* content)
{
  enum status
  {
    LABLE,
    CONTENT
  };

  //std::cout <<"你好  " << result  << std::endl;
  enum status s = LABLE;

  for(char ch:result)
  {
    //std::cout <<"你好  "<< ch  << std::endl;
    switch(s)
    {
      case LABLE:
        if(ch == '>') 
          s = CONTENT;
        break;
      case CONTENT:
        if(ch == '<')
        {
          s = LABLE;
        }
        else 
        {
          // 问题  ch 会 拿到 \n吗 
          // 准确说 getline会不会拿到\n 不会  所以 这里我们可以说是不用担心
          if(ch == '\n')
            ch = ' ';
          content->push_back(ch);
        }
        break;
    }
  }

  return true;
}

static bool ParseUrl(const std::string& file_path, std::string* url)
{
  std::string url_head = "https://www.boost.org/doc/libs/1_78_0/doc/html";
  std::string url_tail = file_path.substr(src_path.size()); 
  *url = url_head + url_tail;
  return true;
}

static void ShowDoc(const DocInfo_t& doc)
{
  std::cout << "标题: " <<doc.title << std::endl;
  std::cout << "内容: " <<doc.content << std::endl;
  std::cout << "url : " <<doc.url << std::endl;
}

bool ParseHtml(const std::vector<std::string>& file_list, std::vector<DocInfo_t>* results)
{
  std::string result;
  for(const std::string& file:file_list)
  {
    // 1. 读取文件
    if(!ns_util::FileUtil::ReadFile(file, &result))
    {
      continue;
    }

    DocInfo_t doc;
    // 2. 提取title
    if(!ParseTitle(result, &doc.title))
    {
      continue;
    }
    // 3. 提取content 本质就是去标签
    if(!ParseContent(result, &doc.content))
    {
      continue;
    }
    // 4. 构建/提取 url
    if(!ParseUrl(file, &doc.url))
    {
      continue;
    }
    
    // for debug
    if(results->size() == 1 || results->size() == 10 
        || results->size() == 15 || results->size() == 50)
    {

      //std::cout << result << std::endl;
      ShowDoc(doc);
    }

    results->push_back(std::move(doc));
    result.clear();
  }
  return true;
}

bool SaveHtml(const std::vector<DocInfo_t>& results, const std::string& output)
{

  return true;
}

int main()
{
  // 1. 保存所有的 文件名
  std::vector<std::string> file_list;
  if(!EnumFile(src_path, &file_list))
  {
    std::cerr << "保存文件名失败 " << std::endl;
    return 1;
  }

  // 2. 读取每一个文件的内容
  std::vector<DocInfo_t> results;
  if(!ParseHtml(file_list, &results))
  {
    std::cerr << "拿到文件内容失败" <<std::endl;
    return 2;
  }

  // 3. 把解析完毕的内容写入到output中, 按照\3作为分割符
  if(!SaveHtml(results, output))
  {
    std::cerr << "保存文件失败" <<std::endl;
    return 3;
  }

  return 0;
}
