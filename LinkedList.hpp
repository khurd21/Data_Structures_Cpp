//
//  LinkedList.hpp
//
//
//  Created by Kyle Hurd on 11/15/20.
//
//  Description
//
//  This file is still in production, but main functionality
//  to insert a node at the front or rear of the linked list
//  is currently working. For inserting, my plan is to create
//  more insert variants in which one can insert after or before
//  other data.
//
//  TODO:
//  1. Destructor needs to delete dynamically allocated memory.
//  2. Insert variants
//  3. Delete variants
//  4. Sorting?
//

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        struct Node *next;
        struct Node *prev;
    };
    Node *front;
    Node *rear;
    
public:
    // Constructor
    LinkedList();
    
    // Destructor
    ~LinkedList();
    
    // Functions
    bool isEmpty();
    void insertFront(T);
    void insertRear(T);
    void insertAfterThis(T, T);
};

// Function Definitions
// **Constructor** //
// LinkedList()
template <class T>
void LinkedList<T>::LinkedList() {
    front = nullptr;
    rear = nullptr;
}

// **Destructor** //
// ~LinkedList()
template <class T>
void LinkedList<T>::~LinkedList() {
    
    // NEED TO DELETE DYNAMIC MEMORY
}

// **Public** //
// isEmpty()
template <class T>
void LinkedList<T>::isEmpty() {
    return (front == nullptr);
}

// **Public** //
// insertFront()
template <class T>
void LinkedList<T>::insertFront(T newItem) {
    Node *newNode;
    newNode = new Node;
    newNode->data = newItem;
    
    if (isEmpty()) {
        front = rear = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    }
    else {
        newNode->next = front;
        newNode->prev = nullptr;
        front->prev = newItem;
        front = newItem;
    }
}

// **Public** //
// insertRear()
template <class T>
void LinkedList<T>::insertRear(T newItem) {
    Node *newNode;
    newNode = new Node;
    newNode->data = newItem;
    
    if (isEmpty()) {
        front = rear = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    }
    else {
        newNode->prev = rear;
        rear->next = newNode;
        newNode->next = nullptr;
        rear = newNode;
    }
}

// **Public** //
// insertAfterThis()
template <class T>
void LinkedList<T>::insertAfterThis(T search, T newItem) {
    Node *newNode;
    newNode = new Node;
    newNode->data = newItem;
    
    std::cout << "This function is not complete" << std::endl;
    delete newNode;
}

#endif /* LinkedList_h */
