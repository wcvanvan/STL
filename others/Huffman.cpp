#include <vector>
#include <queue>
#include <iostream>
#include <string>

class Node {
public:
    char letter;
    int frequency;
    std::vector<Node*> children;
    std::string code;
    explicit Node(int _frequency = 0, char _letter = '!') : frequency(_frequency), letter(_letter) {}
};

void merge(Node *array, int l, int mid, int r, Node *supportArray) {
    int AFlag = l, BFlag = mid + 1;
    for (int i = l; i <= r; i++) {
        if (AFlag > mid) {
            supportArray[i] = array[BFlag];
            BFlag++;
            continue;
        }
        if (BFlag > r) {
            supportArray[i] = array[AFlag];
            AFlag++;
            continue;
        }
        if (array[AFlag].frequency <= array[BFlag].frequency) {
            supportArray[i] = array[AFlag];
            AFlag++;
        } else {
            supportArray[i] = array[BFlag];
            BFlag++;
        }
    }
    for (int i = l; i < r + 1; i++) {
        array[i] = supportArray[i];
    }
}

void merge_sort(Node *array, int l, int r, Node *supportArray) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(array, l, mid, supportArray);
    merge_sort(array, mid + 1, r, supportArray);
    merge(array, l, mid, r, supportArray);
}

class Huffman {
public:
    Node *root = nullptr;
    Huffman(Node *array, int length) { build(array, length); }
    void build(Node *array, int length);
    void traversal_level() const;
    void dfs(Node *sub_root) const;
};

void Huffman::build(Node *array, int length) {
    Node *support_array = new Node[length];
    merge_sort(array, 0, length-1, support_array);
    delete[] support_array;
    std::queue<Node*> queue;
    int array_flag = 0;
    while(array_flag != length || !queue.empty()) {
        if ((length-array_flag + queue.size()) == 1) {
            if (queue.size() == 1) {
                root = queue.front();
            } else {
                root = &array[array_flag];
            }
            break;
        }
        Node *node_a;
        Node *node_b;
        if (queue.empty()) {
            node_a = &array[array_flag];
            node_b = &array[array_flag+1];
            array_flag += 2;
        } else {
            if (array_flag == length) {
                node_a = queue.front();
                queue.pop();
                node_b = queue.front();
                queue.pop();
            }
            else if (queue.size() == 1) {
                if (queue.front()->frequency < array[array_flag+1].frequency) {
                    node_a = &array[array_flag];
                    node_b = queue.front();
                    array_flag += 1;
                    queue.pop();
                } else {
                    node_a = &array[array_flag];
                    node_b = &array[array_flag+1];
                    array_flag += 2;
                }
            } else {
                if (array[array_flag].frequency < queue.front()->frequency) {
                    if (queue.front()->frequency < array[array_flag+1].frequency) {
                        node_a = &array[array_flag];
                        node_b = queue.front();
                        array_flag += 1;
                        queue.pop();
                    } else {
                        node_a = &array[array_flag];
                        node_b = &array[array_flag+1];
                        array_flag += 2;
                    }
                } else {
                    node_a = queue.front();
                    queue.pop();
                    if (array[array_flag].frequency < queue.front()->frequency) {
                        node_b = &array[array_flag];
                        array_flag++;
                    } else {
                        node_b = queue.front();
                        queue.pop();
                    }
                }
            }
        }
        Node *new_node = new Node(node_a->frequency + node_b->frequency);
        new_node->children.push_back(node_a);
        new_node->children.push_back(node_b);
        queue.push(new_node);
    }
}

void Huffman::traversal_level() const {
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();
        std::cout << temp->frequency << " ";
        for (auto &i: temp->children) {
            q.push(i);
        }
    }
    std::cout << std::endl;
}

void Huffman::dfs(Node *sub_root) const {
    for (int i = 0; i < sub_root->children.size(); ++i) {
        Node *child = sub_root->children[i];
        child->code = sub_root->code + char(i + '0');
        dfs(child);
    }
}

int main() {
    // illustration
    Node *array = new Node[10];

    for (int i = 0; i < 10; ++i) {
        array[i].frequency = i + 2;
        array[i].letter = char('a' + i);
    }
    array[5].frequency = 3;
    array[6].frequency = 1;
    array[8].frequency = 10;

    Huffman huffman(array, 10);
    huffman.traversal_level();
    huffman.dfs(huffman.root);
    for (int i = 0; i < 10; ++i) {
        std::cout << array[i].letter << " " << array[i].code << "\n";
    }
    delete[] array;
}




