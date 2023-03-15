#ifndef __DATA_HPP__
#define __DATA_HPP__

#include "util.hpp"
#include <mysql/mysql.h>
#include <mutex>
#include <assert.h>
#include <stdlib.h>

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
      _mysql = MySQLInit();
      if (_mysql == nullptr)
      {
        exit(-1);
      }
    }
    ~TableVideo()
    {
      MySQLDestroy(_mysql);
    }

  public:
    /// @brief 插入数据
    /// @param video
    /// @return
    bool Insert(const Json::Value &video)
    {
      // id, name, info, video, image
      std::string sql;
      sql.resize(4096 + video["info"].asString().size());

#define INSERRT_VIDEO "insert tb_video values(null, '%s', '%s', '%s', '%s');"
      sprintf(&sql[0], INSERRT_VIDEO,
              video["name"].asCString(),
              video["info"].asCString(),
              video["video"].asCString(),
              video["image"].asCString());

      return MySQLQuery(_mysql, sql);
    }

    bool Update(int video_id, const Json::Value &video)
    {
      std::string sql;
      sql.resize(4096 + video["info"].asString().size());
#define UPDATE_VIDEO "update tb_video set name='%s', info='%s' where id = %d;"
      sprintf(&sql[0], UPDATE_VIDEO,
              video["name"].asCString(),
              video["info"].asCString(),
              video_id);
      return MySQLQuery(_mysql, sql);
    }

    bool Delete(int video_id)
    {
#define DELETE_VIDEO "delete from tb_video where id = %d;"
      std::string sql;
      sql.resize(1024);
      sprintf(&sql[0], UPDATE_VIDEO, video_id);
      return MySQLQuery(_mysql, sql);
    }

    /// @brief 注意,为何加锁我们还不知道,这里有点虚
    /// @param videos
    /// @return
    bool SelectAll(Json::Value *videos)
    {

#define SELECTALL_VIDEO "select * from tb_video;"
      _mutex.lock();

      bool ret = MySQLQuery(_mysql, SELECTALL_VIDEO);
      if (ret == false)
      {
        _mutex.unlock();
        return false;
      }

      // 保存结果到本地
      // 保存结果集到本地
      MYSQL_RES *res = mysql_store_result(_mysql);
      if (NULL == res)
      {
        printf("保存的数据出错了 %s\n", mysql_error(_mysql));
        _mutex.unlock();

        return false;
      }
      // 得到行数
      int row_num = mysql_num_rows(res);

      for (int i = 0; i < row_num; i++)
      {
        MYSQL_ROW row = mysql_fetch_row(res);
        // 得到一行
        Json::Value video;
        video["id"] = atoi(row[0]);
        video["name"] = row[1];
        video["info"] = row[2];
        video["video"] = row[3];
        video["image"] = row[4];
        videos->append(video); // 这里我感觉很不适应,项目反转的时候我们注意一下
      }

      _mutex.unlock();
      mysql_free_result(res);
      return true;
    }

    bool SelectOne(int video_id, Json::Value *video)
    {
#define SELECTONE_VIDEO "select  from tb_video where id = %d;"
      _mutex.lock();
      std::string sql;
      sql.resize(1024);
      sprintf(&sql[0], SELECTONE_VIDEO, video_id);
      bool ret = MySQLQuery(_mysql, sql);
      if (ret == false)
      {
        _mutex.unlock();
        return false;
      }

      // 保存结果到本地
      // 保存结果集到本地
      MYSQL_RES *res = mysql_store_result(_mysql);
      if (NULL == res)
      {
        printf("保存的数据出错了 %s\n", mysql_error(_mysql));
        _mutex.unlock();

        return false;
      }

      int row_num = mysql_num_rows(res);
      if (row_num != 1)
      {
        std::cerr << "没有找到数据" << std::endl;
        mysql_free_result(res);
        _mutex.unlock();
        return false;
      }
      MYSQL_ROW row = mysql_fetch_row(res);

      Json::Value video;
      (*video)["id"] = atoi(row[0]);
      (*video)["name"] = row[1];
      (*video)["info"] = row[2];
      (*video)["video"] = row[3];
      (*video)["image"] = row[4];

      _mutex.unlock();
      mysql_free_result(res);
      return true;
    }

    bool SelectLike(const std::string &key, Json::Value *videos)
    {
#define SELECTLIKE_VIDEO "select from tb_video where name like '%%%s%%';"
      _mutex.lock();
      std::string sql;
      sql.resize(1024);
      sprintf(&sql[0], SELECTLIKE_VIDEO, key.c_str());
      bool ret = MySQLQuery(_mysql, sql);
      if (ret == false)
      {
        _mutex.unlock();
        return false;
      }

      // 保存结果到本地
      // 保存结果集到本地
      MYSQL_RES *res = mysql_store_result(_mysql);
      if (NULL == res)
      {
        printf("保存的数据出错了 %s\n", mysql_error(_mysql));
        _mutex.unlock();
        return false;
      }

      int row_num = mysql_num_rows(res);
      for (size_t i = 0; i < row_num; i++)
      {
        MYSQL_ROW row = mysql_fetch_row(res);
        Json::Value video;
        video["id"] = atoi(row[0]);
        video["name"] = row[1];
        video["info"] = row[2];
        video["video"] = row[3];
        video["image"] = row[4];
        videos->append(video);
      }
      _mutex.unlock();
      mysql_free_result(res);
      return true;
    }

  private:
    MYSQL *_mysql;
    std::mutex _mutex;
  };
}

#endif