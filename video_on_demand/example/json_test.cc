/**
 * User: Qkj
 * Description:
 * Date: 2023-03-14
 * Time: 16:35
 */

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <jsoncpp/json/json.h>
void serialize()
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

  Json::StreamWriterBuilder swb;
  std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());

  std::stringstream ss;
  sw->write(val, &ss);

  std::cout << ss.str() << std::endl;
}
// 反序列化
void unserialize()
{
  std::string str = R"({"姓名":"小明", "年龄":18, "成绩":[77.5, 88, 99.5]})";

  Json::Value val;

  Json::CharReaderBuilder crb;
  std::unique_ptr<Json::CharReader> cr(crb.newCharReader());
  std::string err;

  bool ret = cr->parse(str.c_str(), str.c_str() + str.size(), &val, &err);
  if (ret == true)
  {
    std::cout << val["姓名"].asString() << std::endl;
    std::cout << val["年龄"].asString() << std::endl;
    int sz = val["成绩"].size();
    for (int i = 0; i < sz; i++)
    {
      std::cout << val["成绩"][i] << " ";
    }
    std::cout << std::endl;
  }
}

int main()
{
  unserialize();
  return 0;
}
