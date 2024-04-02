#include "my_solution.h"
using namespace MySolution;
int Solution::solution_704(std::vector<int>& nums, int target) {
  int left = -1, right = nums.size();
  while (left + 1 < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] < target)
      left = mid;
    else
      right = mid;
  }
  return -1;
}