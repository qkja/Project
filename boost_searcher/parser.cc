/**
 * User: Qkj
 * Description:  去标签/数据清洗
 * Date: 2023-02-27
 * Time: 20:08
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include <boost/filesystem.hpp> // 引入boost库

#include "util.hpp"

// 这是一个目录,下面放的是所有的html网页
const std::string src_path = "data/input";

// 下面是一个文本文件,该文件保存所有的 网页清洗后的数据
const std::string output = "data/raw_html/raw.txt";

// 解析网页格式
typedef struct DocInfo
{
  std::string title;   // 文档标题
  std::string content; // 文旦内容
  std::string url;     // 该文档在官网的的url
} DocInfo_t;

/// @brief  把目录下的所有html 文件名 保存到 数组中
/// @param src_path 目录
/// @param file_list 数组指针,数组中保存文件名
/// @return 成功返回ture,否则就是false
static bool EnumFile(const std::string &src_path, std::vector<std::string> *file_list)
{
  assert(file_list);
  namespace fs = boost::filesystem; // 这是一个习惯
  fs::path root_path(src_path);     // 定义一个path对象

  if (fs::exists(root_path) == false) // 判断路径是不是存在
  {
    std::cerr << src_path << " 路径是不存在的" << std::endl;
    return false;
  }

  // 定义一个空的迭代器, 用来判断 迭代器递归结束
  fs::recursive_directory_iterator end;
  for (fs::recursive_directory_iterator iter(root_path); iter != end; iter++)
  {
    // 保证是普通的文件
    if (fs::is_regular_file(*iter) == false)
    {
      continue;
    }

    // 普通文件需要 html 文件后缀结束
    if (iter->path().extension() != ".html")
    {
      continue;
    }

    // std::cout << "debug: " << iter->path().string() << std::endl;

    // 此时一定 是以 html 后缀结尾的普通文件
    file_list->push_back(iter->path().string());
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////
/// @brief  提取title
/// @param file
/// @param title
/// @return
static bool ParseTitle(const std::string &file, std::string *title)
{
  assert(title);
  std::size_t begin = file.find("<title>");

  if (begin == std::string::npos)
  {
    return false;
  }

  std::size_t end = file.find("</title>");
  if (end == std::string::npos)
  {
    return false;
  }

  begin += std::string("<title>").size();
  // if (begin >= end)
  // 这里允许 没有标题的
  if (begin > end)
  {
    // if(begin == end)
    // {
    //   std::cout << file <<std::endl;
    // }
    return false;
  }
  // 这里我想测试一下 如果先相等的话  我们结构体的个数是不是会发生变化
  // 在家里面我们确实存在了些问题
  // 这里一定是 存在 title的
  *title = file.substr(begin, end - begin);
  return true;
}

/// @brief 提取 内容
/// @param file
/// @param content
/// @return
static bool ParseContent(const std::string &file, std::string *content)
{
  assert(content);
  // 这就是我们去标签最重要的地方
  // 我们这里使用一个简单的状态机

  enum status
  {
    LABLE,
    CONTENT
  };
  enum status s = LABLE; // 默认第一个是 '<'

  for (char ch : file) // 注意这里我没有使用引用,后面解释
  {
    switch (s)
    {
    case LABLE:
      if (ch == '>')
      {
        // 此时意味这当前的标签被处理完毕
        s = CONTENT;
      }
      break;

    case CONTENT:
      if (ch == '<')
      {
        s = LABLE;
      }
      else
      {
        // 这里有一个细节 我们不想要'\n' 字符
        // 我们希望用'\n' 作为分隔符
        // 注意,这个应该不会出现\n,
        // 毕竟我们读取文件的时候使用的getline,可是不我们不能把希望寄托到被人身上
        if (ch == '\n')
        {
          ch = ' ';
        }
        content->push_back(ch);
      }
      break;

    default:
      break;
    }
  }
  return true;
}

/// @brief 提取url
/// @param file
/// @param url
/// @return
static bool ParseUrl(const std::string &file_path, std::string *url)
{
  assert(url);

  // 我们实际上的url 和库里面的url 是不一样的,有对应关系
  // 官网URL样例： https://www.boost.org/doc/libs/1_78_0/doc/html/accumulators.html
  // 我们下载下来的url样例：boost_1_78_0/doc/html/accumulators.html
  // data/input/accumulators.html

  //  url_head = "https://www.boost.org/doc/libs/1_78_0/doc/html"
  //  url_tail = "/accumulators.html"
  std::string url_head = " https://www.boost.org/doc/libs/1_78_0/doc/html";
  std::string url_tail = file_path.substr(src_path.size());
  *url = url_head + url_tail;

  return true;
}

/// @brief  仅仅是为了调试
/// @param doc
void ShowDoc(const DocInfo_t &doc)
{
  std::cout << "title: " << doc.title << std::endl;
  std::cout << "content: " << doc.content << std::endl;
  std::cout << "url: " << doc.url << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////

/// @brief 读取数组中的每一个文件里面的内容,把它保存到一个结构体中,其中结构体放在数组中
/// @param file_list 保存文件名的数组
/// @param results  保存结构体的数组指针
/// @return  成功返回ture,否则就是false
static bool ParseHtml(const std::vector<std::string> &file_list, std::vector<DocInfo_t> *results)
{
  assert(results);
  for (auto &file_path : file_list)
  {
    // 1. 读取文件
    std::string result;
    if (false == ns_util::FileUtil::ReadFile(file_path, &result))
    {
      continue;
    }

    DocInfo_t doc;
    // 2. 提取title
    if (false == ParseTitle(result, &doc.title))
    {
      continue;
    }
    // 3. 提取content  本质时 去标签
    if (false == ParseContent(result, &doc.content))
    {
      continue;
    }
    // 4. 提取url
    if (false == ParseUrl(file_path, &doc.url))
    {
      continue;
    }
    // for debug
    // ShowDoc(doc);
    // break;
    // 到这里一定时完成了解析任务
    results->push_back(std::move(doc)); // 右值引用
  }

  return true;
}

/// @brief 把结构体数组的内容保存按照一定的格式保存到 文件中
/// @param results 结构体数组
/// @param output  文件名
/// @return 成功返回ture,否则就是false
static bool SaveHtml(const std::vector<DocInfo_t> &results, const std::string &output)
{
#define SEP "\3"
  // 我们按照下面的方式,要知道我们把文档的内容去掉了\n
  // title\3content\3url\n title\3content\3url\n title\3content\3url\n return true;

  // explicit basic_ofstream (const char* filename,
  //                       ios_base::openmode mode = ios_base::out);
  std::ofstream out(output, std::ios::out | std::ios::binary);

  if (out.is_open() == false)
  {
    std::cerr << "打开文件失败 " << output << std::endl;
    return false;
  }

  for (auto &e : results)
  {
    std::string str = e.title;
    str += SEP;

    str += e.content;
    str += SEP;

    str += e.url;
    str += "\n";
    out.write(str.c_str(), str.size());
  }
  out.close();
  return true;
}

int main(void)
{
  // 保存所有的 html 的文件名
  std::vector<std::string> file_list;

  // 第一步: EnumFile 枚举所有的文件名(带路径),仅限 网页,方便后期对一个一个文件进行读取
  if (false == EnumFile(src_path, &file_list))
  {
    std::cerr << "枚举文件名失败" << std::endl;
    return 1;
  }

  // 第二部:读取每一个文件的内容,进行解析,解析的格式 为DocInfo_t
  std::vector<DocInfo_t> results;

  if (false == ParseHtml(file_list, &results))
  {
    std::cerr << "解析文件失败" << std::endl;
    return 2;
  }

  // std::cout << "读取文件的个数 " << results.size() << std::endl;
  // 第三步: 把解析文件的内容写入到output中,按照\3\n 作为每一个文档的分割符
  if (false == SaveHtml(results, output))
  {
    std::cerr << "保存文件失败" << std::endl;
    return 3;
  }
  return 0;
}