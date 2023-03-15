/**
 * User: Qkj
 * Description:测试工具类
 * Date: 2023-03-14
 * Time: 20:30
 */
#include "util.hpp"
#include "data.hpp"
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
  const char *name = "四小明";
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

void DataTset()
{
  aod::TableVideo tb_video;
  Json::Value video;
  // video["name"] = "白娘子传奇";
  // video["info"] = "这是一条白蛇和青蛇之间的故事,精彩";
  // video["video"] = "/video/snake.mp4";
  // video["image"] = "/img/sanke.jpg";

  // video["name"] = "变形金刚";
  // video["info"] = "机器人大战,等你来战";
  // video["video"] = "/video/robot.mp4";
  // video["image"] = "/video/robot.jpg";

  // tb_video.Insert(video);
  // tb_video.Update(2,video);
  // tb_video.SelectAll(&video);
  //tb_video.SelectOne(2, &video);
  //tb_video.SelectLike("传奇", &video);

  // 如何产看结果 序列化
  // std::string body;
  // aod::JsonUtil::Serialize(video, &body);
  // std::cout << body << std::endl;
  tb_video.Delete(1);
}

int main()
{
  // FileTset();
  // JsonTset();
  DataTset();
  return 0;
}
