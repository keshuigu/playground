
#include "data_struct.h"

#include <queue>

std::ostream &MyDataStruct::operator<<(std::ostream &os, const TreeNode *t) {
  std::queue<const TreeNode *> q;
  q.push(t);
  os << t->val;
  while (!q.empty()) {
    std::queue<const TreeNode *> tmp;
    q.swap(tmp);
    while (!tmp.empty()) {
      const TreeNode *node = tmp.front();
      if (node->left) {
        os << node->left->val << " ";
        q.push(node->left);
      } else {
        os << "null ";
      }
      if (node->right) {
        os << node->right->val;
        q.push(node->right);
      } else {
        os << "null ";
      }
      tmp.pop();
    }
  }
  return os;
}