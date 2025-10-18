#include <iostream>
using namespace std;

//doubly linked list
struct Node {
    int val;
    Node* prev;
    Node* next;
    Node(int v) {
        val = v;
        prev = NULL;
        next = NULL;
    }
};

class FrontMiddleBackQueue {
    Node* head;
    Node* tail;
    int count;

    Node* getMiddle() {
        Node* mid = head;
        for (int i = 0; i < count / 2; i++)
            mid = mid->next;
        return mid;
    }

public:
    FrontMiddleBackQueue() {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    void pushFront(int val) {
        Node* node = new Node(val);
        if (!head) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        count++;
    }

    void pushBack(int val) {
        Node* node = new Node(val);
        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        count++;
    }

    void pushMiddle(int val) {
        Node* node = new Node(val);
        if (!head) {
            head = tail = node;
        } else {
            Node* mid = getMiddle();
            if (count % 2 == 0) { // insert before mid
                node->next = mid;
                node->prev = mid->prev;
                if (mid->prev) 
                    mid->prev->next = node;
                mid->prev = node;
                if (mid == head) 
                    head = node;
            } else { // insert after mid
                node->prev = mid;
                node->next = mid->next;
                if (mid->next) 
                    mid->next->prev = node;
                mid->next = node;
                if (mid == tail) 
                    tail = node;
            }
        }
        count++;
    }

    int popFront() {
        if (!head) 
            return -1;
        int val = head->val;
        Node* temp = head;
        head = head->next;
        if (head) 
            head->prev = NULL;
        else tail = NULL;
        delete temp;
        count--;
        return val;
    }

    int popBack() {
        if (!tail) 
            return -1;
        int val = tail->val;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) 
            tail->next = NULL;
        else head = NULL;
        delete temp;
        count--;
        return val;
    }

    int popMiddle() {
        if (!head) return -1;
        Node* mid = getMiddle();
        int val = mid->val;
        if (mid->prev) 
            mid->prev->next = mid->next;
        else head = mid->next;
        if (mid->next) 
            mid->next->prev = mid->prev;
        else tail = mid->prev;
        delete mid;
        count--;
        return val;
    }
};

int main() {
    FrontMiddleBackQueue q;
    q.pushFront(1);
    q.pushBack(2);
    q.pushMiddle(3);
    q.pushMiddle(4);

    cout << q.popFront() << endl;   
    cout << q.popMiddle() << endl;  
    cout << q.popMiddle() << endl;  
    cout << q.popBack() << endl;    
    cout << q.popFront() << endl;   
}

