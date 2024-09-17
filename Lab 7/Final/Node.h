#pragma once

#include <string>
#include <iostream>

using namespace std;

//Node struct
struct Node {
  string key;
  Node *left;
  Node *right;
  Node* parent;

  //contructors 
  Node();
  Node(const string& s);

  //deconstructor, copy-constructor, and assignment operator
  ~Node();
  Node(const Node& other) = delete;
  Node& operator=(const Node &rhs) = delete;
};

