#include <bits/stdc++.h>

using std::cout;
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

int main() {
  Solution s;
  // twoSum(s);
  // groupAnagrams(s);
  vector<int> ss({4, 2, 0, 3, 2, 5});
  // ss.pop_back()
  int ans = s.trap(ss);
  cout << ans << '\n';
  return 0;
}