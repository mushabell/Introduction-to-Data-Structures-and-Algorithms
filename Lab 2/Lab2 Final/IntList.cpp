#include "IntList.h"

#include <iostream>
#include <exception>

using namespace std;

// A global friend function that outputs to the stream all of the data in the nodes in order
ostream & operator<<(ostream &out, const IntList &rhs){
  for (IntNode *curr = rhs.dummyHead.next; curr != &rhs.dummyTail; curr = curr -> next){
    out << curr->data;
    if (curr -> next != &rhs.dummyTail){
      out << " ";
    }
  }
  return out;
}

//clear any allocated memory from the nodes ~deconsturctor 
IntList::~IntList() {
  if(&dummyHead != &dummyTail){
      IntNode *temp = dummyHead.next;
      while(temp != &dummyTail){
	      IntNode *nodeToDelete = temp;
	      temp = temp->next;
	      delete nodeToDelete;
	    }
    }
}

//Inserts a data value (within a new node) at the front end of the list
void IntList::push_front(int value) {
  struct IntNode *newNode = new struct IntNode(value);
  //checks if list is empty (with dummy nodes)
  if (dummyHead.next == &dummyTail){
    dummyHead.next = newNode;
    newNode -> prev = &dummyHead;
    newNode -> next = &dummyTail;
    dummyTail.prev = newNode;
    return;
  }
  struct IntNode *currFirstNode = dummyHead.next;
  currFirstNode -> prev = newNode;
  newNode -> next = currFirstNode;
  dummyHead.next = newNode;
  newNode -> prev = &dummyHead;
}

//Removes the node at the front end of the list (the node after the dummy head).
void IntList::pop_front() {
  //checks if list is empty (with dummy nodes)
  if (dummyHead.next == &dummyTail){
    return;
  }
  struct IntNode *deleteNode = dummyHead.next;
  struct IntNode *afterDeleteNode = deleteNode -> next;
  dummyHead.next = deleteNode -> next;
  afterDeleteNode -> prev = &dummyHead;
  delete deleteNode;
}

//Inserts a data value (within a new node) at the back end of the list.
void IntList::push_back(int value) {
  struct IntNode *newNode = new struct IntNode(value);
  //checks if list is empty (with dummy nodes)
  if (dummyHead.next == &dummyTail){
    dummyHead.next = newNode;
    newNode -> prev = &dummyHead;
    newNode -> next = &dummyTail;
    dummyTail.prev = newNode;
    return;
  }
  struct IntNode *currLastNode = dummyTail.prev;
  dummyTail.prev = newNode;
  newNode -> next = &dummyTail;
  newNode -> prev = currLastNode;
  currLastNode -> next = newNode;
}

//Removes the node at the back end of the list (the node before the dummy tail).
void IntList::pop_back() {
  //checks if list is empty (with dummy nodes)
  if (dummyHead.next == &dummyTail){
    return;
  }
  struct IntNode *deleteNode = dummyTail.prev;
  struct IntNode *prevDeleteNode = deleteNode -> prev;
  dummyTail.prev = deleteNode -> prev;
  prevDeleteNode -> next = &dummyTail;
  delete deleteNode;
}

//Returns true if the list does not store any data values (it 
//only has dummy head and dummy tail), otherwise returns false.
bool IntList::empty() const {
  if (dummyHead.next == &dummyTail){
    return true;
  } else {
    return false;
  }
}

//Prints the data in the list in reverse order 
void IntList::printReverse() const {
  for (IntNode *curr = dummyTail.prev; curr != &dummyHead; curr = curr -> prev){
    cout << curr->data;
    if (curr -> prev != &dummyHead){
      cout << " ";
    }
  }
}

