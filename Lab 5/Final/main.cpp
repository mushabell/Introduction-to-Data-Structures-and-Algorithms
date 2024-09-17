#include <iostream>
#include "Heap.h"

using namespace std;

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Enqueue" << endl
    << "2. Print" << endl
    << "3. Dequeue" << endl
    << "4. Quit" << endl;
  cin >> choice;

  // fix buffer just in case non-numeric choice entered and also gets rid of newline character
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main(){
  Heap max_heap;

  int choice = menu();

  while (choice != 4) {
    if (choice == 1) {
      int priority, jobNumber, numPages;
      //Cheking if valid inputs are provided
      cout << "Enter print job to enqueue (priority, job Number, number of pages): ";
      if (not (cin >> priority)) {
        throw runtime_error("error: could not read priority value");
      }
      if (not (cin >> jobNumber)) {
        throw runtime_error("error: could not read priority value");
      }
      if (not (cin >> numPages)) {
        throw runtime_error("error: could not read priority value");
      }
      cout << endl;

      max_heap.enqueue(new PrintJob(priority, jobNumber, numPages));
    } else if (choice == 2) {
      max_heap.print();
    } else if (choice == 3) {
      max_heap.dequeue();
    }
    //fix buffer just in case non-numeric choice entered
    choice = menu();
  }
  return 0;
}