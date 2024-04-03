
#include "data_struct.h"

#include <queue>

using namespace MyDataStruct;

std::ostream &MyDataStruct::operator<<(std::ostream &os, const TreeNode *t) {
  std::queue<const TreeNode *> q;
  q.push(t);
  os << t->val << " ";
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
        os << node->right->val << " ";
        q.push(node->right);
      } else {
        os << "null ";
      }
      tmp.pop();
    }
  }
  return os;
}

TreeNode *MyDataStruct::construct_binary_tree(const std::vector<int> &vec) {
  std::vector<TreeNode *> vecTree(vec.size(), nullptr);
  TreeNode *root = nullptr;
  for (int i = 0; i < vec.size(); i++) {
    TreeNode *node = nullptr;
    if (vec[i] != -1) {
      node = new TreeNode(vec[i]);
      vecTree[i] = node;
    }
    if (i == 0) {
      root = node;
    }
  }
  // 注意边界
  for (int i = 0; i * 2 + 1 < vecTree.size(); i++) {
    if (vecTree[i]) {
      vecTree[i]->left = vecTree[i * 2 + 1];
      if (i * 2 + 2 < vecTree.size()) {
        vecTree[i]->right = vecTree[i * 2 + 2];
      }
    }
  }
  return root;
}