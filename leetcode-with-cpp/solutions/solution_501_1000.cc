#include <algorithm>
#include <functional>
#include <unordered_map>

#include "my_solution.h"
using namespace MySolution;
using std::function;
using std::sort;
using std::unordered_map;
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