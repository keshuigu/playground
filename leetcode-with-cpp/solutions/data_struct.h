#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

class TreeAncestor {
 private:
  std::vector<std::vector<int>> pa;

 public:
  TreeAncestor(int n, std::vector<int> &parent);
  ~TreeAncestor();
  int getKthAncestor(int node, int k);
};

class TreeAncestorTemplate {
 private:
  std::vector<std::vector<int>> pa;
  std::vector<int> depth;

 public:
  TreeAncestorTemplate(std::vector<std::pair<int, int>> &edges);
  ~TreeAncestorTemplate();
  int getKthAncestor(int node, int k);
  int getLca(int x, int y);
};

class ThroneIneritance {
 private:
  std::unordered_map<std::string, std::vector<std::string>> edges;
  std::unordered_set<std::string> dead;
  std::string king;

 public:
  ThroneIneritance(std::string kingName);
  ~ThroneIneritance();
  void birth(std::string parentName, std::string childName);
  void death(std::string name);
  std::vector<std::string> getInheritanceOrder();
};

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
std::ostream &operator<<(std::ostream &os, const ListNode *t);

}  // namespace MyDataStruct
#endif