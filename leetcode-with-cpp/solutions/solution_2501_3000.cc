#include <algorithm>
#include <deque>
#include <functional>
#include <ranges>
#include <unordered_map>

#include "my_solution.h"
using namespace MySolution;
using std::deque;
using std::function;
using std::max;
using std::min;
using std::unordered_map;
using std::ranges::lower_bound;
using std::ranges::upper_bound;
int Solution::solution_2908(vector<int>& nums) {
  int n = nums.size();
  vector<int> pre(n);
  vector<int> suf(n);
  int pcur = 0x3f3f3f3f;
  int scur = 0x3f3f3f3f;
  for (int i = 0; i < n; i++) {
    if (nums[i] < pcur) {
      pcur = nums[i];
    }
    pre[i] = pcur;
  }

  for (int i = n - 1; i >= 0; i--) {
    if (nums[i] < scur) {
      scur = nums[i];
    }
    suf[i] = scur;
  }
  int ans = 0x3f3f3f3f;
  for (int i = 1; i < n - 1; i++) {
    if (nums[i] > pre[i] && nums[i] > suf[i]) {
      ans = min(ans, nums[i] + pre[i] + suf[i]);
    }
  }
  if (ans < 0x3f3f3f3f)
    return ans;
  else
    return -1;
}

string Solution::solution_2810(string s) {
  deque<char> d;
  bool tail = true;
  for (auto&& n : s) {
    if (n == 'i') {
      tail = !tail;
    } else if (tail) {
      d.push_back(n);
    } else {
      d.push_front(n);
    }
  }
  return tail ? string(d.begin(), d.end()) : string(d.rbegin(), d.rend());
}

int Solution::solution_2529(vector<int>& nums) {
  int neg = lower_bound(nums, 0) - nums.begin();
  int pos = nums.end() - upper_bound(nums, 0);
  return max(neg, pos);
}

int Solution::solution_2923(vector<vector<int>>& grid) {
  int ans = 0;
  for (int i = 0; i < grid.size(); i++) {
    if (grid[i][ans]) {
      ans = i;
    }
  }
  return ans;
}

int Solution::solution_2924(int n, vector<vector<int>>& edges) {
  vector<int> lose(n, 0);
  for (auto&& e : edges) {
    lose[e[1]] = 1;
  }
  int ans = -1;
  for (int i = 0; i < n; i++) {
    if (lose[i]) {
      continue;
    }
    if (ans != -1) {
      return -1;
    }
    ans = i;
  }
  return ans;
}
int Solution::solution_2385(TreeNode* root, int start) {
  TreeNode* fa[100001];
  TreeNode* start_node;
  function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* node,
                                                 TreeNode* from) {
    if (node == nullptr) {
      return;
    }
    fa[node->val] = from;
    if (node->val == start) {
      start_node = node;
    }
    dfs(node->left, node);
    dfs(node->right, node);
  };
  function<int(TreeNode*, TreeNode*)> maxDepth = [&](TreeNode* node,
                                                     TreeNode* from) -> int {
    if (node == nullptr) {
      return -1;
    }
    int res = -1;
    if (node->left != from) {
      res = max(res, maxDepth(node->left, node));
    }
    if (node->right != from) {
      res = max(res, maxDepth(node->right, node));
    }
    if (fa[node->val] != from) {
      res = max(res, maxDepth(fa[node->val], node));
    }
    return res + 1;
  };

  dfs(root, nullptr);
  return maxDepth(start_node, start_node);
}