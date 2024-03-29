#include "solution_1000_1500.h"
SolB1KA1K5::Solution::Solution(/* args */) {}
SolB1KA1K5::Solution::~Solution() {}
int SolB1KA1K5::Solution::solution_1004(std::vector<int>& nums, int k) {
  int left = 0, ans = 0, cnt = 0;
  for (int i = 0; i < nums.size(); i++) {
    cnt += 1 - nums[i];
    while (cnt > k) {
      cnt -= 1 - nums[left++];
    }
    ans = std::max(ans, i - left + 1);
  }
  return ans;
}