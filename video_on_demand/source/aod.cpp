/**
 * User: Qkj
 * Description:测试工具类
 * Date: 2023-03-14
 * Time: 20:30
 */
#include "util.hpp"
/// @brief 工具集的测试
void FileTset()
{
  aod::FileUtil("./www").CreateDirectory();
  aod::FileUtil("./www/index.html").SetContent("aaaaaaaaaaaaaaaaaaaaaaa");
  std::string body;
  aod::FileUtil("./www/index.html").GetContent(&body);
  std::cout << body << std::endl;
  std::cout << aod::FileUtil("./www/index.html").Size() << std::endl;
}
int main()
{
  FileTset();
  return 0;
}
