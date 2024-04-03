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

TreeNode* Solution::solution_1379(TreeNode* original, TreeNode* cloned,
                                  TreeNode* target) {
  if (!original || original == target) {
    return cloned;
  }
  TreeNode* ans = solution_1379(original->left, cloned->left, target);
  if (ans) {
    return ans;
  } else {
    return solution_1379(original->right, cloned->right, target);
  }
}