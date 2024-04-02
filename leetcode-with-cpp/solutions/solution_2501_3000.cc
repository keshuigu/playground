#include <deque>

#include "my_solution.h"
using namespace MySolution;

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