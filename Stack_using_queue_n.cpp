//Implement Stack using  Queue such that the operation push() is of O(n) and pop() is of O(1)
//Implement Stack using  Queue such that the operation push() is of O(1) and pop() is of O(n)
#include<iostream>
using namespace std;

class Queue {
    int A[100], front, rear, size;
public:
    Queue() {
        front = 0;
        rear = -1;
        size = 0;
    }
    
    void enQueue(int x) {
        A[++rear] = x;
        size++;
    }
    
    int deQueue() {
        int val = A[front++];
        size--;
        return val;
    }
    
    bool empty() {
        return size == 0;
    }
    
    int getSize() {
        return size;
    }
    
    int peek() {
        return A[front];
    }
};

class QueueToStack {
    Queue q;
public:
    void push(int x) { 
        q.enQueue(x);
        int n = q.getSize();
        for(int i = 0; i < n - 1; i++) {
            q.enQueue(q.deQueue());
        }
    }
    
    int pop() {
        if(q.empty()) {
            return -1;
        }
        return q.deQueue();
    }
    
    bool empty() {
        return q.empty();
    }
};

int main() {
    QueueToStack s;
    s.push(11);
    s.push(22);
    s.push(33);
    s.push(44);
    s.push(55);
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    return 0;
}
    
