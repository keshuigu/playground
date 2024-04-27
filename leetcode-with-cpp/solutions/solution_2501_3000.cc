#include <algorithm>
#include <deque>
#include <functional>
#include <ranges>
#include <string>
#include <unordered_map>

#include "my_solution.h"
using namespace MySolution;
using std::deque;
using std::function;
using std::max;
using std::min;
using std::to_string;
using std::unordered_map;
using std::ranges::lower_bound;
using std::ranges::upper_bound;
int Solution::solution_2908(vector<int>& nums) {
  int n = nums.size();
  vector<int> pre(n);
  vector<int> suf(n);
  int pcur = 0x3f3f3f3f;
  int scur = 0x3f3f3f3f;
  for (int i = 0; i < n; i++) {
    if (nums[i] < pcur) {
      pcur = nums[i];
    }
    pre[i] = pcur;
  }

  for (int i = n - 1; i >= 0; i--) {
    if (nums[i] < scur) {
      scur = nums[i];
    }
    suf[i] = scur;
  }
  int ans = 0x3f3f3f3f;
  for (int i = 1; i < n - 1; i++) {
    if (nums[i] > pre[i] && nums[i] > suf[i]) {
      ans = min(ans, nums[i] + pre[i] + suf[i]);
    }
  }
  if (ans < 0x3f3f3f3f)
    return ans;
  else
    return -1;
}

string Solution::solution_2810(string s) {
  deque<char> d;
  bool tail = true;
  for (auto&& n : s) {
    if (n == 'i') {
      tail = !tail;
    } else if (tail) {
      d.push_back(n);
    } else {
      d.push_front(n);
    }
  }
  return tail ? string(d.begin(), d.end()) : string(d.rbegin(), d.rend());
}

int Solution::solution_2529(vector<int>& nums) {
  int neg = lower_bound(nums, 0) - nums.begin();
  int pos = nums.end() - upper_bound(nums, 0);
  return max(neg, pos);
}

int Solution::solution_2923(vector<vector<int>>& grid) {
  int ans = 0;
  for (int i = 0; i < grid.size(); i++) {
    if (grid[i][ans]) {
      ans = i;
    }
  }
  return ans;
}

int Solution::solution_2924(int n, vector<vector<int>>& edges) {
  vector<int> lose(n, 0);
  for (auto&& e : edges) {
    lose[e[1]] = 1;
  }
  int ans = -1;
  for (int i = 0; i < n; i++) {
    if (lose[i]) {
      continue;
    }
    if (ans != -1) {
      return -1;
    }
    ans = i;
  }
  return ans;
}

int Solution::solution_2739(int mainTank, int additionalTank) {
  return (mainTank + min((mainTank - 1) / 4, additionalTank)) * 10;
}

vector<int> Solution::solution_2639(vector<vector<int>>& grid) {
  vector<int> ans(grid[0].size(), 0);
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      ans[j] = max(ans[j], static_cast<int>(to_string(grid[i][j]).size()));
    }
  }
  return ans;
}