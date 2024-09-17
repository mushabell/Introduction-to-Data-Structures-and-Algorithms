#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;

struct Node {
    string payload;
    Node* next;
  // PROFPAT: Note that there is no constructor here. We will
  // PROFPAT: directly manipulate payload and next, but be
  // PROFPAT: careful.  Whilst payload will be an empty string
  // PROFPAT: the value inside next is undefined.
};




// PROFPAT: This acts like a call to 'new' with a constructor.  So be
// PROFPAT: sure to call the allocator AND set up the payload/next data
// PROFPAT: And the original passed in the string by value.  const& is
// PROFPAT: better here for passing in the payload
Node* newNode(const string& payload) {
  //cout<<"Amshu: craeted new node"<< endl;
  struct Node* newNode = new Node();
  newNode -> payload = payload;
  newNode -> next = nullptr;
  return newNode;
}

// PROFPAT: The original passed in the vector by value.  Not the best
// PROFPAT: choice!
Node* loadGame(int n, const vector<string>& names) {
  Node* head = nullptr;
  Node* prev = nullptr;
  string name;

  for (int i = 0; i < n; ++i) {
    name = names.at(i);
	  // Special edge case when the list is initially empty
    if (head == nullptr) {
      head = newNode(name);
      prev = head;
      /** fill in this code **/
    } else {
      prev->next = newNode(name);
      prev = prev -> next;
      /** fill in this code **/
    }
  }

  if (prev != nullptr) {
    prev -> next = head;
    /** fill in this code **/ // make circular
    // PROFPAT: Think about what it takes to make the list
    // PROFPAT: circular.  Why did we check if 'prev' is
    // PROFPAT: nullptr?
  }
  
  return head;
}

// PROFPAT: The orginal zybook code passed this as a Node*
// PROFPAT: instead of const Node*.  Why is const Node*
// PROFPAT: better?
// prints list from a starting node
void print(const Node* start) {
  const Node* curr = start;
  // PROFPAT: Ask yourself, why we check for nullptr here and provide
  // PROFPAT: a good comment on why we have to check it since we're
  // PROFPAT: really using the `currr == start` check below to break
  // PROFPAT: out of the loop
  cout<<"Amshu: this is new print" << endl;
  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      cout<<"Amshu: endered the break" << endl;
      break; // exit circular list
    }
  }
}

// josephus w circular list, k = num skips
Node* runGame(Node* start, int k) {
  Node* curr = start;
  Node* prev = curr;
  cout<< "Amshu: area 1" << endl;
  sleep(1);
  while (curr == prev) { // exit condition, last person standing
    for (int i = 0; i < k; ++i) { // find kth node
      prev = curr;
      curr = curr -> next;
      cout<< "Amshu: area 2" << endl;
      sleep(1);
    }
    cout<< "Amshu: area 3" << endl;
    sleep(1);
    prev -> next = curr -> next;
    cout<< "Amshu: area 4" << endl;
    sleep(1);
    /** fill in this code **/ // delete kth node
    //print(curr);
    cout<< "Amshu: area 5" << endl;
    sleep(1);
    delete curr;
    cout<< "Amshu: area 6" << endl;
    sleep(1);
    curr = prev -> next;
    /** fill in this code **/
  }
  cout<< "Amshu: area 7" << endl;
  sleep(1);
  return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
  int n=1, k=1; // n = num names; k = num skips (minus 1)
  string name;
  vector<string> names;

  // get inputs
  cin >> n >> k;
  // PROFPAT: We just need to check before we USE n or k.  The original code
  // PROFPAT: in zybooks didn't bother to check -- naughty, naughty!
  if (!cin) throw runtime_error("error reading n and k from input");
  
  while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

  // initialize and run game
  Node* startPerson = loadGame(n, names);
  print(startPerson);
  Node* lastPerson = runGame(startPerson, k);

  if (lastPerson != nullptr) {
      cout << lastPerson->payload << " wins!" << endl;
  } else {
      cout << "error: null game" << endl;
  }

  return 0;
}

