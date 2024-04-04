#include <algorithm>
#include <functional>
#include <ranges>

#include "my_solution.h"

using namespace MySolution;

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
    ranges::fill(vis, false);
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