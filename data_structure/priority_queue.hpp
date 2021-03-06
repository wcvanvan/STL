#include <vector>
#include <iostream>

using std::vector;

template<typename T>
class PriorityQueue {
public:
	std::vector<T*> priority_queue;

	PriorityQueue() = default;

	explicit PriorityQueue(vector<T>& v);

	void insert(T* new_element);

	T* top();

	void delete_top();

	void traversal_level() const;

};

/*
 * Constructing a priority queue from a random order
 * Using root-fix method
 */
template<typename T>
PriorityQueue<T>::PriorityQueue(vector<T>& v) {
	for (T* t : v) {
		priority_queue.push_back(t);
	}
	size_t start_pos = (priority_queue.size() - 1) / 2;
	for (size_t idx = start_pos; idx >= 0; --idx) {
		size_t pos = idx;
		while (pos < priority_queue.size() / 2) {
			size_t pos_to_swap = pos;
			if (*priority_queue[pos * 2 + 1] < *priority_queue[pos_to_swap]) {
				pos_to_swap = pos * 2 + 1;
			}
			if (pos * 2 + 2 < priority_queue.size() &&
				*priority_queue[pos * 2 + 2] < *priority_queue[pos_to_swap]) {
				pos_to_swap = pos * 2 + 2;
			}
			if (pos_to_swap != pos) {
				T* tmp = priority_queue[pos];
				priority_queue[pos] = priority_queue[pos_to_swap];
				priority_queue[pos_to_swap] = tmp;
				pos = pos_to_swap;
			}
			else {
				break;
			}
		}
	}
}

/*
 * insert a new element in the priority queue
 */
template<typename T>
void PriorityQueue<T>::insert(T* new_element) {
	priority_queue.push_back(new_element);
	size_t pos = priority_queue.size() - 1;
	while (pos > 0 && *priority_queue[pos] < *priority_queue[(pos - 1) / 2]) {
		T* tmp = priority_queue[(pos - 1) / 2];
		priority_queue[(pos - 1) / 2] = priority_queue[pos];
		priority_queue[pos] = tmp;
		pos = (pos - 1) / 2;
	}
}

/*
 * return the reference to the top of the priority queue
 */
template<typename T>
T* PriorityQueue<T>::top() {
	return priority_queue[0];
}

/*
 * Delete the top element in the priority queue and reorder the priority queue
 */
template<typename T>
void PriorityQueue<T>::delete_top() {
	priority_queue[0] = priority_queue[priority_queue.size() - 1];
	priority_queue.pop_back();
	size_t pos = 0;
	while (pos < priority_queue.size() / 2) {
		size_t pos_to_swap = pos;
		if (*priority_queue[pos * 2 + 1] < *priority_queue[pos_to_swap]) {
			pos_to_swap = pos * 2 + 1;
		}
		if (pos * 2 + 2 < priority_queue.size() &&
			*priority_queue[pos * 2 + 2] < *priority_queue[pos_to_swap]) {
			pos_to_swap = pos * 2 + 2;
		}
		if (pos_to_swap != pos) {
			T* tmp = priority_queue[pos];
			priority_queue[pos] = priority_queue[pos_to_swap];
			priority_queue[pos_to_swap] = tmp;
			pos = pos_to_swap;
		}
		else {
			break;
		}
	}
}

template<typename T>
void PriorityQueue<T>::traversal_level() const {
	for (auto* t : priority_queue) {
		std::cout << *t << " ";
	}
	std::cout << std::endl;
}
