#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
#include <vector>
namespace MyDataStruct {
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};
std::ostream &operator<<(std::ostream &os, const TreeNode *t);
TreeNode *construct_binary_tree(const std::vector<int> &vec);
}  // namespace MyDataStruct

#endif