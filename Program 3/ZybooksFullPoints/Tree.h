#pragma once

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree(): root(nullptr){};
  // ~Tree(){
  //   recursivly deltes the children nodes
  //   delete root;
  // };
  void insert(const string &value);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &value);
  bool search (const string &value) const;

private:
  // Add additional functions/variables here
  void preOrder(Node* tree) const;
  void inOrder(Node* tree) const;
  void postOrder(Node* tree) const;
  void merge(Node* node);
  void rotateRight(Node* node);
  void rotateLeft(Node* node);
  void fusion(Node* node);
  void split(const string& value, Node* tree, Node* node, Node* parent);
};
