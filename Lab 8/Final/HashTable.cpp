#include "HashTable.h"
#include "WordEntry.h"
#include <list>

// HashTable constructor: initialize array of lists of WordEntry and size of array
HashTable::HashTable (int s) {
  hashTable = new list<WordEntry>[s];
  size = s;
}


// return an integer based on the input string used for index into the array in hash table
// professor promoted the use of ChatGPT to create the computeHash function
// ChatGPT prompt: c++ code for hasher for a hash table with a given size
int HashTable::computeHash(const string &s) const {
  unsigned long hash = 100;
    for (char c : s) {
      hash = ((hash << 5) + hash) + c; 
    }
    //uses modulo of the array size to ensure that the number is within the array bounds
    return hash % size; 
}

//adds a new entry into the hash table
void HashTable::put(const string &s, int score) {
  //find the slot number for the string
  int hashNum = computeHash(s);
  //check if the word is already in the hash table
  for (auto& i : hashTable[hashNum]) {
    if (i.getWord() == s){
      //if the word is found, update the entry information
      i.addNewAppearance(score);
      return;
    }
  }
  //if the word is not found, add a new entry to the list in the respective slot
  hashTable[hashNum].push_back(WordEntry(s, score));
}

//the result of a call to getAverage() from the WordEntry
double HashTable::getAverage(const string &s) const {
  //find the slot number for the string 
  int hashNum = computeHash(s);
  for (auto i : hashTable[hashNum]) {
    if (i.getWord() == s){
      //getAverage() returns the average score of the word
      return(i.getAverage()); 
    }
  }
  // If the word is not found, return the value 2.0
  return 2.0;
}

//returns true if word is in the hash table or false if word is not in the hash table
bool HashTable::contains(const string &s) const {
  //find the slot number for the string 
  int hashNum = computeHash(s);
  //iterates through the list in the hash table slot 
  for (auto i : hashTable[hashNum]) {
    if (i.getWord() == s){
      return true; 
    }
  }
  return false;
}

//For zybooks, we must include a main funtion that returns 0
//however for VS Code, the main has its own cpp file
/* int main() {
    return 0;
  }*/