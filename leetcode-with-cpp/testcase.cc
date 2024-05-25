#include "testcase.h"

#include <iostream>

#include "data_struct.h"
#include "my_solution.h"
namespace Testcase {
using namespace MySolution;
using namespace std;
using namespace MyDataStruct;
Test::Test(/* args */) {}
Test::~Test() {}

void Test::test_2908() {
  vector<int> v = {8, 6, 1, 5, 3};
  cout << Solution().solution_2908(v) << endl;
  vector<int> v1 = {5, 4, 8, 7, 10, 2};
  cout << Solution().solution_2908(v1) << endl;
  vector<int> v2 = {6, 5, 4, 3, 4, 5};
  cout << Solution().solution_2908(v2) << endl;
}

void Test::test_1004() {
  vector<int> v = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
  cout << Solution().solution_1004(v, 2) << endl;
  vector<int> v1 = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
  cout << Solution().solution_1004(v1, 3) << endl;
}

void Test::test_2810() {
  cout << Solution().solution_2810(string("string")) << endl;
  cout << Solution().solution_2810(string("poiinter")) << endl;
}

void Test::test_894() {
  cout << new TreeNode(0, new TreeNode(1), new TreeNode(2)) << endl;
  vector<TreeNode *> v = Solution().solution_894(7);
  for (auto r : v) {
    cout << r << endl;
  }

  // cout << v << endl;
  // cout << Solution().solution_894(7) << endl;
}

void Test::test_1379() {
  TreeNode *target = new TreeNode(3, new TreeNode(6), new TreeNode(19));
  TreeNode *original = new TreeNode(7, new TreeNode(4), target);
  vector<int> v = {7, 4, 3, -1, -1, 6, 19};
  TreeNode *cloned = construct_binary_tree(v);
  cout << Solution().solution_1379(original, cloned, target) << endl;
}

void Test::test_209() {
  vector<int> v = {2, 3, 1, 2, 4, 3};
  cout << Solution().solution_209(7, v) << endl;
  v = {1, 4, 4};
  cout << Solution().solution_209(4, v) << endl;
  v = {1, 1, 1, 1, 1, 1, 1, 1};
  cout << Solution().solution_209(11, v) << endl;
}

void Test::test_2192() {
  vector<vector<int>> v = {{0, 3}, {0, 4}, {1, 3}, {2, 4}, {2, 7},
                           {3, 5}, {3, 6}, {3, 7}, {4, 6}};
  for (auto &&ans : Solution().solution_2192(8, v)) {
    for (auto &&parent : ans) {
      cout << parent << " ";
    }
    cout << endl;
  }
  vector<vector<int>> v1 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2},
                            {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};
  for (auto &&ans : Solution().solution_2192(5, v1)) {
    for (auto &&parent : ans) {
      cout << parent << " ";
    }
    cout << endl;
  }
}

void Test::test_1026() {
  vector<int> v = {8, 3, 10, 1, 6, -1, 14, -1, -1, 4, 7, 13};
  cout << Solution().solution_1026(construct_binary_tree(v)) << endl;
  v = {1, -1, 2, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, 3};
  cout << Solution().solution_1026(construct_binary_tree(v)) << endl;
  v = {1, 1, 8};
  cout << Solution().solution_1026(construct_binary_tree(v)) << endl;
}

void Test::test_1026_2() {
  vector<int> v = {8, 3, 10, 1, 6, -1, 14, -1, -1, 4, 7, 13};
  cout << Solution().solution_1026_2(construct_binary_tree(v)) << endl;
  v = {1, -1, 2, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, 3};
  cout << Solution().solution_1026_2(construct_binary_tree(v)) << endl;
  v = {1, 1, 8};
  cout << Solution().solution_1026_2(construct_binary_tree(v)) << endl;
}

void Test::test_1483() {
  vector<int> v = {-1, 0, 0, 1, 1, 2, 2};
  TreeAncestor tree = TreeAncestor(7, v);
  cout << tree.getKthAncestor(3, 1) << endl;
  cout << tree.getKthAncestor(5, 2) << endl;
  cout << tree.getKthAncestor(6, 3) << endl;
}

void Test::test_1600() {
  ThroneIneritance *t = new ThroneIneritance("king");
  t->birth("king", "andy");
  t->birth("king", "bob");
  t->birth("king", "catherine");
  t->birth("andy", "matthew");
  t->birth("bob", "alex");
  t->birth("bob", "asha");
  for (auto &&person : t->getInheritanceOrder()) {
    cout << person << " ";
  }
  cout << endl;
  t->death("bob");
  for (auto &&person : t->getInheritanceOrder()) {
    cout << person << " ";
  }
  cout << endl;
}

void Test::test_2009() {
  vector<int> v = {4, 2, 5, 3};
  cout << Solution().solution_2009(v) << endl;
  vector<int> v1 = {1, 2, 3, 5, 6};
  cout << Solution().solution_2009(v1) << endl;
  vector<int> v2 = {1, 10, 100, 1000};
  cout << Solution().solution_2009(v2) << endl;
}

void Test::test_405() {
  cout << Solution().solution_405(26) << endl;
  cout << Solution().solution_405(-1) << endl;
}

void Test::test_2529() {
  vector<int> v = {-2, -1, -1, 1, 2, 3};
  cout << Solution().solution_2529(v) << endl;
  v = {-3, -2, -1, 0, 0, 1, 2};
  cout << Solution().solution_2529(v) << endl;
  v = {5, 20, 66, 1314};
  cout << Solution().solution_2529(v) << endl;
}

void Test::test_59() {
  vector<vector<int>> v = Solution().solution_59(3);
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      cout << v[i][j];
    }
    cout << endl;
  }

  v = Solution().solution_59(1);
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      cout << v[i][j];
    }
    cout << endl;
  }

  v = Solution().solution_59(5);
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      cout << v[i][j];
    }
    cout << endl;
  }
}

void Test::test_1702() {
  cout << Solution().solution_1702(string("000110")) << endl;
  cout << Solution().solution_1702(string("01")) << endl;
}

void Test::test_203() {
  ListNode *head = new ListNode(
      1,
      new ListNode(
          2,
          new ListNode(
              6, new ListNode(
                     3, new ListNode(4, new ListNode(5, new ListNode(6)))))));
  cout << Solution().solution_203(head, 6) << endl;
  head = nullptr;
  cout << Solution().solution_203(head, 1) << endl;
  head = new ListNode(7, new ListNode(7, new ListNode(7, new ListNode(7))));
  cout << Solution().solution_203(head, 7) << endl;
}

void Test::test_1766() {
  vector<int> nums = {2, 3, 3, 2};
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}};
  vector<int> ans = Solution().solution_1766(nums, edges);
  for (auto &&i : ans) {
    cout << i;
  }
  cout << endl;

  nums = {5, 6, 10, 2, 3, 6, 15};
  edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
  ans = Solution().solution_1766(nums, edges);
  for (auto &&i : ans) {
    cout << i;
  }
  cout << endl;
}

void Test::test_409() {
  string s = "abccccdd";
  cout << Solution().solution_409(s) << endl;
  s = "a";
  cout << Solution().solution_409(s) << endl;
  s = "aaaaaccc";
  cout << Solution().solution_409(s) << endl;
}

void Test::test_707() {
  MyLinkedList o = MyLinkedList();
  o.addAtHead(1);
  o.addAtTail(3);
  o.addAtIndex(1, 2);
  cout << o.get(1) << endl;
  o.deleteAtIndex(1);
  cout << o.get(1) << endl;
  // o.~MyLinkedList();
  MyLinkedList o1 = MyLinkedList();
  o1.addAtIndex(0, 10);
  o1.addAtIndex(0, 20);
  o1.addAtIndex(1, 20);
  cout << o1.get(0) << endl;
}

void Test::test_2923() {
  vector<vector<int>> v = {{0, 1}, {0, 0}};
  cout << Solution().solution_2923(v) << endl;
  v = {{0, 0, 1}, {1, 0, 1}, {0, 0, 0}};
  cout << Solution().solution_2923(v) << endl;
}

void Test::test_414() {
  vector<int> v = {3, 2, 1};
  cout << Solution().solution_414(v) << endl;
  v = {1, 2};
  cout << Solution().solution_414(v) << endl;
  v = {2, 2, 3, 1};
  cout << Solution().solution_414(v) << endl;
}

void Test::test_2924() {
  vector<vector<int>> edges = {{0, 1}, {1, 2}};
  cout << Solution().solution_2924(3, edges) << endl;
  edges = {{0, 2}, {1, 3}, {1, 2}};
  cout << Solution().solution_2924(4, edges) << endl;
}

void Test::test_705() {
  MyHashSet s = MyHashSet();

  s.add(1);
  s.add(2);
  cout << s.contains(1) << endl;
  cout << s.contains(3) << endl;
  s.add(2);
  cout << s.contains(2) << endl;
  s.remove(2);
  cout << s.contains(2) << endl;
}

void Test::test_706() {
  MyHashMap o = MyHashMap();
  o.put(1, 1);
  o.put(2, 2);
  cout << o.get(1) << endl;
  cout << o.get(3) << endl;
  o.put(2, 1);
  cout << o.get(2) << endl;
  o.remove(2);
  cout << o.get(2) << endl;
}

void Test::test_924() {
  vector<vector<int>> graph = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
  vector<int> initial = {0, 1};
  cout << Solution().solution_924(graph, initial) << endl;
  graph = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  initial = {0, 2};
  cout << Solution().solution_924(graph, initial) << endl;
  graph = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  initial = {1, 2};
  cout << Solution().solution_924(graph, initial) << endl;
  graph = {{1, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 1}};
  initial = {1, 3};
  cout << Solution().solution_924(graph, initial) << endl;
  graph = {{1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
           {0, 1, 1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
           {1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
           {0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
           {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 0, 1}};
  initial = {1, 3, 0};
  cout << Solution().solution_924(graph, initial) << endl;
}

void Test::test_928() {
  vector<vector<int>> graph = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
  vector<int> initial = {0, 1};
  cout << Solution().solution_928(graph, initial) << endl;
  graph = {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}};
  initial = {0, 1};
  cout << Solution().solution_928(graph, initial) << endl;
  graph = {{1, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 1, 1}, {0, 0, 1, 1}};
  initial = {0, 1};
  cout << Solution().solution_928(graph, initial) << endl;
}

void Test::test_415() {
  cout << Solution().solution_415("11", "123") << endl;
  cout << Solution().solution_415("456", "77") << endl;
  cout << Solution().solution_415("0", "0") << endl;
  cout << Solution().solution_415("10", "90") << endl;
}

void Test::test_2007() {
  vector<int> v = {4, 4, 16, 20, 8, 8, 2, 10};
  for (auto &&i : Solution().solution_2007(v)) {
    cout << i;
  }
  cout << endl;
  v = {1, 3, 4, 2, 6, 8};

  for (auto &&i : Solution().solution_2007(v)) {
    cout << i;
  }
  cout << endl;
  v = {6, 3, 0, 1};
  for (auto &&i : Solution().solution_2007(v)) {
    cout << i;
  }
  cout << endl;
  v = {1};
  for (auto &&i : Solution().solution_2007(v)) {
    cout << i;
  }
  cout << endl;
}

void Test::test_2007_2() {
  vector<int> v = {4, 4, 16, 20, 8, 8, 2, 10};
  for (auto &&i : Solution().solution_2007_2(v)) {
    cout << i;
  }
  cout << endl;
  v = {1, 3, 4, 2, 6, 8};

  for (auto &&i : Solution().solution_2007_2(v)) {
    cout << i;
  }
  cout << endl;
  v = {6, 3, 0, 1};
  for (auto &&i : Solution().solution_2007_2(v)) {
    cout << i;
  }
  cout << endl;
  v = {1};
  for (auto &&i : Solution().solution_2007_2(v)) {
    cout << i;
  }
  cout << endl;
}

void Test::test_1883() {
  vector<int> dist = {1, 3, 2};
  cout << Solution().solution_1883(dist, 4, 2) << endl;
  dist = {7, 3, 5, 5};
  cout << Solution().solution_1883(dist, 2, 10) << endl;
  dist = {7, 3, 5, 5};
  cout << Solution().solution_1883(dist, 1, 10) << endl;
}

void Test::test_39() {
  vector<int> candidates = {2, 3, 6, 7};
  vector<vector<int>> ans = Solution().solution_39(candidates, 7);
  for (auto &&i : ans) {
    cout << '[';
    for (auto &&j : i) {
      cout << j << ' ';
    }
    cout << ']';
  }
  cout << endl;

  candidates = {2, 3, 5};
  ans = Solution().solution_39(candidates, 8);
  for (auto &&i : ans) {
    cout << '[';
    for (auto &&j : i) {
      cout << j << ' ';
    }
    cout << ']';
  }
  cout << endl;

  candidates = {2};
  ans = Solution().solution_39(candidates, 1);
  for (auto &&i : ans) {
    cout << '[';
    for (auto &&j : i) {
      cout << j << ' ';
    }
    cout << ']';
  }
  cout << endl;
}

void Test::test_216() {
  vector<vector<int>> ans = Solution().solution_216(3, 7);
  for (auto &&i : ans) {
    cout << '[';
    for (auto &&j : i) {
      cout << j << ' ';
    }
    cout << ']';
  }
  cout << endl;

  ans = Solution().solution_216(3, 9);
  for (auto &&i : ans) {
    cout << '[';
    for (auto &&j : i) {
      cout << j << ' ';
    }
    cout << ']';
  }
  cout << endl;
  ans = Solution().solution_216(4, 1);
  for (auto &&i : ans) {
    cout << '[';
    for (auto &&j : i) {
      cout << j << ' ';
    }
    cout << ']';
  }
  cout << endl;
}

void Test::test_377() {
  vector<int> nums = {1, 2, 3};
  cout << Solution().solution_377(nums, 4) << endl;
  nums = {9};
  cout << Solution().solution_377(nums, 3) << endl;
}

void Test::test_1052() {
  vector<int> customers = {1, 0, 1, 2, 1, 1, 7, 5};
  vector<int> grumpy = {0, 1, 0, 1, 0, 1, 0, 1};
  cout << Solution().solution_1052(customers, grumpy, 3) << endl;
  customers = {1};
  grumpy = {0};
  cout << Solution().solution_1052(customers, grumpy, 1) << endl;
}

void Test::test_2385() {
  TreeNode *root = construct_binary_tree({1, 5, 3, -1, 4, 10, 6, -1, -1, 9, 2});
  cout << Solution().solution_2385(root, 3) << endl;
  root = new TreeNode(1);
  cout << Solution().solution_2385(root, 1) << endl;
}

void Test::test_2739() {
  cout << Solution().solution_2739(5, 10) << endl;
  cout << Solution().solution_2739(1, 2) << endl;
}

void Test::test_1146() {
  auto o = SnapshotArray(3);
  o.set(0, 5);
  o.snap();
  o.set(0, 6);
  cout << o.get(0, 0) << endl;
}

void Test::test_2639() {
  vector<vector<int>> grid = {{1}, {22}, {333}};
  vector<int> ans = Solution().solution_2639(grid);
  for (auto &&i : ans) {
    cout << i;
  }
  cout << endl;

  grid = {{-15, 1, 3}, {15, 7, 12}, {5, 6, -2}};
  ans = Solution().solution_2639(grid);
  for (auto &&i : ans) {
    cout << i;
  }
  cout << endl;
}

void Test::test_2798() {
  vector<int> grid = {0, 1, 2, 3, 4};
  cout << Solution().solution_2798(grid, 2) << endl;

  grid = {5, 1, 4, 2, 2};
  cout << Solution().solution_2798(grid, 6) << endl;
}

void Test::test_741() {
  vector<vector<int>> grid = {{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
  cout << Solution().solution_741(grid) << endl;

  grid = {{1, 1, -1}, {1, -1, 1}, {-1, 1, 1}};
  cout << Solution().solution_741(grid) << endl;
}

void Test::test_857() {
  vector<int> quality = {10, 20, 5};
  vector<int> wage = {70, 50, 30};
  cout << Solution().solution_857(quality, wage, 2) << endl;
  quality = {3, 1, 10, 10, 1};
  wage = {4, 8, 2, 2, 7};
  cout << Solution().solution_857(quality, wage, 3) << endl;
}

void Test::test_1491() {
  vector<int> salary = {4000, 3000, 1000, 2000};
  cout << Solution().solution_1491(salary) << endl;
  salary = {1000, 2000, 3000};
  cout << Solution().solution_1491(salary) << endl;
  salary = {6000, 5000, 4000, 3000, 2000, 1000};
  cout << Solution().solution_1491(salary) << endl;
  salary = {8000, 9000, 2000, 3000, 6000, 1000};
  cout << Solution().solution_1491(salary) << endl;
}

void Test::test_1235() {
  vector<int> startTime = {1, 2, 3, 3};
  vector<int> endTime = {3, 4, 5, 6};
  vector<int> profit = {50, 10, 40, 70};
  cout << Solution().solution_1235(startTime, endTime, profit) << endl;
  startTime = {1, 2, 3, 4, 6};
  endTime = {3, 5, 10, 6, 9};
  profit = {20, 20, 100, 70, 60};
  cout << Solution().solution_1235(startTime, endTime, profit) << endl;
  startTime = {1, 1, 1};
  endTime = {2, 3, 4};
  profit = {5, 6, 4};
  cout << Solution().solution_1235(startTime, endTime, profit) << endl;
}

void Test::test_1652() {
  vector<int> code = {5, 7, 1, 4};
  vector<int> ans;
  ans = Solution().solution_1652(code, 3);
  for (auto &&x : ans) {
    cout << x << " ";
  }
  cout << endl;
  code = {1, 2, 3, 4};
  ans = Solution().solution_1652(code, 0);
  for (auto &&x : ans) {
    cout << x << " ";
  }
  cout << endl;
  code = {2, 4, 9, 3};
  ans = Solution().solution_1652(code, -2);
  for (auto &&x : ans) {
    cout << x << " ";
  }
  cout << endl;
}

void Test::test_1463() {
  vector<vector<int>> grid = {{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}};
  cout << Solution().solution_1463(grid) << endl;

  grid = {{1, 0, 0, 0, 0, 0, 1},
          {2, 0, 0, 0, 0, 3, 0},
          {2, 0, 9, 0, 0, 0, 0},
          {0, 3, 0, 5, 4, 0, 0},
          {1, 0, 2, 3, 0, 0, 6}};
  cout << Solution().solution_1463(grid) << endl;
}

void Test::test_2079() {
  vector<int> grid = {2, 2, 3, 3};
  cout << Solution().solution_2079(grid, 5) << endl;

  grid = {1, 1, 1, 4, 2, 3};
  cout << Solution().solution_2079(grid, 4) << endl;
}

void Test::test_2105() {
  vector<int> grid = {2, 2, 3, 3};
  cout << Solution().solution_2105(grid, 5, 5) << endl;

  grid = {2, 2, 3, 3};
  cout << Solution().solution_2105(grid, 3, 4) << endl;

  grid = {5};
  cout << Solution().solution_2105(grid, 10, 8) << endl;
}

void Test::test_2960() {
  vector<int> grid = {1, 1, 2, 1, 3};
  cout << Solution().solution_2960(grid) << endl;

  grid = {0, 1, 2};
  cout << Solution().solution_2960(grid) << endl;
}

void Test::test_2391() {
  vector<string> grabage = {"G", "P", "GP", "GG"};
  vector<int> travel = {2, 4, 3};
  cout << Solution().solution_2391(grabage, travel) << endl;

  grabage = {"MMM", "PGM", "GP"};
  travel = {3, 10};
  cout << Solution().solution_2391(grabage, travel) << endl;
}

void Test::test_1553() {
  cout << Solution().solution_1553(10) << endl;
  cout << Solution().solution_1553(6) << endl;
  cout << Solution().solution_1553(1) << endl;
  cout << Solution().solution_1553(56) << endl;
}

void Test::test_994() {
  vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  cout << Solution().solution_994(grid) << endl;
  grid = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
  cout << Solution().solution_994(grid) << endl;
  grid = {{0, 2}};
  cout << Solution().solution_994(grid) << endl;
}

void Test::test_2244() {
  vector<int> grid = {2, 2, 3, 3, 2, 4, 4, 4, 4, 4};
  cout << Solution().solution_2244(grid) << endl;
  grid = {2, 3, 3};
  cout << Solution().solution_2244(grid) << endl;
}

void Test::test_2589() {
  vector<vector<int>> tasks = {{2, 3, 1}, {4, 5, 1}, {1, 5, 2}};
  cout << Solution().solution_2589(tasks) << endl;
  tasks = {{1, 3, 2}, {2, 5, 3}, {5, 6, 2}};
  cout << Solution().solution_2589(tasks) << endl;
}

void Test::test_1953() {
  vector<int> grid = {1, 2, 3};
  cout << Solution().solution_1953(grid) << endl;
  grid = {5, 2, 1};
  cout << Solution().solution_1953(grid) << endl;
}

void Test::test_826() {
  vector<int> difficulty = {2, 4, 6, 8, 10};
  vector<int> profit = {10, 20, 30, 40, 50};
  vector<int> worker = {4, 5, 6, 7};
  cout << Solution().solution_826(difficulty, profit, worker) << endl;
  difficulty = {85, 47, 57};
  profit = {24, 66, 99};
  worker = {40, 25, 25};
  cout << Solution().solution_826(difficulty, profit, worker) << endl;
}

void Test::test_2644() {
  vector<int> nums = {4, 7, 9, 3, 9};
  vector<int> divisors = {5, 2, 3};
  cout << Solution().solution_2644(nums, divisors) << endl;
  nums = {20, 14, 21, 10};
  divisors = {5, 7, 5};
  cout << Solution().solution_2644(nums, divisors) << endl;
}

void Test::test_1535() {
  vector<int> arr = {2, 1, 3, 5, 4, 6, 7};
  cout << Solution().solution_1535(arr, 2) << endl;
  arr = {3, 2, 1};
  cout << Solution().solution_1535(arr, 10) << endl;
  arr = {1, 9, 8, 2, 3, 7, 6, 4, 5};
  cout << Solution().solution_1535(arr, 7) << endl;
  arr = {1, 11, 22, 33, 44, 55, 66, 77, 88, 99};
  cout << Solution().solution_1535(arr, 1000000000) << endl;
}

void Test::test_1542() {
  cout << Solution().solution_1542("3242415") << endl;
  cout << Solution().solution_1542("12345678") << endl;
  cout << Solution().solution_1542("213123") << endl;
  cout << Solution().solution_1542("00") << endl;
}

void Test::test_2903() {
  vector<int> nums = {5, 1, 4, 1};
  vector<int> ans = Solution().solution_2903(nums, 2, 4);
  cout << ans[0] << ans[1] << endl;
  nums = {2, 1};
  ans = Solution().solution_2903(nums, 0, 0);
  cout << ans[0] << ans[1] << endl;
  nums = {1, 2, 3};
  ans = Solution().solution_2903(nums, 2, 4);
  cout << ans[0] << ans[1] << endl;
}

}  // namespace Testcase