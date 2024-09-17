#pragma once
#include "Node.h"

class AVLTree{
    Node* root;
public:
    //contructor
    AVLTree(): root(nullptr){}

    //deconstructor, copy-constructor, and assignment operator
    ~AVLTree() {
        // The Node struct recursively deletes its children
        delete root;
    }
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    //Insert an item to the AVL tree and maintain AVL tree properties
    void insert(const string &key);

    //Return the balance factor of a given node.
    int balanceFactor (Node* node) const;

    //Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.
    void printBalanceFactors();

private:
    //recurrsive function to help find the height of specific node
    int height_of (Node* node) const;

    //recurrsive function to help print all nodes in inOrder with balance factors
    void printBalanceFactors(Node* node) const;

    //recurrsive function to travers thorugh tree and corrects any unbalances in AVL tree
    void balanceTree(Node* node);

    //does a right rotation on the node that is given to maintain AVL tree properties
    void rotateRight(Node* node);

    //does a left rotation on the node that is given to maintain AVL tree properties
    void rotateLeft(Node* node);

    //sets a node as the parent's left or right child and updates the child's parent pointer
    void AVLTreeSetChild(Node* parent, const string &whichChild, Node* child);

    //replaces one of a node's existing child pointers with a new value
    void AVLTreeReplaceChild(Node* parent, Node* currentChild, Node* newChild);

    //traverses through the whole tree to correct any broken AVL properties
    void findUnbalancedNode(Node* tree);
};