//Merge two or more queues
#include<iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) {
        val = v;
        next = NULL;
    }
};

class Queue {
    Node* front;
    Node* rear;
public:
    Queue() {
        front = rear = NULL;
    }

    void enqueue(int val) {
        Node* node = new Node(val);
        if (!rear) {
            front = rear = node;
        } else {
            rear->next = node;
            rear = node;
        }
    }

    int dequeue() {
        if (!front) 
            return -1;
        int val = front->val;
        Node* temp = front;
        front = front->next;
        if (!front) 
            rear = NULL;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return front == NULL;
    }

    // Merge queue
    void merge(Queue &q) {
        if (!q.front) 
            return; 
        if (!front) {         
            front = q.front;
            rear = q.rear;
        } else {
            rear->next = q.front;
            rear = q.rear;
        }
        q.front = q.rear = NULL;
    }

    void printQueue() {
        Node* temp = front;
        while (temp) {
            cout << temp->val << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Queue q1, q2, q3;

    q1.enqueue(1); q1.enqueue(2);
    q2.enqueue(3); q2.enqueue(4);
    q3.enqueue(5); q3.enqueue(6);

    cout << "Queue 1 before merge: "; 
    q1.printQueue();
    cout << "Queue 2 before merge: "; 
    q2.printQueue();
    cout << "Queue 3 before merge: "; 
    q3.printQueue();

    q1.merge(q2);
    q1.merge(q3);

    cout << "\nMerged Queue: "; 
    q1.printQueue();

    cout << "\nDequeuing elements from merged queue: ";
    while (!q1.isEmpty()) {
        cout << q1.dequeue() << " ";
    }
    cout << endl;

    cout << "\nQueue 1 after merge: "; 
    q1.printQueue();
    cout << "Queue 2 after merge: "; 
    q2.printQueue();
    cout << "Queue 3 after merge: "; 
    q3.printQueue();

    return 0;
}


