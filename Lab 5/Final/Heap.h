#pragma once

#include "PrintJob.h"
#include <ostream>
#include <iostream>

const int MAX_HEAP_SIZE = 10;

class Heap {
private:
  PrintJob* arr[MAX_HEAP_SIZE];      // array of PrintJob pointers for the heap.
  int numItems;  //current number of items in heap.

public:
  //Initializes an empty heap.
  Heap();

  //Inserts a PrintJob to the heap without violating max-heap properties.
  void enqueue ( PrintJob* newVlaue);

  //Removes the node with highest priority from the heap. 
  void dequeue ( );

  //Returns the node with highest priority.
  PrintJob* highest ( );

  //Prints the PrintJob with highest priority.
  void print ( );

private:
  //called by dequeue function to move the new root down the heap to the appropriate location.
  void trickleDown(int parentIndexValue);
};