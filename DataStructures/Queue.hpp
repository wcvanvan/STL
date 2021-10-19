class Queue {
 private:
  int max_size;
  int real_size;
  char *array;
  int front, rear;

 public:
  Queue(int max_size);
  ~Queue();
  bool enqueue(char c);
  bool dequeue();
  char peek();
  bool isEmpty();
  bool isFull();
};

Queue::Queue(int max_size) {
  this->max_size = max_size;
  real_size = max_size + 1;
  array = new char[real_size];
  front = rear = 0;
}

Queue::~Queue() { delete[] array; }

bool Queue::enqueue(char c) {
  if (!isFull()) {
    array[rear++] = c;
    if (rear == real_size) {
      rear %= real_size;
    }
    return true;
  } else {
    return false;
  }
}

bool Queue::dequeue() {
  if (!isEmpty()) {
    front++;
    front %= real_size;
    return true;
  } else {
    return false;
  }
}

char Queue::peek() {
  if (!isEmpty()) {
    return array[front];
  } else {
    return 0;
  }
}

bool Queue::isEmpty() {
  if (front == rear) {
    return true;
  }
  return false;
}

bool Queue::isFull() {
  if (((rear + 1) % real_size) == front) {
    return true;
  }
  return false;
}
