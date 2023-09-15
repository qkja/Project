/**
 * User: Qkj
 * Description: 测试mysql
 * Date: 2023-03-06
 * Time: 19:54
 */

// #include <iostream>
// #include <cstdio>
// #include <string>
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>
// using namespace std;

// // 增加
// int add(MYSQL *mysql)
// {
//   assert(mysql);
//   const char *sql = "insert into test_tb values(null, 18, '小张', 77.5);";

//   // 执行语句
//   int ret = mysql_query(mysql, sql);
//   if (ret != 0)
//   {
//     printf("sql 语句执行失败, %s  失败原因 %s\n", sql, mysql_error(mysql));
//     return -2;
//   }
//   return 0;
// }

// // 修改
// int mod(MYSQL *mysql)
// {
//   assert(mysql);
//   const char *sql = "update test_tb set name='小王' where id=2;";
//   // 执行语句
//   int ret = mysql_query(mysql, sql);
//   if (ret != 0)
//   {
//     printf("sql 语句执行失败, %s  失败原因 %s\n", sql, mysql_error(mysql));
//     return -2;
//   }
//   return 0;
// }

// // 删除
// int del(MYSQL *mysql)
// {
//   assert(mysql);
//   const char *sql = "delete from test_tb set where id=2;";
//   // 执行语句
//   int ret = mysql_query(mysql, sql);
//   if (ret != 0)
//   {
//     printf("sql 语句执行失败, %s  失败原因 %s\n", sql, mysql_error(mysql));
//     return -2;
//   }
//   return 0;
// }

// // 查询
// int get(MYSQL *mysql)
// {
//   assert(mysql);
//   const char *sql = "select * from test_t;";
//   // 执行语句
//   int ret = mysql_query(mysql, sql);
//   if (ret != 0)
//   {
//     printf("sql 语句执行失败, %s  失败原因 %s\n", sql, mysql_error(mysql));
//     return -2;
//   }

//   // 保存结果集到本地
//   MYSQL_RES *res = mysql_store_result(mysql);
//   if (NULL == res)
//   {
//     printf("保存的数据出错了 %s\n", mysql_error(mysql));
//     return 3;
//   }
//   // 得到行数
//   int row_num = mysql_num_rows(res);
//   // 得到子段数
//   int col_num = mysql_num_fields(res);

//   for (int i = 0; i < row_num; i++)
//   {
//     MYSQL_ROW row = mysql_fetch_row(res);
//     for (int j = 0; j < col_num; j++)
//     {
//       printf("%s\t", row[j]);
//     }
//     printf("\n");
//   }

//   // 一定要释放掉
//   mysql_free_result(res);
//   return 0;
// }

// int main()
// {
//   // 初始化句柄
//   MYSQL *mysql = mysql_init(NULL);
//   assert(mysql);

//   // 链接服务器
//   if (NULL == mysql_real_connect(mysql /*句柄*/, "127.0.0.1", "root", "" /*密码*/, "test_db" /*数据库名称*/, 0 /*0 默认 就是3306*/, NULL, 0))
//   {
//     printf("数据库链接失败\n");
//     return -1;
//   }

//   // 设置客户端字符集
//   mysql_set_character_set(mysql, "utf8");

//   mysql_close(mysql);
//   return 0;
// }

// int main()
// {

//   MYSQL *my = mysql_init(nullptr); // 创建并初始化一个MySQL句柄
//   if (NULL == mysql_real_connect(my /*句柄*/, "127.0.0.1", "root", "" /*密码*/, "test_db" /*数据库名称*/, 0 /*0 默认 就是3306*/, NULL, 0))
//   {
//     printf("数据库链接失败\n");
//     return -1;
//   }
//   cout << "connect succeed" << endl;
//   mysql_set_character_set(my, "utf8");

//   string sql = "select * from test";
//   int res = mysql_query(my, sql.c_str());
//   if (res != 0)
//   {
//     cout << "execute:" << sql << "failed" << endl;
//     return 2;
//   }
//   cout << "execute:" << sql << endl;
//   MYSQL_RES *result = mysql_store_result(my); // 存放mysql句柄中最后一次返回
//   int rows = mysql_num_rows(result);
//   int cols = mysql_num_fields(result);
//   cout << "行数" << rows << "列数" << cols << endl;
//   MYSQL_FIELD *fields = mysql_fetch_fields(result);
//   for (int i = 0; i < cols; i++)
//   {
//     cout << fields[i].name << "\t";
//   }
//   cout << endl;
//   for (int i = 0; i < rows; i++)
//   {
//     MYSQL_ROW line = mysql_fetch_row(result);
//     for (int j = 0; j < cols; j++)
//     {
//       cout << line[j] << "\t";
//     }
//     cout << endl;
//   }
//   mysql_close(my);
//   return 0;
// }

#include <iostream>
#include <mysql/mysql.h>
using namespace std;
string host = "127.0.0.1";
string user = "root";
string password;
string db = "test_vi_db";
uint16_t port = 3306;

int main()
{
  MYSQL *msql = mysql_init(nullptr);
  if (nullptr == msql)
  {
    cerr << "创建句柄失败" << endl;
    return 0;
  }
  // 1 . 登录认证
  if (mysql_real_connect(msql, host.c_str(), user.c_str(), password.c_str(), db.c_str(), port, nullptr, 0) == nullptr)
  {
    cerr << "链接数据库失败" << endl;
  }
  cerr << "链接数据库成功" << endl;
  // 2. 设置字符集
  mysql_set_character_set(msql, "utf8");
  // string sql = "insert  emp values (31, '吕布', 9999.10)";
  string sql = "select * from emp";

  // 3. sql操作
  int n = mysql_query(msql, sql.c_str());
  if (0 == n)
  {
    // sql语句执行成功
    MYSQL_RES *res = mysql_store_result(msql); // 所有的结果
    int row = mysql_num_rows(res);
    int fields = mysql_num_fields(res);

    MYSQL_FIELD *field = mysql_fetch_fields(res); // 得到所有的字段名
    int i = 0;
    for (; i < fields; i++)
    {
      cout << field[i].name << "\t|\t";
    }
    cout << endl;

    MYSQL_ROW line;
    for (int i = 0; i < row; i++)
    {

      line = mysql_fetch_row(res); // 得到一行数据
      for (int j = 0; j < fields; j++)
      {
        // 解析每一行
        cout << line[j] << "\t|\t";
      }
      cout << endl;
    }
  }

  mysql_close(msql);
  return 0;
}

// 1. 必须先进行初始化
