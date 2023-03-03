/**
* User: Qkj
* Description: 
* Date: 2023-03-03
* Time: 16:59
*/
#include <string>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

int main()
{
  std::vector<std::string> results;
  std::string target = "aaaa\3\3\3\3bbbb\3cccc";

  // 默认的是不压缩
  //boost::split(results, target, boost::is_any_of("\3"));
  
  // 我们不想保留
  boost::split(results, target, boost::is_any_of("\3"),
      boost::token_compress_on);

  for(auto& e:results)
  {
    std::cout << e << std::endl;
  }

  return 0;
}
