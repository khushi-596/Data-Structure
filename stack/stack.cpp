#include "stack.h"
#include <iostream>
using namespace std;

// Constructor
template <class T>
stack<T>::stack(int size) {
    S = size;
    A = new T[S];
    top = -1;
}

// Destructor
template <class T>
stack<T>::~stack() {
    delete[] A;
}

// Push
template <class T>
void stack<T>::push(T key) {
    if (isFull()) {
        cout << "Stack Overflow\n";
        return;
    }
    A[++top] = key;
}

// Pop
template <class T>
T stack<T>::pop() {
    if (isEmpty()) {
        cout << "Stack Underflow\n";
        return T(); // Return default-constructed T
    }
    return A[top--];
}

// Check Full
template <class T>
int stack<T>::isFull() {
    return top == S - 1;
}

// Check Empty
template <class T>
int stack<T>::isEmpty() {
    return top == -1;
}

// Peek
template <class T>
T stack<T>::peek() {
    if (isEmpty()) {
        cout << "Stack is Empty\n";
        return T();
    }
    return A[top];
}

// Explicit instantiation for stack<char>
template class stack<char>;

