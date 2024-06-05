#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
#include <list>
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

class MyLinkedList {
 private:
  class Node {
   private:
   public:
    int val;
    Node *next;
    Node *prev;
    Node(int val);
    ~Node();
  };
  Node *dummyHead;
  Node *dummyTail;
  int size;

 public:
  MyLinkedList();
  ~MyLinkedList();
  int get(int index);
  void addAtHead(int val);
  void addAtTail(int val);
  void addAtIndex(int index, int val);
  void deleteAtIndex(int index);
};

class MyHashSet {
 private:
  std::vector<int> bs;
  void setVal(int bucketId, int bitId, int val);
  int getVal(int bucketId, int bitId);

 public:
  MyHashSet(/* args */);
  ~MyHashSet();
  void add(int key);
  void remove(int key);
  bool contains(int key);
};

class MyHashMap {
 private:
  std::vector<std::list<std::pair<int, int>>> bs;
  int base;

 public:
  MyHashMap(/* args */);
  ~MyHashMap();
  void put(int key, int value);
  int get(int key);
  void remove(int key);
};
class SnapshotArray {
 public:
  inline SnapshotArray(int length) {}

  inline void set(int index, int val) {
    hitory_[index].emplace_back(cur_, val);
  }

  inline int snap() { return cur_++; }

  int get(int index, int snap_id);

 private:
  int cur_ = 0;
  // 每个index的历史修改记录
  std::unordered_map<int, std::vector<std ::pair<int, int>>> hitory_;
};

class Fenwick {
 public:
  explicit Fenwick(int n);
  ~Fenwick();
  std::vector<int> tree;
  void add(int i);
  int pre(int i);
};

}  // namespace MyDataStruct

#endif