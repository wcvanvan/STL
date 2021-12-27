#include <iostream>
#include <stack>
#include <vector>

using std::vector, std::stack;

class Node {
public:
    int key{};
    bool isVisited = false;
    vector<Node *> children;
};

void topological_sort(Node *current_node, stack<Node *> &list) {
    std::cout << char(current_node->key) << std::endl;
    for (Node *child: current_node->children) {
        if (child->isVisited) {
            continue;
        } else {
            child->isVisited = true;
            topological_sort(child, list);
        }
    }
    list.push(current_node);
}

int main() {
    Node *nodes = new Node[9];
    for (int i = 0; i < 9; ++i) {
        nodes[i].key = 'a'+i;
    }
    nodes[0].children.push_back(&nodes[1]);
    nodes[0].children.push_back(&nodes[3]);
    nodes[1].children.push_back(&nodes[2]);
    nodes[2].children.push_back(&nodes[3]);
    nodes[2].children.push_back(&nodes[4]);
    nodes[3].children.push_back(&nodes[6]);
    nodes[6].children.push_back(&nodes[5]);
    nodes[5].children.push_back(&nodes[4]);
    nodes[6].children.push_back(&nodes[8]);
    nodes[8].children.push_back(&nodes[5]);
    stack<Node*> stack;
    topological_sort(nodes, stack);
    size_t length = stack.size();
    for (int i = 0; i < length; ++i) {
        std::cout << char(stack.top()->key) << " ";
        stack.pop();
    }
}