#pragma once

#include <string>

using namespace std;

class Node {

  friend class Tree;

private:
  string small;
  string large;
  int keycount;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

public:
  Node();
  Node(const string& value);
  Node(const string& value, Node* leftChild, Node* rightChild);
  //~Node();
};
