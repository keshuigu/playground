#include <algorithm>
#include <functional>
#include <iostream>
#include <set>

#include "my_solution.h"
#define inf 0x3f3f3f3f
using namespace MySolution;
using std::cout;
using std::function;
using std::reverse;
using std::set;
using std::swap;
using std::unordered_map;

Solution::Solution(/* args */) {}
Solution::~Solution() {}

int Solution::solution_27(vector<int>& nums, int val) {
  int n = nums.size();
  int slowIndex = 0;
  for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
    // 如果是需要移除的
    // fast向前找不是被移除
    // slow指向需要移除的
    if (val != nums[fastIndex]) {
      nums[slowIndex++] = nums[fastIndex];
    }
  }
  return slowIndex;
}

int Solution::solution_209(int target, vector<int>& nums) {
  int left = 0, ans = inf, s = 0;
  for (int right = 0; right < nums.size(); right++) {
    s += nums[right];
    while (s >= target) {
      ans = std::min(ans, right - left + 1);
      s -= nums[left++];
    }
  }
  return ans == inf ? 0 : ans;
}

string Solution::solution_405(int num) {
  string s = "0123456789abcdef";
  string sb;
  for (int i = 7; i >= 0; i--) {
    int part = (num >> (4 * i)) & 0xf;
    if (sb.length() > 0 || part > 0) {
      char digit = s[part];
      sb.push_back(digit);
    }
  }
  return sb;
}

vector<vector<int>> Solution::solution_59(int n) {
  int num = 1;
  vector<vector<int>> matrix(n, vector<int>(n));
  int left = 0, right = n - 1, top = 0, bottom = n - 1;
  while (left <= right && top <= bottom) {
    for (int column = left; column <= right; column++) {
      matrix[top][column] = num;
      num++;
    }
    for (int row = top + 1; row <= bottom; row++) {
      matrix[row][right] = num;
      num++;
    }
    if (left < right && top < bottom) {
      for (int column = right - 1; column > left; column--) {
        matrix[bottom][column] = num;
        num++;
      }
      for (int row = bottom; row > top; row--) {
        matrix[row][left] = num;
        num++;
      }
    }
    left++;
    right--;
    top++;
    bottom--;
  }
  return matrix;
}

ListNode* Solution::solution_203(ListNode* head, int val) {
  ListNode* dummyHead = new ListNode();
  dummyHead->next = head;
  ListNode* p = dummyHead;
  while (p->next) {
    if (p->next->val == val) {
      ListNode* cur = p->next;
      p->next = cur->next;
      delete cur;
    } else {
      p = p->next;
    }
  }
  ListNode* ans = dummyHead->next;
  delete dummyHead;
  return ans;
}

int Solution::solution_409(string s) {
  unordered_map<char, int> cnt;
  for (auto&& c : s) {
    cnt[c]++;
  }
  int ans = 0;
  bool flag = false;
  for (auto&& pair : cnt) {
    if (pair.second % 2 == 0) {
      ans += pair.second;
    } else {
      ans += pair.second - 1;
      flag = true;
    }
  }
  return flag ? ans + 1 : ans;
}

int Solution::solution_414(vector<int>& nums) {
  set<int> s;
  for (auto&& num : nums) {
    s.insert(num);
    if (s.size() > 3) {
      s.erase(s.begin());
    }
  }
  return s.size() == 3 ? *s.begin() : *s.rbegin();
}

string Solution::solution_415(string num1, string num2) {
  reverse(num1.begin(), num1.end());
  reverse(num2.begin(), num2.end());
  if (num1.size() < num2.size()) {
    swap(num1, num2);
  }
  int c = 0;
  int a, b, cur;
  for (int i = 0; i < num2.size(); i++) {
    a = num1[i] - '0';
    b = num2[i] - '0';
    cur = a + b + c;
    if (cur >= 10) {
      cur -= 10;
      c = 1;
    } else {
      c = 0;
    }
    num1[i] = '0' + cur;
  }
  for (int i = num2.size(); i < num1.size(); i++) {
    a = num1[i] - '0';
    cur = a + c;
    if (cur >= 10) {
      cur -= 10;
      c = 1;
    } else {
      c = 0;
    }
    num1[i] = '0' + cur;
  }
  if (c == 1) {
    num1.push_back('1');
  }
  reverse(num1.begin(), num1.end());
  return num1;
}

vector<vector<int>> Solution::solution_39(vector<int>& candidates, int target) {
  function<vector<vector<int>>(int, int)> dfs =
      [&](int i, int res) -> vector<vector<int>> {
    if (res == 0) {
      return vector<vector<int>>(1);
    }
    if (i == candidates.size()) {
      return vector<vector<int>>();
    }

    vector<vector<int>> ans;
    for (int j = 0; j <= res; j = j + candidates[i]) {
      vector<vector<int>> p = dfs(i + 1, res - j);
      vector<int> tmp(j / candidates[i], candidates[i]);
      for (auto&& t : p) {
        vector<int> combined = tmp;
        combined.insert(combined.end(), t.begin(), t.end());
        ans.push_back(combined);
      }
    }
    return ans;
  };
  // 优化的写法
  // path 维护当前走选过的数字
  // vector<vector<int>> ans;
  // vector<int> path;
  // function<void(int, int)> dfs = [&](int i, int left) {
  //   if (left == 0) {
  //     // 找到一个合法组合
  //     ans.push_back(path);
  //     return;
  //   }

  //   if (i == candidates.size() || left < 0) {
  //     return;
  //   }

  //   // 不选
  //   dfs(i + 1, left);

  //   // 选
  //   path.push_back(candidates[i]);
  //   dfs(i, left - candidates[i]);
  //   path.pop_back();  // 恢复现场
  // };

  return dfs(0, target);
}

vector<vector<int>> Solution::solution_216(int k, int n) {
  vector<vector<int>> ans;
  vector<int> path;

  function<void(int, int, int)> dfs = [&](int i, int j, int cur) {
    if (cur > n or j > k) {
      return;
    }
    if (cur == n and j == k) {
      ans.push_back(path);
      return;
    }
    if (i > 9) {
      return;
    }
    path.push_back(i);
    dfs(i + 1, j + 1, cur + i);
    path.pop_back();

    dfs(i + 1, j, cur);
  };
  dfs(1, 0, 0);
  return ans;
}

int Solution::solution_377(vector<int>& nums, int target) {
  vector<int> memo(target + 1, -1);
  function<int(int)> dfs = [&](int i) -> int {
    if (i == 0) {
      return 1;
    }
    int& res = memo[i];
    if (res != -1) {
      return res;
    }
    res = 0;
    for (auto&& x : nums) {
      if (x <= i) {
        res += dfs(i - x);
      }
    }
    return res;
  };

  return dfs(target);
}