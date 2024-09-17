#pragma once

#include <stdexcept>

using std::overflow_error;
using std::runtime_error;
using std::underflow_error;
using std::out_of_range;


//template allows for multiple datatypes for the same class
template<typename T>
class stack {
    static constexpr unsigned MAX_SIZE = 20;
    int size = 0;
    T stack[MAX_SIZE];

public:
    // inserts a new element of type T into the 
    // data and throws an overflow_error if stack is full
    void push(const T& value) {
        if (size == this -> MAX_SIZE){
            throw overflow_error("Called push on full stack.");
        } else {
            stack[this -> size] = value;
            this->size++;
        }
    }

    // returns true if the stack is empty otherwise it returns false.
    bool empty() const { 
        if (this -> size == 0){
            return true;
        }
        return false; 
    }

    // removes the last element from data. If the data array is 
    // empty, this function throws an out_of_range exception
    void pop() {
        if(this -> empty()){
            throw out_of_range("Called pop on empty stack.");
        } else {
            this -> size--;
        }
    }

    // removes the last two elements from data. If the data array is empty or is
    // of size 1, the function throws an out_of_range exception.
    void pop_two() {
        if(this -> empty()){
            throw out_of_range("Called pop_two on empty stack.");
        } else if (this -> size == 1) {
            throw out_of_range("Called pop_two on a stack of size 1.");
        } else {
            this -> size = this -> size - 2;
        }
    }

    //returns the top element of stack. If stack is empty, this function throws an 
    //underflow_error exception. function without const for zybooks.
    T& top() { 
        if (this -> empty()){
            throw underflow_error("Called top on empty stack.");
        } else {
            return stack[this -> size -1];
        }
    }
    //function with const for good coding practice.
    const T& top() const {
        if (empty()){
            throw underflow_error("Called top on empty stack.");
        } else {
            return stack[this -> size -1];
        }
    }
};
