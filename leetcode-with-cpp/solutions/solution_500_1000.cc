#include "solution_500_1000.h"
SolB5HA1K::Solution::Solution(/* args */) {}
SolB5HA1K::Solution::~Solution() {}
int SolB5HA1K::Solution::solution_704(std::vector<int>& nums, int target) {
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