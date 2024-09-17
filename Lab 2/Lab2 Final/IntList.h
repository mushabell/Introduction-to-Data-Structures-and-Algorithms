#pragma once

#include <iostream>

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    //constructor for IntNode
    IntNode(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class IntList {
private:
  IntNode dummyHead;
  IntNode dummyTail;
public:
  IntList()
    : dummyHead(-1),
      dummyTail(-1)
  {
    // The dummy head points to dummy tail
    dummyHead.prev = nullptr;
    dummyHead.next = &dummyTail;

    // The dummy tail points back at head
    dummyTail.prev = &dummyHead;
    dummyTail.next = nullptr;
  }

  //deconstructor
  ~IntList();

  //copy constructor
  IntList(const IntList&) = delete;

  //copy assignmnet operator
  IntList& operator=(const IntList&) = delete;

  //IntList class member function declarations
  void push_front(int value);
  void pop_front();
  void push_back(int value);
  void pop_back();
  bool empty() const;
  friend std::ostream & operator<<(std::ostream &out, const IntList &rhs);
  void printReverse() const;
};
