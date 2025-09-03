#ifndef STACK_H
#define STACK_H

// Template class for Stack
template <class T>
class stack {
    int S;      // size of the stack
    int top;    // index of top element
    T* A;       // dynamic array for storing stack elements

public:
    stack(int size);   // constructor
    ~stack();          // destructor

    void push(T key);  // push an element
    T pop();           // pop an element
    int isFull();      // check if full
    int isEmpty();     // check if empty
    T peek();          // peek at top element
};

#endif // STACK_H

