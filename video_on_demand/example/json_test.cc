/**
 * User: Qkj
 * Description:
 * Date: 2023-03-14
 * Time: 16:35
 */
#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <memory>
#include <fstream>
#include <sstream>
using namespace std;

// #include <iostream>
// #include <sstream>
// #include <string>
// #include <memory>
// #include <jsoncpp/json/json.h>
// void serialize()
// {
//   char *name = "四小明";
//   int age = 18;
//   float score[] = {77.5, 88, 99.5};

//   Json::Value val;
//   val["姓名"] = name;
//   val["年龄"] = 19;
//   val["成绩"].append(score[0]);
//   val["成绩"].append(score[1]);
//   val["成绩"].append(score[2]);

//   Json::StreamWriterBuilder swb;
//   std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());

//   std::stringstream ss;
//   sw->write(val, &ss);

//   std::cout << ss.str() << std::endl;
// }
// // 反序列化
// void unserialize()
// {
//   std::string str = R"({"姓名":"小明", "年龄":18, "成绩":[77.5, 88, 99.5]})";

//   Json::Value val;

//   Json::CharReaderBuilder crb;
//   std::unique_ptr<Json::CharReader> cr(crb.newCharReader());
//   std::string err;

//   bool ret = cr->parse(str.c_str(), str.c_str() + str.size(), &val, &err);
//   if (ret == true)
//   {
//     std::cout << val["姓名"].asString() << std::endl;
//     std::cout << val["年龄"].asString() << std::endl;
//     int sz = val["成绩"].size();
//     for (int i = 0; i < sz; i++)
//     {
//       std::cout << val["成绩"][i] << " ";
//     }
//     std::cout << std::endl;
//   }
// }

// int main()
// {
//   unserialize();
//   return 0;
// }

// #include <iostream>
// #include <string>
// #include <jsoncpp/json/json.h>
// using namespace std;

// int main()
// {
//   Json::Value root;
//   string name1 = "张三";
//   int age1 = 18;
//   double socre1 = 99.5;
//   Json::Value v1;
//   v1["name"] = name1;
//   v1["age"] = age1;
//   v1["score"] = socre1;

//   string name2 = "李四";
//   int age2 = 18;
//   double socre2 = 99.5;
//   Json::Value v2;
//   v2["name"] = name2;
//   v2["age"] = age2;
//   v2["score"] = socre2;

//   root.append(v1);
//   root.append(v2);

//   // Json::FastWriter writer;
//   Json::StyledWriter writer;

//   cout << writer.write(root) << endl;
//   return 0;
// }
// int main()
// {
//   const char *name = "小明";
//   int age = 19;
//   float score[] = {77.5, 88, 99.5};
//   // 构造对象
//   Json::Value val;
//   val["姓名"] = name;
//   val["年龄"] = 19;
//   val["成绩"].append(score[0]);
//   val["成绩"].append(score[1]);
//   val["成绩"].append(score[2]);

//   // 序列化 -- 高版本
//   Json::StreamWriterBuilder swb;
//   std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());

//   std::stringstream ss;
//   int ret = sw->write(val, &ss);
//   if (ret != 0)
//   {
//     std::cout << "write failed!\n";
//     return -1;
//   }
//   std::cout << ss.str() << std::endl;
//   return 0;
// }

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <jsoncpp/json/json.h>
// int main()
// {
//   const char *name = "小明";
//   int age = 19;
//   float score[] = {77.5, 88, 99.5};
//   // 构造对象
//   Json::Value val;
//   val["姓名"] = name;
//   val["年龄"] = 19;
//   val["成绩"].append(score[0]);
//   val["成绩"].append(score[1]);
//   val["成绩"].append(score[2]);

//   // 序列化
//   Json::Writer *wr = new Json::StyledWriter;
//   std::string str = wr->write(val);

//   // 反序列化
//   Json::Value val2;
//   Json::Reader read;
//   read.parse(str, val2);

//   // 打印结果
//   std::cout << val2["姓名"] << std::endl;
//   std::cout << val2["年龄"].asInt() << std::endl;
//   int sz = val2["成绩"].size();
//   for (int i = 0; i < sz; i++)
//   {
//     std::cout << val2["成绩"][i].asFloat() << " ";
//   }
//   std::cout << std::endl;

//   return 0;
// }

// int main()
// {
//   std::string str = R"({"姓名":"小明", "年龄":18, "成绩":[76.5, 55, 88]})"; // 这个是允许的

//   Json::Value root;
//   Json::CharReaderBuilder crb;
//   std::unique_ptr<Json::CharReader> cr(crb.newCharReader());

//   std::string err;
//   cr->parse(str.c_str(), str.c_str() + str.size(), &root, &err);

//   std::cout << root["姓名"].asString() << std::endl;
//   std::cout << root["年龄"].asInt() << std::endl;
//   int sz = root["成绩"].size();
//   for (int i = 0; i < sz; i++)
//   {
//     std::cout << root["成绩"][i].asFloat() << std::endl;
//   }
//   for (auto it = root["成绩"].begin(); it != root["成绩"].end(); it++)
//   {
//     std::cout << it->asFloat() << std::endl;
//   }
//   return 0;
// }