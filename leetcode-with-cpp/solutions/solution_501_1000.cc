#include "my_solution.h"
using namespace MySolution;
int Solution::solution_704(vector<int>& nums, int target) {
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

vector<TreeNode*> Solution::solution_894(int n) {
  // 可以直接拿到外面，因为n不影响这些计算出的值
  vector<TreeNode*> f[11];
  f[0] = {};
  f[1] = {new TreeNode()};
  for (int i = 2; i < 11; i++) {  // 计算f[i]，在题目给的数据范围内最多11个叶子
    for (int j = 1; j < i; j++) {
      // 枚举左子树叶子数 左子树叶子数+右子树叶子数=i
      for (auto&& left : f[j]) {         // 枚举左子树
        for (auto&& right : f[i - j]) {  // 枚举右子树
          f[i].push_back(new TreeNode(0, left, right));
        }
      }
    }
  }
  return f[n % 2 ? (n + 1) / 2 : 0];
}