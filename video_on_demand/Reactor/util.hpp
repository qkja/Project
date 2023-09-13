#pragma once
#include <string>
struct Request
{
  std::string method;
  std::string uri;
  std::string version;
  int length;
  std::string language;
  std::string body;
};

struct Response
{
  std::string version;
  std::string status;
  std::string explain;
  std::string language;
  std::string type;
  std::string body;
  int length;
};
