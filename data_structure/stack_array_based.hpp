template<typename T>
class Stack {
private:
    int max_size;
    T *array;
    int top;

public:
    int length;

    explicit Stack(int _max_size);

    ~Stack();

    bool push(T element);

    bool pop();

    T peek();

    void clear();
};

template<typename T>
Stack<T>::Stack(int _max_size) {
    top = -1;
    max_size = _max_size;
    array = new T[max_size];
    length = 0;
}

template<typename T>
Stack<T>::~Stack() {
    delete[] array;
}

template<typename T>
bool Stack<T>::push(T element) {
    if (top == max_size - 1) {
        return false;
    } else {
        array[++top] = element;
        length++;
        return true;
    }
}

template<typename T>
bool Stack<T>::pop() {
    if (top == -1) {
        return false;
    } else {
        top--;
        length--;
        return true;
    }
}

template<typename T>
T Stack<T>::peek() {
    return array[top];
}

template<typename T>
void Stack<T>::clear() {
    top = -1;
}