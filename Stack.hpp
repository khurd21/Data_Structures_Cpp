// 
// Stack.hpp
// CustomLibraries
//
// Created by Kyle Hurd on 10/21/2020
//

#ifndef Stack_hpp
#define Stack_hpp

#include <iostream>

template<class T>
class Stack {

private:
    struct Node {
        T data;
        Node *next;
    };
    Node *top;

    int numItems;
    int BufferSize;

public:
    
    // Constructors
    Stack(int = 0x0A);

    // Deconstructors
    ~Stack();

    // Functions
    void push(T);
    void pop();
    T    peek();
    bool isEmpty();
    bool isFull();
    int  getSize();
};

// Initializer
template<class T>
Stack<T>::Stack(int n) {
    
    numItems   = 0x00;
    BufferSize = n;

    top = nullptr;
}

// Destructor
template<class T>
Stack<T>::~Stack() {
    
    // Variable Declarations
    T temp;
    
    // Start of Code
    while (!isEmpty()) {
        pop(temp);
    }
    numItems = 0x00;
}

// **Functions** //
// isEmpty()
template<class T>
bool Stack<T>::isEmpty() {
    return !top;
}

// isFull()
template<class T>
bool Stack<T>::isFull() {
    return (BufferSize <= numItems);
}

// size()
template<class T>
int Stack<T>::getSize() {
    return numItems;
}

// push()
template<class T>
void Stack<T>::push(T item) {
    
    // Variable Declarations
    Node *newNode = nullptr;
    newNode = new Node;
    newNode->data = item;
    
    // Start of Code
    if (isEmpty()) {
        top = newNode;
        newNode->next = nullptr;
    }
    else {
        newNode->next = top;
        top = newNode;
    }
}

// pop()
template<class T>
void Stack<T>::pop() {
    
    // Start of Code
    if (!isEmpty()) {
        Node *temp = nullptr;
        temp = top->next;
        delete top;
        top = temp;
    }
    else {
        std::cout << "Stack is empty." << std::endl;
    }
}

// peek()
template<class T>
T Stack<T>::peek() {
    
    if (isEmpty()) {
        std::cout << "Stack is empty." << std::endl;
    }
    return top->data;
}
#endif /* Stack.hpp */
