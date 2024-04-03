#include "my_solution.h"
#define inf 0x3f3f3f3f
using namespace MySolution;
Solution::Solution(/* args */) {}
Solution::~Solution() {}

int Solution::solution_27(vector<int>& nums, int val) {
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

int Solution::solution_209(int target, vector<int>& nums) {
  int left = 0, ans = inf, s = 0;
  for (int right = 0; right < nums.size(); right++) {
    s += nums[right];
    while (s >= target) {
      ans = std::min(ans, right - left + 1);
      s -= nums[left++];
    }
  }
  return ans == inf ? 0 : ans;
}