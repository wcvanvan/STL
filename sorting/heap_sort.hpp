#include <iostream>
#include <queue>

using namespace std;

void insert(int number, int *support_array, int &size, bool is_min_heap);

int delete_top(int *support_array, int &size, bool is_min_heap);


void heap_sort(int *array, int length, bool is_min_heap) {
    int *support_array = new int[length];
    int size = 0;
    for (int i = 0; i < length; ++i) {
        insert(array[i], support_array, size, is_min_heap);
    }
    for (int i = 0; i < length; ++i) {
        array[i] = delete_top(support_array, size, is_min_heap);
    }
}

void insert(int number, int *support_array, int &size, bool is_min_heap) {
    support_array[size++] = number;
    int index = size - 1;
    if (is_min_heap) {
        while (index >= 1 && support_array[(index - 1) / 2] > support_array[index]) {
            int tmp = support_array[(index - 1) / 2];
            support_array[(index - 1) / 2] = support_array[index];
            support_array[index] = tmp;
            index = (index - 1) / 2;
        }
    } else {
        while (index >= 1 && support_array[(index - 1) / 2] < support_array[index]) {
            int tmp = support_array[(index - 1) / 2];
            support_array[(index - 1) / 2] = support_array[index];
            support_array[index] = tmp;
            index = (index - 1) / 2;
        }
    }
}

int delete_top(int *support_array, int &size, bool is_min_heap) {
    int return_value = support_array[0];
    support_array[0] = support_array[--size];
    int index = 0;
    if (is_min_heap) {
        bool has_small_child = false;
        do {
            int index_child = index;
            int smaller_number = support_array[index];
            if (support_array[index * 2 + 1] < smaller_number) {
                has_small_child = true;
                smaller_number = support_array[index * 2 + 1];
                index_child = index * 2 + 1;
            }
            if (index * 2 + 2 < size && support_array[index * 2 + 2] < smaller_number) {
                has_small_child = true;
                index_child = index * 2 + 2;
            }
            if (has_small_child) {
                has_small_child = false;
                int tmp = support_array[index];
                support_array[index] = support_array[index_child];
                support_array[index_child] = tmp;
                index = index_child;
            } else {
                break;
            }
        } while (index < size / 2);
    } else {
        bool has_big_child = false;
        do {
            int index_child = index;
            int bigger_number = support_array[index];
            if (support_array[index * 2 + 1] > bigger_number) {
                has_big_child = true;
                bigger_number = support_array[index * 2 + 1];
                index_child = index * 2 + 1;
            }
            if (index * 2 + 2 < size && support_array[index * 2 + 2] > bigger_number) {
                has_big_child = true;
                index_child = index * 2 + 2;
            }
            if (has_big_child) {
                int tmp = support_array[index];
                support_array[index] = support_array[index_child];
                support_array[index_child] = tmp;
                index = index_child;
            } else {
                break;
            }
            has_big_child = false;
        } while (index < size / 2);
    }
    return return_value;
}

int main() {
    int length = 10;
    int *array = new int[length]{2, 5, 3, 6, 8, 9, 4, 2, 1, 4};
    heap_sort(array, length, true);
    for (int i = 0; i < length; ++i) {
        cout << array[i] << " ";
    }
}