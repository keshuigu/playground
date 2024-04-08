#include "testcase.h"

#include <iostream>

#include "data_struct.h"
#include "my_solution.h"
using namespace MySolution;
using namespace Testcase;
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