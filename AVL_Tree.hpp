// Name: Kyle Hurd
// Date: 01/06/2021
// File: AVLTree.hpp
//
// Description: Design implementation borrowed from Chapter 4 of Mark Allen Weiss
//              Data Structures and Algorithm Analysis. In the book, the AVL Tree
//              is written in the form of a struct. In this implementation, I created
//              a class version in which the node, root, and functions that access
//              the root directly are private. The public functions use the private
//              functions to directly balance the tree and insert/delete nodes.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

// Libraries
#include <iostream>
#include <utility>

// Determines the threshold for how imbalanced
// the tree may be.
static const int ALLOWED_IMBALANCE = 1;


// AVLTree Class
template <class T>
class AVLTree {
private:

    // Private Variables

    struct avl_node {
        T data;
        avl_node* left;
        avl_node* right;
        int height;

        // Constructors for Struct
        avl_node(const T& d, avl_node* lt, avl_node* rt, int h=0)
            : data{d}, left{lt}, right{rt}, height{h} {}

        avl_node(T&& d, avl_node* lt, avl_node* rt, int h=0)
            : data{std::move(d)}, left{lt}, right{rt}, height{h} {}
    };
    avl_node* _root;


    // Private Functions

    /* *
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: Returns height of node passed in 
     *              to function.
     */
    int height(avl_node* n) const {
        return (n == nullptr) ? -1 : n->height;
    }

    /*
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: Balances the structure of tree when the difference
     *              exceeds ALLOWED_IMBALANCE. Height is updated after
     *              every function call regardless of whether any changes
     *              have been performed.
     */
    void balance(avl_node*& n) {
        if (n == nullptr) {
            return;
        }
        if (height(n->left) - height(n->right) > ALLOWED_IMBALANCE) {
            if (height(n->left->left) >= height(n->left->right)) {
                rotate_left_child(n);
            }
            else {
                double_left_child(n);
            }
        }
        else {
            if (height(n->right) - height(n->left) > ALLOWED_IMBALANCE) {
                if (height(n->right->right) >= height(n->right->left)) {
                    rotate_right_child(n);
                }
                else {
                    double_right_child(n);
                }
            }
        }
        n->height = max(height(n->left), height(n->right)) + 1;
    }

    // Rotations


    /*
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: A single rotation of the left child.
     */
    void rotate_left_child(avl_node*& n) {
        avl_node* t = n->left;
        n->left = t->right;
        t->right = n;
        n->height = max(height(n->left), height(n->right)) + 1;
        t->height = max(height(t->left), n->height) + 1;
        n = t;
    }

    /*
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: A single rotation of the right child
     */
    void rotate_right_child(avl_node*& n) {
        avl_node* t = n->right;
        n->right = t->left;
        t->left = n;
        n->height = max(height(n->right), height(n->left)) + 1;
        t->height = max(height(n->right), n->height) + 1;
        n = t;
    }

    /*
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: A double rotation of the left child
     */
    void double_left_child(avl_node*& n) {
        rotate_right_child(n->left);
        rotate_left_child(n);
    }

    /*
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: A double rotation of the left child
     */
    void double_right_child(avl_node*& n) {
        rotate_left_child(n->right);
        rotate_right_child(n);
    }

    // Private Insert and Remove

    /*
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: Inserts element d into the AVL Tree. Notice
     *              how the else-if conditions do not check whether
     *              the d equals the node data exactly. This is purposeful.
     *              If the node data already exists, a new node will 
     *              not be generated for the d value to be stored.
     */
    void insert(const T& d, avl_node*& n) {
        if (n == nullptr) {
            n = new avl_node{d,nullptr,nullptr};
        }
        else if (d < n->data) {
            insert(d, n->left);
        }
        else if (n->data < d) {
            insert(d, n->right);
        }
        balance(n);
    }

    /* *
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: Removes element d from the AVL Tree. 
     */
    void remove(const T& d, avl_node*& n) {
        if (n == nullptr) {
            return;
        }

        if (d < n->data) {
            n = remove(d,n->right);
        }
        else if (n->data < d) {
            n = remove(d,n->left);
        }
        else if (n->left != nullptr && n->right != nullptr) {
            n->data = find_min(n->right)->data;
            remove(n->data, n->right);
        }
        else {
            avl_node* old_node = n;
            n = (n->left != nullptr) ? n->left : n->right;
            delete old_node;
        }

        balance(n);
    }

    /* *
     * Name: Kyle Hurd
     * Date: 02/12/2021     
     * Description: Traverses through the AVL Tree until the data
     *              has either been found or no other elements are to be
     *              traversed. In this case it returns false.
     */
    bool contains(const T& d, avl_node* node) const {
        while (node != nullptr) {
            if (node->data == d) {
                return true;
            }
            else if (node->data < d) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }
        return false;
    }


    /* *
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: Determines if the AVL Tree is within the ALLOWED_IMBALANCE
     *              threshold by taking the height from the right and left nodes
     *              and comparing their difference with the imbalance threshold.
     */
    bool validate(avl_node* node) const {
        if (node == nullptr) {
            return true;
        }
        int lt = 0;
        int rt = 0;
        lt = height(node->left);
        rt = height(node->right);
        return ((lt - rt <= ALLOWED_IMBALANCE
                    && lt - rt >= (-1 * ALLOWED_IMBALANCE))
                        && (validate(node->right)
                            && validate(node->left)))
            ? true : false;
    }


    /* *
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: Traverses the left hand side of the AVL Tree until
     *              it has reached the very bottom of the left tree. This
     *              value is then returned.
     */
    avl_node* find_min(avl_node* n) const {
        if (n == nullptr) {
            return nullptr;
        }
        if (n->left == nullptr) {
            return n;
        }
        return find_min(n->left);
    }

    /* *
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: Determines if the left or right side is larger
     *              and returns the largest value.
     */
    int max(const int& lhs, const int& rhs) const {
            return (lhs >= rhs) ? lhs : rhs;
    }

    // Destroying

    /* *
     * Name: Kyle Hurd
     * Date: 02/12/2021
     * Description: Destroys all elements below and including given node.
     */
    void destroy_subtree(avl_node*& node) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                destroy_subtree(node->left);
            }
            if (node->right != nullptr) {
                destroy_subtree(node->right);
            }
            delete node;
            node = nullptr;
        }
    }

    // Public Accessible Functions
public:

    AVLTree() {_root = nullptr;}

    ~AVLTree() { destroy_subtree(_root);}

    void insert(const T& d) { insert(d, _root);}

    void remove(const T& d) { remove(d, _root);}

    bool contains(const T& d) const { return contains(d, _root);}

    int height() const { return height(_root);}

    bool validate() const { return validate(_root);}

};

#endif /* endif AVL_Tree_hpp */
