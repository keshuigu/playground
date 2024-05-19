#include <algorithm>
#include <climits>
#include <functional>
#include <numeric>
#include <set>

#include "my_solution.h"
namespace MySolution {
using std::accumulate;
using std::function;
using std::iota;
using std::max;
using std::max_element;
using std::min;
using std::min_element;
using std::minmax_element;
using std::multiset;
using std::pair;
using std::sort;
using std::upper_bound;
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

int Solution::solution_1235(vector<int>& startTime, vector<int>& endTime,
                            vector<int>& profit) {
  int n = startTime.size();
  vector<int> indices(n);
  iota(indices.begin(), indices.end(), 0);
  sort(indices.begin(), indices.end(),
       [&endTime](int x, int y) { return endTime[x] < endTime[y]; });
  vector<int> sortedStartTime(n);
  vector<int> sortedEndTime(n);
  vector<int> sortedProfit(n);
  for (int i = 0; i < n; i++) {
    sortedStartTime[i] = startTime[indices[i]];
    sortedEndTime[i] = endTime[indices[i]];
    sortedProfit[i] = profit[indices[i]];
  }
  vector<int> f(n + 1, 0);
  for (int i = 0; i < n; i++) {
    int j = upper_bound(sortedEndTime.begin(), sortedEndTime.begin() + i,
                        sortedStartTime[i]) -
            sortedEndTime.begin();
    // j是结束时间>开始时间的第一个位置
    // 我们需要的是小于等于开始时间的最后一个位置
    // 也就是j-1
    // 因此转移方程从 f[i+1] = f[j+1]+profit[i] 变成 f[i+1] = f[j]+profit[i]
    f[i + 1] = max(f[i], f[j] + sortedProfit[i]);
  }
  return f[n];
}

int Solution::solution_1463(vector<vector<int>>& grid) {
  int n = grid.size(), m = grid[0].size();
  vector<vector<vector<int>>> f(
      n, vector<vector<int>>(m + 2, vector<int>(m + 2, INT_MIN)));
  f[0][1][m] = grid[0][0] + grid[0][m - 1];
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < m; k++) {
        int val = j != k ? grid[i][j] + grid[i][k] : grid[i][j];
        f[i][j + 1][k + 1] = max({
            f[i - 1][j][k],
            f[i - 1][j + 1][k],
            f[i - 1][j + 2][k],

            f[i - 1][j][k + 1],
            f[i - 1][j + 1][k + 1],
            f[i - 1][j + 2][k + 1],

            f[i - 1][j][k + 2],
            f[i - 1][j + 1][k + 2],
            f[i - 1][j + 2][k + 2],
        });
        f[i][j + 1][k + 1] += val;
      }
    }
  }
  int ans = 0;
  for (int j = 0; j < m; j++) {
    for (int k = 0; k < m; k++) {
      ans = max(ans, f[n - 1][j + 1][k + 1]);
    }
  }
  return ans;
}

int Solution::solution_1535(vector<int>& arr, int k) {
  int mx = arr[0];
  int win = -1;
  for (auto&& x : arr) {
    if (x > mx) {
      mx = x;
      win = 0;
    }
    win++;
    if (win == k) {
      break;
    }
  }
  return mx;
}

}  // namespace MySolution