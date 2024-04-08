
#include "data_struct.h"

#include <functional>
#include <queue>

using namespace MyDataStruct;
using namespace std;
ostream &MyDataStruct::operator<<(ostream &os, const TreeNode *t) {
  queue<const TreeNode *> q;
  q.push(t);
  os << t->val << " ";
  while (!q.empty()) {
    queue<const TreeNode *> tmp;
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

TreeNode *MyDataStruct::construct_binary_tree(const vector<int> &vec) {
  vector<TreeNode *> vecTree(vec.size(), nullptr);
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

TreeAncestor::TreeAncestor(int n, vector<int> &parent) {
  int m = 32 - __builtin_clz(n);  // 二进制长度
  pa.resize(n, vector<int>(m, -1));
  for (int i = 0; i < n; i++) {
    pa[i][0] = parent[i];
  }
  for (int i = 0; i < m - 1; i++) {
    for (int x = 0; x < n; x++) {
      if (int p = pa[x][i]; p != -1) {
        pa[x][i + 1] = pa[p][i];
      }
    }
  }
}

TreeAncestor::~TreeAncestor() {}

int TreeAncestor::getKthAncestor(int node, int k) {
  int m = 32 - __builtin_clz(k);
  for (int i = 0; i < m; i++) {
    if ((k >> i) & 1) {
      node = pa[node][i];
      if (node < 0) {
        break;
      }
    }
  }
  return node;
}

TreeAncestorTemplate::TreeAncestorTemplate(vector<pair<int, int>> &edges) {
  int n = edges.size() + 1;
  int m = 32 - __builtin_clz(n);  // 二进制长度
  vector<vector<int>> g(n);
  for (auto &&[x, y] : edges) {
    g[x].push_back(y);
    g[y].push_back(x);
  }

  depth.resize(n);
  pa.resize(n, vector<int>(m, -1));
  function<void(int, int)> dfs = [&](int x, int fa) {
    pa[x][0] = fa;
    for (auto &&y : g[x]) {
      if (!(y == fa)) {
        depth[y] = depth[x] + 1;
        dfs(y, x);
      }
    }
  };
  dfs(0, -1);

  for (int i = 0; i < m; i++) {
    for (int x = 0; x < n; x++) {
      if (int p = pa[x][i]; p != -1) {
        pa[x][i + 1] = pa[p][i];
      }
    }
  }
}

TreeAncestorTemplate::~TreeAncestorTemplate() {}

int TreeAncestorTemplate::getKthAncestor(int node, int k) {
  for (; k; k &= k - 1) {
    node = pa[node][__builtin_ctz(k)];
  }
  return node;
}

int TreeAncestorTemplate::getLca(int x, int y) {
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  y = getKthAncestor(y, depth[y] - depth[x]);
  if (y == x) {
    return x;
  }
  for (int i = pa.size() - 1; i >= 0; i--) {
    int px = pa[x][i], py = pa[y][i];
    if (px != py) {
      x = px;
      y = py;
    }
  }
  return pa[x][0];
}

ThroneIneritance::ThroneIneritance(string kingName)
    : king{std::move(kingName)} {}

ThroneIneritance::~ThroneIneritance() {}

void ThroneIneritance::birth(string parentName, string childName) {
  edges[std::move(parentName)].push_back(std::move(childName));
}

void ThroneIneritance::death(string name) { dead.insert(std::move(name)); }

vector<string> ThroneIneritance::getInheritanceOrder() {
  vector<string> ans;
  function<void(const string &)> preorder = [&](const string &name) {
    if (!dead.count(name)) {
      ans.push_back(name);
    }
    if (edges.count(name)) {
      for (auto &&child : edges[name]) {
        preorder(child);
      }
    }
  };
  preorder(king);
  return ans;
}