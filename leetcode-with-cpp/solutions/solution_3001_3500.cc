#include <algorithm>
#include <functional>
#include <ranges>
#include <utility>

#include "data_struct.h"
#include "my_solution.h"
using std::function;
using std::max;
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
int Solution::solution_3038(vector<int>& nums) {
  int ans = 1;
  int last = nums[0] + nums[1];
  int i = 2;
  while (i < nums.size() - 1) {
    if (nums[i] + nums[i + 1] != last) {
      return ans;
    }
    i += 2;
    ans++;
  }
  return ans;
}
int Solution::solution_3040(vector<int>& nums) {
  int n = nums.size();
  function<int(int, int, int)> helper = [&](int start, int end,
                                            int target) -> int {
    vector<vector<int>> f(n + 1, vector<int>(n + 1));
    for (int i = end - 1; i >= start; i--) {
      for (int j = i + 1; j <= end; j++) {
        if (nums[i] + nums[i + 1] == target) {
          f[i][j + 1] = max(f[i][j + 1], f[i + 2][j + 1] + 1);
        }
        if (nums[j - 1] + nums[j] == target) {
          f[i][j + 1] = max(f[i][j + 1], f[i][j - 1] + 1);
        }
        if (nums[i] + nums[j] == target) {
          f[i][j + 1] = max(f[i][j + 1], f[i + 1][j] + 1);
        }
      }
    }
    return f[start][end + 1];
  };
  int res1 = helper(2, n - 1, nums[0] + nums[1]);          // 删除前两个数
  int res2 = helper(0, n - 3, nums[n - 2] + nums[n - 1]);  // 删除后两个数
  int res3 = helper(1, n - 2, nums[0] + nums[n - 1]);  // 删除第一个和最后一个数
  return max({res1, res2, res3}) + 1;                  // 加上第一次操作
}

}  // namespace MySolution
