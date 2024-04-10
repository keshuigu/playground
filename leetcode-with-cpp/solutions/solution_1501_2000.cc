#include <functional>
#include <set>

#include "my_solution.h"
using namespace MySolution;

string Solution::solution_1702(string binary) {
  int i = binary.find('0');
  if (i < 0) {
    return binary;
  }
  int cnt1 = count(binary.begin() + i, binary.end(), '1');
  return string(binary.size() - 1 - cnt1, '1') + '0' + string(cnt1, '1');
}