#include <algorithm>
#include <functional>
#include <ranges>
#include <utility>

#include "data_struct.h"
#include "my_solution.h"
using std::function;
using std::pair;
using std::unique;
namespace MySolution {

vector<int> Solution::solution_3067(vector<vector<int>>& edges,
                                    int signalSpeed) {
  int n = edges.size() + 1;
  vector<vector<pair<int, int>>> g(n);
  for (auto&& e : edges) {
    int x = e[0], y = e[1], wt = e[2];
    g[x].push_back({y, wt});
    g[y].push_back({x, wt});
  }
  function<int(int, int, int)> dfs = [&](int x, int fa, int sum) -> int {
    int cnt = sum % signalSpeed == 0;
    for (auto&& [y, wt] : g[x]) {
      if (y != fa) {
        cnt += dfs(y, x, sum + wt);
      }
    }
    return cnt;
  };
  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (auto&& [y, wt] : g[i]) {
      int cnt = dfs(y, i, wt);
      ans[i] += cnt * sum;
      sum += cnt;
    }
  }
  return ans;
}
vector<int> Solution::solution_3072(vector<int>& nums) {
  auto sorted = nums;
  std::ranges::sort(sorted);
  sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
  int m = sorted.size();
  vector<int> a{nums[0]}, b{nums[1]};
  MyDataStruct::Fenwick t1(m + 1), t2(m + 1);
  t1.add(std::ranges::lower_bound(sorted, nums[0]) - sorted.begin() + 1);
  t2.add(std::ranges::lower_bound(sorted, nums[1]) - sorted.begin() + 1);
  for (int i = 2; i < nums.size(); i++) {
    int x = nums[i];
    int v = std::ranges::lower_bound(sorted, x) - sorted.begin() + 1;
    int gc1 = a.size() - t1.pre(v);
    int gc2 = b.size() - t2.pre(v);
    if (gc1 > gc2 || gc1 == gc2 && a.size() <= b.size()) {
      a.push_back(x);
      t1.add(v);
    } else {
      b.push_back(x);
      t2.add(v);
    }
  }
  a.insert(a.end(), b.begin(), b.end());
  return a;
}

}  // namespace MySolution
