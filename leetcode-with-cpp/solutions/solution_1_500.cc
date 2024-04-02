#include "my_solution.h"
using namespace MySolution;
Solution::Solution(/* args */) {}
Solution::~Solution() {}

int Solution::solution_27(std::vector<int>& nums, int val) {
  int n = nums.size();
  int slowIndex = 0;
  for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
    // 如果是需要移除的
    // fast向前找不是被移除
    // slow指向需要移除的
    if (val != nums[fastIndex]) {
      nums[slowIndex++] = nums[fastIndex];
    }
  }
  return slowIndex;
}