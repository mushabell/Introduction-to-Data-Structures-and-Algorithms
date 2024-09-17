#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void BSTree::insert(const string& key) {
  // Edge case:  The tree is empty
  Node* newNode = new Node(key);
  Node* curr = root;
  if (curr == nullptr){
    root = newNode;
    //cout<<"Amshu: The value in the tree are: ";
    //inOrder();
    return;
    
  }
  // Edge case: If we find the key in the tree, just increment its count
  if (search(key)){
    //cout<<"Amshu: repeat value!"<<endl;
    while (curr -> key != key){
      if (key < curr -> key){
        curr = curr -> left;
      }else{
        curr = curr -> right;
      }
    }
    curr -> count++;
    //cout<<"Amshu: The value in the tree are: ";
    //inOrder();
    return;
  }
  // Typical case, we find a hole where this key belongs
  while (true){
    if (key < curr -> key){
      //if we would go left and there is no child there, insert new node to left
      if (curr -> left == nullptr){
        curr -> left = newNode;
        //cout<<"Amshu: The value in the tree are: ";
        //inOrder();
        return;
      } else {
        curr = curr -> left;
      }
    } else {
      //if we would go right and there is no child there, insert new node to right
      if (curr -> right == nullptr){
        curr -> right = newNode;
        //cout<<"Amshu: The value in the tree are: ";
        //inOrder();
        return;
      } else {
        curr = curr -> right;
      }
    }
  }
  //cout<<"Amshu: The value in the tree are: ";
  //inOrder();
}

bool BSTree::search(const string& key) const {
  // Search can be done in a loop (or recursively).  A loop is best here
  Node* curr = root;
  while(curr != nullptr){
    if (curr->key == key){
      return true;
    } else if (key < curr->key){
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return false;
}

string BSTree::largest() const {
  // Edge case: Tree is empty (return "")
  if (root == nullptr){
    return "";
  }
  // Largest can be done in a loop (or recursively).  A loop is best here
  Node* curr = root;
  while (curr -> right != nullptr){
    curr = curr -> right;
  }
  return curr -> key;
}

string BSTree::smallest() const {
  // Edge case: Tree is empty
  if (root == nullptr){
    return "";
  }
  // Smallest can be done in a loop (or recursively).  A loop is best here
  Node* curr = root;
  while (curr -> left != nullptr){
    curr = curr -> left;
  }
  return curr -> key;
}

int BSTree::height(const string& key) const {
  // First find the node with this key, then run "height_of" to get
  // the height that zybooks wants
  // Edge case: Tree is empty
  if (root == nullptr){
    return -1;
  }
  Node* curr = root;
  while (curr->key != key){
    if (key < curr->key){
      if (curr->left == nullptr){
        return -1;
      }else{
        curr = curr->left;
      }
    } else {
      if (curr->right == nullptr){
        return -1;
      }else {
        curr = curr->right;
      }
    }
  }
  return height_of(curr);
}

void BSTree::remove(const string& key) {
  remove(nullptr, root, key);
}

void BSTree::preOrder() const {
  // print key, do left, do right
  // This wants a ", " after each node and exactly one newline once done
  //cout<<"Amshu: entered the loop for preOrder"<<endl;
  preOrder(root);
  cout<<endl;
}

void BSTree::postOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  postOrder(root);
  cout<<endl;
}

void BSTree::inOrder() const {
  // This wants a ", " after each node and exactly one newline once done
  inOrder(root);
  cout<<endl;
}

void BSTree::remove(Node* parent, Node* tree, const string& key) {
  if (root==nullptr){
    return;
  }
  // Hint: A good approach is to find the parent and the curr node that holds that key
  for (Node* curr = tree; curr!=nullptr; ){
    // Edge case: The key is not found (do nothing)
    //cout<<"Amshu: I am inside the for loop"<<endl;
    if (key==curr->key){
      //cout<<"Amshu: I found the smae key"<<endl;
      // Edge case.  The key count is greater than 1.  Just decrement the count
      curr->count--;
      if (curr->count == 0){
        //if the node is a leaf
        if ((curr->left == nullptr) and (curr->right == nullptr)){
          // Edge case: is it the root
          if (parent == nullptr){
            root = nullptr;
            return;
          }
          //if the curr node is left leaf
          if (curr == parent->left){
            delete(curr);
            parent->left = nullptr;
            return;
          } else {
          //if the curr node is right leaf
            //cout<<"Amshu: before delete"<<endl;
            delete(curr);
            //cout<<"Amshu: after delete"<<endl;
            parent->right = nullptr;
            //cout<<"Amshu: after assignment"<<endl;
            return;
          }
        }
        //internal node with left child
        if (curr->left != nullptr){
          Node* largest = curr->left;
          if (largest != nullptr){
            while(largest->right != nullptr){
              largest = largest->right;
            }
          }
          curr->count = largest->count;
          curr->key = largest->key;
          largest->count = 1;
          remove(curr, curr->left, curr->key);
        } else {
          //cout<<"Amshu: entered the right child loop"<<endl;
          Node* smallest = curr -> right;
          if (smallest != nullptr){
            while(smallest->left != nullptr){
              smallest = smallest->left;
            }
          }
          curr->count = smallest->count;
          curr->key = smallest->key;
          smallest->count=1;
          remove(curr, curr->right, curr->key);
        }
      }
      return;
    }else if (key < curr->key){
      parent = curr;
      curr = curr->left;
    } else if (key > curr->key){
      //cout<<"Amshu: I am moving to the right"<<endl;
      parent = curr;
      curr = curr->right;
      //cout<<"Amshu: This is the key after right - "<<curr->key<<endl;
    }
  }
  return;
  // Edge case: leaf (no children).  Just remove from parent
  //  ==> case 1: parent is nullptr (we are removing the last node from root)
  //  ==> case 2: curr is the left child, remove it from parent
  //  ==> case 3: curr is the right child, remove it from parent
  // Typical case.  Find the target
  // It is either the largest key in the left tree (if one exists)
  // or the smallest key in the right tree (since not a leaf one will exist)
  // Copy the target information into the node we found, set the target count to
  // one, and recursively remove it from left or right subtree (current node is the parent)
}

int BSTree::height_of(Node* tree) const {
  // The height (length of longest path to the bottom) of an empty tree is -1
  // Otherwise, you pick the larger of the left height and the right height
  // and add one to that
  Node* curr = tree;
  // Base case
  if (curr == nullptr){
    return -1;
  }
  int leftHeight = height_of(curr->left);
  int rightHeight = height_of(curr->right);
  return 1 + max(leftHeight, rightHeight);
}

void BSTree::preOrder(Node* tree) const {
  // print key, do left, do right
  //cout<<"Amshu: entered preOrder with tree"<<endl;
  Node* curr = tree;
  if (curr == nullptr){
    return;
  }
  cout<<curr->key << "(" << curr->count << ")" << ", ";
  preOrder(curr->left);
  preOrder(curr->right);
}

void BSTree::postOrder(Node* tree) const {
  // do left, do right, print key
  //cout<<"Amshu: I am inside postOrder"<<endl;
  Node* curr = tree;
  //cout<<"Amshu: position 1"<<endl;
  if (curr == nullptr){
    return;
  }
  postOrder(curr->left);
  postOrder(curr->right);
  cout<<curr->key << "(" << curr->count << ")" << ", ";
}

void BSTree::inOrder(Node* tree) const {
  // do left, print key, do right
  Node* curr = tree;
  if (curr == nullptr){
    return;
  }
  inOrder(curr->left);
  cout<<curr->key << "(" << curr->count << ")" << ", ";
  inOrder(curr->right);
}

// This is a pre-order traversal that shows the full state of the tree
// (but it is a code turd)
void BSTree::debug(Node* tree, int indent) const {
  if (tree == nullptr) return;
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << tree << ' ' << *tree << endl;
  debug(tree->left,indent+1);
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << "-" << endl;
  debug(tree->right,indent+1);
}
