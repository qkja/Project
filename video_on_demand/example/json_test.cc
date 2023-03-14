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

int main()
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
  return 0;
}