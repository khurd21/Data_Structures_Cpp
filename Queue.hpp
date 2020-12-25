//
//  Queue.hpp
//  CustomLibraries
//
//  Created by Kyle Hurd on 11/13/2020
//
//  Description
//
//  This Queue can hold a T type for data.
//  For any type that is created by the user, you do not need to
//  overload any boolean operations. You can get the front data
//  and rear data from the queue, which is separate from the dequeue
//  and enqueue operations.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>

template <class T>
class Queue {
private:
    struct QueueNode {
        T data;
        QueueNode *next;
    };

    QueueNode *front;
    QueueNode *rear;
    int numItems;
    int size;

public:
    // Constructor
    Queue(int=10);

    // Destructor
    ~Queue();

    // Functions
    void enqueue(T);
    void dequeue();
    bool isEmpty() const;
    bool isFull() const;
    void clear();

    int getSize();
    int getNumItems();
    T   getFront();
    T   getRear();
};

// Constructor
template <class T>
Queue<T>::Queue(int s) {
    size        = s;
    numItems    = 0;
    front       = nullptr;
    rear        = nullptr;
}

// Destructor
template <class T>
Queue<T>::~Queue() {
    clear();
}

// **Public** //
// isEmpty()
template <class T>
bool Queue<T>::isEmpty() const {
    return (numItems <= 0);
}

// **Public** //
// isFull()
template <class T>
bool Queue<T>::isFull() const {
    return (numItems >= size);
}

// **Public** //
// getSize()
template <class T>
int Queue<T>::getSize() {
    return size;
}

// **Public** //
// getNumItems()
template <class T>
int Queue<T>::getNumItems() {
    return numItems;
}

// **Public** //
// front()
template <class T>
T Queue<T>::getFront() {
    return front->data;
}

// **Public** //
// rear()
template <class T>
T Queue<T>::getRear() {
    return rear->data;
}

// **Public** //
// enqueue()
template <class T>
void Queue<T>::enqueue(T newData) {
    QueueNode *newNode = nullptr;
    newNode = new QueueNode;

    newNode->data = newData;
    newNode->next = nullptr;

    if (isEmpty()) {
        front = rear = newNode;
    }
    else if (isFull()) {
        std::cout << "Queue is full. Cannot add data." << std::endl;
        delete newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
    ++numItems;
}

// **Public** //
// dequeue()
template <class T>
void Queue<T>::dequeue() {
    QueueNode *temp = nullptr;

    if (isEmpty()) {
        std::cout << "Queue is empty. Nothing to grab" << std::endl;
    }
    else {
        temp = front;
        front = front->next;
        delete temp;
        --numItems;
    }
}

// **Public** //
// clear()
template <class T>
void Queue<T>::clear() {
    while (!isEmpty()) {
        dequeue();
    }
    std::cout << "Queue is cleared." << std::endl;
}

#endif /* Queue.hpp */
