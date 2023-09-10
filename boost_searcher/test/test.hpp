#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <unistd.h>

void test(const std::string &name, int len)
{
  umask(0);
  int fd = open("/home/qkj/Project/boost_searcher/test/for_test.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
  std::string s1 = name + std::to_string(len);
  s1 += "\n";

  write(fd, s1.c_str(), s1.size());
  close(fd);
}