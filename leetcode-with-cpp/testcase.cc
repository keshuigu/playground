#include "testcase.h"

#include <iostream>
Testcase::Test::Test(/* args */) {}

Testcase::Test::~Test() {}

void Testcase::Test::test_2908() {
  std::vector<int> v = {8, 6, 1, 5, 3};
  std::cout << (new SolB2K5A3K::Solution())->solution_2908(v) << std::endl;
  std::vector<int> v1 = {5, 4, 8, 7, 10, 2};
  std::cout << (new SolB2K5A3K::Solution())->solution_2908(v1) << std::endl;
  std::vector<int> v2 = {6, 5, 4, 3, 4, 5};
  std::cout << (new SolB2K5A3K::Solution())->solution_2908(v2) << std::endl;
}

void Testcase::Test::test_1004() {
  std::vector<int> v = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
  std::cout << (new SolB1KA1K5::Solution())->solution_1004(v, 2) << std::endl;
  std::vector<int> v1 = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0,
                         1, 1, 0, 0, 0, 1, 1, 1, 1};
  std::cout << (new SolB1KA1K5::Solution())->solution_1004(v1, 3) << std::endl;
}

void Testcase::Test::test_2810() {
  std::cout
      << (new SolB2K5A3K::Solution())->solution_2810(std::string("string"))
      << std::endl;
  std::cout
      << (new SolB2K5A3K::Solution())->solution_2810(std::string("poiinter"))
      << std::endl;
}