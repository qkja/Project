#ifndef __DATA_HPP__
#define __DATA_HPP__

#include "util.hpp"
#include <mysql/mysql.h>
#include <mutex>
#include <assert.h>

namespace aod
{
  static MYSQL *MySQLInit()
  {
    // 初始化句柄
    MYSQL *mysql = mysql_init(NULL);
    assert(mysql);

    // 链接服务器
    if (NULL == mysql_real_connect(mysql /*句柄*/, "127.0.0.1", "root", "" /*密码*/, "aod_system" /*数据库名称*/, 0 /*0 默认 就是3306*/, NULL, 0))
    {
      printf("数据库链接失败\n");
      mysql_close(mysql);
      return nullptr;
    }
    mysql_set_character_set(mysql, "utf8");
    return mysql;
  }

  static void MySQLDestroy(MYSQL *mysql)
  {
    if (mysql == nullptr)
      return;
    mysql_close(mysql);
  }

  static bool MySQLQuery(MYSQL *mysql, const std::string &sql)
  {
    int ret = mysql_query(mysql, sql.c_str());
    if (ret != 0)
    {
      std::cout << "sql:  " << sql << std::endl;
      std::cout << mysql_errno(mysql) << std::endl;  
      return false;
    }
    return true;
  }
  
  class TableVideo
  {
  public:
    TableVideo()
    {
    }
    ~TableVideo()
    {
    }

  public:
    /// @brief 插入数据
    /// @param video
    /// @return
    bool Insert(const Json::Value &video)
    {
    }

    bool Update(int video_id, const Json::Value &video)
    {
    }

    bool Delete(int video_id)
    {
    }
    bool SelectAll(Json::Value *videos)
    {
    }
    bool SelectOne(int video_id, Json::Value *video)
    {
    }
    bool SelectLike(const std::string &key, Json::Value *videos)
    {
    }

  private:
    MYSQL *_mysql;
    std::mutex _mutex;
  };
}

#endif