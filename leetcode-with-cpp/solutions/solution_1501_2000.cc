#include <functional>
#include <numeric>
#include <set>

#include "my_solution.h"
using namespace MySolution;

string Solution::solution_1702(string binary) {
  int i = binary.find('0');
  if (i < 0) {
    return binary;
  }
  int cnt1 = count(binary.begin() + i, binary.end(), '1');
  return string(binary.size() - 1 - cnt1, '1') + '0' + string(cnt1, '1');
}

vector<int> Solution::solution_1766(vector<int>& nums,
                                    vector<vector<int>>& edges) {
  const int MX = 51;
  vector<int> coprime[MX];
  for (int i = 1; i < MX; i++) {
    for (int j = 0; j < MX; j++) {
      if (gcd(i, j) == 1) {
        coprime[i].push_back(j);
      }
    }
  }
  int n = nums.size();
  vector<vector<int>> g(n);
  pair<int, int> val_depth_id[MX];
  vector<int> ans(n, -1);

  for (auto&& e : edges) {
    int x = e[0], y = e[1];
    g[x].push_back(y);
    g[y].push_back(x);
  }

  function<void(int, int, int)> dfs = [&](int x, int fa, int depth) {
    int val = nums[x];
    int max_depth = 0;
    for (auto&& j : coprime[val]) {
      auto [depth, id] = val_depth_id[j];
      if (depth > max_depth) {
        max_depth = depth;
        ans[x] = id;
      }
    }

    auto tmp = val_depth_id[val];
    val_depth_id[val] = {depth, x};
    for (auto&& y : g[x]) {
      if (y != fa) {
        dfs(y, x, depth + 1);
      }
    }
    val_depth_id[val] = tmp;
  };

  dfs(0, -1, 1);
  return ans;
}