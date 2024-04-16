#include <algorithm>
#include <functional>
#include <ranges>

#include "my_solution.h"

using namespace MySolution;
using std::function;
using std::max;
using std::unique;
using std::ranges::fill;
using std::ranges::sort;
vector<vector<int>> Solution::solution_2192(int n, vector<vector<int>>& edges) {
  vector<vector<int>> g(n);
  for (auto&& e : edges) {
    g[e[1]].push_back(e[0]);
  }
  vector<vector<int>> ans(n);
  vector<int> vis(n);
  function<void(int)> dfs = [&](int x) {
    vis[x] = true;
    for (auto y : g[x]) {
      if (!vis[y]) {
        dfs(y);
      }
    }
  };
  for (int i = 0; i < n; i++) {
    fill(vis, false);
    dfs(i);
    vis[i] = false;
    for (int j = 0; j < n; j++) {
      if (vis[j]) {
        ans[i].push_back(j);
      }
    }
  }
  return ans;
}

int Solution::solution_2009(vector<int>& nums) {
  int n = nums.size();
  int j = 1;
  sort(nums);
  // for (int i = 1; i < n; i++) {
  //   if (nums[i] != nums[i - 1]) {
  //     nums[j++] = nums[i];
  //   }
  // }
  int e = unique(nums.begin(), nums.end()) - nums.begin();
  int ans = 0, left = 0;
  for (int i = 0; i < e; i++) {
    while (nums[left] < nums[i] - n + 1) {
      left++;
    }
    ans = max(ans, i - left + 1);
  }
  return n - ans;
}