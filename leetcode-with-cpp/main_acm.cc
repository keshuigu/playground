#include <iostream>

#include "solution_1_500.h"
#include "solution_500_1000.h"
int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums;
  for (int i = 0; i < n; i++) {
    int x;
    std::cin >> x;
    nums.push_back(x);
  }
  int val;
  std::cin >> val;
  std::cout << (new SolB1A5K::Solution())->solution_27(nums, val) << std::endl;
  return 0;
}