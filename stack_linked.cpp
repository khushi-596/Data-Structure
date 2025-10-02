//Stack of strings using linked list + friend function
#include<iostream>
using namespace std;

struct Node {
    string data;
    Node *next;
    Node(string val) {
        data = val;
        next = NULL;
    }
};

class Stack {
    Node *top;
public:
    Stack() {
        top = NULL;
    }
    
    void push(string val) {
        Node *temp = new Node(val);
        temp->next = top;
        top = temp;
    }
    
    void pop() {
        if(top) {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    void display() {
        Node *temp = top;
        while(temp) {
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
    
    friend void removeDuplicates(Stack &s);
};

void removeDuplicates(Stack &s) {
    if(!s.top) return;
    Node *curr = s.top;
    while(curr && curr->next) {
        if(curr->data == curr->next->data) {
            Node *dup = curr->next;
            curr->next = dup->next;
            delete dup;
        }
        else {
            curr = curr->next;
        }
    }
}

int main() {
    Stack s;
    s.push("Apple");
    s.push("cherry");
    s.push("cherry");
    s.push("Apple");
    s.push("Mango");
    cout<<"Actual stack: ";
    s.display();
    
    removeDuplicates(s);
    cout<<"After removing duplicates: ";
    s.display();
    return 0;
}
    
    
