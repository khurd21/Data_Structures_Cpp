//
//  BinarySearchTree.hpp
//  CustomLibraries
//
//  Created by Kyle Hurd on 10/27/2020
//
//  Description
//
//  This Binary Search Tree can hold a T type for data.
//  For any type that is created by the user, it will be necessary
//  to overload boolean operations (<, >, <=, ==). Only these
//  four operation need to be overloaded for this class to
//  work without standard types like an <int> or <char>
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "ttype.hpp"
#include <iostream>
#include <string>
#include <fstream>

template<class T>
class BinarySearchTree {
private:
    // Struct Declaration
    struct TreeNode {
        T data; // ttype
        TreeNode *right;
        TreeNode *left;
    };
    TreeNode *root;
    
    // Deletions
    void destroySubTree(TreeNode *);
    void deleteNode(T, TreeNode *&);
    void makeDeletion(TreeNode *&);
    
    // Inserts
    void insert(TreeNode *&, TreeNode *&); //if(TreeNode.data < otherNode.data) {}
    
    // Displays
    void displayInOrder(TreeNode *) const;
    void displayPreOrder(TreeNode *) const;
    void displayPostOrder(TreeNode *) const;

public:
    
    // Constructors
    BinarySearchTree() {
        root = nullptr;
    }
    
    // Destructors
    ~BinarySearchTree() {
        destroySubTree(root);
    }
    
    // Getters
    T getData(T);
    
    // Functions
    void insertNode(T);
    void remove(T);
    bool isNode(T);
    
    // Override Display Functions
    void displayInOrder() const {
        displayInOrder(root);
    }
    void displayPreOrder() const {
        displayPreOrder(root);
    }
    void displayPostOrder() const {
        displayPostOrder(root);
    }
};

// Function Definitions
// **Private** //
// destroySubTree()
template<class T>
void BinarySearchTree<T>::destroySubTree(TreeNode *nodePtr) {
    
    if (nodePtr) {
        if (nodePtr->left) {
            destroySubTree(nodePtr->left);
        }
        if (nodePtr->right) {
            destroySubTree(nodePtr->right);
        }
        delete nodePtr;
    }
}

// **Private** //
// deleteNode()
template<class T>
void BinarySearchTree<T>::deleteNode(T d, TreeNode *& nodePtr) {
    
    if (d < nodePtr->data) {
        deleteNode(d, nodePtr->left);
    }
    else if (d > nodePtr->data) {
        deleteNode(d, nodePtr->right);
    }
    else {
        makeDeletion(nodePtr);
    }
}

// **Private** //
// makeDeletion()
template<class T>
void BinarySearchTree<T>::makeDeletion(TreeNode *&nodePtr) {
    
    TreeNode *tempPtr = nullptr;
    
    if (nodePtr == nullptr) {
        std::cout << "Node is empty. Cannot delete." << std::endl;
    }
    else if (nodePtr->right == nullptr) {
        tempPtr = nodePtr;
        nodePtr = nodePtr->left;
        delete tempPtr;
    }
    else if (nodePtr->left == nullptr) {
        tempPtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempPtr;
    }
    else {
        tempPtr = nodePtr->right;
        while (tempPtr->left) {
            tempPtr = tempPtr->left;
        }
        
        tempPtr->left = nodePtr->left;
        tempPtr = nodePtr;
        nodePtr = nodePtr->right;
        
        delete tempPtr;
    }
}

// **Private** //
// insert()
template<class T>
void BinarySearchTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
    
    if (nodePtr == nullptr) {
        nodePtr = newNode;
    }
    else if (newNode->data <= nodePtr->data) {
        insert(nodePtr->left, newNode);
    }
    else {
        insert(nodePtr->right, newNode);
    }
}

// **Private** //
// displayInOrder()
template<class T>
void BinarySearchTree<T>::displayInOrder(TreeNode *nodePtr) const {
    
    if (nodePtr) {
        displayInOrder(nodePtr->left);
        std::cout << nodePtr->data << std::endl;
        displayInOrder(nodePtr->right);
    }
}

// **Private** //
// displayPreOrder
template<class T>
void BinarySearchTree<T>::displayPreOrder(TreeNode *nodePtr) const {
    
    if (nodePtr) {
        std::cout << nodePtr->data << std::endl;
        displayPreOrder(nodePtr->left);
        displayPreOrder(nodePtr->right);
    }
}

// **Private** //
// displayPostOrder()
template<class T>
void BinarySearchTree<T>::displayPostOrder(TreeNode *nodePtr) const {
    
    if (nodePtr) {
        displayPostOrder(nodePtr->left);
        displayPostOrder(nodePtr->right);
        std::cout << nodePtr->data << std::endl;
    }
}

// **Public** //
// getString()
template<class T>
T BinarySearchTree<T>::getData(T d) {
    
    TreeNode *tempNode = root;
    
    while (tempNode) {
        if (tempNode->data == d) return tempNode->data;
        else if (tempNode->data < d) tempNode = tempNode->right;
        else tempNode = tempNode->left;
    }
    return tempNode->data;
}

// **Public** //
// insertNode()
template<class T>
void BinarySearchTree<T>::insertNode(T d) {
    
    TreeNode *newNode = nullptr;
    newNode = new TreeNode;
    
    newNode->data = d;
    newNode->right = newNode->left = nullptr;
    
    insert(root, newNode);
}

// **Public** //
// remove()
template<class T>
void BinarySearchTree<T>::remove(T d) {
    
    deleteNode(d, root);
}

// **Public** //
// isNode()
template<class T>
bool BinarySearchTree<T>::isNode(T d) {
    
    TreeNode *tempNode = root;
    
    while (tempNode) {
        if (tempNode->data == d) return true;
        else if (tempNode->data < d) tempNode = tempNode->right;
        else tempNode = tempNode->left;
    }
    return false;
}

#endif /* BinarySearchTree.hpp */
