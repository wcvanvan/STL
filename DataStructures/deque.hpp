template <typename T>
class Deque {
 private:
  int max_size;
  int real_size;
  T *array;
  int front, rear;

 public:
  Deque(int max_size);
  ~Deque();
  bool enqueue_rear(T element);
  bool enqueue_front(T element);
  bool dequeue_front();
  bool dequeue_rear();
  T peek_front();
  T peek_rear();
  bool isEmpty();
  bool isFull();
};

template <typename T>
Deque<T>::Deque(int _max_size) {
  max_size = _max_size;
  real_size = max_size + 1;
  array = new T[real_size];
  front = 0;
  rear = 0;
}

template <typename T>
Deque<T>::~Deque() {
  delete[] array;
}

template <typename T>
bool Deque<T>::enqueue_rear(T element) {
  if (!isFull()) {
    array[rear++] = element;
    rear %= real_size;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool Deque<T>::enqueue_front(T element) {
  if (!isFull()) {
    front--;
    if (front < 0) {
      front = real_size - 1;
    }
    array[front] = element;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool Deque<T>::dequeue_front() {
  if (!isEmpty()) {
    front++;
    front %= real_size;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool Deque<T>::dequeue_rear() {
  if (!isEmpty()) {
    rear--;
    if (rear < 0) {
      rear = real_size - 1;
    }
    return true;
  } else {
    return false;
  }
}

template <typename T>
T Deque<T>::peek_front() {
  return array[front];
}

template <typename T>
T Deque<T>::peek_rear() {
  if (!rear) {
    return array[real_size - 1];
  } else {
    return array[rear - 1];
  }
}

template <typename T>
bool Deque<T>::isEmpty() {
  if (front == rear) {
    return true;
  }
  return false;
}

template <typename T>
bool Deque<T>::isFull() {
  if (((rear + 1) % real_size) == front) {
    return true;
  }
  return false;
}
