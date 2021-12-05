#include <iostream>
#include <queue>

class Node {
public:
    int key{0};
    Node *(children[2]){};
    Node *parent{nullptr};
    int children_size{0};

    Node() = default;

    explicit Node(int _key) : key(_key) {
        children[0] = children[1] = nullptr;
    }
};

class BinarySearchTree {
public:
    Node *root;

    [[nodiscard]] Node *query_predecessor(int target) const;

    [[nodiscard]] Node *query_successor(int target) const;

    [[nodiscard]] bool insert(int target);

    [[nodiscard]] bool remove(int target);

    void traversal_level() const;
};

Node *BinarySearchTree::query_predecessor(int target) const {
    Node *current_node = root;
    Node *answer = root;
    while (current_node != nullptr) {
        if (target < current_node->key) {
            current_node = current_node->children[0];
        } else if (target > current_node->key) {
            answer = current_node;
            current_node = current_node->children[1];
        } else {
            answer = current_node;
            return answer;
        }
    }
    return answer;
}

Node *BinarySearchTree::query_successor(int target) const {
    Node *current_node = root;
    Node *answer = root;
    while (current_node != nullptr) {
        if (target < current_node->key) {
            answer = current_node;
            current_node = current_node->children[0];
        } else if (target > current_node->key) {
            current_node = current_node->children[1];
        } else {
            answer = current_node;
            return answer;
        }
    }
    return answer;
}

bool BinarySearchTree::insert(int target) {
    Node *new_node = new Node(target);
    if (root == nullptr) {
        root = new_node;
        return true;
    }
    Node *current_node = root;
    while (current_node != nullptr) {
        if (target < current_node->key) {
            if (current_node->children[0] == nullptr) {
                current_node->children[0] = new_node;
                current_node->children_size++;
                new_node->parent = current_node;
                return true;
            } else {
                current_node = current_node->children[0];
            }
        } else if (target > current_node->key) {
            if (current_node->children[1] == nullptr) {
                current_node->children[1] = new_node;
                current_node->children_size++;
                new_node->parent = current_node;
                return true;
            } else {
                current_node = current_node->children[1];
            }
        }
        // exclude the possibility of two identical key
    }
    return false;
}

bool BinarySearchTree::remove(int target) {
    // find the node to be removed
    Node *removed_node = root;
    int child_index = 0;
    while (removed_node != nullptr) {
        if (target < removed_node->key) {
            removed_node = removed_node->children[0];
            child_index = 0;
        } else if (target > removed_node->key) {
            removed_node = removed_node->children[1];
            child_index = 1;
        } else {
            break;
        }
    }

    if (removed_node->children_size == 0) {
        removed_node->parent->children[child_index] = nullptr;
        delete removed_node;
    } else if (removed_node->children[1] != nullptr) {
        // find removed_node's successor
        Node *current_node = removed_node->children[1];
        Node *successor = current_node;
        int child_index_2 = 1;
        int successor_index = child_index_2;
        while (current_node != nullptr) {
            if (removed_node->key < current_node->key) {
                successor = current_node;
                successor_index = child_index_2;
                current_node = current_node->children[0];
                child_index_2 = 0;
            } else if (removed_node->key > successor->key) {
                current_node = current_node->children[1];
                child_index_2 = 1;
            } else {
                std::cerr << __func__ << ": identical key" << std::endl;
            }
        }

        removed_node->key = successor->key;
        if (successor->children_size == 0) {
            successor->parent->children[successor_index] = nullptr;
            delete successor;
        } else {
            // successor can only have right subtree but no left subtree
            successor->parent->children[successor_index] = successor->children[1];
            successor->children[1]->parent = successor->parent;
            delete successor;
        }
    } else {
        // removed_node only has left subtree
        if (removed_node != root) {
            removed_node->parent->children[child_index] = removed_node->children[0];
        } else {
            root = removed_node->children[0];
            root->parent = nullptr;
            delete removed_node;
        }
    }
    return false;
}

void BinarySearchTree::traversal_level() const {
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();
        for (auto &i: temp->children) {
            if (i == nullptr) {
                continue;
            }
            q.push(i);
        }
        std::cout << temp->key << " ";
    }
}


int main() {
    BinarySearchTree tree{};
    tree.insert(1);
    tree.insert(4);
    tree.insert(2);
    tree.insert(0);
    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    tree.remove(3);

    tree.traversal_level();
}



