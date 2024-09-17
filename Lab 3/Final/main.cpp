#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

//function given by zybooks to generate a random vector of chracters with a random size
vector<char> createVector() {
  int vecSize = rand() % 26;
  char c = 'a';
  vector<char> vals;
  for(int i = 0; i < vecSize; i++) {
    vals.push_back(c);
    c++;
  }
  return vals;
}

//returns the index of the min value starting from "index" to the end of the "vector"
template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
  int minValueIndex = index;
  //loop through the whole vector
  for (int i = index; i < int(vals.size()); i ++){
    //checking for smaller value
    if (vals.at(i) < vals.at(minValueIndex)){
      minValueIndex = i;
    } 
  }
  return minValueIndex;
}

//passes in a vector of type T and sorts them based on the selection sort method
template<typename T>
void selection_sort(vector<T> &vals) {
  //loop through vector and keep swaping to place smallest to largest number in order
  for (int i = 0; i < int(vals.size()); ++i){
    int smallest_at = min_index(vals, i);
    swap(vals[i], vals[smallest_at]);
  }
}

//returns the element located at the index of the vals or out of range error
template<typename T>
T getElement(const vector<T>& vals, int index) {
  // Question:  Should you use .at() or [] here?
  // We should use [] and not .at() because we want to be able to catch a 
  // out of range error which .at() does not allow. 
  return vals[index];
}

//first half tests the try and catch method
//second half tests the min_index function and the selection_sort function
int main() {
  // Seeding the random number generator so we get a different
  // run every time.
  srand(time(0));

  // Fill in a vector of some random size with some random characters
  vector<char> vals = createVector();
  int numOfRuns = 10;
  while(--numOfRuns >= 0){
    cout << "Enter a number: " << endl;
    //checking for valid input
    int index;
    if (not (cin >> index)) {
      throw runtime_error("could not read the index");
    }
    //try and catch for out of range error
    try {
      if (index >= int(vals.size()) || index < 0){
          throw out_of_range("out of range exception occured");
      }
      char curChar = getElement(vals,index);
      cout << "Element located at " << index << ": is " << curChar << endl;
    }
    catch (const std::out_of_range& excpt) {
      cout << excpt.what() << endl;
    }
  }
  //----------------------------------Testing selection sort here------------------------------------
  //---testing with string---
  /*//read the testing file
  ifstream fin("testWords.txt");
  // Create an empty vector
  vector<string> v;
  // Read the contents of the file and store them in the vector
  string newString;
  while (fin >> newString) {
      v.push_back(newString);
  }
  // Close the file
  fin.close();
  cout<< "The values in the vector is: ";
  //print all values
  for (int i = 0; i < int(v.size()); i ++){
  cout << v.at(i) << " ";
  }
  cout << endl;
  //check is min_index funciton is working
  cout << "The smallest value index is: " << min_index(v, 0) << endl;
  selection_sort(v);
  //print all values after selction_sort
  cout << "The full vector is: ";
  for (int i = 0; i < int(v.size()); i ++){
  cout << v.at(i) << " ";
  }
  cout << endl;*/

  //---testing with int---
  //read the testing file
  ifstream fin("testNumbers.txt");
  // Create an empty vector
  vector<int> v;
  // Read the contents of the file and store them in the vector
  int newInt;
  while (fin >> newInt) {
      v.push_back(newInt);
  }
  // Close the file
  fin.close();
  cout<< "The values in the vector is: ";
  //print all values
  for (int i = 0; i < int(v.size()); i ++){
  cout << v.at(i) << " ";
  }
  cout << endl;
  //check is min_index funciton is working
  cout << "The smallest value index is: " << min_index(v, 0) << endl;
  selection_sort(v);
  //print all values after selction_sort
  cout << "The full vector is: ";
  for (int i = 0; i < int(v.size()); i ++){
  cout << v.at(i) << " ";
  }
  cout << endl;

  //---testing with double---
  //read the testing file
  /*ifstream fin("testDoubleNumbers.txt");
  // Create an empty vector
  vector<double> v;
  // Read the contents of the file and store them in the vector
  double newDouble;
  while (fin >> newDouble) {
      v.push_back(newDouble);
  }
  // Close the file
  fin.close();
  cout<< "The values in the vector is: ";
  //print all values
  for (int i = 0; i < int(v.size()); i ++){
  cout << v.at(i) << " ";
  }
  cout << endl;
  //check is min_index funciton is working
  cout << "The smallest value index is: " << min_index(v, 0) << endl;
  selection_sort(v);
  //print all values after selction_sort
  cout << "The full vector is: ";
  for (int i = 0; i < int(v.size()); i ++){
  cout << v.at(i) << " ";
  }
  cout << endl;*/
  return 0;
}
