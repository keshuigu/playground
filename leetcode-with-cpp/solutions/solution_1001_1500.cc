#include "my_solution.h"
using namespace MySolution;

int Solution::solution_1004(vector<int>& nums, int k) {
  int left = 0, ans = 0, cnt = 0;
  for (int i = 0; i < nums.size(); i++) {
    cnt += 1 - nums[i];
    while (cnt > k) {
      cnt -= 1 - nums[left++];
    }
    ans = max(ans, i - left + 1);
  }
  return ans;
}