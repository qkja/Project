/**
 * User: Qkj
 * Description:
 * Date: 2023-03-03
 * Time: 16:59
 **/

#include <iostream>
#include <iostream>
#include <vector>
#include <assert.h>
#include <boost/filesystem.hpp>

std::string src = "/home/bit/Project/boost_searcher/test/abb";

static bool EnumFile(const std::string &src_path, std::vector<std::string> *file_list)
{
  assert(file_list);
  namespace fs = boost::filesystem; // 这是一个习惯,也就是打开 一个命名空间
  fs::path root_path(src_path);     // 定义一个path对象

  //if (fs::exists(root_path) == false) // 判断路径是不是存在
  //{
  //  std::cerr << src_path << " 路径是不存在的" << std::endl;
  //  return false;
  //}

  // 定义一个空的迭代器, 用来判断 迭代器递归结束
  fs::recursive_directory_iterator end;
  for (fs::recursive_directory_iterator iter(root_path); iter != end; iter++)
  {
    // 保证是普通的文件
    //if (fs::is_regular_file(*iter) == false)
    //{
    //  continue;
    //}

    file_list->push_back(iter->path().string());
  }

  return true;
}

int main()
{

  std::vector<std::string> result;
  EnumFile(src, &result);
  for(auto& e: result)
  {
    std::cout << e << std::endl;
  }

  return 0;
}


//#include <string>
//#include <iostream>
//#include <vector>
//
//#include <jsoncpp/json/json.h>
//
//int main()
//{
//  Json::Value root;
//  Json::Value item1;
//  item1["key1"] = "value1";
//  item1["key2"] = "value2";
//
//  Json::Value item2;
//  item2["key1"] = "value1";
//  item2["key2"] = "value2";
//
//  root.append(item1);
//  root.append(item2);
//
//  Json::StyledWriter writer;
//  std::string s = writer.write(root);
//  std::cout << s << std::endl;
//  return 0;
//}
//
// #include <boost/algorithm/string.hpp>
//
// int main()
//{
//   std::vector<std::string> results;
//   std::string target = "aaaa\3\3\3\3bbbb\3cccc";
//
//   // 默认的是不压缩
//   //boost::split(results, target, boost::is_any_of("\3"));
//
//   // 我们不想保留
//   boost::split(results, target, boost::is_any_of("\3"),
//       boost::token_compress_on);
//
//   for(auto& e:results)
//   {
//     std::cout << e << std::endl;
//   }
//
//   return 0;
// }
