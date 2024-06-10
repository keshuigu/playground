#ifndef MY_SOLUTION_H
#define MY_SOLUTION_H
#include <string>
#include <vector>

#include "data_struct.h"
using MyDataStruct::ListNode;
using MyDataStruct::TreeNode;
using std::string;
using std::vector;
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
  string solution_405(int num);
  vector<vector<int>> solution_59(int n);
  ListNode* solution_203(ListNode* head, int val);
  int solution_409(string s);
  int solution_414(vector<int>& nums);
  string solution_415(string num1, string num2);
  vector<vector<int>> solution_39(vector<int>& candidates, int target);
  vector<vector<int>> solution_216(int k, int n);
  int solution_377(vector<int>& nums, int target);
  int solution_312(vector<int>& nums);
  /* solution 1 - 500 */

  /* solution 501 - 1000 */
  int solution_704(vector<int>& nums, int target);
  vector<TreeNode*> solution_894(int n);
  void solution_705();  // data_struct.cc#MyHashSet
  void solution_707();  // data_struct.cc#MyLinkedList
  void solution_706();  // data_struct.cc#MyHashMap
  int solution_924(vector<vector<int>>& graph, vector<int>& initial);
  int solution_928(vector<vector<int>>& graph, vector<int>& initial);
  int solution_741(vector<vector<int>>& grid);
  double solution_857(vector<int>& quality, vector<int>& wage, int k);
  int solution_994(vector<vector<int>>& grid);
  int solution_826(vector<int>& difficulty, vector<int>& profit,
                   vector<int>& worker);
  int solution_575(vector<int>& candyType);
  int solution_881(vector<int>& people, int limit);
  /* solution 501 - 1000 */

  /* solution 1001 - 1500 */
  int solution_1004(vector<int>& nums, int k);
  TreeNode* solution_1379(TreeNode* original, TreeNode* cloned,
                          TreeNode* target);
  int solution_1026(TreeNode* root);
  int solution_1026_2(TreeNode* root);
  void solution_1483();  // data_struct.cc#TreeAncestor
  int solution_1052(vector<int>& customers, vector<int>& grumpy, int minutes);
  void solution_1146();  // data_struct.cc#SnapshotArray
  double solution_1491(vector<int>& salary);
  int solution_1235(vector<int>& startTime, vector<int>& endTime,
                    vector<int>& profit);
  int solution_1463(vector<vector<int>>& grid);
  vector<int> solution_1103(int candies, int num_people);
  /* solution 1001 - 1500 */

  /* solution 1501 - 2000 */
  void solution_1600();  // data_struct.cc#ThroneInheritance
  vector<int> solution_1652(vector<int>& code, int k);
  string solution_1702(string binary);
  vector<int> solution_1766(vector<int>& nums, vector<vector<int>>& edges);
  int solution_1883(vector<int>& dist, int speed, int hoursBefore);
  int solution_1553(int n);
  long long solution_1953(vector<int>& milestones);
  int solution_1535(vector<int>& arr, int k);
  int solution_1542(string s);
  vector<int> solution_1673(vector<int>& nums, int k);
  int solution_1738(vector<vector<int>>& matrix, int k);
  /* solution 1501 - 2000 */

  /* solution 2001 - 2500 */
  vector<int> solution_2007(vector<int>& changed);
  vector<int> solution_2007_2(vector<int>& changed);
  int solution_2009(vector<int>& nums);
  int solution_2079(vector<int>& plants, int capacity);
  int solution_2105(vector<int>& plants, int capacityA, int capacityB);
  vector<vector<int>> solution_2192(int n, vector<vector<int>>& edges);
  int solution_2385(TreeNode* root, int start);
  int solution_2391(vector<string>& garbage, vector<int>& travel);
  int solution_2244(vector<int>& tasks);
  vector<vector<int>> solution_2225(vector<vector<int>>& matches);
  vector<int> solution_2028(vector<int>& rolls, int mean, int n);
  /* solution 2001 - 2500 */

  /* solution 2501 - 3000 */
  int solution_2529(vector<int>& nums);
  int solution_2908(vector<int>& nums);
  string solution_2810(string s);
  int solution_2923(vector<vector<int>>& grid);
  int solution_2924(int n, vector<vector<int>>& edges);
  int solution_2739(int mainTank, int additionalTank);
  vector<int> solution_2639(vector<vector<int>>& grid);
  int solution_2798(vector<int>& hours, int target);
  int solution_2960(vector<int>& batteryPercentages);
  int solution_2589(vector<vector<int>>& tasks);
  int solution_2644(vector<int>& nums, vector<int>& divisors);
  vector<int> solution_2903(vector<int>& nums, int indexDifference,
                            int valueDifference);
  int solution_2769(int num, int t);
  int solution_2831(vector<int>& nums, int k);
  vector<int> solution_2951(vector<int>& mountain);
  int solution_2981(string s);
  int solution_2982(string s);
  vector<int> solution_2965(vector<vector<int>>& grid);
  int solution_2928(int n, int limit);
  long long solution_2938(string s);
  /* solution 2501 - 3000 */

  /* solution 3001 - 3500 */
  vector<int> solution_3067(vector<vector<int>>& edges, int signalSpeed);
  vector<int> solution_3072(vector<int>& nums);
  int solution_3038(vector<int>& nums);
  int solution_3040(vector<int>& nums);
  /* solution 3001 - 3500 */
};
}  // namespace MySolution

#endif