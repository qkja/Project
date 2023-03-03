/**
* User: Qkj
* Description: 
* Date: 2023-03-03
* Time: 16:59
*/
#include <string>
#include <iostream>
#include <vector>

#include <jsoncpp/json/json.h>

int main()
{
  Json::Value root;
  Json::Value item1;
  item1["key1"] = "value1";
  item1["key2"] = "value2";

  Json::Value item2;
  item2["key1"] = "value1";
  item2["key2"] = "value2";

  root.append(item1);
  root.append(item2);

  Json::StyledWriter writer;
  std::string s = writer.write(root);
  std::cout << s << std::endl;
  return 0;
}



//#include <boost/algorithm/string.hpp>
//
//int main()
//{
//  std::vector<std::string> results;
//  std::string target = "aaaa\3\3\3\3bbbb\3cccc";
//
//  // 默认的是不压缩
//  //boost::split(results, target, boost::is_any_of("\3"));
//  
//  // 我们不想保留
//  boost::split(results, target, boost::is_any_of("\3"),
//      boost::token_compress_on);
//
//  for(auto& e:results)
//  {
//    std::cout << e << std::endl;
//  }
//
//  return 0;
//}
