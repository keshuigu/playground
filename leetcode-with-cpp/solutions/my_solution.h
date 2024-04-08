#ifndef MY_SOLUTION_H
#define MY_SOLUTION_H
#include <string>
#include <vector>

#include "data_struct.h"
using namespace MyDataStruct;
using namespace std;
namespace MySolution {
class Solution {
 private:
  /* data */
 public:
  Solution(/* args */);
  ~Solution();
  /* solution 1 - 500 */
  int solution_27(vector<int>& nums, int val);
  int solution_209(int target, vector<int>& nums);
  /* solution 1 - 500 */

  /* solution 501 - 1000 */
  int solution_704(vector<int>& nums, int target);
  vector<TreeNode*> solution_894(int n);
  /* solution 501 - 1000 */

  /* solution 1001 - 1500 */
  int solution_1004(vector<int>& nums, int k);
  TreeNode* solution_1379(TreeNode* original, TreeNode* cloned,
                          TreeNode* target);
  int solution_1026(TreeNode* root);
  int solution_1026_2(TreeNode* root);
  void solution_1483();  // data_struct.cc#TreeAncestor
  /* solution 1001 - 1500 */

  /* solution 1501 - 2000 */
  void solution_1600();  // data_struct.cc#ThroneInheritance
  /* solution 1501 - 2000 */
  /* solution 2001 - 2500 */
  int solution_2009(vector<int>& nums);
  /* solution 2001 - 2500 */

  /* solution 2501 - 3000 */
  vector<vector<int>> solution_2192(int n, vector<vector<int>>& edges);
  int solution_2908(vector<int>& nums);
  string solution_2810(string s);
  /* solution 2501 - 3000 */
};
}  // namespace MySolution

#endif