#ifndef __DATA_HPP__
#define __DATA_HPP__

#include "util.hpp"
#include <mysql/mysql.h>
#include <mutex>

namespace aod
{
  static MYSQL *MySQLInit();
  static void MySQLDestroy();
  static bool MySQLQuery(MYSQL *mysql, const std::string &sql);
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