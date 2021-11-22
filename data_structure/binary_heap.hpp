#include <iostream>
#include <queue>
#include <vector>

class Node {
public:
    int key{};
    Node *parent = nullptr;
    std::vector<Node *> children;

    Node() = default;

    explicit Node(int _key) : key(_key) {}
};

class BinaryHeap {
public:
    Node *root = nullptr;
    std::queue<Node *> queue;
    std::vector<Node *> nodes;
    int size{0};

    BinaryHeap() = default;

    BinaryHeap(int *array, int length);

    void insert(int key);

    void insert_queue(int key);

    void remove();

    void traversal_level() const;
};

BinaryHeap::BinaryHeap(int *array, int length) {
    for (int i = 0; i < length; ++i) {
        insert_queue(array[i]);
    }
}

void BinaryHeap::insert_queue(int key) {
    auto *new_node = new Node(key);
    queue.push(new_node);
    if (root == nullptr) {
        root = new_node;
    } else {
        Node *parent = queue.front();
        parent->children.push_back(new_node);
        if (parent->children.size() == 2) {
            queue.pop();
        }
        new_node->parent = parent;
        int count = 0;
        while (new_node != root && new_node->key > new_node->parent->key) {
            int tmp = new_node->key;
            new_node->key = new_node->parent->key;
            new_node->parent->key = tmp;
            new_node = new_node->parent;
            count++;
        }
        std::cout << count << " ";
    }
}

void BinaryHeap::remove() {
    for (Node *child: root->children) {
        child->parent = nodes[size - 1];
        nodes[size - 1]->children.push_back(child);
    }
    nodes[size-1]->parent->children.pop_back();
    
    root->children.clear();
    root = nodes[size - 1];
    root->parent = nullptr;
    Node *node = root;
    bool has_small_child = false;
    do {
        has_small_child = false;
        Node *small_child = node;
        for (Node *child: node->children) {
            if (child->key < small_child->key) {
                small_child = child;
                has_small_child = true;
            }
        }
        if (has_small_child) {
            int tmp = small_child->key;
            small_child->key = node->key;
            node->key = tmp;
            node = small_child;
        }
    } while (has_small_child);
}

void BinaryHeap::traversal_level() const {
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();
        std::cout << temp->key << " ";
        for (auto &i: temp->children) {
            q.push(i);
        }
    }
    std::cout << std::endl;
}

void BinaryHeap::insert(int key) {
    Node *new_node = new Node(key);
    nodes.push_back(new_node);
    size++;
    if (root == nullptr) { root = new_node; }
    if (nodes.size() >= 2) {
        new_node->parent = nodes[size / 2 - 1];
        new_node->parent->children.push_back(new_node);
        while (new_node->parent != nullptr && new_node->key < new_node->parent->key) {
            int tmp = new_node->parent->key;
            new_node->parent->key = new_node->key;
            new_node->key = tmp;
            new_node = new_node->parent;
        }
    }
}
