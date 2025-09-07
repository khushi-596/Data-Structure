//Infix to postfix evaluation
#include<iostream>
#include<string>

using namespace std;

class CharStack {
    char arr[50];
    int top;
public:
    CharStack() {
        top = -1;
    }
    void push(char c) {
        arr[++top] = c;
    }
    
    char pop() {
        return arr[top--];
    }
    
    char peek() {
        return arr[top];
    }
    
    bool empty() {
        return top == -1;
    }
};

class IntStack {
    int arr[50];
    int top;
public:
    IntStack() {
        top = -1;
    }
    
    void push(int x) {
        arr[++top] = x;
    }
    
    int pop() {
        return arr[top--];
    }
    
    bool empty() {
        return top == -1;
    }
};

class Expression {
    string infix;
public:
    Expression(string exp) {
        infix = exp;
    }
    
    int precedence(char op) {
        if(op == '+' || op == '-')
            return 1;
        if(op == '*' || op == '/')
            return 2;
        return 0;
    }
    
    string toPostfix() {
        CharStack s;
        string postfix = "";
        for(char ch : infix) {
            if(ch >= '0' && ch <= '9') {
                postfix += ch;
            }
            else if(ch == '(') {
                s.push(ch);
            }
            else if(ch == ')') {
                while(!s.empty() && s.peek() != '(') {
                    postfix += s.pop();
                }
                s.pop();
            }
            else {
                while(!s.empty() && precedence(s.peek()) >= precedence(ch)) {
                    postfix += s.pop();
                }
                s.push(ch);
            }
        }
        while(!s.empty()) {
            postfix += s.pop();
        }
        return postfix;
    }
    
    int evaluate(string postfix) {
        IntStack s;
        for(char ch : postfix) {
            if(ch >= '0' && ch <= '9') {
                s.push(ch - '0');
            }
            else {
                int b = s.pop();
                int a = s.pop();
                switch(ch) {
                    case '+':
                        s.push(a + b);
                        break;
                    case '-':
                        s.push(a - b);
                        break;
                    case '*':
                        s.push(a * b);
                        break;
                    case '/':
                        s.push(a / b);
                        break;
                }
            }
        }
        return s.pop();
    }
};

int main() {
    string ep;
    cout<<"Enter infix expression: ";
    cin>>ep;
    
    Expression e(ep);
    string postfix = e.toPostfix();
    cout<<"Postfix: "<<postfix<<endl;
    cout<<"Evaluated result: "<<e.evaluate(postfix)<<endl;
    return 0;
}
  
