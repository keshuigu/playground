#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#include "my_solution.h"
using namespace MySolution;
using std::function;
using std::min_element;
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