#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
  IntList list;
  
  cout << "empty: " << list << endl;
  //Add 3 to front of list
  list.push_front(3);
  cout << "push front 3: " << list << endl;
  //Add 1 to back of list
  list.push_back(1);
  cout << "push back 1: " << list << endl;
  //Add 5 to back of list
  list.push_back(5);
  cout << "push back 5: " << list << endl;
  //Add 2 to front of list
  list.push_front(2);
  cout << "push front 2: " << list << endl;
  //remove the last element of the list
  list.pop_back();
  cout << "pop back: " << list << endl;
  //remove the first element of the list
  list.pop_front();
  cout << "pop front: " << list << endl;
  //print the list in reverse order 
  list.printReverse();
  cout << "reverse print" << endl;
  //checks if th list is empty
  list.empty();
  cout << "check if empty: " << list << endl;
       
  return 0;
}
