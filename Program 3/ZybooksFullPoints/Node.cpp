#include "Node.h"

Node::Node(): keycount(0), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {};
Node::Node(const string& value): small(value), keycount(1), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {} 
Node::Node(const string& value, Node* leftChild, Node* rightChild): small(value), keycount(1), left(leftChild), middle(rightChild), right(nullptr), parent(nullptr) {}
