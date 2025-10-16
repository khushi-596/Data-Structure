//Evaluating infix expression without converting to postfix
#include <iostream>
#include <string>

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
    
    int peek() {
        return arr[top];
    }
    
    bool empty() {
        return top == -1;
    }   
};

int precedence(char op) {
    if(op == '+' || op == '-') 
    		return 1;
    if(op == '*' || op == '/') 
    		return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    if(op == '/') return a / b;
    return 0;
}

int evaluate(string exp) {
    IntStack value;
    CharStack opr;
    int i = 0;
    

    while(i < exp.length()) {
        if(exp[i] == ' ') {
            i++;
            continue;
        }

        if(isdigit(exp[i])) {
            int num = 0;
            while(i < exp.length() && isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            value.push(num);
        }

        else {
            while(!opr.empty() && precedence(opr.peek()) >= precedence(exp[i])) {
                int b = value.peek(); 
                value.pop();
                int a = value.peek(); 
                value.pop();
                char op = opr.peek(); 
                opr.pop();
                value.push(applyOp(a, b, op));
            }
            opr.push(exp[i]);
            i++;
        }
    }

    while(!opr.empty()) {
        int b = value.peek(); 
        value.pop();
        int a = value.peek(); 
        value.pop();
        char op = opr.peek(); 
        opr.pop();
        value.push(applyOp(a, b, op));
    }
    return value.peek();
}

int main(int argc, char* argv[]) {

    string expression = argv[1];
    int result = evaluate(expression);
    cout << "Result: " << result << endl;
    return 0;
}
