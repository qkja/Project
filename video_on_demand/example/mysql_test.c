/**
* User: Qkj
* Description: 测试mysql
* Date: 2023-03-06
* Time: 19:54
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mysql/mysql.h>

// 增加
int add(MYSQL* mysql)
{
  assert(mysql);
  const char* sql = "insert into test_tb values(null, 18, '小张', 77.5);";

  // 执行语句
  int ret = mysql_query(mysql, sql);
  if(ret != 0)
  {
    printf("sql 语句执行失败, %s  失败原因 %s\n", sql, mysql_error(mysql));
    return -2;
  }
  return 0;
}

// 修改
int mod(MYSQL* mysql)
{
  assert(mysql);
  const char* sql = "update test_tb set name='小王' where id=2;";
  // 执行语句
  int ret = mysql_query(mysql, sql);
  if(ret != 0)
  {
    printf("sql 语句执行失败, %s  失败原因 %s\n",sql, mysql_error(mysql));
    return -2;
  }
  return 0;
}

// 删除
int del(MYSQL* mysql)
{
  assert(mysql);
  const char* sql = "delete from test_tb set where id=2;";
  // 执行语句
  int ret = mysql_query(mysql, sql);
  if(ret != 0)
  {
    printf("sql 语句执行失败, %s  失败原因 %s\n", sql, mysql_error(mysql));
    return -2;
  }
  return 0;
}

// 查询 
int get(MYSQL* mysql)
{
  assert(mysql);
  const char* sql = "select * from test_t;";
  // 执行语句
  int ret = mysql_query(mysql, sql);
  if(ret != 0)
  {
    printf("sql 语句执行失败, %s  失败原因 %s\n", sql, mysql_error(mysql));
    return -2;
  }


  // 保存结果集到本地
  MYSQL_RES* res = mysql_store_result(mysql);
  if(NULL == res)
  {
    printf("保存的数据出错了 %s\n", mysql_error(mysql));
    return 3;
  }
  // 得到行数
  int row_num = mysql_num_rows(res);
  // 得到子段数
  int col_num = mysql_num_fields(res);

  for(int i = 0; i < row_num; i++)
  {
    MYSQL_ROW row = mysql_fetch_row(res);
    for(int j = 0; j < col_num; j++)
    {
      printf("%s\t", row[j]);
    }
    printf("\n");
  }

  // 一定要释放掉
  mysql_free_result(res);
  return 0;
}



int main()
{
  // 初始化句柄
  MYSQL* mysql = mysql_init(NULL);
  assert(mysql);

  // 链接服务器
  if (NULL == mysql_real_connect(mysql /*句柄*/, "127.0.0.1", "root", "" /*密码*/, "test_db" /*数据库名称*/, 0 /*0 默认 就是3306*/, NULL, 0))
  {
    printf("数据库链接失败\n");
    return -1;
  }

  // 设置客户端字符集
  mysql_set_character_set(mysql, "utf8");

  mysql_close(mysql);
  return 0;
}