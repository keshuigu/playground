#include <algorithm>
#include <functional>
#include <ranges>
#include <set>
#include <unordered_map>

#include "my_solution.h"

using std::function;
using std::max;
using std::multiset;
using std::unique;
using std::unordered_map;
using std::ranges::fill;
using std::ranges::sort;
namespace MySolution {
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

vector<int> Solution::solution_2007(vector<int>& changed) {
  // TLE
  // vector<int> ans;
  // if (changed.size() % 2 == 1) {
  //   return ans;
  // }
  // multiset<int> s;
  // for (auto&& i : changed) {
  //   s.insert(i);
  // }
  // int cnt = changed.size() / 2;
  // while (cnt > 0) {
  //   int cur = *s.begin();
  //   if ((cur == 0 && s.count(0) >= 2) || (cur != 0 && s.count(cur * 2) > 0))
  //   {
  //     s.erase(s.begin());
  //     s.erase(s.find(cur * 2));
  //     ans.push_back(cur);
  //     cnt--;
  //   } else {
  //     return vector<int>();
  //   }
  // }
  // return ans;
  if (changed.size() % 2 == 1) {
    return vector<int>();
  }
  unordered_map<int, int> m;
  for (auto&& num : changed) {
    if (m.contains(num)) {
      m[num] += 1;
    } else {
      m[num] = 1;
    }
  }
  vector<int> ans;
  sort(changed.begin(), changed.end());
  for (auto&& num : changed) {
    if (num == 0 && m[0] >= 2) {
      m[0] -= 2;
      ans.push_back(0);
    } else if (num != 0 && m.contains(num * 2) && m[num] > 0 &&
               m[num * 2] > 0) {
      m[num] -= 1;
      m[num * 2] -= 1;
      ans.push_back(num);
    }
  }
  return ans.size() == changed.size() / 2 ? ans : vector<int>();
}

vector<int> Solution::solution_2007_2(vector<int>& changed) {
  unordered_map<int, int> cnt;
  for (auto&& x : changed) {
    cnt[x]++;
  }
  int cnt0 = cnt[0];
  if (cnt0 % 2) {
    return {};
  }
  cnt.erase(0);
  vector<int> ans(cnt0 / 2);
  for (auto&& [key, _] : cnt) {
    int x = key;
    if (x % 2 == 0 && cnt.contains(x / 2)) {
      continue;
    }
    while (cnt.contains(x)) {
      int cnt_x = cnt[x];
      if (cnt_x > cnt[x * 2]) {
        return {};
      }
      ans.insert(ans.end(), cnt_x, x);
      if (cnt_x < cnt[x * 2]) {
        cnt[x * 2] -= cnt_x;
        x *= 2;
      } else {
        x *= 4;
      }
    }
  }
  return ans;
}

int Solution::solution_2385(TreeNode* root, int start) {
  TreeNode* fa[100001];
  TreeNode* start_node;
  function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* node,
                                                 TreeNode* from) {
    if (node == nullptr) {
      return;
    }
    fa[node->val] = from;
    if (node->val == start) {
      start_node = node;
    }
    dfs(node->left, node);
    dfs(node->right, node);
  };
  function<int(TreeNode*, TreeNode*)> maxDepth = [&](TreeNode* node,
                                                     TreeNode* from) -> int {
    if (node == nullptr) {
      return -1;
    }
    int res = -1;
    if (node->left != from) {
      res = max(res, maxDepth(node->left, node));
    }
    if (node->right != from) {
      res = max(res, maxDepth(node->right, node));
    }
    if (fa[node->val] != from) {
      res = max(res, maxDepth(fa[node->val], node));
    }
    return res + 1;
  };

  dfs(root, nullptr);
  return maxDepth(start_node, start_node);
}

int Solution::solution_2079(vector<int>& plants, int capacity) {
  int ans = plants.size();
  int water = capacity;
  for (int i = 0; i < plants.size(); i++) {
    // 只计算往返
    // 每一步已经在ans的初始化中了
    if (water < plants[i]) {
      ans += i * 2;
      water = capacity;
    }
    water -= plants[i];
  }
  return ans;
}

int Solution::solution_2105(vector<int>& plants, int capacityA, int capacityB) {
  int left = 0, right = plants.size() - 1, ans = 0;
  int cap_l = capacityA, cap_r = capacityB;
  while (left < right) {
    if (plants[left] > cap_l) {
      ans++;
      cap_l = capacityA;
    }
    if (plants[right] > cap_r) {
      ans++;
      cap_r = capacityB;
    }
    cap_l -= plants[left];
    cap_r -= plants[right];
    left++;
    right--;
  }
  if (left == right && (plants[left] > max(cap_l, cap_r))) {
    ans += 1;
  }
  return ans;
}

int Solution::solution_2244(vector<int>& tasks) {
  unordered_map<int, int> cnt;
  for (auto&& t : tasks) {
    cnt[t]++;
  }
  int ans = 0;
  for (auto&& [_, v] : cnt) {
    if (v == 1) {
      return -1;
    }
    ans += (v + 2) / 3;
  }
  return ans;
}
vector<vector<int>> Solution::solution_2225(vector<vector<int>>& matches) {
  vector<vector<int>> ans(2, vector<int>());
  unordered_map<int, int> f;
  for (auto&& m : matches) {
    int w = m[0];
    int l = m[1];
    if (!f.contains(w)) {
      f[w] = 0;
    }
    if (!f.contains(l)) {
      f[l] = 1;
    } else {
      f[l]++;
    }
  }
  for (auto&& p : f) {
    if (p.second == 0) {
      ans[0].push_back(p.first);
    } else if (p.second == 1) {
      ans[1].push_back(p.first);
    }
  }
  sort(ans[0].begin(), ans[0].end());
  sort(ans[1].begin(), ans[1].end());
  return ans;
}
}  // namespace MySolution