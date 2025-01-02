#include <bits/stdc++.h>

using std::array;
using std::cout;
using std::deque;
using std::function;
using std::max;
using std::min;
using std::pair;
using std::priority_queue;
using std::sort;
using std::string;
using std::swap;
using std::unordered_map;
using std::unordered_set;
using std::vector;
class Solution {
 public:
  Solution() {}
  ~Solution() {}
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> s;
    for (int i = 0; i < nums.size(); i++) {
      int x = nums[i];
      auto it = s.find(target - x);
      if (it != s.end()) {
        return vector<int>{i, (*it).second};
      }
      s[x] = i;
    }
    return {-1, -1};
  }
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> ans;
    vector<unordered_map<char, int>> ref;
    for (auto&& x : strs) {
      unordered_map<char, int> r;
      for (int i = 0; i < x.size(); i++) {
        r[x[i]]++;
      }
      bool flag = false;
      for (int i = 0; i < ans.size(); i++) {
        if (compareUnorderedMaps(r, ref[i])) {
          ans[i].push_back(x);
          flag = true;
          break;
        }
      }
      if (!flag) {
        ans.push_back(vector<string>{x});
        ref.push_back(r);
      }
    }
    return ans;
  }

  vector<vector<string>> groupAnagramsRef(vector<string>& strs) {
    unordered_map<string, vector<string>> m;
    for (auto&& s : strs) {
      string t = s;
      sort(t.begin(), t.end());
      m[t].push_back(s);
    }

    vector<vector<string>> ans;
    for (auto&& [_, value] : m) {
      ans.push_back(value);
    }
    return ans;
  }

  int longestConsecutive(vector<int>& nums) {
    int n = nums.size();
    unordered_set<int> s(nums.begin(), nums.end());
    // for (int i = 0; i < n; i++) {
    //   s.insert(nums[i]);
    // }
    int ans = 0;
    // 测试数据有大量重复
    // 遍历set
    for (auto iter = s.begin(); iter != s.end(); iter++) {
      int x = *(iter);
      if (s.contains(x - 1)) {
        continue;
      }
      int y = x + 1;
      while (s.contains(y)) {
        y = y + 1;
      }
      ans = max(ans, y - x);
    }
    return ans;
  }

  void moveZeroes(vector<int>& nums) {
    int i = 0;
    int n = nums.size();
    while (i < n && nums[i] != 0) {
      i++;
    }
    int j = i + 1;
    while (j < n && nums[j] == 0) {
      j++;
    }
    while (i < n && j < n) {
      nums[i] = nums[j];
      nums[j] = 0;
      i++;
      j++;
      while (i < n && nums[i] != 0) {
        i++;
      }
      while (j < n && nums[j] == 0) {
        j++;
      }
    }
  }

  void moveZeroesRef(vector<int>& nums) {
    int i0 = 0;
    for (int& x : nums) {
      if (x) {
        swap(x, nums[i0]);
        i0++;
      }
    }
  }

  int maxArea(vector<int>& height) {
    int ans = 0;
    int i = 0, j = height.size() - 1;
    while (i < j) {
      ans = max(ans, min(height[i], height[j]) * (j - i));
      if (height[i] > height[j]) {
        j--;
      } else {
        i++;
      }
    }
    return ans;
  }

  vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      if (i && x == nums[i - 1]) {
        continue;
      }
      if (x + nums[i + 1] + nums[i + 2] > 0) {
        break;
      }
      if (x + nums[n - 2] + nums[n - 1] < 0) {
        continue;
      }
      int j = i + 1, k = n - 1;
      while (j < k) {
        int s = x + nums[j] + nums[k];
        if (s > 0) {
          k--;
        } else if (s < 0) {
          j++;
        } else {
          ans.push_back({x, nums[j], nums[k]});
          for (j++; j < k && nums[j] == nums[j - 1]; j++);  // 跳过重复数字
          for (k--; k > j && nums[k] == nums[k + 1]; k--);  // 跳过重复数字
        }
      }
    }
    return ans;
  }

  int trap(vector<int>& height) {
    int n = height.size();
    vector<int> pre(n + 1), suf(n + 1);
    for (int i = 1; i < n + 1; i++) {
      pre[i] = max(pre[i - 1], height[i - 1]);
    }
    for (int i = n - 1; i > -1; i--) {
      suf[i] = max(suf[i + 1], height[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += max(min(pre[i], suf[i + 1]) - height[i], 0);
    }
    return ans;
  }

  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> m;
    int left = 0, n = s.size();
    int ans = 0;
    for (int right = 0; right < n; right++) {
      char c = s[right];
      m[c]++;
      while (m[c] > 1) {
        m[s[left]]--;
        left++;
      }
      ans = max(ans, right - left + 1);
    }
    return ans;
  }

  bool isValid(string s) {
    vector<char> st;
    for (char x : s) {
      if (x == '(' || x == '{' || x == '[') {
        st.push_back(x);
      } else if (st.size() > 0 && (x == ')' && st[st.size() - 1] == '(' ||
                                   x == '}' && st[st.size() - 1] == '{' ||
                                   x == ']' && st[st.size() - 1] == '[')) {
        st.pop_back();
      } else {
        return false;
      }
    }
    return st.size() == 0;
  }
  int searchInsert(vector<int>& nums, int target) {
    int left = -1, right = nums.size();
    while (left + 1 < right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] >= target) {
        right = mid;
      } else {
        left = mid;
      }
    }
    return right;
  }

  bool compareUnorderedMaps(const std::unordered_map<char, int>& m1,
                            const std::unordered_map<char, int>& m2) {
    if (m1.size() != m2.size()) {
      return false;
    }
    for (auto&& p : m1) {
      auto it = m2.find(p.first);
      if (it == m2.end() || it->second != p.second) {
        return false;
      }
    }
    return true;
  }

  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> m;
    for (auto&& x : nums) {
      m[x]++;
    }
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
      return a.second < b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq;
    for (auto&& [k, v] : m) {
      pq.push({k, v});
    }
    vector<int> ans;
    for (int i = 0; i < k; i++) {
      ans.push_back(pq.top().first);
      pq.pop();
    }
    return ans;
  }

  vector<int> findAnagrams(string s, string p) {
    int n = s.size();
    int m = p.size();
    unordered_map<char, int> ms;
    unordered_map<char, int> mp;
    for (auto&& x : p) {
      mp[x]++;
    }
    int left = 0;
    vector<int> ans;
    for (int right = 0; right < n; right++) {
      ms[s[right]]++;
      if (right < m - 1) {
        continue;
      }
      if (compareUnorderedMaps(ms, mp)) {
        ans.push_back(left);
      }
      ms[s[left]]--;
      if (ms[s[left]] == 0) {
        ms.erase(s[left]);
      }
      left++;
    }
    return ans;
  }

  vector<int> findAnagramsRef(string s, string p) {
    vector<int> ans;
    array<int, 26> cnt_p{};
    array<int, 26> cnt_s{};
    for (auto&& x : p) {
      cnt_p[x - 'a']++;
    }
    for (int right = 0; right < s.size(); right++) {
      cnt_s[s[right] - 'a']++;
      int left = right - p.size() + 1;
      if (left < 0) {
        continue;
      }
      if (cnt_s == cnt_p) {
        ans.push_back(left);
      }
      cnt_s[s[left] - 'a']--;
    }
    return ans;
  }

  int subarraySum(vector<int>& nums, int k) {
    int cnt = 0;
    int n = nums.size();
    vector<int> pre(n + 1);
    for (int i = 0; i < n; i++) {
      pre[i + 1] = pre[i] + nums[i];
    }
    // 两数之和
    unordered_map<int, int> s;
    for (int i = 0; i < n + 1; i++) {
      auto it = s.find(pre[i] - k);
      if (it != s.end()) {
        cnt += (*it).second;
      }
      s[pre[i]]++;
    }
    return cnt;
  }

  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    // 懒删除堆
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) -> bool {
      return a.first < b.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(
        cmp);
    int left = 0;
    vector<int> ans;
    for (int right = 0; right < nums.size(); right++) {
      pq.push({nums[right], right});
      if (right < k - 1) {
        continue;
      }
      while (pq.top().second < left) {
        pq.pop();
      }
      ans.push_back(pq.top().first);
      left++;
    }
    return ans;
  }

  vector<int> maxSlidingWindowRef(vector<int>& nums, int k) {
    // 单调队列
    vector<int> ans;
    deque<int> dq;
    for (int i = 0; i < nums.size(); i++) {
      int x = nums[i];
      while (!dq.empty() && nums[dq[dq.size() - 1]] < x) {
        dq.pop_back();
      }
      dq.push_back(i);
      if (i - dq[0] >= k) {
        dq.pop_front();
      }
      if (i >= k - 1) {
        ans.push_back(nums[dq[0]]);
      }
    }
    return ans;
  }

  string minWindow(string s, string t) {
    array<int, 52> cnt_s{};
    array<int, 52> cnt_t{};
    for (int i = 0; i < t.size(); i++) {
      char c = t[i];
      if ('a' <= c && c <= 'z') {
        cnt_t[c - 'a']++;
      } else {
        cnt_t[c - 'A' + 26]++;
      }
    }
    int left = 0;
    int ans_l = 0, ans_r = s.size();
    for (int i = 0; i < s.size(); i++) {
      char c = s[i];
      if ('a' <= c && c <= 'z') {
        cnt_s[c - 'a']++;
      } else {
        cnt_s[c - 'A' + 26]++;
      }
      char m = s[left];
      int idx = -1;
      if ('a' <= m && m <= 'z') {
        idx = m - 'a';
      } else {
        idx = m - 'A' + 26;
      }
      while (left <= i && cnt_s[idx] > cnt_t[idx]) {
        cnt_s[idx]--;
        left++;
        m = s[left];
        if ('a' <= m && m <= 'z') {
          idx = m - 'a';
        } else {
          idx = m - 'A' + 26;
        }
      }
      if (i - left >= ans_r - ans_l) {
        continue;
      }
      bool flag = true;
      for (int j = 0; j < 52; j++) {
        if (cnt_s[j] < cnt_t[j]) {
          flag = false;
          break;
        }
      }
      if (flag) {
        ans_l = left;
        ans_r = i;
      }
    }
    if (ans_r - ans_l + 1 > s.size()) {
      return "";
    }

    return string(s.data() + ans_l, ans_r - ans_l + 1);
  }

  int singleNumber(vector<int>& nums) {
    int ans = 0;
    for (auto&& x : nums) {
      ans ^= x;
    }
    return ans;
  }

  int minAnagramLength(string s) {
    int ans = s.size();
    for (int i = s.size() - 1; i > 0; i--) {
      if (s.size() % i != 0) {
        continue;
      }
      array<int, 26> cnt_s{};
      for (int j = 0; j < i; j++) {
        cnt_s[s[j] - 'a']++;
      }
      bool flag = true;
      for (int j = i; j < s.size(); j += i) {
        array<int, 26> cnt_t{};
        for (int k = j; k < j + i; k++) {
          cnt_t[s[k] - 'a']++;
        }
        if (cnt_s != cnt_t) {
          flag = false;
          break;
        }
      }
      if (!flag) {
        break;
      } else {
        ans = i;
      }
    }
    return ans;
  }
  int maxSubArray(vector<int>& nums) {
    int mx = -INT_MAX;
    vector<int> f(nums.size() + 1);
    for (int i = 0; i < nums.size(); i++) {
      f[i + 1] = max(0, f[i]) + nums[i];
      mx = max(mx, f[i + 1]);
    }
    return mx;
  }
  int maxSubArrayRef(vector<int>& nums) {
    int mx = -INT_MAX;
    int mn_pre = 0;
    int pre = 0;
    for (int i = 0; i < nums.size(); i++) {
      pre += nums[i];
      mx = max(mx, pre - mn_pre);
      mn_pre = min(mn_pre, pre);
    }
    return mx;
  }
  int climbStairs(int n) {
    if (n < 2) {
      return n;
    }
    int f1, f2;
    f1 = 1;
    f2 = 2;
    for (int i = 3; i <= n; i++) {
      int tmp = f1 + f2;
      f1 = f2;
      f2 = tmp;
    }
    return f2;
  }

  vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    ans.push_back({1});
    numRows--;
    while (numRows--) {
      vector<int> last = ans[ans.size() - 1];
      vector<int> tmp(last.size() + 1);
      tmp[0] = 1;
      tmp[tmp.size() - 1] = 1;
      for (int i = 1; i < tmp.size() - 1; i++) {
        tmp[i] = last[i - 1] + last[i];
      }
      ans.push_back(tmp);
    }
    return ans;
  }
};

class Solution22 {
 public:
  char path[16];
  vector<string> ans;
  int len;

  void dfs(int i, int cnt) {
    if (i == len) {
      if (cnt == 0) {
        ans.push_back(string(path, len));
      }
      return;
    }
    path[i] = '(';
    dfs(i + 1, cnt + 1);
    if (cnt > 0) {
      path[i] = ')';
      dfs(i + 1, cnt - 1);
    }
  }

  vector<string> generateParenthesis(int n) {
    len = 2 * n;
    ans.clear();
    dfs(0, 0);
    return ans;
  }
};

void twoSum(Solution& s) {
  vector<int> a = {2, 7, 11, 15};
  vector<int> ans = s.twoSum(a, 9);
  std::cout << ans[0] << ' ' << ans[1] << '\n';
}

void groupAnagrams(Solution& s) {
  vector<string> a = {"eat", "tea", "tan", "ate", "nat", "bat"};
  vector<vector<string>> ans = s.groupAnagramsRef(a);
  for (auto&& x : ans) {
    for (auto&& y : x) {
      std::cout << y << ' ';
    }
    std::cout << '\n';
  }
}

class MyCalendar {
 public:
  vector<pair<int, int>> times;
  MyCalendar() { times.clear(); }

  bool book(int startTime, int endTime) {
    int left = -1;
    int right = times.size();
    if (right == 0) {
      times.push_back({startTime, endTime});
      return true;
    }
    while (left + 1 < right) {
      int mid = (right - left) / 2 + left;
      if (times[mid].first < startTime) {
        left = mid;
      } else {
        right = mid;
      }
    }
    // for (auto x: times){
    //     cout << x.first << ' '<< x.second << ' ' << left << ' ';
    // }
    if ((left == -1 && times[left + 1].first >= endTime) ||
        (times[left].second <= startTime &&
         (left == times.size() - 1 || times[left + 1].first >= endTime))) {
      // times.push_back({startTime, endTime});
      times.insert(times.begin()+(left+1),{startTime,endTime});
      return true;
    }
    return false;
  }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(startTime,endTime);
 */

int main() {
  MyCalendar* obj = new MyCalendar();
  bool param_1 = obj->book(47, 50);
  param_1 = obj->book(33, 41);
  param_1 = obj->book(39, 45);
  param_1 = obj->book(33, 42);
  param_1 = obj->book(25, 32);
  param_1 = obj->book(26, 35);
  param_1 = obj->book(19, 25);
  param_1 = obj->book(3, 8);
  param_1 = obj->book(8, 13);
  param_1 = obj->book(18, 27);
  return 0;
}