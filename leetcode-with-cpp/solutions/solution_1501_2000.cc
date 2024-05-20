#include <stdlib.h>

#include <functional>
#include <numeric>
#include <set>
#include <unordered_map>

#include "my_solution.h"

namespace MySolution {
using std::abs;
using std::accumulate;
using std::function;
using std::gcd;
using std::max;
using std::max_element;
using std::min;
using std::pair;
using std::reduce;
using std::unordered_map;
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

int Solution::solution_1883(vector<int>& dist, int speed, int hoursBefore) {
  if (accumulate(dist.begin(), dist.end(), 0) >
      (long long)speed * hoursBefore) {
    return -1;
  }

  vector<int> f(dist.size(), 0);
  for (int i = 0;; i++) {
    int pre = 0;
    for (int j = 0; j < dist.size() - 1; j++) {
      int tmp = f[j + 1];
      f[j + 1] = (f[j] + dist[j] + speed - 1) / speed * speed;
      if (i > 0) {
        f[j + 1] = min(f[j + 1], pre + dist[j]);
      }
      pre = tmp;
    }
    if (f[f.size() - 1] + dist[dist.size() - 1] <=
        (long long)hoursBefore * speed) {
      return i;
    }
  }
}

vector<int> Solution::solution_1652(vector<int>& code, int k) {
  // 定长滑动窗口
  int n = code.size();
  vector<int> ans(n);
  int r = k > 0 ? k + 1 : n;  // 确定初始区间
  // k>0  -> code[1:k+1]
  // k<=0 -> code[n-abs(k),n]
  k = abs(k);
  int s = reduce(code.begin() + r - k, code.begin() + r);
  for (int i = 0; i < n; i++) {
    ans[i] = s;
    s += code[r % n] - code[(r - k) % n];
    r++;
  }
  return ans;
}

int Solution::solution_1553(int n) {
  unordered_map<int, int> memo;
  function<int(int)> dfs = [&memo, &dfs](int x) -> int {
    if (x <= 1) {
      return x;
    }
    if (memo.contains(x)) {
      return memo[x];
    }
    return memo[x] = min({x % 2 + dfs(x / 2), x % 3 + dfs(x / 3)}) + 1;
  };

  return dfs(n);
}

long long Solution::solution_1953(vector<int>& milestones) {
  long long mx = *max_element(milestones.begin(), milestones.end());
  long long total = accumulate(milestones.begin(), milestones.end(), 0LL);
  if (2 * mx <= total) {
    return total;
  } else {
    return (total - mx) * 2 + 1;
  }
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
int Solution::solution_1542(string s) {
  int n = s.size();
  vector<int> pos(1 << 10, n);
  int ans = 0;
  pos[0] = -1;
  int pre = 0;
  for (int i = 0; i < n; i++) {
    int t = s[i] - '0';
    pre ^= 1 << t;
    ans = max(ans, i - pos[pre]);
    for (int j = 0; j < 10; j++) {
      ans = max(ans, i - pos[pre ^ (1 << j)]);
    }
    if (pos[pre] == n) {
      pos[pre] = i;
    }
  }
  return ans;
}
}  // namespace MySolution