template <typename T>
class Deque {
 private:
  int max_size;
  T *array;
  int front, rear;

 public:
  int length;
  Deque(int max_size);
  ~Deque();
  bool enqueue_rear(T element);
  bool enqueue_front(T element);
  bool dequeue_front();
  bool dequeue_rear();
  T peek_front();
  T peek_rear();
};

template <typename T>
Deque<T>::Deque(int _max_size) {
  max_size = _max_size;
  array = new T[max_size];
  front = rear = 0;
  length = 0;
}

template <typename T>
Deque<T>::~Deque() {
  delete[] array;
}

template <typename T>
bool Deque<T>::enqueue_rear(T element) {
  if (length != max_size) {
    array[rear++] = element;
    rear %= max_size;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool Deque<T>::enqueue_front(T element) {
  if (length != max_size) {
    front--;
    if (front < 0) {
      front = max_size - 1;
    }
    array[front] = element;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool Deque<T>::dequeue_front() {
  if (length) {
    front++;
    front %= max_size;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool Deque<T>::dequeue_rear() {
  if (length) {
    rear--;
    if (rear < 0) {
      rear = max_size - 1;
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
    return array[max_size - 1];
  } else {
    return array[rear - 1];
  }
}