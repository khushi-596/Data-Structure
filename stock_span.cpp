//stock span problem
#include<iostream>
using namespace std;

class Stack {
    int arr[100];
    int top;
public:
    Stack() {
        top = -1;
    }
    
    void push(int val) {
        if(top < 99)
            arr[++top] = val;
    }
    
    void pop() {
        if(top >= 0)
            top--;
    }
    
    int peek() {
        if(top >= 0)
            return arr[top];
        return -1;
    }
    
    bool empty() {
        return top == -1;
    }
};

void stockSpan(int prices[], int n, int span[]) {
    Stack s;
    for(int i = 0; i < n; i++) {
        while(!s.empty() && prices[s.peek()] <= prices[i]) {
            s.pop();
        }
        if(s.empty()) {
            span[i] = i + 1;
        }
        else {
            span[i] = i - s.peek();
        }
        s.push(i);
    }
}

int main() {
    int n;
    cout<<"Enter number of days: ";
    cin>>n;
    int prices[100], span[100];
    for(int i = 0; i < n; i++) {
        cout<<"Enter price for day "<<i+1<<": ";
        cin>>prices[i];
    }
    stockSpan(prices, n, span);
    cout<<"Stock span: ";
    for(int i = 0; i < n; i++) {
        cout<<span[i]<<" ";
    }
    cout<<endl;
    return 0;
}
        
