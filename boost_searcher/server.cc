/**
 * User: Qkj
 * Description:
 * Date: 2023-01-21
 * Time: 13:54
 */
#include "searcher.hpp"
#include <string>
#include <iostream>

const std::string input = "./data/raw_html/raw.txt";
int main()
{
  // for test
  ns_srearchre::Searcher *search = new ns_srearchre::Searcher();
  search->InitSearcher(input);

  std::string query;
  std::string json_string;
  while (1)
  {
    std::cout << "Please Enter You Searcher# ";
    std::cin >> query;

    //std::cout << query << std::endl;

    search->Search(query, &json_string);

    std::cout << json_string << std::endl;
  }
  return 0;
}
