#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <ranges>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "my_solution.h"
using std::array;
using std::deque;
using std::function;
using std::get;
using std::greater;
using std::lower_bound;
using std::max;
using std::max_element;
using std::min;
using std::sort;
using std::stack;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
namespace MySolution {

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
  int neg = std::ranges::lower_bound(nums, 0) - nums.begin();
  int pos = nums.end() - std::ranges::upper_bound(nums, 0);
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

int Solution::solution_2798(vector<int>& hours, int target) {
  int ans = 0;
  for (auto&& num : hours) {
    if (num >= target) {
      ans++;
    }
  }
  return ans;
}

int Solution::solution_2960(vector<int>& batteryPercentages) {
  int ans = 0;
  for (auto&& i : batteryPercentages) {
    if (i > ans) {
      ans++;
    }
  }
  return ans;
}

int Solution::solution_2391(vector<string>& garbage, vector<int>& travel) {
  int ans = garbage[0].size();
  unordered_set<char> s;
  for (int i = garbage.size() - 1; i > 0; i--) {
    auto& g = garbage[i];
    s.insert(g.begin(), g.end());
    ans += g.size() + travel[i - 1] * s.size();
  }
  return ans;
}

int Solution::solution_2589(vector<vector<int>>& tasks) {
  sort(tasks.begin(), tasks.end(),
       [](auto& a, auto& b) { return a[1] < b[1]; });
  // 保存左右端点和栈底到栈顶的区间长度的和
  vector<array<int, 3>> st{{-2, -2, 0}};  // 哨兵，保证不和任何区间相交
  for (auto&& t : tasks) {
    int start = t[0], end = t[1], d = t[2];
    auto [_, r, s] =
        *--lower_bound(st.begin(), st.end(), start,
                       [](const auto& a, int b) { return a[0] < b; });
    // 这一段是除了r位于上面那段的可利用时间外，全部的可利用时间
    d -= st.back()[2] - s;
    if (start <= r) {
      d -= r - start + 1;  // 上面那一段里的可利用时间
    }
    if (d <= 0) {
      continue;  // 不需要新增
    }
    while (end - st.back()[1] <= d) {
      // 如果需要的新增时间填满了最后一段与现在end间的空余，需要合并
      auto [l, r, _] = st.back();
      st.pop_back();
      d += r - l + 1;  // 合并时长
    }
    st.push_back({end - d + 1, end, st.back()[2] + d});
  }
  return st.back()[2];
}

int Solution::solution_2644(vector<int>& nums, vector<int>& divisors) {
  sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
  sort(divisors.begin(), divisors.end());
  int dup = nums.size() - unordered_set<int>(nums.begin(), nums.end()).size();
  int mx = -1, ans = 0;
  for (auto&& d : divisors) {
    if ((mx - dup + 1) > ((nums[0] + d - 1) / d)) {
      break;
    }
    int cnt = 0;
    for (auto&& num : nums) {
      if (num < d) {
        break;
      }
      if (num % d == 0) {
        cnt++;
      }
    }
    if (cnt > mx) {
      mx = cnt;
      ans = d;
    }
  }
  return ans;
}
vector<int> Solution::solution_2903(vector<int>& nums, int indexDifference,
                                    int valueDifference) {
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + indexDifference; j < nums.size(); j++) {
      if (abs(nums[i] - nums[j]) >= valueDifference) {
        return {i, j};
      }
    }
  }
  return {-1, -1};
}
int Solution::solution_2769(int num, int t) { return num + t * 2; }
int Solution::solution_2831(vector<int>& nums, int k) {
  unordered_map<int, vector<int>> pos_lists;
  for (int i = 0; i < nums.size(); i++) {
    int x = nums[i];
    if (pos_lists.find(x) == pos_lists.end()) {
      pos_lists[x] = vector<int>();
    }
    pos_lists[x].push_back(i - pos_lists[x].size());
  }
  int ans = 0;
  for (auto&& [_, pos] : pos_lists) {
    int left = 0;
    for (int right = 0; right < pos.size(); right++) {
      while (pos[right] - pos[left] > k) {
        left++;
      }
      ans = max(ans, right - left + 1);
    }
  }
  return ans;
}
vector<int> Solution::solution_2951(vector<int>& mountain) {
  vector<int> ans;
  for (int i = 1; i < mountain.size() - 1; i++) {
    if (mountain[i] > mountain[i - 1] && mountain[i] > mountain[i + 1]) {
      ans.push_back(i);
    }
  }
  return ans;
}

int Solution::solution_2981(string s) {
  unordered_map<char, vector<int>> map;
  int start = 0;
  for (int i = 0; i < s.size(); i++) {
    if (i != s.size() - 1 and s[i] == s[i + 1]) {
      continue;
    }
    map[s[start]].push_back(i - start + 1);
    start = i + 1;
  }
  int ans = 0;
  for (auto&& [c, v] : map) {
    sort(v.begin(), v.end(), greater<int>());
    v.push_back(0);
    v.push_back(0);
    ans = max({ans, v[0] - 2, min(v[0] - 1, v[1]), v[2]});
  }
  return ans == 0 ? -1 : ans;
}
int Solution::solution_2982(string s) { return solution_2981(s); }
vector<int> Solution::solution_2965(vector<vector<int>>& grid) {
  int n = grid.size();
  int m = n * n;
  int d1 = -m * (m + 1) / 2;
  long long d2 = (long long)-m * (m + 1) * (m * 2 + 1) / 6;
  for (auto& row : grid) {
    for (int x : row) {
      d1 += x;
      d2 += x * x;
    }
  }
  int d = d2 / d1;
  return {(d + d1) / 2, (d - d1) / 2};
}
int Solution::solution_2928(int n, int limit) {
  function<int(int)> c2 = [](int n) -> int {
    return n > 1 ? n * (n - 1) / 2 : 0;
  };
  return c2(n + 2) - 3 * c2(n - limit + 1) + 3 * c2(n - 2 * limit) -
         c2(n - 3 * limit - 1);
}
long long Solution::solution_2938(string s) {
  long long ans = 0, cnt1 = 0;
  for (auto&& c : s) {
    if (c == '1') {
      cnt1++;
    } else {
      ans += cnt1;
    }
  }
  return ans;
}
int Solution::solution_2806(int purchaseAmount) {
  int a = 10 * (purchaseAmount / 10);
  int b = a + 10;
  int x = 0;
  if (purchaseAmount - a < b - purchaseAmount) {
    x = a;
  } else {
    x = b;
  }
  return 100 - x;
}
long long Solution::solution_2813(vector<vector<int>>& items, int k) {
  std::ranges::sort(items,
                    [](const auto& a, const auto& b) { return a[0] > b[0]; });
  long long ans = 0, total_profit = 0;
  unordered_set<int> vis;
  stack<int> dup;
  for (int i = 0; i < items.size(); i++) {
    int profit = items[i][0], category = items[i][1];
    if (i < k) {
      total_profit += profit;
      if (!vis.insert(category).second) {
        dup.push(profit);
      }
    } else if (!dup.empty() && vis.insert(category).second) {
      total_profit += profit - dup.top();
      dup.pop();
    }
    ans =
        max(ans, total_profit + (long long)vis.size() * (long long)vis.size());
  }
  return ans;
}
long long Solution::solution_2786(vector<int>& nums, int x) {
  long long f[2]{};
  for (int i = nums.size() - 1; i >= 0; i--) {
    int v = nums[i];
    int r = v % 2;
    f[r] = max(f[r], f[r ^ 1] - x) + v;
  }
  return f[nums[0] % 2];
}
int Solution::solution_2779(vector<int>& nums, int k) {
  int m = *max_element(nums.begin(), nums.end());
  vector<int> d(m + k * 2 + 2);
  for (auto&& x : nums) {
    d[x]++;
    d[x + k * 2 + 1]--;
  }
  int ans = 0, s = 0;
  for (auto&& x : d) {
    s += x;
    ans = max(ans, s);
  }
  return ans;
}
}  // namespace MySolution
