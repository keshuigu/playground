#include <iostream>

#include "p704_search.h"
int main() {
  p704_search* s = new p704_search();
  std::vector<int> nums = {-1, 0, 3, 5, 9, 12};
  int target = 9;
  std::cout << s->search(nums, target) << std::endl;
  return 0;
}