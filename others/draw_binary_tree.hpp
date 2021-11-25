#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

int get_digits(int key);

class Node {
public:
    int key{};
    Node *parent = nullptr;
    std::vector<Node *> children;

    Node() = default;

    explicit Node(int _key) : key(_key) {}
};

void draw_binary_tree(Node *root, int size) {
    int height = 0;
    int total_height = int(log(size) / log(2));
    std::queue<Node *> queue;
    queue.push(root);
    while (!queue.empty()) {
        if (height == 2) {
            int tmp = 0;
        }
        int start_blank = int(pow(2, total_height - height + 1)) - 2;
        int interval_blank = int(pow(2, total_height + 2 - height)) - 1;
        for (int i = 0; i < start_blank; ++i) {
            std::cout << ' ';
        }
        int nullptr_count = 0;
        for (int i = 0; i < pow(2, height); ++i) {
            Node *node = queue.front();
            if (node == nullptr) {
                queue.push(nullptr);
                queue.push(nullptr);
                nullptr_count += 2;
                std::cout << 'x';
                for (int j = 0; j < interval_blank; ++j) {
                    std::cout << ' ';
                }
                queue.pop();
                continue;
            }
            for (Node *child: node->children) {
                queue.push(child);
            }
            for (int j = 0; j < 2 - node->children.size(); ++j) {
                queue.push(nullptr);
                nullptr_count++;
            }
            std::cout << node->key;
            int digits = get_digits(node->key);
            for (int j = 0; j < interval_blank - digits + 1; ++j) {
                std::cout << ' ';
            }
            queue.pop();
        }
        std::cout << std::endl;
        if (nullptr_count == int(pow(2, height + 1))) {
            break;
        }
        height++;
    }
}

int get_digits(int key) {
    int count = 1;
    while (key /= 10) {
        count++;
    }
    return count;
}