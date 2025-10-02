//Tower of Hanoi
#include <iostream>
using namespace std;

struct TOHF {
    int n;
    char from, a, to; //a = temporary variable
    int state; 
};

class Stack {
    TOHF arr[100];
    int top;
public:
    Stack() { 
        top = -1; 
    }
    
    void push(TOHF f) { 
        arr[++top] = f; 
    }
    
    void pop() { 
        top--; 
    }
    
    TOHF peek() { 
        return arr[top]; 
    }
    
    void updateTop(TOHF f) { 
        arr[top] = f; 
    }
    
    bool empty() { 
        return top == -1; 
    }
};

void TOH(int n, char from, char a, char to) {
    Stack s;
    TOHF first = {n, from, a, to, 0};
    s.push(first);

    while (!s.empty()) {
        TOHF f = s.peek();

        if (f.n == 0) {
            s.pop();
        } 
        
        else if (f.state == 0) {
            f.state = 1;
            s.updateTop(f);
            TOHF next = {f.n - 1, f.from, f.to, f.a, 0};
            s.push(next);
        } 
        
        else if (f.state == 1) {
            cout << "Move disk " << f.n << " from " << f.from << " to " << f.to << endl;
            f.state = 2;
            s.updateTop(f);
            TOHF next = {f.n - 1, f.a, f.from, f.to, 0};
            s.push(next);
        } 
        
        else {
            s.pop();
        }
    }
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;
    TOH(n, 'A', 'B', 'C');
    return 0;
}

