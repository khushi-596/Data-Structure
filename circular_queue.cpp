//Circular queue
#include <iostream>
using namespace std;

class CircularQueue {
private:
    int front, rear, size;
    int *queue;

public:
    CircularQueue(int s) {
        front = rear = -1;
        size = s;
        queue = new int[size];
    }

    ~CircularQueue() {
        delete[] queue;
    }

    bool isFull() {
        return (front == 0 && rear == size - 1) || (rear == (front - 1 + size) % size);
    }

    bool isEmpty() {
        return front == -1;
    }

    bool enqueue(int value) {
        if (isFull()) return false;

        if (front == -1)  
            front = rear = 0;
        else if (rear == size - 1 && front != 0)
            rear = 0; 
        else
            rear++;

        queue[rear] = value;
        return true;
    }

    bool dequeue(int &removedValue) {
        if (isEmpty()) return false;

        removedValue = queue[front];

        if (front == rear)  
            front = rear = -1;
        else if (front == size - 1)
            front = 0;  
        else
            front++;

        return true;
    }

    bool peek(int &frontValue) {
        if (isEmpty()) return false;
        frontValue = queue[front];
        return true;
    }

    void getElements() {
        if (isEmpty()) {
            cout << "Queue is Empty!" << endl;
            return;
        }

        if (rear >= front) {
            for (int i = front; i <= rear; i++)
                cout << queue[i] << " ";
        } else {
            for (int i = front; i < size; i++)
                cout << queue[i] << " ";
            for (int i = 0; i <= rear; i++)
                cout << queue[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    CircularQueue q(5);
    int val;

    if (q.enqueue(10)) cout << "Inserted 10\n";
    if (q.enqueue(20)) cout << "Inserted 20\n";
    if (q.enqueue(30)) cout << "Inserted 30\n";
    if (q.enqueue(40)) cout << "Inserted 40\n";

    cout << "Queue elements: ";
    q.getElements();

    if (q.dequeue(val)) cout << "Deleted " << val << endl;

    cout << "Queue elements: ";
    q.getElements();

    q.enqueue(50);
    q.enqueue(60);  

    cout << "Queue elements: ";
    q.getElements();

    if (q.peek(val)) cout << "Front element: " << val << endl;

    return 0;
}

