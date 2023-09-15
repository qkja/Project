#include <mysql/mysql.h>
#include <mutex>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <stdlib.h>

namespace aod
{

  static MYSQL *MysqlInit()
  {
#define HOST "127.0.0.1"
#define USER "root"
#define PASSWARD ""
#define DB "aod_system"
#define PORT 3306

    MYSQL *mysql = mysql_init(nullptr);
    if (nullptr == mysql)
    {
      std::cerr << "创建句柄失败" << std::endl;
      return nullptr;
    }
    // 1 . 登录认证
    if (mysql_real_connect(mysql, HOST, USER, PASSWARD, DB, PORT, nullptr, 0) == nullptr)
    {
      std::cerr << "链接数据库失败" << std::endl;
      mysql_close(mysql);
      return nullptr;
    }
    std::cerr << "链接数据库成功" << std::endl;
    // 2. 设置字符集
    mysql_set_character_set(mysql, "utf8");

    return mysql;
  }
  static void MysqlDestroy(MYSQL *mysql)
  {
    if (nullptr == mysql)
      return;
    mysql_close(mysql);
  }
  static bool MysqlQuery(MYSQL *mysql, const std::string &sql)
  {
    int ret = mysql_query(mysql, sql.c_str());
    if (ret != 0)
    {
      std::cerr << "sql: " << sql << std::endl;
      std::cerr << mysql_errno(mysql) << std::endl;
      return false;
    }

    return true;
  }

  class TableVideo
  {
  private:
    MYSQL *_mysql;     // 一个对象就是一个客户端，管理一张表
    std::mutex _mutex; // 防备操作对象在多线程中使用存在的线程安全 问题
  public:
    TableVideo()
    {
      _mysql = MysqlInit();
      if (nullptr == _mysql)
        exit(-1);
    }
    ~TableVideo()
    {
      MysqlDestroy(_mysql);
    } // 释放msyql操作句柄
    bool Insert(const Json::Value &video)
    {
      // id name info video video
      std::string sql;
      sql.resize(4096 + video["info"].asString().size());
#define INSERT_VIDEO "insert tb_video values(null, '%s', '%s', '%s', '%s' )"
      sprintf(&sql[0], INSERT_VIDEO, video["name"].asCString(),
              video["info"].asCString(),
              video["video"].asCString(),
              video["video"].asCString());

      MysqlQuery(_mysql, sql);
    }
    bool Update(int video_id, const Json::Value &video)
    {
    }
    bool Delete(const int video_id);                              // 删除-传入视频ID
    bool SelectAll(Json::Value *videos);                          // 查询所有--输出所有视频信息
    bool SelectOne(int video_id, Json::Value *video);             // 查询单个-输入视频id,输出信息
    bool SelectLike(const std::string &key, Json::Value *videos); // 模糊匹配-输入名称关键字，输出视频信息
  };
}