class Stack {
 private:
  int max_size;
  char *array;
  int top;

 public:
  Stack(int max_size);
  ~Stack();
  bool push(char c);
  bool pop();
  char peek();
  bool isEmpty();
  void clear();
};

Stack::Stack(int max_size) {
  this->max_size = max_size;
  array = new char[max_size];
}

Stack::~Stack() { delete[] array; }

bool Stack::push(char c) {
  if (top == max_size - 1) {
    return false;
  } else {
    array[++top] = c;
    return true;
  }
}
bool Stack::pop() {
  if (top == -1) {
    return false;
  } else {
    top--;
    return true;
  }
}
char Stack::peek() {
  if (top == -1) {
    return 0;
  } else {
    return array[top];
  }
}
bool Stack::isEmpty() {
  if (top == -1) {
    return true;
  } else {
    return false;
  }
}
void Stack::clear() { top = -1; }