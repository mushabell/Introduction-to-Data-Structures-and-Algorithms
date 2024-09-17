#include "Heap.h"
#include <algorithm>
#include <stdexcept>
#include <ostream>
#include <iostream>
using std::runtime_error;
using std::overflow_error;
using std::underflow_error;

//Initializes an empty heap.
Heap::Heap():numItems(0){}

//Inserts a PrintJob to the heap
void Heap::enqueue ( PrintJob* newValue){
  //if the array is full, return nothing 
  if (numItems==MAX_HEAP_SIZE){
    throw overflow_error("error: the array is full, can not aff any more elements");
  }
  //add the new value to the end of array
  arr[numItems++] = newValue;
  int childIndex = numItems-1;
  int parentIndex = (childIndex - 1) / 2;
  //change the positions in the array to maintain heap properties
  while (arr[childIndex] -> getPriority() > arr[parentIndex] -> getPriority()) {
    if (arr[childIndex] -> getPriority() <= arr[parentIndex] -> getPriority()){
      return;
    }else {
      std::swap(arr[parentIndex], arr[childIndex]);
      childIndex = parentIndex;
      parentIndex = (childIndex - 1) / 2;
    }
  }
}

//Removes the node with highest priority from the heap. 
void Heap::dequeue ( ){
  //if empty return nothing
  if (numItems == 0){
    throw underflow_error("error: no vlaues in the array to dequeue");
  }
  //if not empty swap first and last elements in array
  std::swap(arr[0], arr[numItems-1]);
  --numItems;
  //call trickleDown to change array positions to follow heap properties
  trickleDown(0);
}

//Returns the node with highest priority.
PrintJob* Heap::highest(){
  //if empty return a nullptr
  if (numItems == 0){
    return nullptr;
  }
  return(arr[0]);
}

//Prints the PrintJob with highest priority 
void Heap::print(){
  //if empty return nothing
  if(numItems == 0){
    throw underflow_error("error: no vlaues in the array to print");
  }
  std::cout<<"Priority: "<<arr[0]->getPriority()<<", Job Number: "<<arr[0]->getJobNumber()<<", Number of Pages: " <<arr[0]->getPages()<<endl;
}

void Heap::trickleDown(int parentIndexValue){
  //find parent and child indexes
  int parentIndex = parentIndexValue;
  int childIndex = 2 * parentIndex + 1;

  while (childIndex < numItems) {
    // Find the max among the node and all the node's children
    int maxValue = arr[parentIndex] -> getPriority();
    int maxIndex = -1;
    for (int i = 0; i < 2 && i + childIndex < numItems; i++) {
      if (arr[i + childIndex] -> getPriority() > maxValue) {
        maxValue = arr[i + childIndex] -> getPriority();
        maxIndex = i + childIndex;
      }
    }
    //break the loop if the values follow the heap property
    if (maxValue == arr[parentIndex] -> getPriority()) {
      break;
    } else {
      //swap and reassign values if the heap properties are not followed
      std::swap(arr[parentIndex], arr[maxIndex]);
      parentIndex = maxIndex;
      childIndex = 2 * parentIndex + 1;
    }
  }
}