/**
 * User: Qkj
 * Description:  去标签/数据清洗
 * Date: 2023-02-27
 * Time: 20:08
 */

#include <iostream>
#include <string>
#include <vector>

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
}

/// @brief 读取数组中的每一个文件里面的内容,把他保存到一个结构体中,其中结构体放在数组中
/// @param file_list 保存文件名的数组
/// @param results  保存结构体的数组指针
/// @return  成功返回ture,否则就是false
static bool ParseHtml(const std::vector<std::string> &file_list, std::vector<DocInfo_t> *results)
{
}

/// @brief 把数组结构体的内容保存按照一定的格式保存到 文件中
/// @param results 结构体数组
/// @param output  文件名
/// @return 成功返回ture,否则就是false
static bool SaveHtml(const std::vector<DocInfo_t> &results, const std::string *output)
{
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
  // 第三步: 把解析文件的内容写入到output中,按照\3\n 作为每一个文档的分割符
  if (false == SaveHtml(results, &output))
  {
    std::cerr << "保存文件失败" << std::endl;
    return 3;
  }
  return 0;
}