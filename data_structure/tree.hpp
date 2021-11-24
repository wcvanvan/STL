#include <queue>
#include <vector>

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

    void traversal_level() const;

    void traversal_preorder(TreeNode *_root);

    void traversal_inorder();

    void traversal_postorder();
};

void Tree::traversal_level() const {
    queue<TreeNode *> q;
    q.push(root);
    root->isVisited = true;
    while (!q.empty()) {
        TreeNode *temp = q.front();
        q.pop();
        for (auto &i: temp->children) {
            if (!i->isVisited) {
                i->isVisited = true;
                q.push(i);
            }
        }
    }
}