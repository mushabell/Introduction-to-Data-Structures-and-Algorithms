#include "AVLTree.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//Insert an item to the AVL tree and perform rotation if necessary.
void AVLTree::insert(const string &key){
    Node* newNode = new Node(key);
    Node* curr = root;
    //Edge case: The tree is empty
    if (curr == nullptr){
        root = newNode;
        return;
    }
    // Typical case, we find a hole where this key belongs
    while (true){
        //Edge Case: we find the key already in the tree
        if (key == curr->key){
            //I would write: throw runtime_error("duplicate keys are not allowed");
            //but, for zybooks I am going to exit the function
            return;
        } else if (key < curr -> key){
            //we would go left and if there is no child there, insert new node to left
            if (curr -> left == nullptr){
                newNode -> parent = curr;
                curr -> left = newNode;
                //after inerting a new node, check to see if the AVL properties are maintained
                findUnbalancedNode(root);
                return;
            } else {
                curr = curr -> left;
            }
        } else {
            //we would go right and if there is no child there, insert new node to right
            if (curr -> right == nullptr){
                newNode -> parent = curr;
                curr -> right = newNode;
                //after inerting a new node, check to see if the AVL properties are maintained
                findUnbalancedNode(root);
                return;
            } else {
                curr = curr -> right;
            }
        }
    }
}

//traverses through the whole tree to correct any broken AVL properties
void AVLTree::findUnbalancedNode(Node* tree){
    Node* curr = tree;
    //base case
    if (curr == nullptr){
        return;
    }
    findUnbalancedNode(curr->left);
    findUnbalancedNode(curr->right);
    //calls on function to check height balance property
    balanceTree(curr);
}

//corrects any unbalances in AVL tree from the given node
void AVLTree::balanceTree(Node* node){
    int currentBalance = balanceFactor(node);
    int leftBalance;
    int rightBalance;
    //gets the left and right subtree heights of the node
    //checks for nullptr to ensure nullptr is not passed to balaceFactor funtion
    if (node->left==nullptr){
        leftBalance = 0;
    } else {
        leftBalance = balanceFactor(node->left);
    }
    if (node->right == nullptr){
        rightBalance = 0;
    } else {
        rightBalance = balanceFactor(node->right);
    }
    //Check the different balance factors to see if they fit into any of the four cases for rotation
    if (currentBalance == 2  and leftBalance == 1){
        //case one: three nodes going left with no right children, rotate right
        rotateRight(node);
    } else if (currentBalance == -2 and rightBalance == -1){
        //case two: three nodes going right with no left children, rotate left
        rotateLeft(node);
    } else if (currentBalance == 2 and leftBalance == -1){
        //case three: node has only one left child and one right grandchild
        rotateLeft(node->left);
        rotateRight(node);
    } else if (currentBalance == -2 and rightBalance == 1){
        //case four: node has only one right child and one left grandchild
        rotateRight(node->right); 
        rotateLeft(node);
    }
}

//does a right rotation on the node that is given to maintain AVL tree properties
void AVLTree::rotateRight(Node* node){
    Node* leftRightChild = node->left->right;
    if (node->parent != nullptr){
        //calls on helper function to do the rotation with the parent
        AVLTreeReplaceChild(node->parent, node, node->left);
    } else { // node is root
        root = node->left;
        root->parent = nullptr;
    }
    //sets the proper children for the rotation
    AVLTreeSetChild(node->left, "right", node);
    AVLTreeSetChild(node, "left", leftRightChild);
}

//sets a node as the parent's left or right child and updates the child's parent pointer
void AVLTree::AVLTreeSetChild(Node* parent, const string &whichChild, Node* child) {
    //checks for proper inputs for the string
    if (whichChild != "left" and whichChild != "right"){
        return;
    }
    //assigns the correct child to the parent
    if (whichChild == "left"){
        parent->left = child;
    }else{
        parent->right = child;
    }
    //assigns the child a parent if not a leaf node
    if (child != nullptr){
        child->parent = parent;
    }
}

//replaces one of a node's existing child pointers with a new value
void AVLTree::AVLTreeReplaceChild(Node* parent, Node* currentChild, Node* newChild){
    //rotates the parent's children correctly based on the currentChild
    if (parent->left == currentChild){
        AVLTreeSetChild(parent, "left", newChild);
    }else if (parent->right == currentChild){
        AVLTreeSetChild(parent, "right", newChild);
    }
}

//does a left rotation on the node that is given to maintain AVL tree properties
void AVLTree::rotateLeft(Node* node){
    Node* rightLeftChild = node->right->left;
    if (node->parent != nullptr){
        //calls on helper function to do the rotation with the parent
        AVLTreeReplaceChild(node->parent, node, node->right);
    } else { // node is root
        root = node->right;
        root->parent = nullptr;
    }
    //sets the proper children for the rotation
    AVLTreeSetChild(node->right, "left", node);
    AVLTreeSetChild(node, "right", rightLeftChild);
}

//Returns the balance factor of a given node
int AVLTree::balanceFactor (Node* node) const{
    //calulates both subtree heights and substracts left from right for node balance height 
    int leftSubTree = height_of(node->left);
    int rightSubTree = height_of(node->right);
    return (leftSubTree-rightSubTree);
}

//Traverse and print the tree in inorder notation.
void AVLTree::printBalanceFactors(){
    //calls on recursive function
    printBalanceFactors(root);
    cout<<endl;
}

//recurrsive function to help print all nodes in inOrder with balance factors
void AVLTree::printBalanceFactors(Node* node) const{
    //prints in the order of left, root, and right
    Node* curr = node;
    //base case
    if (curr == nullptr){
        return;
    }
    printBalanceFactors(curr->left);
    cout<< curr->key << "(" << balanceFactor(curr) << ")"<<", ";
    printBalanceFactors(curr->right);
}

//recurrsive function to help find the height of specific node
int AVLTree::height_of(Node* node) const{
    Node* curr = node;
    // Base case
    if (curr == nullptr){
        return -1;
    }
    int leftHeight = height_of(curr->left);
    int rightHeight = height_of(curr->right);
    //pick the larger of the left height and the right height and add one to that 
    return 1 + max(leftHeight, rightHeight);
}