template <typename T>
class Queue {
 private:
  int max_size;
  int real_size;
  T *array;
  int front, rear;

 public:
  int length;
  Queue(int max_size);
  ~Queue();
  bool enqueue(T element);
  bool dequeue();
  T front();
  bool isEmpty();
  bool isFull();
};

template <typename T>
Queue<T>::Queue(int _max_size) {
  max_size = _max_size;
  real_size = max_size + 1;
  array = new T[real_size];
  front = rear = 0;
}

template <typename T>
Queue<T>::~Queue() {
  delete[] array;
}

template <typename T>
bool Queue<T>::enqueue(T element) {
  if (!isFull()) {
    array[rear++] = element;
    rear %= real_size;
    length++;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool Queue<T>::dequeue() {
  if (!isEmpty()) {
    front++;
    front %= real_size;
    length-- return true;
  } else {
    return false;
  }
}

template <typename T>
T Queue<T>::front() {
  return array[front];
}

template <typename T>
bool Queue<T>::isEmpty() {
  if (!length) {
    return true;
  }
  return false;
}

template <typename T>
bool Queue<T>::isFull() {
  if (length == max_size) {
    return true;
  }
  return false;
}
