#ifndef SIZEAVL_MYSIZEAVL_H
#define SIZEAVL_MYSIZEAVL_H

#include<bits/stdc++.h>
using namespace std;

namespace sizeavl {
    template <class T>
    class Node {
    public:
        Node<T> *left;
        Node<T> *right;
        int height;
        int size;
        T data;
    };

    // A utility function to get maximum
    // of two integers
    int max(int a, int b);

    // A utility function to get height
    // of the tree
    template <class T>
    int height(Node<T> *N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    template <class T>
    int size(Node<T> *N) {
        if (N == nullptr)
            return 0;
        return N->size;
    }

    template <class T>
    void update(Node<T> *N) {
        if (N != nullptr) {
            N->height = max(height(N->left),height(N->right))+1;
            N->size = size(N->left)+size(N->right)+1;
        }
    }

    // A utility function to get maximum
    // of two integers
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    /* Helper function that allocates a
    new node with the given key and
    nullptr left and right pointers. */
    template <class T>
    Node<T> *newNode(T data) {
        auto node = new Node<T>();
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1; // new node is initially
        node->size = 1;
        node->data = data;
        // added at leaf
        return (node);
    }

    // brings x to root
    template <class T>
    Node<T> *rightRotate(Node<T> *y) {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        update(y);
        update(x);
        // Return new root
        return x;
    }

    // brings y to root
    template <class T>
    Node<T> *leftRotate(Node<T> *x) {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        update(x);
        update(y);
        // Return new root
        return y;
    }

    // Get Balance factor of node N
    template <class T>
    int getBalance(Node<T> *N) {
        if (N == nullptr)
            return 0;
        return height(N->left)-height(N->right);
    }

    template <class T>
    Node<T> *insert(Node<T> *node, int s, T data) {
        /* 1. Perform the normal BST rotation */
        if (node == nullptr)
            return (newNode<T>(data));

        if (s <= size(node->left))
            node->left = insert(node->left, s, data);
        else if (s > size(node->left)+1)
            node->right = insert(node->right, s-size(node->left)-1, data);
        else // Equal keys not allowed
            return node;

        update(node);

        int balance = getBalance<T>(node);

        // Left Left Case
        if (balance > 1 && s <= size(node->left->left))
            return rightRotate<T>(node);

        // Right Right Case
        if (balance < -1 && s > size(node->right->left)+1)
            return leftRotate<T>(node);

        // Left Right Case
        if (balance > 1 && s > size(node->left->left)+1) {
            node->left = leftRotate<T>(node->left);
            return rightRotate<T>(node);
        }

        // Right Left Case
        if (balance < -1 && s <= size(node->right->left)) {
            node->right = rightRotate<T>(node->right);
            return leftRotate<T>(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    /* Given a non-empty binary search tree,
    return the node with minimum key value
    found in that tree.*/
    template <class T>
    Node<T> *minValueNode(Node<T> *node) {
        Node<T> *current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    // Recursive function to delete a node
    // with given key from subtree with
    // given root. It returns root of the
    // modified subtree.
    template <class T>
    Node<T> *deleteNode(Node<T> *root, int s) {

        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == nullptr)
            return root;

        if (s <= size(root->left))
            root->left = deleteNode<T>(root->left, s);

        else if (s > size(root->left)+1)
            root->right = deleteNode<T>(root->right, s-size(root->left)-1);

            // This is the node to be deleted
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node<T> *temp = root->left ?
                             root->left :
                             root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else // One child case
                    *root = *temp; // Copy the contents of
                // the non-empty child
                free(temp);
            } else {
                // node with two children
                auto temp = minValueNode<T>(root->right);

                // Copy data if there are
                root->data = temp->data;

                // Delete the inorder successor
                root->right = deleteNode<T>(root->right, 1);
            }
        }

        // If the tree had only one node
        // then return
        if (root == nullptr)
            return root;

        update(root);

        int balance = getBalance<T>(root);

        // Left Left Case
        if (balance > 1 &&
            getBalance<T>(root->left) >= 0)
            return rightRotate<T>(root);

        // Left Right Case
        if (balance > 1 &&
            getBalance<T>(root->left) < 0) {
            root->left = leftRotate<T>(root->left);
            return rightRotate<T>(root);
        }

        // Right Right Case
        if (balance < -1 &&
            getBalance<T>(root->right) <= 0)
            return leftRotate<T>(root);

        // Right Left Case
        if (balance < -1 &&
            getBalance<T>(root->right) > 0) {
            root->right = rightRotate<T>(root->right);
            return leftRotate<T>(root);
        }

        return root;
    }

    // A utility function to print preorder
    // traversal of the tree.
    template <class T>
    void preOrder(Node<T> *root) {
        if (root != nullptr) {
            cout << root->data << " size:" << root->size << " , ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    template <class T>
    void show(Node<T> *root) {
        preOrder<T>(root);
        cout << endl;
    }
}

#endif //SIZEAVL_MYSIZEAVL_H
