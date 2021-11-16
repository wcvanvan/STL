#include <queue>
#include <vector>
#include <iostream>
using std::queue;
using std::vector;

class TreeNode {
 public:
  int key;
  bool isVisited = false;
  vector<TreeNode *> children;
};

class Tree {
 public:
  TreeNode *root;
  void traversal_level();
  void traversal_preorder(TreeNode *_root);
  void traversal_inorder();
  void traversal_postorder();
};

void Tree::traversal_level() {
  queue<TreeNode *> q;
  q.push(root);
  root->isVisited = true;
  while (!q.empty()) {
    TreeNode *temp = q.front();
    q.pop();
    for (int i = 0; i < temp->children.size(); i++) {
      if (!temp->children[i]->isVisited) {
        temp->children[i]->isVisited = true;
        q.push(temp->children[i]);
      }
    }
  }
}