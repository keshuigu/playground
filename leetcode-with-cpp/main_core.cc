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
}