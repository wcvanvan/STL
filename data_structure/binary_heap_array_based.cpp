#include <iostream>
#include <queue>
#include <vector>

class Node {
public:
    int key{};

    Node() = default;

    explicit Node(int _key) : key(_key) {}
};

class BinaryHeap {
public:
    std::vector<Node *> nodes;
    int size{0};

    BinaryHeap() = default;

    BinaryHeap(int *array, int length);

    void insert(int key);

    void delete_top();

    void traversal_level() const;
};

BinaryHeap::BinaryHeap(int *array, int length) {
    for (int i = 0; i < length; ++i) {
        insert(array[i]);
    }
}

void BinaryHeap::insert(int key) {
    nodes.push_back(new Node(key));
    size++;
    int index = size - 1;
    while (index >= 1 && nodes[(index - 1) / 2]->key > nodes[index]->key) {
        int tmp = nodes[(index - 1) / 2]->key;
        nodes[(index - 1) / 2]->key = nodes[index]->key;
        nodes[index]->key = tmp;
        index = (index - 1) / 2;
    }
}

void BinaryHeap::delete_top() {
    nodes[0]->key = nodes[size - 1]->key;
    nodes.pop_back();
    size--;
    int index = 0;
    bool has_small_child = false;
    do {
        int index_child = index;
        Node *smaller_child = nodes[index];
        if (nodes[index * 2 + 1]->key < smaller_child->key) {
            has_small_child = true;
            smaller_child = nodes[index * 2 + 1];
            index_child = index * 2 + 1;
        }
        if (index * 2 + 2 < size && nodes[index * 2 + 2]->key < smaller_child->key) {
            has_small_child = true;
            smaller_child = nodes[index * 2 + 2];
            index_child = index * 2 + 2;
        }
        if (has_small_child) {
            int tmp = nodes[index]->key;
            nodes[index]->key = smaller_child->key;
            smaller_child->key = tmp;
            index = index_child;
        }
    } while (index < size/2);
}

void BinaryHeap::traversal_level() const {
    for (int i = 0; i < size; ++i) {
        std::cout << nodes[i]->key << " ";
    }
    std::cout << std::endl;
}

int main() {
    int * array = new int[10] {2,4,3,5,2,1,2,7,4,3};
    BinaryHeap heap(array, 10);
    heap.traversal_level();
}
