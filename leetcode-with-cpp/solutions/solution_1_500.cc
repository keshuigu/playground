#include <algorithm>
#include <set>

#include "my_solution.h"
#define inf 0x3f3f3f3f
using namespace MySolution;
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