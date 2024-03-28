#include <iostream>

#include "solution_1_500.h"
#include "solution_500_1000.h"
int main() {
  std::vector<int> nums = {3, 2, 2, 3};
  int val = 3;
  std::cout << (new SolB1A5K::Solution())->solution_27(nums, val) << std::endl;
  return 0;
}