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
#include "util.hpp"

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
bool EnumFile(const std::string &src_path, std::vector<std::string> *files_list)
{
  namespace fs = boost::filesystem;

  // 构建一个对象
  fs::path root_path(src_path);
  // 判断 路径是不是存在
  if (!fs::exists(root_path))
  {
    std::cerr << "文件路径不存在" << std::endl;
    return false;
  }

  // 定义一个空的迭代器
  fs::recursive_directory_iterator end;
  for (fs::recursive_directory_iterator iter(root_path); iter != end; iter++)
  {
    // 此时我们遍历所有的文件
    // 筛选出常规文件
    if (!fs::is_regular_file(*iter))
    {
      continue;
    }
    // 检测带路径的文件名
    if (!(iter->path().extension() == ".html"))
    {
      continue;
    }
    // std::cout << iter->path().string() <<std::endl;
    // 当前的路径一定是一个以.html的普通文件
    files_list->push_back(iter->path().string());
  }

  return true;
}

static bool ParseTitle(const std::string &res, std::string *title)
{
  assert(title);
  // 搜索 <title> 和 </title>
  // 剪切字符串
  std::size_t begin = res.find("<title>");
  if (begin == std::string::npos)
  {
    return false;
  }
  std::size_t end = res.find("</title>");
  if (end == std::string::npos)
  {
    return false;
  }

  begin += std::string("<title>").size();
  if (begin > end)
  {
    return false;
  }

  *title = res.substr(begin, end - begin);
  return true;
}

static bool ParseContent(const std::string &res, std::string *content)
{
  assert(content);
  // 基于一个简易的状态机编写
  enum status
  {
    LABLE,
    CONTENT
  };

  enum status s = LABLE;
  for (char ch : res)
  {
    switch (s)
    {
    case LABLE:
      if (ch == '>')
        s = CONTENT;
      break;
    case CONTENT:
      if (ch == '<')
      {
        s = LABLE;
      }
      else
      {
        if (ch == '\n')
          ch = ' ';
        content->push_back(ch);
      }
      break;
    default:
      break;
    }
  }
  return true;
}

// 解析url
static bool ParseUrl(const std::string &file_path, std::string *url)
{
  assert(url);
  std::string url_head = "https://www.boost.org/doc/libs/1_81_0/doc/html";
  // std:: cout << file_path << std::endl;
  std::string url_tail = file_path.substr(src_path.size()); // 这里会自动 带上  /
  // std:: cout << url_tail << std::endl;
  *url = url_head + url_tail;
  return true;
}

void ShowDoc(const DocInfo_t &doc)
{
  std::cout << "title: " << doc.title << std::endl;
  std::cout << "content: " << doc.content << std::endl;
  std::cout << "url: " << doc.url << std::endl;
}
// int g = 0;
// 2. 去标签,把 files_list 中所有的文件内容保存到一个结构体中,
// 把结构体放在 result中
bool ParseHtml(const std::vector<std::string> files_list, std::vector<DocInfo_t> *result)
{
  // std:: cout << "--------------------" <<std::endl;
  assert(result);
  for (const std::string &file : files_list)
  {
    std::string res;
    // 1. 读取
    if (!ns_util::FileUtil::ReadFile(file, &res))
    {
      continue;
    }

    DocInfo_t doc;
    // 2. 提取文件 tile

    if (!ParseTitle(res, &doc.title))
    {
      continue;
    }
    // 3. 提取content  去标签
    if (!ParseContent(res, &doc.content))
    {
      continue;
    }
    // 4. 提取 特定的文件路径,构建  url
    if (!ParseUrl(file, &doc.url))
    {
      continue;
    }
    // 注意 push 会发生拷贝,效率有点低 bug 可以采用右值
    // result->push_back(doc);

    result->push_back(std::move(doc));
    // std:: cout << "--------------------" <<std::endl;
    // if(g == 0)
    //{
    // g++;
    // ShowDoc(doc);
    // }
  }
  return true;
}

bool SaveHtml(const std::vector<DocInfo_t> &result, const std::string &output)
{
#define SEP '\3'

  // 打开文件
  std::ofstream out(output, std::ios::out | std::ios::binary);
  if (!out.is_open())
  {
    std::cerr << " open " << output << " fail" << std::endl;
    return false;
  }
  //  添加写入规则
  std::string s;
  for (auto &it : result)
  {
    s.clear();
    s += it.title;
    s += SEP;
    s += it.content;
    s += SEP;
    s += it.url;
    s += '\n';
    out.write(s.c_str(), s.size());
  }
  out.close();
  return true;
}

int main()
{
  std::vector<std::string> files_list;
  // 1. 保存所有文件名 到 files_list 中
  if (!EnumFile(src_path, &files_list))
  {
    std::cerr << "enum file name errno" << std::endl;
    exit(1); // 退出码可以自己定
  }

  // 2. 去标签
  std::vector<DocInfo_t> result;
  if (!ParseHtml(files_list, &result))
  {
    std::cerr << "parse html errno" << std::endl;
    exit(2); // 退出码可以自己定
  }

  // 3. 把所有文件内容 写入到 output中 ,按照\3作为分割符
  if (!SaveHtml(result, output))
  {
    std::cerr << "save html errno" << std::endl;
    exit(3); // 退出码可以自己定
  }

  return 0;
}
