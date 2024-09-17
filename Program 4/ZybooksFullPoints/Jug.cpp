#include "Jug.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::stoi;
using namespace std;

//return the steps and the cost of the path to reach a solution
//returns 1, 0, or -1 based on input
int Jug::solve(string &solution){
    //if there are invalid inputs we must return -1
    if (!validInputs){
        solution = "";
        return -1;
    }
    //use a stack to save the operations needed to reach the goal
    stack<string> operations;
    //start at the finished position
    int wantedPosition = state_number(0, n, Ca, Cb);
    //Check if there is a path to the solution, if not return 0
    if (states[wantedPosition].distance == infinity){
        solution = "";
        return 0;
    }
    operations.push(states[wantedPosition].connection);
    int previousPosition = states[wantedPosition].previous;
    //loop through the path until (0,0) is reached which is when the preious is infinty
    while(previousPosition != infinity){
        // operations.push(states[previousPosition].connection);
        // previousPosition = states[previousPosition].previous;
        //add each operation to the stack
        if (states[previousPosition].connection != "no connection"){
            operations.push(states[previousPosition].connection);
        }
        previousPosition = states[previousPosition].previous;
    }
    //loop through the stack until all the operations are added to the string solution
    while(!operations.empty()){
        string temp = operations.top();
        operations.pop();
        solution = solution + temp + "\n";
    }
    //add the cost of the path to the string
    solution = solution + "success " + std::to_string(states[wantedPosition].distance);
    return 1;
}

//returns the position of the jugs in the array
int Jug::state_number(int a, int b, int Ca, int Cb) {
  //incase it goes out of bounds
  if (a > Ca or b > Cb) {
    throw std::runtime_error("domain error");
  }
  return a*(Cb+1)+b;
}

//creates the map in the array and calls on find_path() after checking for valid inputs
void Jug::make_map(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA){
    // //check that all the inputs are valid
    if ((Ca >= Cb) or (N > Cb) or (Cb >= 1000) or (Ca <= 0) or (Cb <= 0) or (N <= 0) 
    or (cfA <= 0) or (cfB <= 0) or (ceA <= 0) or (ceB <= 0) or (cpAB <= 0) or (cpBA<= 0)){
        validInputs = false;
        return;
    }
    //loops through each case senario that the Jugs could be in
    for(int a=0;a<=Ca;++a) {
        for(int b=0;b<=Cb;++b) {
            //compute action fill A. A will have Ca gallons and B is unchanged
            //compute action fill B. A is unchanged and B will have Cb gallons
            int fillA = state_number(Ca,b, Ca,Cb);
            int fillB = state_number(a,Cb, Ca,Cb);

            //for each empties, just set the appropriate amount to zero
            int emptyA = state_number(0,b, Ca,Cb);
            int emptyB = state_number(a,0, Ca,Cb);

            //for the transfers, we can only pour in as much as we have
            //in the "from" jug OR as much room as we have in the "to" jug
            //making sure to leave waer not poured into the second jug in the first jug
            int transferFromA = std::min(a, Cb-b);
            int AtoB = state_number(a-transferFromA,b+transferFromA, Ca,Cb);
            int transferFromB = std::min(b, Ca-a);
            int BtoA = state_number(a+transferFromB,b-transferFromB, Ca,Cb);

            //we can use emplace_back here to construct the state at the location of the vector
            states.emplace_back(a,b, fillA,fillB, emptyA,emptyB, AtoB,BtoA);
        }
    }
    //call find path to map connect the map together
    find_path(cfA, cfB, ceA, ceB, cpAB, cpBA);
}

//maps out all the paths from two empty jugs to all the possible senarios
//including mapping the jugs back to themselves
void Jug::find_path(int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA){
    //continue to loop through the array until all the nodes are met
    while(true) {
        //our start node is 0 because that is the location where both jugs are empty
        //We set its distance to zero and its previous to infinity to mean no node
        states[0].distance = 0;
        states[0].previous = infinity;
        for(unsigned i=0;i<states.size();++i) {
            //we look for the node with the shortest distance that we have not yet visited
            int distance = infinity;
            int current = infinity;
            //if a node that is not visited is found and the diatance is shorter we look at the node
            for(unsigned i=0;i<states.size();++i) {
                if (states[i].distance < distance and not states[i].visited) {
                    distance = states[i].distance;
                    current = i;
                }
            }
            if (distance == infinity) {
                //Appropriate here to quit because all nodes would be visted if true
                return;
            }
            //mark the state has been visited
            states[current].visited = true;

            //must look at each of the six actions and see if it takes a shorter distance than saved.
            //this includes paths that have lead back to it
            int fillA = states[current].fillA;
            int fillB = states[current].fillB;
            int emptyA = states[current].emptyA;
            int emptyB = states[current].emptyB;
            int AtoB = states[current].AtoB;
            int BtoA = states[current].BtoA;

            //the distance there is the current distance plus the cost of doing each operation respectivly
            int fillA_distance = distance + cfA;
            int fillB_distance = distance + cfB;
            int emptyA_distance = distance + ceA;
            int emptyB_distance = distance + ceB;
            int AtoB_distance = distance + cpAB;
            int BtoA_distance = distance + cpBA;

            //compare the distance we have saved with the distance that we get with this visit.
            //If it is shorter, we update the distance, the previous, and the connection 
            if (fillA_distance < states[fillA].distance) { //update filling A
                states[fillA].distance = fillA_distance;
                states[fillA].previous = current;
                states[fillA].connection = "fill A";
            }
            if (fillB_distance < states[fillB].distance) { //update filling B
                states[fillB].distance = fillB_distance;
                states[fillB].previous = current;
                states[fillB].connection = "fill B";
            }
            if (emptyA_distance < states[emptyA].distance) { //update emptying A 
                states[emptyA].distance = emptyA_distance;
                states[emptyA].previous = current;
                states[emptyA].connection = "empty A";
            }
            if (emptyB_distance < states[emptyB].distance) { //update emptying B
                states[emptyB].distance = emptyB_distance;
                states[emptyB].previous = current;
                states[emptyB].connection = "empty B";
            }
            if (AtoB_distance < states[AtoB].distance) { //update pouring from A to B
                states[AtoB].distance = AtoB_distance;
                states[AtoB].previous = current;
                states[AtoB].connection = "pour A B";
            }
            if (BtoA_distance < states[BtoA].distance) { //update pouring from B to A
                states[BtoA].distance = BtoA_distance;
                states[BtoA].previous = current;
                states[BtoA].connection = "pour B A";
            }
        }
    }

}
