//power function
#include <iostream>
using namespace std;

struct Power {
    int n;
    int stat;
};

class Stack {
    Power arr[100];
    int top;
public:
    Stack() {
        top = -1;
    }
    void push(Power f) {
        arr[++top] = f;
    }
    void pop() {
        top--;
    }
    Power peek() {
        return arr[top];
    }
    void updateTop(Power f) {
        arr[top] = f;
    }
    bool empty() { 
        return top==-1;
    }
};

int power(int x, int n){
    Stack s;
    Power first = {n, 0};
    s.push(first);
    int result = 0;

    while(!s.empty()) {
        Power f = s.peek();
        if(f.n == 0) {
            result = 1;
            s.pop();
        }
        else if(f.stat == 0) {
            f.stat = 1; 
            s.updateTop(f); 
            Power next = {f.n-1, 0}; 
            s.push(next);
        }
        else {
            result=x*result; 
            s.pop();
        }
    }
    return result;
}

int main() {
    int x, n;
    cout<<"Enter base and exponent: ";
    cin>>x>>n;
    cout<<"Power: "<<power(x, n)<<endl;
    return 0;
}


