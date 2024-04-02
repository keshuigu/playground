#ifndef MY_SOLUTION_H
#define MY_SOLUTION_H
#include <string>
#include <vector>
namespace MySolution {
class Solution {
 private:
  /* data */
 public:
  Solution(/* args */);
  ~Solution();
  int solution_27(std::vector<int>& nums, int val);
  int solution_704(std::vector<int>& nums, int target);
  int solution_1004(std::vector<int>& nums, int k);
  int solution_2908(std::vector<int>& nums);
  std::string solution_2810(std::string s);
};
}  // namespace MySolution

#endif