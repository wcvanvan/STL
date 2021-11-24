template<typename T>
class Node {
public:
    T value;
    Node *next, *prev;

    Node() : value(), next(), prev() {}

    explicit Node(T _value, Node *_next = nullptr, Node *_prev = nullptr)
            : value(_value), next(_next), prev(_prev) {}
};

template<typename T>
class Deque {
    Node<T> *front, *rear;

public:
    int length;

    Deque() {
        front = rear = nullptr;
        length = 0;
    }

    ~Deque() { clear(); }

    bool enqueue_front(T _value) {
        auto *newNode = new Node<T>(_value);
        if (!length) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        length++;
        return true;
    }

    bool enqueue_rear(T _value) {
        Node<T> *newNode = new Node<T>(_value);
        if (!length) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        length++;
        return true;
    }

    bool dequeue_front() {
        if (!length) {
            return false;
        }
        if (length == 1) {
            delete front;
            front = rear = nullptr;
            length--;
            return true;
        }
        front = front->next;
        delete front->prev;
        front->prev = nullptr;
        length--;
        return true;
    }

    bool dequeue_rear() {
        if (!length) {
            return false;
        }
        if (length == 1) {
            delete rear;
            front = rear = nullptr;
            length--;
            return true;
        }
        rear = rear->prev;
        delete rear->next;
        rear->next = nullptr;
        length--;
        return true;
    }

    Node<T> *peek_front() { return front; }

    Node<T> *peek_rear() { return rear; }

    bool clear() {
        while (front != rear) {
            front = front->next;
            delete front->prev;
        }
        delete rear;

        front = rear = nullptr;
        return true;
    }
};