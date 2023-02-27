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
  if(false == SaveHtml(results, &output))
  {
    std::cerr << "保存文件失败" << std::endl;
    return 3;
  }
  return 0;
}