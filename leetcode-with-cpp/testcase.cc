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