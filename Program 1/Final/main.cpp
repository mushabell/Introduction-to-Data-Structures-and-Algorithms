#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//struct for the Node of the circular linked list
struct Node {
    string payload;
    Node* next;
};

//Creates a new node with payload and pointer set to null
Node* newNode(const string& payload) {
    struct Node* newNode = new Node();
    newNode -> payload = payload;
    newNode -> next = nullptr;
    return newNode;
}

//Create the circular linked list for the game using names in a vector
Node* loadGame(int n, const vector<string>& names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;
    // integer n is the number of names in the circular list
    for (int i = 0; i < n; ++i) {
        name = names.at(i);
	    // Special edge case when the list is initially empty
        if (head == nullptr) {
        head = newNode(name);
        prev = head;
        } else {
        prev->next = newNode(name);
        prev = prev -> next;
        }
    }

    if (prev != nullptr) {
        prev -> next = head;
    }

    return head;
}

//prints list from a starting node
void print(const Node* start) {
    const Node* curr = start;
    /*checks for nullptr to ensure the list is not empty and 
    will not keep printing the same node in an infinite loop*/
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) {
        break; // exit circular list
        }
    }
}

// josephus probelm with circular list, k = number of skips
Node* runGame(Node* start, int k) {
    Node* curr = start;
    Node* prev = curr;
  
    while (curr -> next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
        prev = curr;
        curr = curr -> next;
        }
        prev -> next = curr -> next;
        delete curr;
        curr = prev -> next;
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    //checking inputs
    if (!cin) throw runtime_error("error reading n and k from input");
  
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    //prints the winner or error message
    if (lastPerson != nullptr) {
          cout << lastPerson->payload << " wins!" << endl;
    } else {
          cout << "error: null game" << endl;
    }
    delete lastPerson;
    return 0;
}