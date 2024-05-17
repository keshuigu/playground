#include <algorithm>
#include <climits>
#include <functional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "my_solution.h"

namespace MySolution {
using std::function;
using std::make_pair;
using std::max;
using std::min;
using std::min_element;
using std::pair;
using std::priority_queue;
using std::sort;
using std::unordered_map;
using std::unordered_set;
int Solution::solution_704(vector<int>& nums, int target) {
  int left = -1, right = nums.size();
  while (left + 1 < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] < target)
      left = mid;
    else
      right = mid;
  }
  return -1;
}

vector<TreeNode*> Solution::solution_894(int n) {
  // 可以直接拿到外面，因为n不影响这些计算出的值
  vector<TreeNode*> f[11];
  f[0] = {};
  f[1] = {new TreeNode()};
  for (int i = 2; i < 11; i++) {  // 计算f[i]，在题目给的数据范围内最多11个叶子
    for (int j = 1; j < i; j++) {
      // 枚举左子树叶子数 左子树叶子数+右子树叶子数=i
      for (auto&& left : f[j]) {         // 枚举左子树
        for (auto&& right : f[i - j]) {  // 枚举右子树
          f[i].push_back(new TreeNode(0, left, right));
        }
      }
    }
  }
  return f[n % 2 ? (n + 1) / 2 : 0];
}

int Solution::solution_924(vector<vector<int>>& graph, vector<int>& initial) {
  int n = graph.size();
  vector<int> fa(n);
  for (int i = 0; i < n; i++) {
    fa[i] = i;
  }

  sort(initial.begin(), initial.end());
  function<int(int)> find = [&fa, &find](int x) -> int {
    if (fa[x] != x) {
      fa[x] = find(fa[x]);
    }
    return fa[x];
  };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (graph[i][j]) {
        int x = find(i);
        int y = find(j);
        if (x != y) {
          fa[x] = y;
        }
      }
    }
  }
  unordered_map<int, int> cnt;
  for (int i = 0; i < n; i++) {
    int x = find(i);
    if (cnt.contains(x)) {
      cnt[x] = cnt[x] + 1;
    } else {
      cnt[x] = 1;
    }
  }
  unordered_map<int, int> m;
  for (vector<int>::iterator it = initial.begin(); it != initial.end(); ++it) {
    int x = find(*it);
    if (cnt.contains(x)) {
      m[x] = m[x] + 1;
    } else {
      m[x] = 1;
    }
  }
  int survived = 0;
  int idx = initial[0];
  for (vector<int>::iterator it = initial.begin(); it != initial.end(); it++) {
    int x = find(*it);
    if (m[x] == 1) {
      int cur = cnt[find(x)];
      if (survived < cur) {
        survived = cur;
        idx = *it;
      }
    }
  }
  return idx;
}

int Solution::solution_928(vector<vector<int>>& graph, vector<int>& initial) {
  unordered_set<int> st(initial.begin(), initial.end());
  vector<int> vis(graph.size());
  int node_id, size;
  function<void(int)> dfs = [&](int x) {
    vis[x] = true;
    size++;
    for (int y = 0; y < graph[x].size(); y++) {
      if (graph[x][y] == 0) {
        continue;
      }
      if (st.contains(y)) {
        if (node_id != -2 && node_id != y) {
          node_id = node_id == -1 ? y : -2;
        }
      } else if (!vis[y]) {
        dfs(y);
      }
    }
  };

  unordered_map<int, int> cnt;
  for (int i = 0; i < graph.size(); i++) {
    if (vis[i] || st.contains(i)) {
      continue;
    }
    node_id = -1;
    size = 0;
    dfs(i);
    if (node_id >= 0) {
      cnt[node_id] += size;
    }
  }
  int max_cnt = 0;
  int min_node_id = 0;
  for (auto&& [node_id, c] : cnt) {
    if (c > max_cnt || c == max_cnt && node_id < min_node_id) {
      max_cnt = c;
      min_node_id = node_id;
    }
  }
  return cnt.empty() ? *min_element(initial.begin(), initial.end())
                     : min_node_id;
}

double Solution::solution_857(vector<int>& quality, vector<int>& wage, int k) {
  int n = quality.size();
  vector<pair<int, int>> pairs(n);
  for (int i = 0; i < n; i++) {
    pairs[i] = make_pair(quality[i], wage[i]);
  }
  std::sort(
      pairs.begin(), pairs.end(),
      [](const pair<int, int>& a, const pair<int, int>& b) {
        return (static_cast<double>(a.second) / static_cast<double>(a.first)) <
               (static_cast<double>(b.second) / static_cast<double>(b.first));
      });
  priority_queue<int> pq;
  int sum_q = 0;
  for (int i = 0; i < k; i++) {
    pq.push(pairs[i].first);
    sum_q += pairs[i].first;
  }
  double ans = sum_q * (static_cast<double>(pairs[k - 1].second) /
                        static_cast<double>(pairs[k - 1].first));
  for (int i = k; i < n; i++) {
    int q = pairs[i].first;
    if (q < pq.top()) {
      sum_q -= pq.top() - q;
      pq.pop();
      pq.push(q);
      ans = min(ans, sum_q * (static_cast<double>(pairs[i].second) /
                              static_cast<double>(pairs[i].first)));
    }
  }
  return ans;
}

int Solution::solution_741(vector<vector<int>>& grid) {
  int n = grid.size();
  vector<vector<vector<int>>> f(
      n * 2 - 1, vector<vector<int>>(n + 1, vector<int>(n + 1, INT_MIN)));
  f[0][1][1] = grid[0][0];
  for (int t = 1; t < n * 2 - 1; t++) {
    for (int j = max(t - n + 1, 0); j <= min(t, n - 1); j++) {
      if (grid[t - j][j] == -1) {
        continue;
      }
      for (int k = j; k <= min(t, n - 1); k++) {
        if (grid[t - k][k] == -1) {
          continue;
        }
        f[t][j + 1][k + 1] = max({f[t - 1][j + 1][k + 1], f[t - 1][j + 1][k],
                                  f[t - 1][j][k + 1], f[t - 1][j][k]}) +
                             grid[t - j][j] + (k != j ? grid[t - k][k] : 0);
      }
    }
  }
  return max(f[n * 2 - 2][n][n], 0);
}

int Solution::solution_994(vector<vector<int>>& grid) {
  int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  int m = grid.size(), n = grid[0].size();
  int fresh = 0;
  vector<pair<int, int>> q;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 1) {
        fresh++;
      } else if (grid[i][j] == 2) {
        q.emplace_back(i, j);
      }
    }
  }
  int ans = -1;
  while (!q.empty()) {
    ans++;
    vector<pair<int, int>> nxt;
    for (auto&& [x, y] : q) {
      for (auto&& d : direction) {
        int i = x + d[0], j = y + d[1];
        if (0 <= i && i < m && 0 <= j && j < n && grid[i][j] == 1) {
          grid[i][j] = 2;
          fresh--;
          nxt.emplace_back(i, j);
        }
      }
    }
    q = std::move(nxt);
  }
  return fresh ? -1 : max(ans, 0);
}

int Solution::solution_826(vector<int>& difficulty, vector<int>& profit,
                           vector<int>& worker) {
  int n = difficulty.size();
  vector<pair<int, int>> jobs(n);
  for (int i = 0; i < n; i++) {
    jobs[i] = {difficulty[i], profit[i]};
  }
  sort(jobs.begin(), jobs.end());
  sort(worker.begin(), worker.end());
  int ans = 0, j = 0, mx_profit = 0;
  for (auto&& w : worker) {
    while (j < n && jobs[j].first <= w) {
      mx_profit = max(mx_profit, jobs[j].second);
      j++;
    }
    ans += mx_profit;
  }
  return ans;
}

}  // namespace MySolution