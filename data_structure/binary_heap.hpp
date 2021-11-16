#include <iostream>
#include <vector>
#include <queue>

class TreeNode {
public:
    int key{};
    TreeNode *parent{};
    std::vector<TreeNode *> children;

    TreeNode() = default;

    explicit TreeNode(int _key) : key(_key) {}
};

class BinaryHeap {
public:
    TreeNode *root = nullptr;
    std::queue<TreeNode *> queue;

    BinaryHeap(int *array, int length);

    void insert(int key);

    void traversal_level();
};

BinaryHeap::BinaryHeap(int *array, int length) {
    for (int i = 0; i < length; ++i) {
        insert(array[i]);
    }
}

void BinaryHeap::insert(int key) {
    auto *new_node = new TreeNode(key);
    queue.push(new_node);
    if (root == nullptr) {
        root = new_node;
    } else {
        TreeNode *parent = queue.front();
        parent->children.push_back(new_node);
        if (parent->children.size() == 2) {
            queue.pop();
        }
        new_node->parent = parent;
        while (new_node != root && new_node->key < new_node->parent->key) {
            int tmp = new_node->key;
            new_node->key = new_node->parent->key;
            new_node->parent->key = tmp;
            new_node = new_node->parent;
        }
    }
}

void BinaryHeap::traversal_level() {
    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *temp = q.front();
        q.pop();
        std::cout << temp->key << std::endl;
        for (auto & i : temp->children) {
            q.push(i);
        }
    }
}