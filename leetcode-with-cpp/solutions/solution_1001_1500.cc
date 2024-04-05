#include <climits>
#include <functional>
#include <set>

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

int Solution::solution_1026(TreeNode* root) {
  multiset<int> vals;
  int ans = 0;
  function<void(TreeNode*)> dfs = [&](TreeNode* node) {
    vals.insert(node->val);
    ans = max({ans, *vals.rbegin() - node->val, node->val - *vals.begin()});
    if (node->left) {
      dfs(node->left);
    }
    if (node->right) {
      dfs(node->right);
    }
    vals.erase(vals.find(node->val));
  };
  dfs(root);
  return ans;
}

int Solution::solution_1026_2(TreeNode* root) {
  int ans = 0;
  function<pair<int, int>(TreeNode*)> dfs =
      [&](TreeNode* node) -> pair<int, int> {
    if (node == nullptr) {
      return {INT_MAX, INT_MIN};
    }
    int mn = node->val, mx = mn;
    auto [l_mn, l_mx] = dfs(node->left);
    auto [r_mn, r_mx] = dfs(node->right);
    mn = min(mn, min(l_mn, r_mn));
    mx = max(mx, max(l_mx, r_mx));
    ans = max(ans, max(node->val - mn, mx - node->val));
    return {mn, mx};
  };
  dfs(root);
  return ans;
}