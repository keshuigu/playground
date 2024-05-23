#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "testcase.h"
using namespace std;
void getTestcase(map<string, function<void()>>& testMap, Testcase::Test& t);
int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Please provide a test case name as a command line argument."
         << endl;
    return 1;
  }
  string testName = argv[1];
  Testcase::Test t = Testcase::Test();
  map<string, function<void()>> testMap;
  getTestcase(testMap, t);
  if (testMap.find(testName) != testMap.end()) {
    testMap[testName]();
  } else {
    cout << "Test case not found." << endl;
  }
  return 0;
}

void getTestcase(map<string, function<void()>>& testMap, Testcase::Test& t) {
  testMap["2908"] = bind(&Testcase::Test::test_2908, &t);
  testMap["1004"] = bind(&Testcase::Test::test_1004, &t);
  testMap["2810"] = bind(&Testcase::Test::test_2810, &t);
  testMap["894"] = bind(&Testcase::Test::test_894, &t);
  testMap["1379"] = bind(&Testcase::Test::test_1379, &t);
  testMap["209"] = bind(&Testcase::Test::test_209, &t);
  testMap["2192"] = bind(&Testcase::Test::test_2192, &t);
  testMap["1026"] = bind(&Testcase::Test::test_1026, &t);
  testMap["1026_2"] = bind(&Testcase::Test::test_1026_2, &t);
  testMap["1483"] = bind(&Testcase::Test::test_1483, &t);
  testMap["1600"] = bind(&Testcase::Test::test_1600, &t);
  testMap["2009"] = bind(&Testcase::Test::test_2009, &t);
  testMap["405"] = bind(&Testcase::Test::test_405, &t);
  testMap["2529"] = bind(&Testcase::Test::test_2529, &t);
  testMap["59"] = bind(&Testcase::Test::test_59, &t);
  testMap["1702"] = bind(&Testcase::Test::test_1702, &t);
  testMap["203"] = bind(&Testcase::Test::test_203, &t);
  testMap["1766"] = bind(&Testcase::Test::test_1766, &t);
  testMap["409"] = bind(&Testcase::Test::test_409, &t);
  testMap["707"] = bind(&Testcase::Test::test_707, &t);
  testMap["2923"] = bind(&Testcase::Test::test_2923, &t);
  testMap["414"] = bind(&Testcase::Test::test_414, &t);
  testMap["2924"] = bind(&Testcase::Test::test_2924, &t);
  testMap["705"] = bind(&Testcase::Test::test_705, &t);
  testMap["706"] = bind(&Testcase::Test::test_706, &t);
  testMap["924"] = bind(&Testcase::Test::test_924, &t);
  testMap["928"] = bind(&Testcase::Test::test_928, &t);
  testMap["415"] = bind(&Testcase::Test::test_415, &t);
  testMap["2007"] = bind(&Testcase::Test::test_2007, &t);
  testMap["2007_2"] = bind(&Testcase::Test::test_2007_2, &t);
  testMap["1883"] = bind(&Testcase::Test::test_1883, &t);
  testMap["39"] = bind(&Testcase::Test::test_39, &t);
  testMap["216"] = bind(&Testcase::Test::test_216, &t);
  testMap["377"] = bind(&Testcase::Test::test_377, &t);
  testMap["1052"] = bind(&Testcase::Test::test_1052, &t);
  testMap["2385"] = bind(&Testcase::Test::test_2385, &t);
  testMap["2739"] = bind(&Testcase::Test::test_2739, &t);
  testMap["1146"] = bind(&Testcase::Test::test_1146, &t);
  testMap["2639"] = bind(&Testcase::Test::test_2639, &t);
  testMap["2798"] = bind(&Testcase::Test::test_2798, &t);
  testMap["741"] = bind(&Testcase::Test::test_741, &t);
  testMap["857"] = bind(&Testcase::Test::test_857, &t);
  testMap["1491"] = bind(&Testcase::Test::test_1491, &t);
  testMap["1235"] = bind(&Testcase::Test::test_1235, &t);
  testMap["1652"] = bind(&Testcase::Test::test_1652, &t);
  testMap["1463"] = bind(&Testcase::Test::test_1463, &t);
  testMap["2079"] = bind(&Testcase::Test::test_2079, &t);
  testMap["2105"] = bind(&Testcase::Test::test_2105, &t);
  testMap["2960"] = bind(&Testcase::Test::test_2960, &t);
  testMap["2391"] = bind(&Testcase::Test::test_2391, &t);
  testMap["1553"] = bind(&Testcase::Test::test_1553, &t);
  testMap["994"] = bind(&Testcase::Test::test_994, &t);
  testMap["2244"] = bind(&Testcase::Test::test_2244, &t);
  testMap["2589"] = bind(&Testcase::Test::test_2589, &t);
  testMap["1953"] = bind(&Testcase::Test::test_1953, &t);
  testMap["826"] = bind(&Testcase::Test::test_826, &t);
  testMap["2644"] = bind(&Testcase::Test::test_2644, &t);
  testMap["1535"] = bind(&Testcase::Test::test_1535, &t);
  testMap["1542"] = bind(&Testcase::Test::test_1542, &t);
  testMap["2225"] = bind(&Testcase::Test::test_2225, &t);
  testMap["2769"] = bind(&Testcase::Test::test_2769, &t);
  testMap["2831"] = bind(&Testcase::Test::test_2831, &t);
}