#include <iostream>
using namespace std;

template <typename T>
class Node {
 public:
  T value;
  Node *next, *prev;
  Node() : value(), next(), prev() {}
  Node(T _value, Node *_next = nullptr, Node *_prev = nullptr)
      : value(_value), next(_next), prev(_prev) {}
};

template <typename T>
class Stack {
 private:
  Node<T> *head;
  Node<T> *top;

 public:
  int length;
  Stack();
  ~Stack();
  bool push(T element);
  bool pop();
  T peek();
  void clear();
};

template <typename T>
Stack<T>::Stack() {
  head = new Node<T>();
  top = head;
  length = 0;
}

template <typename T>
Stack<T>::~Stack() {
  delete head;
  clear();
}

template <typename T>
bool Stack<T>::push(T element) {
  top->next = new Node<T>(element, nullptr, top);
  length++;
  top = top->next;
  return true;
}

template <typename T>
bool Stack<T>::pop() {
  if (!length) {
    return false;
  } else {
    top = top->prev;
    delete top->next;
    length--;
    return true;
  }
}

template <typename T>
T Stack<T>::peek() {
  return top->value;
}

template <typename T>
void Stack<T>::clear() {
  while (top != head) {
    top = top->prev;
    delete top->next;
  }
}