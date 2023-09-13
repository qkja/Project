#pragma once

#include <vector>
#include <string>

int splitPagce(std::vector<std::string> *result, std::string &package)
{
  result->push_back(package);
  return 0;
}
