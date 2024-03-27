#include "p704_search.h"
p704_search::p704_search(/* args */) {}
p704_search::~p704_search() {}
int p704_search::search(std::vector<int>& nums, int target) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] < target)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}