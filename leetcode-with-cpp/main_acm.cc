#include <iostream>

#include "my_solution.h"
using namespace MySolution;
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
  std::cout << Solution().solution_27(nums, val) << std::endl;
  return 0;
}