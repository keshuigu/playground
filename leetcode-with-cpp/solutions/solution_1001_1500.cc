#include <algorithm>
#include <climits>
#include <functional>
#include <numeric>
#include <set>

#include "my_solution.h"
using namespace MySolution;
using std::accumulate;
using std::function;
using std::max;
using std::max_element;
using std::min;
using std::min_element;
using std::minmax_element;
using std::multiset;
using std::pair;
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

int Solution::solution_1052(vector<int>& customers, vector<int>& grumpy,
                            int minutes) {
  int ans0 = 0;
  for (int i = 0; i < customers.size(); i++) {
    if (grumpy[i] == 0) {
      ans0 += customers[i];
      customers[i] = 0;
    }
  }
  int ans1 = 0, cur = 0;
  for (int right = 0; right < customers.size(); right++) {
    cur += customers[right];
    ans1 = max(ans1, cur);
    if (right < minutes - 1) {
      continue;
    }
    cur -= customers[right - minutes + 1];
  }
  return ans0 + ans1;
}

double Solution::solution_1491(vector<int>& salary) {
  // int mn = *min_element(salary.begin(), salary.end());
  // int mx = *max_element(salary.begin(), salary.end());
  auto [mn_it, mx_it] = minmax_element(salary.begin(), salary.end());
  int mn = *mn_it, mx = *mx_it;
  return (static_cast<double>(accumulate(salary.begin(), salary.end(), 0) - mn -
                              mx) /
          (static_cast<double>(salary.size() - 2)));
}