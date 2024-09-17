#include "Node.h"

#include <iostream>

using namespace std;

//default constructor
Node::Node(): left(nullptr),right(nullptr),parent(nullptr) {}

//constructor with parameter
Node::Node(const string& s): key(s),left(nullptr),right(nullptr),parent(nullptr){}

// Tear down my left and right subtrees when deleted
Node::~Node() {
  delete left;
  delete right;
}


