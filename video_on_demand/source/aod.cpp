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
void JsonTset()
{
  char *name = "四小明";
  int age = 18;
  float score[] = {77.5, 88, 99.5};

  Json::Value val;
  val["姓名"] = name;
  val["年龄"] = 19;
  val["成绩"].append(score[0]);
  val["成绩"].append(score[1]);
  val["成绩"].append(score[2]);

  std::string body;
  aod::JsonUtil::Serialize(val, &body);
  std::cout << body << std::endl;
  std::cout << "=====================================" << std::endl;

  Json::Value stu;
  aod::JsonUtil::UnSerialize(body, &stu);
  std::cout << stu["姓名"].asString() << std::endl;
  std::cout << stu["年龄"].asString() << std::endl;

  // 换一种用法
  for (auto &e : stu["成绩"])
  {
    std::cout << e.asFloat() << std::endl;
  }
  // int sz = stu["成绩"].size();
  // for (int i = 0; i < sz; i++)
  // {
  //   std::cout << stu["成绩"][i] << " ";
  // }
  // std::cout << std::endl;
}

int main()
{
  // FileTset();
  JsonTset();
  return 0;
}
