//Circular doubly linked list
#include<iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node *prev;
    Node(int val) {
        data = val;
        next = prev = NULL;
    }
};

class CDLL {
    Node *head;
public:
    CDLL() {
        head = NULL;
    }
    
    //Insert at end
    void InsertEnd(int val) {
        Node *nn = new Node(val);
        if(!head) {
            head = nn;
            head->next = head;
            head->prev = head;
            return;
        }
        Node *tail = head->prev;
        tail->next = nn;
        nn->prev = tail;
        nn->next = head;
        head->prev = nn;
    }
    
    //Insert at beginning
    void InsertBeg(int val) {
        InsertEnd(val);
        head = head->prev;
    }
    
    //Delete node
    void DeleteNode(int val) {
        if(!head) {
            cout<<"List is empty\n";
            return;
        }
        Node *current = head;
        do {
            if(current->data == val) {
                if(current->next == current) {
                    delete current;
                    head = NULL;
                    return;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                
                if(current == head) {
                    head = current->next;
                }
                delete current;
                return;
            }
            current = current->next;
        }
        while(current != head);
        cout<<"Value not found\n";
    }
    
    //search node
    bool Search(int val) {
        if(!head)
            return false;
        Node *temp = head;
        do {
            if(temp->data == val)
                return true;
            temp = temp->next;
        }
        while(temp != head);
        return false;
    }
    
    //display from front
    void DisplayForward() {
        if(!head) {
            cout<<"List is empty\n";
            return;
        }
        Node *temp = head;
        do {
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        while(temp != head);
        cout<<endl;
    }
    
    //display from back
    void DisplayBackward() {
        if(!head) {
            cout<<"List is empty\n";
            return;
        }
        Node *temp = head->prev;
        do {
            cout<<temp->data<<" ";
            temp = temp->prev;
        }
        while(temp != head->prev);
        cout<<endl;
    }
};

int main() {
    CDLL c;
    int choice, val;
    
    do {
        cout<<"\n--Menu--\n";
        cout<<"1. Insert at beginning\n";
        cout<<"2. Insert at end\n";
        cout<<"3. Delete a node\n";
        cout<<"4. Search a node\n";
        cout<<"5. Display forward\n";
        cout<<"6. Display backward\n";
        cout<<"0. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;
        
        switch(choice) {
            case 1:
                cout<<"Enter value: ";
                cin>>val;
                c.InsertBeg(val);
                break;
             case 2:
                cout<<"Enter value: ";
                cin>>val;
                c.InsertEnd(val);
                break;
             case 3:
                cout<<"Enter value to delete: ";
                cin>>val;
                c.DeleteNode(val);
                break;
             case 4:
                cout<<"Enter value to search: ";
                cin>>val;
                if(c.Search(val))
                    cout<<"Found\n";
                else
                    cout<<"Not found\n";
                break;
             case 5:
                c.DisplayForward();
                break;
             case 6:
                c.DisplayBackward();
                break;
             case 0:
                cout<<"Exiting...\n";
                break;
             default:
                cout<<"Invalid choice\n";
        }
    }
    while(choice != 0);
    return 0;
}
              

