#include<iostream>
using namespace std;

struct node {
    int coeff, exp;
    node *next, *prev;
    node(int val, int power) {
        coeff = val;
        exp = power;
        next = NULL;
        prev = NULL;
    }
};

class Poly {
    node *head, *tail;
    
    public:
    Poly() {
        head = tail = NULL;
    }

    // Insert term in sorted order and combine like terms
    void insertPoly(int val, int power) {
        if(val == 0) return;

        node* p = head;
        while(p) {
            if(p->exp == power) {
                p->coeff += val;
                if(p->coeff == 0) { // remove node if coefficient becomes 0
                    if(p->prev) p->prev->next = p->next;
                    if(p->next) p->next->prev = p->prev;
                    if(p == head) head = p->next;
                    if(p == tail) tail = p->prev;
                    delete p;
                }
                return;
            }
            p = p->next;
        }

        node* nn = new node(val, power);

        // insert in decreasing order of exponent
        if(!head) {
            head = tail = nn;
            return;
        }

        p = head;
        while(p && p->exp > power) p = p->next;

        if(!p) {
            tail->next = nn;
            nn->prev = tail;
            tail = nn;
        }
        else if(p == head) {
            nn->next = head;
            head->prev = nn;
            head = nn;
        }
        else {
            node* prev = p->prev;
            prev->next = nn;
            nn->prev = prev;
            nn->next = p;
            p->prev = nn;
        }
    }

    void display() {
        node *p = head;
        if(!p) {
            cout<<"0\n";
            return;
        }
        bool first = true;
        while(p) {
            if(p->coeff != 0) {
                if(!first && p->coeff > 0)
                    cout<<" + ";
                else if(p->coeff < 0)
                    cout<<" - ";
                else if (!first)
                    cout<<" ";
                cout<<abs(p->coeff)<<"x^"<<p->exp;
                first = false;
            }
            p = p->next;
        }
        cout<<endl;
    }

    Poly operator + (Poly &p2) {
        Poly result;
        node *p = head;
        while(p) {
            result.insertPoly(p->coeff, p->exp);
            p = p->next;
        }
        p = p2.head;
        while(p) {
            result.insertPoly(p->coeff, p->exp);
            p = p->next;
        }
        return result;
    }

    Poly operator - (Poly &p2) {
        Poly result;
        node *p = head;
        while(p) {
            result.insertPoly(p->coeff, p->exp);
            p = p->next;
        }
        p = p2.head;
        while(p) {
            result.insertPoly(-p->coeff, p->exp); 
            p = p->next;
        }
        return result;
    }
};

int main() {
    Poly p1, p2;

    p1.insertPoly(3, 3);
    p1.insertPoly(4, 2);
    p1.insertPoly(1, 0);
    cout << "P1: ";
    p1.display();

    p2.insertPoly(5, 4);
    p2.insertPoly(-2, 3);
    p2.insertPoly(4, 1);
    cout << "P2: ";
    p2.display();
    
    Poly p3 = p1 + p2;
    cout << "P1 + P2: ";
    p3.display();

    Poly p4 = p1 - p2;
    cout << "P1 - P2: ";
    p4.display();

    return 0;
}

